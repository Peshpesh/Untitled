#include "EDoor.h"

CDoor::CDoor()
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_NPC;
	Enum_Dest = -1;
	dX = dY = 0.0;
}

CDoor::CDoor(int Enum_Dest, float dX, float dY)
{
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_NPC;
	this->Enum_Dest = Enum_Dest;
	this->dX = dX;
	this->dY = dY;
}

bool CDoor::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CDoor::OnLoop()
{
	CEntity::OnLoop();
}

void CDoor::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CDoor::OnCleanup()
{
	CEntity::OnCleanup();
}

void CDoor::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CDoor::OnCollision(CEntity* Entity)
{
	return true;
}

bool CDoor::OnInteract(SDL_Renderer* renderer)
{
	if (Enum_Dest >= 0)
	{
		CTransport::Transporter.OnRequest(Enum_Dest, dX, dY);
		Engaged = false;
	}
	return false;
}
