#ifndef _C_CONTROLS_H_
#define _C_CONTROLS_H_

#include <stdio.h>
#include "CEvent.h"

enum Gamecon {
	CON_NONE,
	CON_ATTACK,
	CON_DEFEND,
	CON_JUMP,
	CON_SPEC,
	CON_LEFT,
	CON_RIGHT,
	CON_DOWN,
	CON_UP,
	CON_CYCLE_L,
	CON_CYCLE_R,
	CON_MAP,
	CON_INVENTORY,
	CON_PAUSE,
};

struct ControlKey {
  int c_attack;
	int c_defend;
  int c_jump;
	int c_spec;
  int c_left;
  int c_right;
  int c_down;
  int c_up;
	int c_cycle_l;
	int c_cycle_r;
	int c_map;
	int c_inventory;
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
