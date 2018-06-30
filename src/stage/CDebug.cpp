#include "CDebug.h"

CDebug_Stage CDebug_Stage::anch;

CDebug_Stage::CDebug_Stage() {

}

void CDebug_Stage::OnInit() {

}

void CDebug_Stage::OnLoad() {
	if (!CArea::control.Load(location::DEFAULT)) {
		// ERROR LOADING AREA
	}
	if (!CEntityIO::Load(location::DEFAULT)) {
		// ERROR LOADING ENTITIES
	}
	if (!CSceneryIO::Load(location::DEFAULT)) {
		// ERROR LOADING SCENERY
	}
  CTransition::control.activated = false;
}

void CDebug_Stage::OnLoop() {
  if (!CInterrupt::isSuspended()) {
    for (int i = 0; i < CEntity::EntityList.size(); i++) {
      if (!CEntity::EntityList[i]) continue;
      CEntity::EntityList[i]->OnLoop();
    }

  }
}

void CDebug_Stage::OnRender() {
  int scn_i = CScenery::drawBackground();

  CArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);

	for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
		if (!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnRender();
	}

  CArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);

  CScenery::drawForeground(scn_i);

  CHud::control.OnRender();
}

void CDebug_Stage::OnCleanup() {

}
