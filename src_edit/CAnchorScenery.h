#ifndef _C_ANCHORSCENERY_H_
#define _C_ANCHORSCENERY_H_

#include "CAsset.h"
#include "CFont.h"
#include "CCamera.h"
#include "CEvent.h"
#include "CInterrupt.h"
#include "CScenery.h"

class CAnchorScenery : public CEvent {
  CScenery* anchor;

public:
  double anch_x, anch_y, anch_z;
  int disp_x, disp_y;
  unsigned short layer;
  bool planview;

public:
  static CAnchorScenery Control;

  CAnchorScenery();

  void OnInit(const unsigned short& layer);

  void OnEvent(SDL_Event* Event);

  bool OnRender();

public:
  void advanceAnchor();
  double getRelX();
  double getRelY();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);

private:
  void handleGrabAnchor(const SDL_Point* m);
  void handleMakeAnchor(const SDL_Point* m);
};

#endif
