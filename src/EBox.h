#ifndef _EBOX_H_
#define _EBOX_H_

#include "CEntity.h"

class CBox : public CEntity
{
public:
	CBox();

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

};

#endif