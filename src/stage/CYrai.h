#ifndef _C_STAGE_YRAI_
#define _C_STAGE_YRAI_

#include "CStage.h"
#include "../CGamedata.h"
#include "../CHUD.h"
#include "../CArea.h"
#include "../CEntity.h"
#include "../CScenery.h"
#include "../CTransition.h"
#include "../CCamera.h"
#include "../CInterrupt.h"
#include "../CSound.h"
#include "../CHero.h"

class CYrai : public CStage {
  CYrai():data(&CGamedata::control.data_yrai),rhighid(&CGamedata::control.data_rhighid){};
public:
  static CYrai anch;
private:
  CYraiData* const data;
  const CRhighidData* const rhighid;
public:
  void OnInit();
  void OnLoad();
  void OnLoop();
  void OnRender();
  void OnCleanup();
};

#endif
