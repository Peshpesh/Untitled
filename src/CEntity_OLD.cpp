#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity()
{
	Tex_Entity = NULL;
	X = Y = 0.0f;
	Xo = Yo = 0;
	Width = Height = Col_Width = Col_Height = 0;
	MoveLeft = MoveRight = false;

	Type = ENTITY_TYPE_GENERIC;

	Health = Damage = 0;
	Dead = false;
	Engaged = false;
	Wet = false;
	Icy = false;

	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;

	SpeedX = SpeedY = AccelX = AccelY = 0.0f;
	MaxSpeedX = 10.0f;
	MaxSpeedY = 10.0f;
	MaxAccelX = 0.5f;
	MaxAccelY = 0.75f;

	Jumper = false;
	Grounded = false;

	CurrentFrameCol = 0;
	CurrentFrameRow = 0;

	Col_X = 0;
	Col_Y = 0;
}

CEntity::~CEntity()
{
	//
}

bool CEntity::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	Tex_Entity = entityset;
	if (Tex_Entity == NULL) return false;

	this->Xo = Xo;
	this->Yo = Yo;
	this->Width = Width;
	this->Height = Height;
	Anim_Control.MaxFrames = MaxFrames;
	return true;
}

void CEntity::OnLoop()
{
	ChkEnviro();
	if (MoveLeft == false && MoveRight == false) StopMove();
	else if (MoveLeft) AccelX = -MaxAccelX;
	else if (MoveRight) AccelX = MaxAccelX;

	if (Flags & ENTITY_FLAG_GRAVITY) AccelY = MaxAccelY;

	if (Icy) AccelX = AccelX / 3.0f;

	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	if (Wet)
	{
		SpeedX = SpeedX / 1.66f;
		SpeedY = SpeedY / 1.66f;
	}

	// Make sure we're not overstepping our boundaries,
	// so to speak...
	if (SpeedX > MaxSpeedX) SpeedX = MaxSpeedX;
	if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
	if (SpeedY > MaxSpeedY) SpeedY = MaxSpeedY;
	if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	OnAnimate();
	OnMove(SpeedX, SpeedY);
}

void CEntity::OnAnimate()
{
	if (MoveLeft)
	{
		CurrentFrameRow = 0;
	}
	else if (MoveRight)
	{
		CurrentFrameRow = 1;
	}
	Anim_Control.OnAnimate();
}

bool CEntity::OnMove(float MoveX, float MoveY)
{
	Jumper = false;
	if (MoveX == 0 && MoveY == 0) return false;
	bool CanMove = true;

	// resolutions of pathfinders (in pixels)
	double NewX = 0;
	double NewY = 0;
	double Slope = 0;

	// Normalize movement by speed of the program loop
	// Ex: GSF = 1 for FPS = targetFPS. GSF < 1.0 when
	// the program runs at FPS > targetFPS.
	MoveX *= CFPS::FPSControl.GetSpeedFactor();
	MoveY *= CFPS::FPSControl.GetSpeedFactor();

	if (MoveX != 0)
	{
		if (MoveX >= 0) NewX = CFPS::FPSControl.GetSpeedFactor();
		else NewX = -CFPS::FPSControl.GetSpeedFactor();
	}
	if (MoveY != 0)
	{
		if (MoveY >= 0) NewY = CFPS::FPSControl.GetSpeedFactor();
		else NewY = -CFPS::FPSControl.GetSpeedFactor();
	}
	if (MoveX != 0 && MoveY != 0)
	{
		Slope = MoveY / MoveX;
		if (Slope < 0) Slope = -Slope;
		if (Slope > 1.0)
		{
			NewX /= Slope;
		}
		else
		{
			NewY *= Slope;
		}
	}

	while (true)
	{
		// if (Flags & ENTITY_FLAG_GHOST)
		// {
		// 	// We don't care about collisions, but we need to send events to other entities
		// 	PosValid((int)(X + NewX), (int)(Y + NewY), true);
		// 	X += NewX;
		// 	Y += NewY;
		// }

		Translate(NewX, NewY);

		MoveX -= NewX;
		MoveY -= NewY;
		if (NewX > 0 && MoveX <= 0) NewX = 0;
		if (NewX < 0 && MoveX >= 0) NewX = 0;
		if (NewY > 0 && MoveY <= 0) NewY = 0;
		if (NewY < 0 && MoveY >= 0) NewY = 0;
		if (MoveX == 0) NewX = 0;
		if (MoveY == 0) NewY = 0;
		if (MoveX == 0 && MoveY == 0) break;
		if (NewX == 0 && NewY == 0) break;
	}
	return CanMove;
}

