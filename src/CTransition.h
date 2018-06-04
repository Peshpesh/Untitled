#ifndef _C_TRANSITION_H_
#define _C_TRANSITION_H_

#include "CMode.h"
#include "CAsset.h"
#include "CLocation.h"
#include "Define.h"

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
  void reqReset();
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
