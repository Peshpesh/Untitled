#ifndef _C_TITLE_H_
#define _C_TITLE_H_

#include "CControls.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "CSound.h"

namespace Title {
  extern const SDL_Color* f_def;
  extern const SDL_Color* f_hov;
  extern const SDL_Color* f_lock;
  extern const SDL_Point* o_def;
  extern const SDL_Point* o_hov;
  extern const SDL_Point* o_lock;
  extern const short num_options;
  extern const short w;
  extern const short h;
  extern const short dx;
  extern const short dy;
  extern const short x;
  extern const short y;
  extern const short stroke_w;
  extern const char* const opt_list[];
  enum menus {
    MAIN = 0,
    NEW_GAME,
    LOAD_GAME,
    OPTIONS,
  };
  namespace decision {
    enum {
      DEC_NEW = 0,
      DEC_LOAD,
      DEC_OPTIONS,
      DEC_QUIT,
    };
  };
  namespace new_game {
    //
  };
  namespace load_game {
    //
  };
  namespace options {
    extern const SDL_Color* f_def;
    extern const SDL_Color* f_hov;
    extern const SDL_Color* f_act;
    extern const SDL_Point* o_def;
    extern const SDL_Point* o_hov;
    extern const SDL_Point* o_act;
    extern const short num_controls;
    extern const short num_config;
    extern const short num_options;
    extern const char* const controls_list[];
    extern const Gamecon key_list[];
    extern const char* const config_list[];
    extern const short dx;
    extern const short dy;
    extern const short name_w;
    extern const short val_w;
    extern const short w;
    extern const short h;
    extern const short x;
    extern const short y;
    extern const short stroke_w;
  };
};

class CTitle : public CEvent {
  CTitle();

  short menu_kind;
  short pos;

public:

  static CTitle control;
  bool call_terminate;

public:
  void OnInit();

  void OnEvent(SDL_Event* Event);

  bool OnRender();

  void OnLoop();

  void OnCleanup();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

private:
  void eventTitle(const Gamecon& action);
  void eventNewGame(const Gamecon& action);
  void eventLoadGame(const Gamecon& action);
  void eventOptions(const Gamecon& action);

private:
  bool drawMainMenu();
  bool drawNewGame();
  bool drawLoadGame();
  bool drawOptions();

private:
  short getNumOptions();
};

#endif
