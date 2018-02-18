#ifndef _C_CONTROLS_H_
#define _C_CONTROLS_H_

#include <stdio.h>
#include "CEvent.h"

enum Gamecon {
	CON_NONE,
	CON_ATTACK,
	CON_JUMP,
	CON_LEFT,
	CON_RIGHT,
	CON_DOWN,
	CON_UP,
	CON_PAUSE,
};

struct ControlKey {
  int c_attack;
  int c_jump;
  int c_left;
  int c_right;
  int c_down;
  int c_up;
  int c_pause;
};

class CControls : public CEvent {
  CControls();
  ControlKey key;

public:
	Gamecon con_change;

public:
  static CControls handler;
	void OnEvent(SDL_Event* Event);

private:
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	bool validKey(SDL_Keycode sym, Uint16 mod);

public:
	Gamecon getAction(SDL_Keycode sym, Uint16 mod);
	SDL_Keycode getAssignKey(const Gamecon& action);

private:
	bool OnInit();
	void reset();
	void save();
};

#endif
