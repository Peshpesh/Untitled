#include "CEntity.h"

std::vector<CEntity*> CEntity::EntityList;

CEntity::CEntity()
{
	Tex_Entity = NULL;
	X = Y = 0.0f;
	Xo = Yo = 0;
	Width = Height = 0;
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
	Col_Width = Col_Height = 0;
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

void CEntity::OnRender()
{
	if (Tex_Entity == NULL) return;

	CSurface::OnDraw(Tex_Entity, X - CCamera::CameraControl.GetX(),
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

	int cX = (X + Col_X + ((Width - Col_Width - 1) / 2)) / TILE_SIZE;
	int cY = (Y + Col_Y + ((Height - Col_Height - 1) * (1 - 0.5))) / TILE_SIZE;
	int uY = (Y + Col_Y + Height - Col_Height) / TILE_SIZE;

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

bool CEntity::Jump()
{
	if (Jumper == false) return false;
	SpeedY = -MaxSpeedY;
	return true;
}

// Checks to see if the position an entity is moving toward
// is valid. Returns false if the destination is invalid.
// First checks if the entity collides with the map, then
// checks for other entities.
bool CEntity::PosValid(int NewX, int NewY, bool Vertical)
{
	bool Return = true;
	bool OnColl = false;

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
			if (!OnColl && Tile->CollID != SOLID_NONE)
			{
				OnColl = true;
			}
			if (PosValidTile(Tile) == false)
			{
				Return = false;
			}
		}
	}
	if (Return && OnColl)
	{
		int TileRefXe = (EndX % TILE_SIZE) + 1;   // right side of new hitbox position
		int TileRefYe = (EndY % TILE_SIZE) + 1;   // bottom side of new hitbox position
		int TileRefXs = (StartX % TILE_SIZE) + 1; // left side of new hitbox position
		int TileRefYs = (StartY % TILE_SIZE) + 1; // top side of new hitbox position
		CTile* TileBL = CArea::AreaControl.GetTile((StartX / TILE_SIZE) * TILE_SIZE, (EndY / TILE_SIZE) * TILE_SIZE);
		CTile* TileBR = CArea::AreaControl.GetTile((EndX / TILE_SIZE) * TILE_SIZE, (EndY / TILE_SIZE) * TILE_SIZE);

		// switch (TileBL->CollID)
		// {
		// 	case SLOPE_DSC:
		// 	{
		// 		if (TileRefYe > TileRefXs / 2)
		// 		{
		// 			if (Vertical) Return = false;
		// 			if (Flags & ENTITY_FLAG_BULLET) Return = false;
		// 			else BoostY = (TileRefXs / 2) - TileRefYe;
		// 		}
		// 		break;
		// 	}
		// 	case SLOPE_DSCE:
		// 	{
		// 		if (TileRefYe > (TILE_SIZE + TileRefXs) / 2)
		// 		{
		// 			if (Vertical) Return = false;
		// 			if (Flags & ENTITY_FLAG_BULLET) Return = false;
		// 			else BoostY = ((TILE_SIZE + TileRefXs) / 2) - TileRefYe;
		// 		}
		// 		break;
		// 	}
		// 	default:
		// 	{
		// 		break;
		// 	}
		// }
		// switch (TileBR->CollID)
		// {
		// 	case SLOPE_ASC:
		// 	{
		// 		if (TileRefYe > TILE_SIZE - (TileRefXe / 2))
		// 		{
		// 			if (Vertical) Return = false;
		// 			if (Flags & ENTITY_FLAG_BULLET) Return = false;
		// 			else if ((TILE_SIZE - (TileRefXe / 2)) - TileRefYe < BoostY)
		// 				BoostY = (TILE_SIZE - (TileRefXe / 2)) - TileRefYe;
		// 		}
		// 		break;
		// 	}
		// 	case SLOPE_ASCE:
		// 	{
		// 		if (TileRefYe > (TILE_SIZE - TileRefXe) / 2)
		// 		{
		// 			if (Vertical) Return = false;
		// 			if (Flags & ENTITY_FLAG_BULLET) Return = false;
		// 			else BoostY = ((TILE_SIZE - TileRefXe) / 2) - TileRefYe;
		// 		}
		// 		break;
		// 	}
		// 	default:
		// 	{
		// 		if (TileRefYe > TILE_SIZE / 2 && TileBR->Slope == SLOPE_DSCE)
		// 		{
		// 			if (Vertical) Return = false;
		// 			if (Flags & ENTITY_FLAG_BULLET) Return = false;
		// 			else if ((int)(BoostY) >= 0) BoostY = (TILE_SIZE / 2) - TileRefYe;
		// 		}
		// 		else if (TileBR->Slope == SLOPE_DSC)
		// 		{
		// 			if (Vertical) Return = false;
		// 			if (Flags & ENTITY_FLAG_BULLET) Return = false;
		// 			else if ((int)(BoostY) >= 0) BoostY = -TileRefYe;
		// 		}
		// 		break;
		// 	}
		// }
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
				Return = false;
			}
		}
	}
	if (Return && !Vertical)
	{
		Y += BoostY;
	}
	return Return;
}

bool CEntity::PosValidTile(CTile* Tile)
{
	if (Tile == NULL) return true;
	// if (Tile->TypeID == TILE_TYPE_BLOCK || Tile->TypeID == TILE_TYPE_ICE)
	// {
	// 	return false;
	// }
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

bool CEntity::OnMove(float MoveX, float MoveY)
{
	Jumper = false;
	bool CanMove = true;
	if (MoveX == 0 && MoveY == 0) return false;

	double NewX = 0;
	double NewY = 0;

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
		MoveX += -NewX;
		MoveY += -NewY;
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

bool CEntity::OnInteract()
{
	return false;
}

void CEntity::OnCleanup()
{
	if (Tex_Entity) SDL_DestroyTexture(Tex_Entity);
	Tex_Entity = NULL;
}
