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

  static CSceneryEditor control;
  CSceneryEditor();

public:
  bool OnInit();
  void OnEvent(SDL_Event* Event);
  void OnTerminate();

private:



};

#endif
