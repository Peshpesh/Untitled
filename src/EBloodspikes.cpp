#include "EBloodspikes.h"

CBldspkup::CBldspkup()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW | ENTITY_FLAG_DAMAGE;
	Damage = 4;
}

bool CBldspkup::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CBldspkup::OnLoop()
{
	CEntity::OnLoop();
}

void CBldspkup::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CBldspkup::OnCleanup()
{
	CEntity::OnCleanup();
}

void CBldspkup::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CBldspkup::OnCollision(CEntity* Entity)
{
	return true;
}
