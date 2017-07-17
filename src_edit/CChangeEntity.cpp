#include "CChangeEntity.h"

CChangeEntity CChangeEntity::Control;

namespace defs {
  const SDL_Rect canv           = CAsset::getWinCentRect(440, 320);
  const short but_w             = 90;
  const short but_h             = 20;
  const short grList_x          = canv.x + ((canv.w / 2) - but_w) / 2;
  const short grList_y          = canv.y + 30;
  const short enList_x          = canv.x + (canv.w / 2) + ((canv.w / 2) - but_w) / 2;
  const short enList_y          = canv.y + 30;

  const SDL_Rect title_bar      = CAsset::getRect(canv.x, canv.y + 9, canv.w, 11);
  const SDL_Rect tbar_group     = CAsset::getRect(title_bar.x,                    title_bar.y, title_bar.w / 2, title_bar.h);
  const SDL_Rect tbar_entity    = CAsset::getRect(title_bar.x + title_bar.w / 2,  title_bar.y, title_bar.w / 2, title_bar.h);
  const char* const titleGroup  = "Groups";
  const char* const titleEntity = "Group Entities";

  const short d_spac            = 30;
  const short d_y               = (canv.y + canv.h) - 30;
  const short d_w               = 60;
  const short d_h               = 15;
  const SDL_Rect okButton       = CAsset::getRect(canv.x + (canv.w / 2) - (d_w + d_spac), d_y, d_w, d_h);
  const SDL_Rect caButton       = CAsset::getRect(canv.x + (canv.w / 2) + (d_spac),       d_y, d_w, d_h);
  const char* const okText      = "Confirm";
  const char* const caText      = "Cancel";

  const short b_sz              = 2;
  const SDL_Point* canvCol      = &palette::dark_cyan;
  const SDL_Point* idleCol      = &palette::silver;
  const SDL_Point* usedCol      = &palette::light_green;
  const SDL_Point* activeCol    = &palette::magenta;
  const SDL_Point* hovCol       = &palette::light_yellow;
  const SDL_Point* confirmCol   = &palette::green;
  const SDL_Point* titleCol     = &palette::black;
  const SDL_Color* titletextCol = &rgb::white;
}

CChangeEntity::CChangeEntity() {
  Group_Tex   = NULL;
  succ        = false;
  group_ID    = 0;
  entity_ID   = 0;
}

void CChangeEntity::OnInit(const short& group_ID, const short& entity_ID) {
  using namespace defs;

  this->group_ID  = group_ID;
  Group_Tex = CEntity::getSrcTexture(group_ID);
  updateEntityButtons();
  this->entity_ID = entity_ID;

  if (groupButtons.empty()) {
    for (int i = 0; i < CEntityData::getNumGroups(); i++) {
      groupButtons.push_back(CAsset::getRect(grList_x, grList_y + (i * but_h), but_w, but_h));
    }
  }
}

void CChangeEntity::handleChanges(short& group_ID, short& entity_ID) {
  if (!succ) {
    if (!CEntity::isTextureLoaded(group_ID)) {
      CEntity::loadTexInfo(group_ID);
    }
    return;
  }
  group_ID  = this->group_ID;
  entity_ID = this->entity_ID;
  succ = false;
}

void CChangeEntity::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CChangeEntity::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: CInterrupt::removeFlag(INTRPT_CHANGE_EN); succ = true; break;
    case SDLK_ESCAPE: CInterrupt::removeFlag(INTRPT_CHANGE_EN); succ = false; break;
    default: break;
  }
}

void CChangeEntity::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (!SDL_PointInRect(&m, &defs::canv)) return;

  if (handleConfirm(&m)) return;
  if (handleCancel(&m)) return;
  if (handleGroup(&m)) return;
  if (handleEntity(&m)) return;
}

bool CChangeEntity::handleConfirm(const SDL_Point* m) {
  if (SDL_PointInRect(m, &defs::okButton)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_EN);
    succ = true;
    return true;
  }
  return false;
}

