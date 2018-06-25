#ifndef _C_STAGE_YRAI_
#define _C_STAGE_YRAI_

#include "CStage.h"
#include "../CArea.h"
#include "../CEntity.h"
#include "../CScenery.h"
#include "../CTransition.h"
#include "../CCamera.h"
#include "../CInterrupt.h"
#include "../CSound.h"
#include "../CHero.h"

class CYrai : public CStage {
  CYrai();
public:
  static CYrai anch;
  
public:
  void OnInit();
  void OnLoad();
  void OnLoop();
  void OnRender();
  void OnCleanup();
};

#endif
