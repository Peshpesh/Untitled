#ifndef _C_CONFIG_H_
#define _C_CONFIG_H_

#include <SDL.h>
#include <stdio.h>
#include <cstring>
#include "CFont.h"
#include "Define.h"

enum
{
	CF_RETURN = 0,
	CF_CONFIRM,
	CF_JUMP,
	CF_LEFT,
	CF_RIGHT,
	CF_DOWN,
	CF_UP,
	CF_SELECT,
	CF_PAUSE,
	CF_RESTORE,
};

class CConfig
{
public:
	static CConfig ConfControl;
	bool modify;
	bool querykey;
	unsigned short hilight;

public: // main
	int confirm;
	int pause;
	int select;
	int left;
	int right;
	int down;
	int up;
	int jump;

public:
	CConfig();

	bool OnInit();

	void OnEvent(SDL_Keycode sym);

	bool OnRender(SDL_Renderer* renderer);

	bool ErrCheck(SDL_Keycode sym);
	void Reset();
	void Save();
};
#endif
