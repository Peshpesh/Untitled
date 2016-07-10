#ifndef _CCINEMA_H_
#define _CCINEMA_H_

#include "CArea.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "CSurface.h"
#include "All_Entities.h"
#include "CDialogue.h"

class CCinema {
public:
	static CCinema* CinemaControl;
	bool Scene;

public:
	int *Progress;

public:
	CCinema();

	virtual ~CCinema();

	virtual bool OnLoad(SDL_Renderer* renderer, int* prog);

	virtual void OnLoop(float &pX, float &pY, SDL_Renderer* renderer);

	virtual void OnRender(SDL_Renderer* renderer);

	virtual void OnSceneLoop();

	virtual void OnCleanup();
};
#endif
