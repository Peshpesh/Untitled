#include "CGame.h"

void CGame::OnRender() {
  // draw stage area, entities, scenery, etc.
  CStage::stage->OnRender();

  // draw dialogue
  CDialogue::control.OnRender();

  // draw interruptions last
  drawIntrpt();

  // TESTING/DEBUGGING
  for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
    if (!CEntity::EntityList[i]) continue;
    // CEntity::EntityList[i]->OnRenderHitbox();
  }
  int cam_x_min, cam_y_min, cam_x_max, cam_y_max;
  CCamera::CameraControl.GetLimits(cam_x_min, cam_y_min, cam_x_max, cam_y_max);
  std::string lims_str    = CUtil::intToStr(cam_x_min) + ". " + CUtil::intToStr(cam_y_min) + ". "
                          + CUtil::intToStr(cam_x_max) + ". " + CUtil::intToStr(cam_y_max);
  const SDL_Point lims_pos = {200,1};
  CType::Write(FONT_MINI, lims_str.c_str(), lims_pos, &rgb::white);
}

void CGame::drawIntrpt() {
  if (!CInterrupt::isNone()) {
    if (CInterrupt::isFlagOn(INTRPT_PAUSE)) {
      CPause::control.OnRender(); return;
    }
    if (CInterrupt::isFlagOn(INTRPT_VIEW_MAP)) {
      CMapModel::control.OnRender(CHero::Hero.X, CHero::Hero.Y);
      return;
    }
    if (CInterrupt::isFlagOn(INTRPT_INVENTORY)) {
      CInventory::control.OnRender(); return;
    }
  }
}
