#ifndef _C_STAGE_DEBUG_
#define _C_STAGE_DEBUG_

#include "CStage.h"
#include "../CArea.h"
#include "../CEntityIO.h"
#include "../CSceneryIO.h"
#include "../CTransition.h"
#include "../CCamera.h"
#include "../CInterrupt.h"
#include "../CHero.h"

class CDebug_Stage : public CStage {
  CDebug_Stage();
public:
  static CDebug_Stage anch;

public:
  void OnInit();
  void OnLoad();
  void OnLoop();
  void OnRender();
  void OnCleanup();
};

#endif