void CEntity::Translate(double NewX, double NewY)
{
	// NOTE: NewX, NewY params should be <= 1.0.
	int destXl = X + NewX + Col_X;
	int destYt = Y + NewY + Col_Y;
	int destXr = destXl + Col_Width - 1;
	int destYb = destYt + Col_Height - 1;
	int srcXl = X + Col_X;
	int srcYt = Y + Col_Y;
	int srcXr = srcXl + Col_Width - 1;
	int srcYb = srcYt + Col_Height - 1;
	int pushY = 0;

	Grounded = false;

	// First, let's see what lies ahead in terms of the map.
	// These two conditional blocks handle sloping grounds.
	// If necessary, a deflection (push) amount is assigned to pushY.
	// This value is such that adding it to the intended Y position
	// will yield a valid Y position on the map (use this for entities,
	// tiles that might block movement, etc.). The pushY term is basically
	// a "correction" term in Y, which must be satisfied if this entity is to move
	// horizontally.
	if (NewX > 0.0)	// Moving right
	{
		// int Yrel = destYb - ((srcYb / TILE_SIZE) * TILE_SIZE);
		int Yrel = srcYb - ((srcYb / TILE_SIZE) * TILE_SIZE);
		CTile* Tile = CArea::AreaControl.GetTile(destXr, srcYb);
		// if (Tile->CollID == SOLID_U_BL_MR || (Tile->CollID == SOLID_U_ML_TR && Yrel <= TILE_SIZE / 2))
		if (Tile->CollID == SOLID_U_BL_MR || (Tile->CollID == SOLID_U_ML_TR && Yrel < TILE_SIZE / 2))
		{
			pushY = CollGround(Tile->CollID, destXr % TILE_SIZE, Yrel);
		}
		if (pushY == 0)
		{
			Tile = CArea::AreaControl.GetTile(destXr, srcYt);
			Yrel = srcYt - ((srcYt / TILE_SIZE) * TILE_SIZE);
			if (Tile->CollID == SOLID_A_TL_MR || (Tile->CollID == SOLID_A_ML_BR && Yrel >= TILE_SIZE / 2))
			{
				pushY = CollGround(Tile->CollID, destXr % TILE_SIZE, Yrel);
			}
		}
	}
	else if (NewX < 0.0)	// Moving left
	{
		// int Yrel = destYb - ((srcYb / TILE_SIZE) * TILE_SIZE);
		int Yrel = srcYb - ((srcYb / TILE_SIZE) * TILE_SIZE);
		CTile* Tile = CArea::AreaControl.GetTile(destXl, srcYb);
		// if (Tile->CollID == SOLID_U_ML_BR || (Tile->CollID == SOLID_U_TL_MR && Yrel <= TILE_SIZE / 2))
		if (Tile->CollID == SOLID_U_ML_BR || (Tile->CollID == SOLID_U_TL_MR && Yrel < TILE_SIZE / 2))
		{
			pushY = CollGround(Tile->CollID, destXl % TILE_SIZE, Yrel);
		}
		if (pushY == 0)
		{
			Tile = CArea::AreaControl.GetTile(destXl, srcYt);
			Yrel = srcYt - ((srcYt / TILE_SIZE) * TILE_SIZE);
			if (Tile->CollID == SOLID_A_ML_TR || (Tile->CollID == SOLID_A_BL_MR && Yrel >= TILE_SIZE / 2))
			{
				pushY = CollGround(Tile->CollID, destXl % TILE_SIZE, Yrel);
			}
		}
	}

	// Now, let's see if the destination hitbox will collide with
	// something that will stop this entity.
	if (pushY != 0)
	{
		if (CheckPathXY(destXl, destXr, srcYt + pushY, srcYb + pushY))
		{
			// The entity can move in X and Y. The entity is being "pushed"
			// in Y by a sloping surface, which means that we also have checked
			// for stoppages in the Y direction and found none.
			X += NewX;
			Y += pushY;
			if (pushY < 0)
			{
				Jumper = true;
				Grounded = true;
				if (NewY > 0)
				{
					SpeedY = 0;
				}
			}
			else
			{
				if (NewY < 0)
				{
					SpeedY = 0;
				}
			}
		}
		else
		{
			// The entity CANNOT move in X. The queried movement in X
			// required a change in Y, so we must check if the entity can move in only Y
			// now that it is apparent it cannot move in X.
			SpeedX = 0;
			if (CheckPathXY(srcXl, srcXr, destYt, destYb))
			{
				Y += NewY;
			}
			else
			{
				SpeedY = 0;
				if (NewY > 0)
				{
					Jumper = true;
					Grounded = true;
				}
			}
		}
	}
	else
	{
		// If there is no push in Y, then we can just check for
		// if movement is possible in X, and then in Y.
		if (CheckPathXY(destXl, destXr, srcYt, srcYb))
		{
			X += NewX;
		}
		else
		{
			SpeedX = 0;
		}

		if (CheckPathXY(srcXl, srcXr, destYt, destYb))
		{
			Y += NewY;
		}
		else
		{
			SpeedY = 0;
			if (NewY > 0)
			{
				Jumper = true;
				Grounded = true;
			}
		}
	}
}

