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

  // TESTING/DEBUGGING
  for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
    if (!CEntity::EntityList[i]) continue;
    CEntity::EntityList[i]->OnRenderHitbox();
  }
}
