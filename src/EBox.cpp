#include "EBox.h"

CBox::CBox()
{
	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;
	Health = 2;
	MaxSpeedX = 0;
	MaxSpeedY = 0;

	Flags = ENTITY_FLAG_NONE;
}

bool CBox::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CBox::OnLoop()
{
	if (Health <= 0)
		Dead = true;

	CEntity::OnLoop();
}

void CBox::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CBox::OnCleanup()
{
	CEntity::OnCleanup();
}

void CBox::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CBox::OnCollision(CEntity* Entity)
{
	return true;
}