bool CEntity::CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb)
{
	bool pathclear = true;
	for (int i = 0; i < EntityList.size(); i++)
	{
		if (CollEntity(EntityList[i], destXl, destXr, destYt, destYb) && pathclear)
			pathclear = false;
	}

	if (pathclear)
	{
		for (int tY = destYt / TILE_SIZE; tY <= destYb / TILE_SIZE; tY++)
		{
			for (int tX = destXl / TILE_SIZE; tX <= destXr / TILE_SIZE; tX++)
			{
				CTile* Tile = CArea::AreaControl.GetTile(tX * TILE_SIZE, tY * TILE_SIZE);
				// Check if the collided tile is entirely solid.
				// If it is, entity can't move to destination.
				if (Tile->CollID == SOLID_ALL)
				{
					return false;
				}

				// Check if the collided tile is partially solid.
				// If it is, the entity MIGHT be able to move.
				if (Tile->CollID != SOLID_NONE)
				{
					// Cases where colliding with a partially-filled tile
					// should prevent movement:
					// 1. The top of the hitbox intersects with the
					// 		"lowest height" of a sloping roof, or the bottom of a sloping floor
					// 2. The bottom of the hitbox intersects with the
					//		"highest height" of a sloping floor, or the top of a sloping roof
					// 3.	The left/right sides of the hitbox intersect with a
					//		sloped floor or roof
					// 4. The internal hitbox (non-side) somehow negotiates
					//		an intersection

					// Handling cases #3 and #4
					// There are no exceptions that allow the entity to move if
					// the colliding sector is not from the top or bottom of the hitbox.
					if ((tY != destYt / TILE_SIZE) && (tY != destYb / TILE_SIZE))
					{
						return false;
					}

					// Handling case #1:
					if (tY == destYt / TILE_SIZE)	// If the current tile is associated with the top of the hitbox...
					{
						if (Tile->CollID == SOLID_A_ML_BR)
						{
							if (tX != destXr / TILE_SIZE)
							{
								return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXr % TILE_SIZE, destYt % TILE_SIZE)) return false;
							}
						}
						else if (Tile->CollID == SOLID_A_BL_MR)
						{
							// These sloped roof tiles occupy space from Y = [16, 31] relative to
							// the tile.
							// This entity can't move to the destination. The lowest height of
							// the colliding tile is the bottom of the tile itself.
							if (tX != destXl / TILE_SIZE)
							{
								return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXl % TILE_SIZE, destYt % TILE_SIZE)) return false;
							}
						}
						else if (Tile->CollID == SOLID_A_TL_MR)
						{
							// These sloped roof tiles occupy space from Y = [0, 15] relative to
							// the tile.
							// IF the top of the hitbox destination collides with the space
							// occupied by the sloping roof, then the entity cannot move to
							// the destination.
							if (tX != destXr / TILE_SIZE)
							{
								if (destYt % TILE_SIZE < TILE_SIZE / 2) return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXr % TILE_SIZE, destYt % TILE_SIZE)) return false;
							}
						}
						else if (Tile->CollID == SOLID_A_ML_TR)
						{
							// These sloped roof tiles occupy space from Y = [0, 15] relative to
							// the tile.
							// IF the top of the hitbox destination collides with the space
							// occupied by the sloping roof, then the entity cannot move to
							// the destination.
							if (tX != destXl / TILE_SIZE)
							{
								if (destYt % TILE_SIZE < TILE_SIZE / 2) return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXl % TILE_SIZE, destYt % TILE_SIZE)) return false;
							}
						}
						else // Hitbox top collides with a sloped floor. Maybe the tile's underside.
						{
							if (tX != destXl / TILE_SIZE && tX != destXr / TILE_SIZE)
							{
								if (Tile->CollID == SOLID_U_ML_TR || Tile->CollID == SOLID_U_TL_MR)
								{
									return false;
								}
								// else if (destYt % TILE_SIZE >= TILE_SIZE / 2)
								else
								{
									int Yrel = destYb - ((destYt / TILE_SIZE) * TILE_SIZE);
									if (destYb - ((destYt / TILE_SIZE) * TILE_SIZE) >= TILE_SIZE / 2)
									{
										return false;
									}
								}
							}
							else
							{
								int Yrel = destYb - ((destYt / TILE_SIZE) * TILE_SIZE);
								if (tX == destXl / TILE_SIZE)
								{
									if (CollGround(Tile->CollID, destXl % TILE_SIZE, Yrel)) return false;
								}
								if (tX == destXr / TILE_SIZE)
								{
									if (CollGround(Tile->CollID, destXr % TILE_SIZE, Yrel)) return false;
								}
							}
						}
					}

					// Handling case #2:
					if (tY == destYb / TILE_SIZE) // If the current tile is associated with the bottom of hitbox...
					{
						if (Tile->CollID == SOLID_U_ML_BR)
						{
							if (tX != destXl / TILE_SIZE)
							{
								if (destYb % TILE_SIZE >= TILE_SIZE / 2) return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXl % TILE_SIZE, destYb % TILE_SIZE)) return false;
							}
						}
						else if (Tile->CollID == SOLID_U_BL_MR)
						{
							if (tX != destXr / TILE_SIZE)
							{
								if (destYb % TILE_SIZE >= TILE_SIZE / 2) return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXr % TILE_SIZE, destYb % TILE_SIZE)) return false;
							}
						}
						else if (Tile->CollID == SOLID_U_TL_MR)
						{
							if (tX != destXl / TILE_SIZE)
							{
								return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXl % TILE_SIZE, destYb % TILE_SIZE)) return false;
							}
						}
						else if (Tile->CollID == SOLID_U_ML_TR)
						{
							if (tX != destXr / TILE_SIZE)
							{
								return false;
							}
							else
							{
								if (CollGround(Tile->CollID, destXr % TILE_SIZE, destYb % TILE_SIZE)) return false;
							}
						}
						else // Hitbox bottom collides with a sloped roof. Maybe the tile's top.
						{
							if (tX != destXl / TILE_SIZE && tX != destXr / TILE_SIZE)
							{
								if (Tile->CollID == SOLID_A_ML_BR || Tile->CollID == SOLID_A_BL_MR)
								{
									return false;
								}
								else if (destYb % TILE_SIZE < TILE_SIZE / 2)
								{
									return false;
								}
							}
							else
							{
								if (tX == destXl / TILE_SIZE)
								{
									if (CollGround(Tile->CollID, destXl % TILE_SIZE, destYb % TILE_SIZE)) return false;
								}
								if (tX == destXr / TILE_SIZE)
								{
									if (CollGround(Tile->CollID, destXr % TILE_SIZE, destYb % TILE_SIZE)) return false;
								}
							}
						}
					}
				}
			}
		}
	}
	return pathclear;
}

