#ifndef _ESIGN_H_
#define _ESIGN_H_

#include "CEntity.h"
#include "CDialogue.h"

class CSign : public CEntity
{

public:
	CSign();

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	bool OnInteract(SDL_Renderer* renderer);

public:
	void ChangeText(char* message);

private:
	char* content;							// What the sign says (dynamic; changed via ChangeText function)

};

#endif