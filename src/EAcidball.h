#ifndef _EACIDBALL_H_
#define _EACIDBALL_H_

#include "CEntity.h"

class CAcidball : public CEntity
{
public:
	CAcidball();

	bool OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

};

#endif
