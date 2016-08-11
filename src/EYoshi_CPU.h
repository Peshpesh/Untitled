#ifndef _EYOSHI_H_
#define _EYOSHI_H_

#include "CEntity.h"

class CYoshi : public CEntity
{
public:
	CYoshi();

	bool OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);


};

#endif