// Returns true (non-zero) if the queried tile-relative X, Y intersect solid ground.
int CEntity::CollGround(const int& collID, const int& Xrel, const int& Yrel)
{
	bool solidabove = false;
	int Yo = 0;
	double slope = 0.5;

	switch (collID)
	{
		case SOLID_U_BL_MR:	Yo = TILE_SIZE - 1; 																				break;
		case SOLID_U_ML_TR:	Yo = (TILE_SIZE / 2) - 1; 																	break;
		case SOLID_U_TL_MR: 													slope = -0.5; 										break;
		case SOLID_U_ML_BR: Yo = TILE_SIZE / 2; 			slope = -0.5; 										break;
		case SOLID_A_BL_MR: Yo = TILE_SIZE - 1; 										solidabove = true; 	break;
		case SOLID_A_ML_TR:	Yo = (TILE_SIZE / 2) - 1; 							solidabove = true; 	break;
		case SOLID_A_TL_MR: 													slope = -0.5; solidabove = true; 	break;
		case SOLID_A_ML_BR: Yo = TILE_SIZE / 2; 			slope = -0.5; solidabove = true; 	break;
		default: break;
	}

	int Yl = Yo - (int)(slope * Xrel);
	int Ypush = 0;
	if (!solidabove && Yrel >= Yl)
	{
		Ypush = Yl - Yrel - 1;
	}
	else if (solidabove && Yrel <= Yl)
	{
		Ypush = Yl - Yrel + 1;
	}

	return Ypush;
}

