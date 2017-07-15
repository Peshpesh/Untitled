#include "CEntityEditor.h"

bool CEntityEditor::OnRender(const SDL_Point* m) {
  if (!drawHitboxes()) return false;
  if (!drawWorkingEntity(m)) return false;
  if (!CAsset::drawAppFrame()) return false;
  if (!drawChGroup(m)) return false;
  if (!drawChEntity(m)) return false;
  if (!drawEntityList(m)) return false;
  if (!drawOpacEntity()) return false;
  if (!drawOpacHitbox()) return false;
  if (!drawSwitchView()) return false;

  // using namespace entityEngine::buttons::placeRelPos;
  //
  // for (int i = 0; i < 9; i++) {
  //   buttons[i].OnRender(false);
  // }

  return true;
}

bool CEntityEditor::drawEntities() {
  if (!showEntity) return true;

  for (int i = 0; i < CEntity::entityList.size(); i++) {
    if (!CEntity::entityList[i].OnRender()) {
      CInform::InfoControl.pushInform("Problem rendering entity");
      return false;
    }
  }
  return true;
}

bool CEntityEditor::drawWorkingEntity(const SDL_Point* m) {
  if (!showWorkEntity) return true;

  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  return CSurface::OnDraw(CEntity::getSrcTexture(group_ID), &srcR, m);
}

bool CEntityEditor::drawHitboxes() {
  if (!showHitbox) return true;

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

bool CEntityEditor::drawEntityList(const SDL_Point* m) {
  Font::FontControl.SetFont(FONT_MINI);
  std::string name;
  for (int i = 0; i < entityButtons.size(); i++) {
    if (!entityButtons[i].OnRender(m, (i != entity_ID), (i == entity_ID))) return false;
    name = CEntityData::getEntityName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &entityButtons[i].dstR);
  }
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

bool CEntityEditor::drawSwitchView() {
  using namespace entityEngine::switches;
  using namespace entityEngine::switches::view;

  const bool flags[] = {
    showEntity,
    showHitbox,
    showWorkEntity,
    showWorkHitbox
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (!buttons[i].OnRender(flags[i])) return false;

    const SDL_Point tPos = {buttons[i].dstR.x + lab_x_offset, buttons[i].dstR.y + lab_y_offset};
    Font::Write(FONT_MINI, labels[i], &tPos);
  }
  return true;
}
