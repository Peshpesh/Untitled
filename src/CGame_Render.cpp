#include "CGame.h"

void CGame::OnRender() {
  // draw stage area, entities, scenery, etc.
  CStage::stage->OnRender();

  // draw heads-up display
  CHud::control.OnRender();

  // draw interruptions last
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
      CMapModel::control.OnRender(CHero::Hero.X, CHero::Hero.Y);
      return;
    }
    if (CInterrupt::isFlagOn(INTRPT_INVENTORY)) {
      CInventory::control.OnRender(); return;
    }
  }
}
