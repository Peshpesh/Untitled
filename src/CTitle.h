#ifndef _C_TITLE_H_
#define _C_TITLE_H_

#include "CMode.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "CUtil.h"
#include "CSound.h"

#include "CControls.h"
#include "CConfig.h"

#include "CGameIO.h"
#include "CTransition.h"

namespace Title {
  extern const SDL_Color* f_def;
  extern const SDL_Color* f_hov;
  extern const SDL_Color* f_lock;
  extern const SDL_Point* o_def;
  extern const SDL_Point* o_hov;
  extern const SDL_Point* o_lock;
  extern const short num_options;
  extern const short opt_w;
  extern const short opt_h;
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
  namespace pick_game {
    namespace slot {
      extern const short num;
      extern const short w;
      extern const short h;
      extern const SDL_Point diff_pos;
      extern const SDL_Point time_pos;
    };
    extern const SDL_Color* f_def;
    extern const SDL_Color* f_hov;
    extern const SDL_Color* f_lock;
    extern const SDL_Point* o_def;
    extern const SDL_Point* o_hov;
    extern const SDL_Point* o_lock;
    extern const short num_other;
    extern const short num_options;
    extern const char* const other_list[];
    extern const char* const diff_list[];
    extern const short opt_w;
    extern const short opt_h;
    extern const short dx;
    extern const short dy;
    extern const short w;
    extern const short h;
    extern const short x;
    extern const short y;
    extern const short stroke_w;
    extern const char* const empty_text;
    namespace difficulty {
      extern const SDL_Color* f_def;
      extern const SDL_Color* f_hov;
      extern const short num;
      extern const short opt_w;
      extern const short opt_h;
      extern const short info_w;
      extern const short info_h;
      extern const short dx;
      extern const short dy;
      extern const short w;
      extern const short h;
      extern const short x;
      extern const short y;
      extern const Difficulty d_list[];
      extern const char* const list[];
      extern const char* const info[];
      extern const SDL_Point* o_diff[];
      extern const SDL_Point* h_diff[];
      extern const short stroke_w;
    };
    namespace overwrite {
      extern const SDL_Color* f_col;
      extern const SDL_Point* o_col;
      extern const short w;
      extern const short h;
      extern const short x;
      extern const short y;
      extern const short stroke_w;
      extern const char* const info;
    };
  };
  namespace options {
    extern const SDL_Color* f_def;
    extern const SDL_Color* f_hov;
    extern const SDL_Color* f_act;
    extern const SDL_Point* o_def;
    extern const SDL_Point* o_hov;
    extern const SDL_Point* o_act;
    extern const SDL_Point* fill_col;
    extern const short num_controls;
    extern const short num_config;
    extern const short num_options;
    extern const char* const controls_text[];
    extern const Gamecon controls_list[];
    extern const char* const config_text[];
    extern const Configflag config_list[];
    extern const short dx;
    extern const short dy;
    extern const short name_w;
    extern const short val_w;
    extern const short w;
    extern const short h;
    extern const short x;
    extern const short y_control;
    extern const short y_config;
    extern const short stroke_w;
  };
};

class CTitle : public CEvent {
  CTitle();

  short menu_kind;
  short pos;
  bool sel_difficulty;
  short difficulty;

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
  bool handleDifficulty(const Gamecon& action);
  bool handleNewGame();
  bool handleLoadGame();

private:
  bool drawMainMenu();
  bool drawNewGame();
  bool drawLoadGame();
  bool drawOptions();

private:
  bool drawGameSlot(const CGameinfo& info, const SDL_Rect& slot);
  bool drawDifficulty();
  bool drawOverwriteWarn(const short& slot);
  bool drawGameInfo();
  bool drawControls();
  bool drawConfig();

private:
  void returnToMain();
  short getNumOptions();
};

#endif