bool CEntity::CollEntity(CEntity* Entity, const int& destXl, const int& destXr, const int& destYt, const int& destYb)
{
	if (this == Entity || Entity == NULL) return false;
	if (Entity->Flags & ~ENTITY_FLAG_MAPONLY && Entity->Collides(destXl, destYt, destXr, destYb))
	{
		CEntityCol EntityCol;
		EntityCol.EntityA = this;
		EntityCol.EntityB = Entity;
		CEntityCol::EntityColList.push_back(EntityCol);

		// If the entity is NOT hollow, then the requested position is denied.
		// Otherwise, return true (i.e., the entities don't stop each other,
		// but a collision is still triggered).
		if (Entity->Flags & ~ENTITY_FLAG_HOLLOW) return true;
	}
	return false;
}

void CEntity::OnRender(SDL_Renderer* Surf_Dest)
{
	if (Tex_Entity == NULL || Surf_Dest == NULL) return;

	CSurface::OnDraw(Surf_Dest, Tex_Entity, X - CCamera::CameraControl.GetX(),
		Y - CCamera::CameraControl.GetY(), Xo + (CurrentFrameCol + Anim_Control.GetCurrentFrame()) * Width,
		Yo + CurrentFrameRow * Height, Width, Height);
}

void CEntity::ChkEnviro()
{
	// at initialization, cX is the center of the hitbox in X,
	// and cY is a location inside the hitbox in Y
	// (the final quantity in cY is a 0 to 1 ratio;
	// a larger ratio leads to a larger Y, and a ratio of
	// 0.5 corresponds to the hitbox center in Y)
	// uY is Y of the pixel under the hitbox.
	int cX = X + Col_X + (Col_Width / 2);
	int cY = Y + Col_Y + (Col_Height / 2);
	int uY = Y + Col_Y + Col_Height;
	int bY = uY - 1;

	CTile* WTile = CArea::AreaControl.GetTile(cX * TILE_SIZE, cY * TILE_SIZE);
	if (WTile == NULL) return;
	if (Wet && WTile->TypeID != TILE_TYPE_WATER)
	{
		Wet = false;
	}
	if (WTile->TypeID == TILE_TYPE_WATER && !Wet)
	{
		Wet = true;
	}
	if (!Wet)
	{
		CTile* ITile = CArea::AreaControl.GetTile(cX * TILE_SIZE, uY * TILE_SIZE);
		if (Icy && ITile->TypeID != TILE_TYPE_ICE)
		{
			Icy = false;
		}
		if (ITile->TypeID == TILE_TYPE_ICE && !Icy)
		{
			Icy = true;
		}
	}
}

