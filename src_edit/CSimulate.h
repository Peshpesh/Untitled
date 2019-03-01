#ifndef _C_SIMULATE_H_
#define _C_SIMULATE_H_

#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"

enum simstate {INACTIVE, PLACE, ACTIVE, SUSPENDED};

namespace simulator {
  extern const char* const start_lab;
  extern const char* const reset_lab;
  extern const char* const suspend_lab;
  extern const char* const stop_lab;
  extern const short w_main;
  extern const short h_main;
  extern const short x_main;
  extern const short y_main;
  extern const SDL_Rect r_start;
  extern const SDL_Rect r_suspend;
  extern const SDL_Rect r_stop;
  extern const short bsiz;
  extern const SDL_Point* off_col;
  extern const SDL_Point* start_col;
  extern const SDL_Point* start_hcol;
  extern const SDL_Point* reset_col;
  extern const SDL_Point* reset_hcol;
  extern const SDL_Point* suspend_col;
  extern const SDL_Point* suspend_hcol;
  extern const SDL_Point* stop_col;
  extern const SDL_Point* stop_hcol;
}

class CSimulate : public CEvent {
  CSimulate();

public:
  static CSimulate control;

private:
  simstate status;

public:
  bool OnInit();
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);

private:
  bool handleInterr(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);
  bool handleStartSim(const SDL_Point* m);
  bool handleStopSim(const SDL_Point* m);

public:
  bool OnRender(const SDL_Point* m);

private:
  bool drawMain(const SDL_Point* m);
  bool drawIntrpt(const SDL_Point* m);

public:
  simstate getStatus();
  void stopSim();
};

#endif
