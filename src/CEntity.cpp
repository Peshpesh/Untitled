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
		if (Flags & ENTITY_FLAG_GHOST)
		{
			// We don't care about collisions, but we need to send events to other entities
			PosValid((int)(X + NewX), (int)(Y + NewY), true);
			X += NewX;
			Y += NewY;
		}
		else
		{
			// Check if the new position is valid...
			if (PosValid((int)(X + NewX), (int)(Y), false))
			{
				X += NewX;
			}
			else
			{
				SpeedX = 0;
				CanMove = false;
			}
			if (PosValid((int)(X), (int)(Y + NewY), true))
			{
				Y += NewY;
			}
			else
			{
				if (MoveY > 0)
				{
					Jumper = true;
				}
				SpeedY = 0;
				CanMove = false;
			}
		}
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

bool CEntity::Translate(double NewX, double NewY)
{
	// NOTE: NewX, NewY params should be <= 1.0.

	bool movethis = true;
	int destXl = X + NewX + Col_X;
	int destYt = Y + NewY + Col_Y;
	int destXr = destXl + Col_Width - 1;
	int destYb = destYt + Col_Height - 1;
	int deflectY = 0;

	// First, let's see what lies ahead in terms of the map.
	// These two conditional blocks handle sloping grounds.
	// If necessary, a deflection amount is assigned to deflectY.
	// This value is such that adding it to the intended Y position
	// will yield a valid Y position on the map (use this for entities,
	// tiles that might block movement, etc.). The deflectY term is basically
	// a "correction" term in Y, which must be satisfied if this entity is to move
	// horizontally.
	if (NewX > 0.0)	// Moving right
	{
		CTile* Tile = CArea::AreaControl.GetTile(destXr, destYb - NewY);
		if (Tile->CollID == SOLID_U_BL_MR || Tile->CollID == SOLID_U_ML_TR)
		{
			int Yo = SOLID_U_BL_MR ? TILE_SIZE - 1 : (TILE_SIZE / 2) - 1;
			double slope = 0.5;
			int Xrel = destXr % TILE_SIZE;
			int Yrel = destYb % TILE_SIZE;
			int Yground = Yo - (slope * Xrel);
			if (Yrel >= Yground) // intended destination of bottom side is "in the ground"
			{
				deflectY = Yground - Yrel - 1;
			}
		}
	}
	else if (NewX < 0.0)	// Moving left
	{
		CTile* Tile = CArea::AreaControl.GetTile(destXl, destYb - NewY);
		if (Tile->CollID == SOLID_U_TL_MR || Tile->CollID == SOLID_U_ML_BR)
		{
			int Yo = SOLID_U_TL_MR ? 0 : TILE_SIZE / 2;
			double slope = -0.5;
			int Xrel = destXl % TILE_SIZE;
			int Yrel = destYb % TILE_SIZE;
			int Yground = Yo - (slope * Xrel);
			if (Yrel >= Yground) // intended destination of bottom side is "in the ground"
			{
				deflectY = Yground - Yrel - 1;
			}
		}
	}

	// Now, let's see if the destination hitbox will collide with
	// something that will stop this entity. First, let's check the map.
	if (deflect != 0)
	{
		if (!CheckPathXY(destXl, destXr, destYt + deflectY, destYb + deflectY))
		{
			// The entity cannot move.
		}
		else
		{
			// The entity can move.
		}
	}
	else
	{
		CheckPathX();
		CheckPathY();
	}

	return retval;
}

bool CEntity::CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb)
{
	for (int tY = destYt / TILE_SIZE; tY <= destYb / TILE_SIZE; tY++)
	{
		for (int tX = destXl / TILE_SIZE; tX <= destXr / TILE_SIZE; tX++)
		{
			CTile* Tile = CArea::AreaControl.GetTile(tX * TILE_SIZE, tY * TILE_SIZE);
			// Check if the collided tile is entirely solid.
			// If it is, entity can't move to destination.
			if (Tile->CollID == SOLID_ALL) return false;

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
					else // Hitbox top collides with a sloped floor. Probably the tile's underside.
					{
						return false;
					}
				}

				// Handling case #2:
				else if (tY == destYb / TILE_SIZE) // If the current tile is associated with the bottom of hitbox...
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
					else
					{
						return false;
					}
				}

				// Handling cases #3 and #4
				else
				{
					// There are no exceptions that allow the entity to move if
					// the colliding sector is not from the top or bottom of the hitbox.
					return false;
				}
			}
		}
	}
	return true;
}

bool CEntity::CheckPathX(double NewX)
{
	return true;
}

bool CEntity::CheckPathY(double NewY)
{
	bool retval = true;
	int destXi = X + Col_X;
	int destYi = Y + NewY + Col_Y;
	int destXf = destXi + Col_Width - 1;
	int destYf = destYf + Col_Height - 1;

	return retval;
}

// Returns true if the queried tile-relative X, Y intersect solid ground.
bool CEntity::CollGround(const int& collID, const int& Xrel, const int& Yrel)
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

	int Yl = Yo - (slope * Xrel);

	return !solidabove ? (Yrel >= Yl) : (Yrel <= Yl);
}