bool CEntity::Jump()
{
	if (Jumper == false) return false;
	SpeedY = -MaxSpeedY;
	return true;
}

bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY)
{
	if (this != Entity && Entity != NULL && Entity->Dead == false &&
		Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
		Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width, Height - Col_Height) == true)
	{
		CEntityCol EntityCol;
		EntityCol.EntityA = this;
		EntityCol.EntityB = Entity;
		CEntityCol::EntityColList.push_back(EntityCol);

		// If the entity is NOT hollow, then the requested position is denied.
		// Otherwise, return true (i.e., the entities don't stop each other,
		// but a collision is still triggered).
		if (!(Entity->Flags & ENTITY_FLAG_HOLLOW)) return false;
	}
	return true;
}

bool CEntity::Collides(const int& oXl, const int& oYt, const int& oXr, const int& oYb)
{
	int Xl = (int)(X) + Col_X;
	int Yt = (int)(Y) + Col_Y;
	int Xr = Xl + Col_Width - 1;
	int Yb = Yt + Col_Height - 1;

	if (Yb < oYt) return false;
	if (oYb < Yt) return false;
	if (Xr < oXl) return false;
	if (oXr < Xl) return false;

	return true;
}

void CEntity::StopMove()
{
	if (SpeedX > 0) AccelX = -MaxAccelX * 1.5;
	if (SpeedX < 0) AccelX = MaxAccelX * 1.5;
	if (!Icy)
	{
		if (SpeedX < 2.0f && SpeedX > -2.0f)
		{
			AccelX = 0;
			SpeedX = 0;
		}
	}
	else
	{
		if (SpeedX < 0.1f && SpeedX > -0.1f)
		{
			AccelX = 0;
			SpeedX = 0;
		}
	}
}

bool CEntity::OnCollision(CEntity* Entity)
{
	//
	return true;
}

bool CEntity::OnInteract(SDL_Renderer* renderer)
{
	return false;
}

void CEntity::OnCleanup()
{
	if (Tex_Entity) SDL_DestroyTexture(Tex_Entity);
	Tex_Entity = NULL;
}

//*************************************************************
//*************************************************************
//*************************************************************

void CEntity::GetColInfo(int& colX, int& colY, int& colW, int& colH)
{
	colX = this->Col_X;
	colY = this->Col_Y;
	colW = this->Col_Width;
	colH = this->Col_Height;
}

void CEntity::GetPos(float& X, float& Y)
{
	X = this->X;
	Y = this->Y;
}
