#ifndef _C_SIMULATE_H_
#define _C_SIMULATE_H_

#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"

namespace simulator {
  extern const char* const start_lab;
  extern const char* const reset_lab;
  extern const char* const suspend_lab;
  extern const char* const stop_lab;
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

public:
  bool OnInit();
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);

  bool handleInterr(SDL_Event* Event);

public:
  bool OnRender(const SDL_Point* m);

private:
  bool drawIntrpt(const SDL_Point* m);
};

#endif
