#include "EShop.h"

CShop::CShop()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_NPC;
}

bool CShop::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CShop::OnLoop()
{
	CEntity::OnLoop();
}

void CShop::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
	if (Engaged)
	{
		if (CDialogue::DiaControl.OnSpeech(renderer, "THIS SANDWICH SHOP\nIS CLOSED ASSHOLE") == 0)
		{
			Engaged = false;
		}
	}
}

void CShop::OnCleanup()
{
	CEntity::OnCleanup();
}

void CShop::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CShop::OnCollision(CEntity* Entity)
{
	return true;
}

bool CShop::OnInteract(SDL_Renderer* renderer)
{
	return Engaged;
}
