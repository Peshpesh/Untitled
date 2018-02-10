#ifndef _C_TITLE_H_
#define _C_TITLE_H_

#include "CConfig.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "CSound.h"

namespace Title {
  extern const SDL_Color* f_def;
  extern const SDL_Color* f_hov;
  extern const SDL_Color* f_act;
  extern const short num_options;
  extern const short w;
  extern const short h;
  extern const short x;
  extern const short y;
  extern const char* const opt_list[];
  enum menus {
    MAIN = 0,
    NEW_GAME,
    LOAD_GAME,
    OPTIONS,
  };
  namespace new_game {
    //
  };
  namespace load_game {
    //
  };
  namespace options {
    //
  };
};

class CTitle : public CEvent {
  CTitle();

  short menu_kind;
  short pos;

public:
  void OnInit();

  void OnEvent(SDL_Event* Event);

  bool OnRender();

  void OnLoop();

  void OnCleanup();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

private:
  bool drawMainMenu();
  bool drawNewGame();
  bool drawLoadGame();
  bool drawOptions();
};

#endif