#ifndef _CCINEMA_DEBUG_H_
#define _CCINEMA_DEBUG_H_

#include "CCinema.h"

enum
{
	NEW_AREA			= 0,
	KILLED_MINION	= 0x00000001,
	STOLE_GEM			= 0x00000002,
	KILLED_BOSS		= 0x00000004,
};

class CCinema_Debug : public CCinema {
public:

	CCinema_Debug();

	bool OnLoad(SDL_Renderer* renderer, int* prog);

	void OnLoop(float &pX, float &pY, SDL_Renderer* renderer);

	void OnRender(SDL_Renderer* renderer);

	void OnSceneLoop();

	void OnCleanup();

private:
	CEntity* BossID;
	CEntity* Bars_A;
	CEntity* Bars_B;
};

class CCinema_DebugB : public CCinema {
private:
	enum
	{
		NEW_AREA = 0,
		SANDWICH = 0x00000001,
		SANDWICHB = 0x00000002,
		SANDWICHC = 0x00000004,
	};
public:

	CCinema_DebugB();

	bool OnLoad(SDL_Renderer* renderer, int* prog);

	void OnLoop(float &pX, float &pY, SDL_Renderer* renderer);

	void OnRender(SDL_Renderer* renderer);

	void OnSceneLoop();

	void OnCleanup();
};

class CCinema_Arena : public CCinema {
private:
	enum
	{
		NEW_AREA = 0,
	};
public:

	CCinema_Arena();

	bool OnLoad(SDL_Renderer* renderer, int* prog);

	void OnLoop(float &pX, float &pY, SDL_Renderer* renderer);

	void OnRender(SDL_Renderer* renderer);

	void OnSceneLoop();

	void OnCleanup();
};
#endif