// Checks to see if the position an entity is moving toward
// is valid. Returns false if the destination is invalid.
// First checks if the entity collides with the map, then
// checks for other entities.
bool CEntity::PosValid(int NewX, int NewY, bool Vertical)
{
	bool retval = true;
	bool OnSlope = false;

	int StartX = (NewX + Col_X) ;
	int StartY = (NewY + Col_Y) ;

	int EndX = ((NewX + Col_X) + Width - Col_Width - 1) ;
	int EndY = ((NewY + Col_Y) + Height - Col_Height - 1) ;

	float BoostY = 0.0;

	for (int iY = StartY / TILE_SIZE; iY <= EndY / TILE_SIZE; iY++)
	{
		for (int iX = StartX / TILE_SIZE; iX <= EndX / TILE_SIZE; iX++)
		{
			CTile* Tile = CArea::AreaControl.GetTile(iX * TILE_SIZE, iY * TILE_SIZE);
			if (!OnSlope && Tile->Slope != SLOPE_FLAT)
			{
				OnSlope = true;
			}
			if (PosValidTile(Tile) == false)
			{
				retval = false;
			}
		}
	}
	if (retval && OnSlope)
	{
		int TileRefXe = (EndX % TILE_SIZE) + 1;   // right side of new hitbox position
		int TileRefYe = (EndY % TILE_SIZE) + 1;   // bottom side of new hitbox position
		int TileRefXs = (StartX % TILE_SIZE) + 1; // left side of new hitbox position
		int TileRefYs = (StartY % TILE_SIZE) + 1; // top side of new hitbox position
		CTile* TileBL = CArea::AreaControl.GetTile((StartX / TILE_SIZE) * TILE_SIZE, (EndY / TILE_SIZE) * TILE_SIZE);
		CTile* TileBR = CArea::AreaControl.GetTile((EndX / TILE_SIZE) * TILE_SIZE, (EndY / TILE_SIZE) * TILE_SIZE);

		switch (TileBL->Slope)
		{
			case SLOPE_DSC:
			{
				if (TileRefYe > TileRefXs / 2)
				{
					if (Vertical) retval = false;
					if (Flags & ENTITY_FLAG_BULLET) retval = false;
					else BoostY = (TileRefXs / 2) - TileRefYe;
				}
				break;
			}
			case SLOPE_DSCE:
			{
				if (TileRefYe > (TILE_SIZE + TileRefXs) / 2)
				{
					if (Vertical) retval = false;
					if (Flags & ENTITY_FLAG_BULLET) retval = false;
					else BoostY = ((TILE_SIZE + TileRefXs) / 2) - TileRefYe;
				}
				break;
			}
			default:
			{
				break;
			}
		}
		switch (TileBR->Slope)
		{
			case SLOPE_ASC:
			{
				if (TileRefYe > TILE_SIZE - (TileRefXe / 2))
				{
					if (Vertical) retval = false;
					if (Flags & ENTITY_FLAG_BULLET) retval = false;
					else if ((TILE_SIZE - (TileRefXe / 2)) - TileRefYe < BoostY)
						BoostY = (TILE_SIZE - (TileRefXe / 2)) - TileRefYe;
				}
				break;
			}
			case SLOPE_ASCE:
			{
				if (TileRefYe > (TILE_SIZE - TileRefXe) / 2)
				{
					if (Vertical) retval = false;
					if (Flags & ENTITY_FLAG_BULLET) retval = false;
					else BoostY = ((TILE_SIZE - TileRefXe) / 2) - TileRefYe;
				}
				break;
			}
			default:
			{
				if (TileRefYe > TILE_SIZE / 2 && TileBR->Slope == SLOPE_DSCE)
				{
					if (Vertical) retval = false;
					if (Flags & ENTITY_FLAG_BULLET) retval = false;
					else if ((int)(BoostY) >= 0) BoostY = (TILE_SIZE / 2) - TileRefYe;
				}
				else if (TileBR->Slope == SLOPE_DSC)
				{
					if (Vertical) retval = false;
					if (Flags & ENTITY_FLAG_BULLET) retval = false;
					else if ((int)(BoostY) >= 0) BoostY = -TileRefYe;
				}
				break;
			}
		}
	}
	if (Flags & ENTITY_FLAG_MAPONLY)
	{
		// If the entity only is blocked by the map, then
		// don't worry about entities (the else block).
	}
	else
	{
		for (int i = 0; i < EntityList.size(); i++)
		{
			if (PosValidEntity(EntityList[i], NewX, NewY + BoostY) == false)
			{
				retval = false;
			}
		}
	}
	if (retval && !Vertical)
	{
		Y += BoostY;
	}
	return retval;
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

	// int cX = (X + Col_X + ((Width - Col_Width - 1) / 2)) / TILE_SIZE;
	// int cY = (Y + Col_Y + ((Height - Col_Height - 1) * (1 - 0.5))) / TILE_SIZE;
	// int uY = (Y + Col_Y + Height - Col_Height) / TILE_SIZE;
	int cX = X + Col_X + (Col_Width / 2);
	int cY = Y + Col_Y + (Col_Height / 2);
	int uY = Y + Col_Y + Col_Height;
	int bY = uY - 1;

	CTile* WTile = CArea::AreaControl.GetTile(cX * TILE_SIZE, cY * TILE_SIZE);
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

bool CEntity::PosValidTile(CTile* Tile)
{
	if (Tile == NULL) return true;
	if (Tile->CollID == SOLID_ALL)	return false;

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

bool CEntity::Collides(int oX, int oY, int oW, int oH)
{
	int left1, left2;
	int right1, right2;
	int top1, top2;
	int bottom1, bottom2;
	int tX = (int)X + Col_X;
	int tY = (int)Y + Col_Y;

	left1 = tX;
	left2 = oX;
	right1 = left1 + Width - 1 - Col_Width;
	right2 = oX + oW - 1;
	top1 = tY;
	top2 = oY;
	bottom1 = top1 + Height - 1 - Col_Height;
	bottom2 = oY + oH - 1;

	if (bottom1 < top2) return false;
	if (bottom2 < top1) return false;
	if (right1 < left2) return false;
	if (right2 < left1) return false;
	return true;
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
