#ifndef _ESPIKEFALL_H_
#define _ESPIKEFALL_H_

#include "CEntity.h"

class CSpikefall : public CEntity
{
public:
	CSpikefall();

	bool OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

};

#endif
