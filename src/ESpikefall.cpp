#include "ESpikefall.h"

CSpikefall::CSpikefall()
{
	MaxSpeedX = 0;
	MaxSpeedY = 5;
	Flags = ENTITY_FLAG_HOLLOW;
	Flags = Flags | ENTITY_FLAG_DAMAGE;
	Damage = 1;
}

bool CSpikefall::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CSpikefall::OnLoop()
{
	// horizontal distance from player
	float X_dist = (this->X + (this->Width/2) - CEntity::EntityList[0]->X + (CEntity::EntityList[0]->Width/2));
	// vertical distance from player
	float Y_dist = (this->Y - CEntity::EntityList[0]->Y);

	// If player comes within a 64 px "pillar" area, and player is underneath...
	if (X_dist < 64 && Y_dist < 0)
	{
		Flags |= ENTITY_FLAG_GRAVITY;
	}

	if (Flags & ENTITY_FLAG_GRAVITY)
	{
		AccelY = 0.75f;
	}

	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	// Make sure we're not overstepping our boundaries,
	// so to speak...
	if (SpeedY > MaxSpeedY) SpeedY = MaxSpeedY;
	if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	OnAnimate();
	if ((Flags & ENTITY_FLAG_GRAVITY) && !OnMove(0.0, SpeedY))
		Dead = true;
}

void CSpikefall::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CSpikefall::OnCleanup()
{
	CEntity::OnCleanup();
}

void CSpikefall::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CSpikefall::OnCollision(CEntity* Entity)
{
	return true;
}
