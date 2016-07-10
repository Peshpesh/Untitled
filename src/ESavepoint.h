#ifndef _ESAVEPOINT_H_
#define _ESAVEPOINT_H_

#include "CEntity.h"
#include "CGamedata.h"
#include "CDialogue.h"
#include "CMenu.h"

//class CMenu;

class CSVPT : public CEntity
{
private:
	bool Prompt;

public:
	CSVPT();

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void ExitMenu(CMenu* menu);
	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	bool OnInteract(SDL_Renderer* renderer);

private:
	CMenu* SaveMenu;
	CMenu* ConfirmMenu;
};

#endif
