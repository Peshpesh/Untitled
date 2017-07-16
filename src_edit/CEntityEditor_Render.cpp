#include "CEntityEditor.h"

bool CEntityEditor::OnRender(const SDL_Point* m) {
  bool hov = CInterrupt::isNone();

  if (!drawHitboxes()) return false;
  if (!drawWorkingEntity(m)) return false;
  if (!CAsset::drawAppFrame()) return false;
  if (!drawChGroup(m, hov)) return false;
  if (!drawChEntity(m, hov)) return false;
  if (!drawEntityList(m, hov)) return false;
  if (!drawPlaceRelPos(m, hov)) return false;
  if (!drawOpacEntity()) return false;
  if (!drawOpacHitbox()) return false;
  if (!drawSwitchView()) return false;

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
  using namespace entityEngine::misc::placeRelPos;

  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);

  int x_placeCell = placePos % numpos_x;
  int y_placeCell = placePos / numpos_x;

  if (y_placeCell >= numpos_y) return false;

  int disp_x = -(((x_placeCell * srcR.w) / 2) - (x_placeCell / 2));
  int disp_y = -(((y_placeCell * srcR.h) / 2) - (y_placeCell / 2));

  SDL_Rect dstR = {m->x + disp_x, m->y + disp_y, srcR.w, srcR.h};

  return CSurface::OnDraw(CEntity::getSrcTexture(group_ID), &srcR, &dstR);
}

bool CEntityEditor::drawHitboxes() {
  if (!showHitbox) return true;

  return true;
}

bool CEntityEditor::drawChGroup(const SDL_Point* m, const bool& hov) {
  using namespace entityEngine::buttons::chGroup;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CH_ENTGRP))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CEntityEditor::drawChEntity(const SDL_Point* m, const bool& hov) {
  using namespace entityEngine::buttons::chEntity;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CH_ENTITY))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CEntityEditor::drawEntityList(const SDL_Point* m, const bool& hov) {
  Font::FontControl.SetFont(FONT_MINI);
  std::string name;
  for (int i = 0; i < entityButtons.size(); i++) {
    if (!entityButtons[i].OnRender(m, (hov && i != entity_ID), (i == entity_ID))) return false;
    name = CEntityData::getEntityName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &entityButtons[i].dstR);
  }
  return true;
}

bool CEntityEditor::drawPlaceRelPos(const SDL_Point* m, const bool& hov) {
  using namespace entityEngine::buttons::placeRelPos;
  using namespace entityEngine::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    buttons[i].OnRender(m, hov, (placePos == i));
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