bool CChangeEntity::handleCancel(const SDL_Point* m) {
  if (SDL_PointInRect(m, &defs::caButton)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_EN);
    succ = false;
    return true;
  }
  return false;
}

bool CChangeEntity::handleGroup(const SDL_Point* m) {
  for (int i = 0; i < groupButtons.size(); i++) {
    if (i != group_ID && SDL_PointInRect(m, &groupButtons[i])) {
      group_ID = i;
      Group_Tex = updateTexture();
      updateEntityButtons();
      return true;
    }
  }
  return false;
}

bool CChangeEntity::handleEntity(const SDL_Point* m) {
  for (int i = 0; i < entityButtons.size(); i++) {
    if (i != entity_ID && SDL_PointInRect(m, &entityButtons[i])) {
      entity_ID = i;
      return true;
    }
  }
  return false;
}

bool CChangeEntity::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  Font::FontControl.SetFont(FONT_MINI);
  CAsset::drawStrBox(&defs::canv, defs::b_sz, defs::canvCol);

  if (!drawGroupButtons(m)) return false;
  if (!drawEntityButtons(m)) return false;
  if (!drawConfirmButtons(m)) return false;

  CAsset::drawBoxFill(&defs::title_bar, defs::titleCol);
  Font::NewCenterWrite(defs::titleGroup, &defs::tbar_group, defs::titletextCol);
  Font::NewCenterWrite(defs::titleEntity, &defs::tbar_entity, defs::titletextCol);
  return true;
}

bool CChangeEntity::drawGroupButtons(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < groupButtons.size(); i++) {
    const SDL_Point* col = (i == group_ID)  ?
                            defs::activeCol : (SDL_PointInRect(m, &groupButtons[i]) ?
                            defs::hovCol    : (CEntity::isGroupUsed(i) ?
                            defs::usedCol   : defs::idleCol));
    if (!CAsset::drawStrBox(&groupButtons[i], defs::b_sz, col)) return false;
    name = CEntityData::getGroupName(i);
    Font::NewCenterWrite(name.c_str(), &groupButtons[i]);
  }
  return true;
}

bool CChangeEntity::drawEntityButtons(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < entityButtons.size(); i++) {
    const SDL_Point* col = (i == entity_ID) ?
                            defs::activeCol : (SDL_PointInRect(m, &entityButtons[i]) ?
                            defs::hovCol    : (CEntity::isEntityUsed(group_ID, i) ?
                            defs::usedCol   : defs::idleCol));
    if (!CAsset::drawStrBox(&entityButtons[i], defs::b_sz, col)) return false;
    name = CEntityData::getEntityName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &entityButtons[i]);
  }
  return true;
}

bool CChangeEntity::drawConfirmButtons(const SDL_Point* m) {
  using namespace defs;

  if (!CAsset::drawStrBox(&okButton, b_sz, SDL_PointInRect(m, &okButton) ? confirmCol : idleCol)) return false;
  if (!CAsset::drawStrBox(&caButton, b_sz, SDL_PointInRect(m, &caButton) ? confirmCol : idleCol)) return false;
  Font::NewCenterWrite(okText, &okButton);
  Font::NewCenterWrite(caText, &caButton);

  return true;
}

SDL_Texture* CChangeEntity::updateTexture() {
  CEntity::purgeStaleTextures();
  if (CEntity::isGroupUsed(group_ID)) {
    return CEntity::getSrcTexture(group_ID);
  }
  else
  {
    return CEntity::loadTexInfo(group_ID);
  }
}

void CChangeEntity::updateEntityButtons() {
  using namespace defs;
  entityButtons.clear();
  for (int i = 0; i < CEntityData::getNumEntities(group_ID); i++) {
    entityButtons.push_back(CAsset::getRect(enList_x, enList_y + (i * but_h), but_w, but_h));
  }
  entity_ID = 0;
}
