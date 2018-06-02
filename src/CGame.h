#ifndef _C_GAME_H_
#define _C_GAME_H_

#include "CEvent.h"
#include "CControls.h"
#include "CConfig.h"
#include "CGameIO.h"
#include "CInterrupt.h"

#include "CPause.h"
#include "CTransition.h"
#include "CArea.h"
#include "CEntityIO.h"
#include "CSceneryIO.h"
#include "CHero.h"

class CGame : public CEvent {
  CGame();

public:
  static CGame control;
  CHero Hero;

private:
  Difficulty diff;
  int suspend_flag;

public:
  bool OnInit();
private:
  void initHero();

public:
	void OnEvent(SDL_Event* Event);
private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnKeyUp(SDL_Keycode sym, Uint16 mod);
  bool handleInterrupts(SDL_Event* Event);

public:
	void OnLoop();
private:
  bool handleTransit();

public:
	void OnRender();
private:
  void drawIntrpt();

public:
  void OnExit();
	void OnCleanup();
};

#endif
