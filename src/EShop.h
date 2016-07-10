#ifndef _ESHOP_H_
#define _ESHOP_H_

#include "CEntity.h"
#include "CDialogue.h"

class CShop : public CEntity
{
public:
	CShop();

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	bool OnInteract(SDL_Renderer* renderer);
};

#endif