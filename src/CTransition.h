#ifndef _C_TRANSITION_H_
#define _C_TRANSITION_H_

#include "CMode.h"
#include "CAsset.h"
#include "Define.h"

namespace location {
  enum {
    DEFAULT = 0,
    YRAI_HOME = 1,
    YRAI = 2,
    YRAI_OUTSKIRTS = 3,
  };
  const short num = 4;
  const char* const abbrname[] = {
    "default",
    "yraihome",
    "yrai",
    "yraiout",
  };
  const char* const fullname[] = {
    "Debug Area",
    "Home",
    "Yrai",
    "Yrai -- Outskirts",
  };
};

class CTransition {
  CTransition();

private:
  int fadeout_timer;
  int fadein_timer;
  int delay_timer;
  int last_time;
  app_module mode;
  bool switch_mode;

public:
  int locationID;
  int X;
  int Y;
  bool activated;
  SDL_Color color;

public:
  static CTransition control;

  void setColor(const SDL_Color& color);
  void reqTrans(const int& loc, const int &X, const int &Y);
  void reqMode(const app_module& mode);
  bool isActive();
  app_module getMode();

  void OnLoop();

  bool OnRender();

private:
  bool wipeout();
  bool blank();
  bool wipein();
  void changeMode();
};

#endif
