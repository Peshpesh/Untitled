#ifndef _C_GAME_H_
#define _C_GAME_H_

#include "CEvent.h"
#include "CControls.h"
#include "CConfig.h"
#include "CGameIO.h"
#include "CInterrupt.h"

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

  bool OnInit();
  void initHero();

	void OnEvent(SDL_Event* Event);
  bool handleInterrupts(SDL_Event* Event);

	void OnExit();

	void OnLoop();

	void OnRender();

	void OnCleanup();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);
};

#endif
