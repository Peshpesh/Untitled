#ifndef _EEXPLODE_H_
#define _EEXPLODE_H_

#include "CEntity.h"

class CExplode : public CEntity
{
private:
  float ExplodeTime;

public:
	CExplode();

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);
};

#endif
