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

public:
  static CTransition control;

  void reqTrans(const int& loc, const int &X, const int &Y);
  void reqMode(const app_module& mode);

  void OnLoop();

  bool OnRender();

private:
  bool fadeout();
  bool blank();
  bool fadein();
  void changeMode();
};

#endif
