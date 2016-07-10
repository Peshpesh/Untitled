#include "EItems.h"

CHeart::CHeart()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_ITEM;
	Health = 2;
}

bool CHeart::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CHeart::OnLoop()
{
	CEntity::OnLoop();
}

void CHeart::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CHeart::OnCleanup()
{
	CEntity::OnCleanup();
}

void CHeart::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CHeart::OnCollision(CEntity* Entity)
{
	if (Entity->Health > 0 && Entity->Type == ENTITY_TYPE_PLAYER)
	{
		Health = 0;
		Dead = true;
		return true;
	}
	return false;
}

/**********************************************************************/
/**********************************************************************/
/**********************************************************************/

CAmythyst::CAmythyst()
{
	MaxSpeedX = 0;
	MaxSpeedY = 5;
	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_COIN;
	Health = 1;
}

bool CAmythyst::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CAmythyst::OnLoop()
{
	CEntity::OnLoop();
}

void CAmythyst::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CAmythyst::OnCleanup()
{
	CEntity::OnCleanup();
}

void CAmythyst::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CAmythyst::OnCollision(CEntity* Entity)
{
	if (Entity->Type == ENTITY_TYPE_PLAYER)
	{
		Health = 0;
		Dead = true;
		return true;
	}
	return false;
}