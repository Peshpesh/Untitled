#ifndef _CTITLE_H_
#define _CTITLE_H_

#include "Font.h"
#include "Config.h"
#include "CGamedata.h"
#include "Define.h"

enum MAIN_OPTIONS
{
	NEW_GAME = 0,
	LOAD_GAME,
	STATISTICS,
	OPTIONS,
	QUIT_GAME,
	// MAP_EDITOR,
};

class CTitle
{
public:
	static CTitle		MainMenu;

	bool Active;
	bool Submit;
	bool selectGame;
	char sfile;
	bool showstats;
	unsigned short hilight;
	char* options;

public:

	CTitle();

	bool OnInit();

	void OnEvent(SDL_Keycode sym);

	void OnLoop();

	void OnRender(SDL_Renderer* renderer);
	void RenderStats(SDL_Renderer* renderer);
};

#endif
