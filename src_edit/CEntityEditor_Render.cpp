#include "CEntityEditor.h"

bool CEntityEditor::OnRender(const SDL_Point* m) {
  if (!drawHitboxes()) return false;
  if (!drawWorkingEntity(m)) return false;
  if (!CAsset::drawAppFrame()) return false;
  if (!drawChGroup(m)) return false;
  if (!drawChEntity(m)) return false;
  if (!drawOpacEntity()) return false;
  if (!drawOpacHitbox()) return false;
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

bool CEntityEditor::drawChGroup(const SDL_Point* m) {
  using namespace entityEngine::buttons::chGroup;

  if (!button.OnRender(m, CInterrupt::isNone(), CInterrupt::isFlagOn(INTRPT_CH_ENTGRP))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CEntityEditor::drawChEntity(const SDL_Point* m) {
  using namespace entityEngine::buttons::chEntity;

  if (!button.OnRender(m, CInterrupt::isNone(), CInterrupt::isFlagOn(INTRPT_CH_ENTITY))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CEntityEditor::drawOpacEntity() {
  using namespace entityEngine::meters::opacEntity;
  return meter.OnRender((double)(entity_alpha) / MAX_RGBA, label);
}

bool CEntityEditor::drawOpacHitbox() {
  using namespace entityEngine::meters::opacHitbox;
  return meter.OnRender((double)(hitbox_alpha) / MAX_RGBA, label);
}
