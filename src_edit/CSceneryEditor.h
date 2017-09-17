#ifndef _C_SCENERYEDITOR_H_
#define _C_SCENERYEDITOR_H_

#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CSurface.h"

namespace sceneryEngine {
  //
};

class CSceneryEditor : public CEvent {
  CSceneryEditor();

public:
  static CSceneryEditor control;
  bool OnInit();
  bool drawBackground();
  bool drawForeground();
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);

private:

public:
  bool OnRender(const SDL_Point* m);

private:
  bool drawIntrpt(const SDL_Point* m);
};

#endif
