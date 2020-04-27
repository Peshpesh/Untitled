#ifndef _C_PLANEDITOR_H_
#define _C_PLANEDITOR_H_

#include "CPlanArea.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
#include "CEntity.h"
#include "CScenery.h"
#include "CCamera.h"
#include "CChangeTile.h"
#include "CTileset.h"
#include "CInterrupt.h"
#include "CInform.h"
#include "CError.h"
#include "Define.h"

class CPlanEditor : public CEvent {
  CPlanEditor();

public:
  static CPlanEditor control;

  bool OnInit();

  void OnTerminate();

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point& mouse);

  void RenderMap();

private:
  void extendMap_R();
  void extendMap_L();
  void extendMap_D();
  void extendMap_U();
  void removeMap_R();
  void removeMap_L();
  void removeMap_D();
  void removeMap_U();
};

#endif
