#ifndef _C_TERMINATE_H_
#define _C_TERMINATE_H_

#include "CEvent.h"
#include "CInterrupt.h"
#include "CSurface.h"
#include "CAsset.h"
#include "CFont.h"
#include "Define.h"

class CTerminate : public CEvent {
  CTerminate();

  bool confirm_termination;

public:
  static CTerminate control;

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point& m);

  bool willTerminate();

private:
  void OnLButtonDown(int mX, int mY);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
};

#endif
