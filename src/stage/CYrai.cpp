#include "CYrai.h"

CYrai CYrai::anch;

void CYrai::OnInit() {

}

void CYrai::OnLoad() {

}

void CYrai::OnLoop() {

}

void CYrai::OnRender() {
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

void CYrai::OnCleanup() {

}
