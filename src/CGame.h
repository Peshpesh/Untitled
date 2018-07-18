#ifndef _C_GAME_H_
#define _C_GAME_H_

#include "CEvent.h"
#include "CControls.h"
#include "CConfig.h"
#include "CGameIO.h"
#include "CInterrupt.h"

#include "CDifficulty.h"
#include "CStages.h"

#include "CPause.h"
#include "CTransition.h"
#include "CArea.h"
#include "CDialogue.h"
#include "CMapModel.h"
#include "CInventory.h"
#include "CEntityIO.h"
#include "CSceneryIO.h"
#include "CHero.h"
#include "CHUD.h"

class CGame : public CEvent {
  CGame();

public:
  static CGame control;
  short test_resp;

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
