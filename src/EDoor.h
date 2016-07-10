#ifndef _EDOOR_H_
#define _EDOOR_H_

#include "CEntity.h"
#include "CTransport.h"

class CDoor : public CEntity
{
public:
	CDoor();
	CDoor(int Enum_Dest, float dX, float dY);

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	bool OnInteract(SDL_Renderer* renderer);

public:
	int Enum_Dest;
	float dX;
	float dY;

};

#endif