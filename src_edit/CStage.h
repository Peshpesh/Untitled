#ifndef _C_STAGE_H_
#define _C_STAGE_H_

#include "CEditMap.h"
#include "CPlanEditor.h"
#include "CEntityEditor.h"
#include "CSceneryEditor.h"
#include "CArea.h"
#include "CScenery.h"
#include "CSimulate.h"
#include "CCamera.h"
#include "COptions.h"
#include "CModule.h"
#include "CEvent.h"
#include <string>

class CStage {
  CStage();

public:
  static CStage control;
  bool planview;
  std::string name;

  void OnEvent(SDL_Event* Event);
  void OnEventPlatform(SDL_Event* Event);
  void OnEventPlanview(SDL_Event* Event);

  void OnRender(const SDL_Point& m);
  void OnRenderPlatform(const SDL_Point& m);
  void OnRenderPlanview(const SDL_Point& m);
};

#endif
