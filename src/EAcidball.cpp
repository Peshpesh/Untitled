#include "EAcidball.h"

CAcidball::CAcidball()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_NONE;
}

bool CAcidball::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CAcidball::OnLoop()
{
	CEntity::OnLoop();
}

void CAcidball::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CAcidball::OnCleanup()
{
	CEntity::OnCleanup();
}

void CAcidball::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CAcidball::OnCollision(CEntity* Entity)
{
	return true;
}
