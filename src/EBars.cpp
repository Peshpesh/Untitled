#include "EBars.h"

CBars::CBars()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_NONE;
}

bool CBars::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CBars::OnLoop()
{
	CEntity::OnLoop();
}

void CBars::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CBars::OnCleanup()
{
	CEntity::OnCleanup();
}

void CBars::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CBars::OnCollision(CEntity* Entity)
{
	return true;
}
