#ifndef _EBARS_H_
#define _EBARS_H_

#include "CEntity.h"

class CBars : public CEntity
{
public:
	CBars();

	bool OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

};

#endif
