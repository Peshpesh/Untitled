#ifndef _C_STAGE_H_
#define _C_STAGE_H_

#include "CArea.h"
#include "CEntity.h"
#include "CScenery.h"
#include "CTransition.h"
#include "CCamera.h"
#include "CSound.h"

class CStage {
public:
  static CStage* stage;
  CStage();
  virtual ~CStage();
  virtual void OnInit();
  virtual void OnLoad();
  virtual void OnLoop();
  virtual void OnRender();
  virtual void OnCleanup();
};

#endif
