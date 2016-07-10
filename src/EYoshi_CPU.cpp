#include "EYoshi_CPU.h"

CYoshi::CYoshi()
{
	MaxSpeedX = 3;
	MaxSpeedY = 3;
//	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_DAMAGE;
	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;
	Flags = Flags | ENTITY_FLAG_DAMAGE;
	Health = 10;
	Damage = 3;
}

bool CYoshi::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CYoshi::OnLoop()
{
	if (Health <= 0)
		Dead = true;

	MoveRight = MoveLeft = false;
	
	// horizontal distance from player
	float X_dist = (this->X - CEntity::EntityList[0]->X);
	// vertical distance from player
	float Y_dist = (this->Y - CEntity::EntityList[0]->Y);
	// total distance from player squared
	float sq_dist = (X_dist * X_dist) + (Y_dist + Y_dist);

	// If player comes within a 128 px radius...
	if (sq_dist < 128 * 128)
	{
		// Face player
		if (X_dist > 0.0)
			// Face Left
			CurrentFrameRow = 0;
		if (X_dist < 0.0)
			// Face Right
			CurrentFrameRow = 1;	
	}

	// Move toward player if they are closer
	if (sq_dist < 96 * 96)
	{
		if (X_dist > 0.0)
			MoveLeft = true;
		if (X_dist < 0.0)
			MoveRight = true;
		if (Y_dist > 10.0)
			Jump();
	}

	CEntity::OnLoop();
}

void CYoshi::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CYoshi::OnCleanup()
{
	CEntity::OnCleanup();
}

void CYoshi::OnAnimate()
{
	if (SpeedX != 0)
	{
		Anim_Control.MaxFrames = 8;
	}
	else
	{
		Anim_Control.MaxFrames = 0;
	}

	CEntity::OnAnimate();
}

bool CYoshi::OnCollision(CEntity* Entity)
{
	return true;
}