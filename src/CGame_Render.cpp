#include "CGame.h"

void CGame::OnRender() {
  // Draw background scenery
  int scn_i = CScenery::drawBackground();

  CArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);

	// Render entities
	for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
		if (!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnRender();
	}

  CArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);

  // Draw foreground scenery
  CScenery::drawForeground(scn_i);

  // Draw interruptions last
  drawIntrpt();

  // TESTING/DEBUGGING
  for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
    if (!CEntity::EntityList[i]) continue;
    CEntity::EntityList[i]->OnRenderHitbox();
  }
}

void CGame::drawIntrpt() {
  if (!CInterrupt::isNone()) {
    if (CInterrupt::isFlagOn(INTRPT_PAUSE)) {
      CPause::control.OnRender(); return;
    }
    if (CInterrupt::isFlagOn(INTRPT_VIEW_MAP)) {
      CMapModel::control.OnRender(); return;
    }
    if (CInterrupt::isFlagOn(INTRPT_INVENTORY)) {
      CInventory::control.OnRender(); return;
    }
  }
}
