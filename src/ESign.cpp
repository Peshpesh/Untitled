#include "ESign.h"

CSign::CSign()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_NPC;
	content = "SUP SCRO";
}

bool CSign::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CSign::OnLoop()
{
	CEntity::OnLoop();
}

void CSign::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
	if (Engaged)
	{
		if (CDialogue::DiaControl.OnSpeech(renderer, content) == 0)
		{
			Engaged = false;
			content = "P S YOU SUCK SCRO";
		}
	}
}

void CSign::OnCleanup()
{
	CEntity::OnCleanup();
}

void CSign::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CSign::OnCollision(CEntity* Entity)
{
	return true;
}

bool CSign::OnInteract(SDL_Renderer* renderer)
{
	return Engaged;
}

void CSign::ChangeText(char* message)
{

}
