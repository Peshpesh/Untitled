#include "CEntityEditor.h"

bool CEntityEditor::OnRender(const SDL_Point* m) {
  if (!drawHitboxes()) return false;
  if (!drawWorkingEntity(m)) return false;
  if (!CAsset::drawAppFrame()) return false;

  return true;
}

bool CEntityEditor::drawEntities() {
  for (int i = 0; i < CEntity::entityList.size(); i++) {
    if (!CEntity::entityList[i].OnRender()) {
      CInform::InfoControl.pushInform("Problem rendering entity");
      return false;
    }
  }

  return true;
}

bool CEntityEditor::drawWorkingEntity(const SDL_Point* m) {
  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  return CSurface::OnDraw(CEntity::getSrcTexture(group_ID), &srcR, m);
}

bool CEntityEditor::drawHitboxes() {
  return true;
}
