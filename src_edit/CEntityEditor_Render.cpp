#include "CEntityEditor.h"

bool CEntityEditor::OnRender(const SDL_Point* m) {
  if (CInterrupt::isNone()) {
    if (!drawWorkingEntity(m)) return false;
    if (!drawWorkingHitbox(m)) return false;
  }
  return true;
}

bool CEntityEditor::OnRenderSettings(const SDL_Point* m) {
  bool no_intrpt = CInterrupt::isNone();
  if (!drawChEntity(m, no_intrpt)) return false;
  if (!drawEditHitbox(m, no_intrpt)) return false;
  if (!drawEntityList(m, no_intrpt)) return false;
  if (!drawPlaceRelPos(m, no_intrpt)) return false;
  if (!drawOpacEntity()) return false;
  if (!drawOpacHitbox()) return false;
  if (!drawSwitchView()) return false;
  if (!drawSwitchPlace()) return false;

  if (!no_intrpt) {
    if (!drawIntrpt(m)) return false;
  }

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

  if (!drawHitboxes()) {
    CInform::InfoControl.pushInform("Problem rendering hitbox");
    return false;
  }

  return true;
}

bool CEntityEditor::drawWorkingEntity(const SDL_Point* m) {
  if (!showWorkEntity) return true;

  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  SDL_Rect hitR = CEntityData::getHitboxDims(group_ID, entity_ID);

  int X = place_hitbox ? m->x - hitR.x : m->x;
  int Y = place_hitbox ? m->y - hitR.y : m->y;

  getPosDisplace(X, Y, m, place_hitbox ? hitR : srcR);
  SDL_Rect dstR = {X, Y, srcR.w, srcR.h};

  return CSurface::OnDraw(CEntity::getSrcTexture(group_ID), &srcR, &dstR);
}

bool CEntityEditor::drawWorkingHitbox(const SDL_Point* m) {
  if (!showWorkHitbox) return true;

  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  SDL_Rect hitR = CEntityData::getHitboxDims(group_ID, entity_ID);

  int X = place_hitbox ? m->x : m->x + hitR.x;
  int Y = place_hitbox ? m->y : m->y + hitR.y;

  getPosDisplace(X, Y, m, place_hitbox ? hitR : srcR);
  SDL_Rect dstR = {X, Y, hitR.w, hitR.h};

  CAsset::paletteAlpha(hitbox_alpha);
  bool retval = CAsset::drawBox(&dstR, &palette::green);
  CAsset::paletteAlpha(MAX_RGBA);
  return retval;
}

bool CEntityEditor::drawHitboxes() {
  if (!showHitbox) return true;

  bool retval = true;
  CAsset::paletteAlpha(hitbox_alpha);

  for (int i = 0; i < CEntity::entityList.size(); i++) {
    if (!CEntity::entityList[i].OnRenderHitbox()) {
      CInform::InfoControl.pushInform("Problem rendering hitbox");
      retval = false;
      break;
    }
  }
  CAsset::paletteAlpha(MAX_RGBA);
  return retval;
}

bool CEntityEditor::drawChEntity(const SDL_Point* m, const bool& hov) {
  using namespace entityEngine::buttons::chEntity;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CHANGE_EN))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CEntityEditor::drawEditHitbox(const SDL_Point* m, const bool& hov) {
  using namespace entityEngine::buttons::editHitbox;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_MODIFY_HB))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CEntityEditor::drawEntityList(const SDL_Point* m, const bool& hov) {
  using namespace entityEngine::misc::entityButtons;
  std::string name;

  int i = list_page * max_buttons;
  while (i < entityButtons.size() && i < (list_page + 1) * max_buttons) {
    if (!entityButtons[i].OnRender(m, (hov && i != entity_ID), (i == entity_ID))) return false;
    name = CEntityData::getEntityName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &entityButtons[i].dstR);
    i++;
  }

  if (entityButtons.size() > max_buttons) {
    bool prev_option = list_page; // true if "previous" button is valid
    bool next_option = false;     // true if "next" button is valid

    // how many buttons remain?
    int butts_remain = entityButtons.size() - (list_page * max_buttons);
    if (butts_remain > max_buttons) {
      next_option = true;
    }
    CAsset::drawBoxFill(&prev_pg, prev_option ? (m && SDL_PointInRect(m, &prev_pg) ? hovCol : onCol) : offCol);
    CAsset::drawBoxFill(&curr_pg, offCol);
    CAsset::drawBoxFill(&next_pg, next_option ? (m && SDL_PointInRect(m, &next_pg) ? hovCol : onCol) : offCol);
    std::string page_str = Font::intToStr(list_page);
    Font::NewCenterWrite(page_str.c_str(), &curr_pg);
    Font::NewCenterWrite("$L$L", &prev_pg);
    Font::NewCenterWrite("$R$R", &next_pg);
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

bool CEntityEditor::drawSwitchPlace() {
  using namespace entityEngine::switches;
  using namespace entityEngine::switches::place;

  const bool flags[] = {
    place_hitbox,
    snap_tile
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (!buttons[i].OnRender(flags[i])) return false;

    const SDL_Point tPos = {buttons[i].dstR.x + lab_x_offset, buttons[i].dstR.y + lab_y_offset};
    Font::Write(FONT_MINI, labels[i], &tPos);
  }
  return true;
}

bool CEntityEditor::drawIntrpt(const SDL_Point* m)
{
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_EN)) {
    if (!CChangeEntity::Control.OnRender(m)) return false;
  }
  if (CInterrupt::isFlagOn(INTRPT_MODIFY_HB)) {
    if (!CHitboxEditor::Control.OnRender(m)) return false;
  }
  return true;
}
