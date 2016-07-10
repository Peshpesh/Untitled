#ifndef _EBULLET_H_
#define _EBULLET_H_

#include "CEntity.h"

class CArm_Test : public CEntity
{
public:
	CArm_Test(bool right);

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	void OnDeath(bool hit);

private:
	int Level;			// Weapon level
	bool Dir_Right;		// Facing right?
	bool Used;			// Has the bullet done damage yet?

	int Life_Time;		// How many frames does the bullet have left?
};

#endif