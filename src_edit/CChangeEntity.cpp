#include "CChangeEntity.h"

CChangeEntity CChangeEntity::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(440, 320);
  const short subcanv_w         = canv.w / 3;
  const short but_w             = 120;
  const short but_h             = 11;
  const short grList_x          = canv.x + (subcanv_w - but_w) / 2;
  const short grList_y          = canv.y + 30;
  const short enList_x          = canv.x + subcanv_w + (subcanv_w - but_w) / 2;
  const short enList_y          = canv.y + 30;
  const short samp_sz           = 128;
  const SDL_Rect sampleCanv     = CAsset::getRect(canv.x + (2 * subcanv_w) + (subcanv_w - samp_sz) / 2,
                                                  canv.y + (canv.h - samp_sz) / 2,
                                                  samp_sz,
                                                  samp_sz);

  const SDL_Rect title_bar      = CAsset::getRect(canv.x, canv.y + 9, canv.w, 11);
  const SDL_Rect tbar_group     = CAsset::getRect(title_bar.x,                      title_bar.y, title_bar.w / 3, title_bar.h);
  const SDL_Rect tbar_entity    = CAsset::getRect(tbar_group.x  + title_bar.w / 3,  title_bar.y, title_bar.w / 3, title_bar.h);
  const SDL_Rect tbar_sample    = CAsset::getRect(tbar_entity.x + title_bar.w / 3,  title_bar.y, title_bar.w / 3, title_bar.h);
  const char* const titleGroup  = "Groups";
  const char* const titleEntity = "Group Entities";
  const char* const titleSample = "Sample";

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
  const SDL_Point* sampCanvCol  = &palette::dark_gray;
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
  // using namespace defs;

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
  if (!SDL_PointInRect(&m, &canv)) return;

  if (handleConfirm(&m)) return;
  if (handleCancel(&m)) return;
  if (handleGroup(&m)) return;
  if (handleEntity(&m)) return;
}

bool CChangeEntity::handleConfirm(const SDL_Point* m) {
  if (SDL_PointInRect(m, &okButton)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_EN);
    succ = true;
    entityButtons.clear();
    return true;
  }
  return false;
}

bool CChangeEntity::handleCancel(const SDL_Point* m) {
  if (SDL_PointInRect(m, &caButton)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_EN);
    succ = false;
    entityButtons.clear();
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
  CAsset::drawStrBox(&canv, b_sz, canvCol);

  if (!drawTitle()) return false;
  if (!drawGroupButtons(m)) return false;
  if (!drawEntityButtons(m)) return false;
  if (!drawSampleEntity(m)) return false;
  if (!drawConfirmButtons(m)) return false;

  return true;
}

bool CChangeEntity::drawTitle() {
  if (!CAsset::drawBoxFill(&title_bar, titleCol)) return false;
  Font::NewCenterWrite(titleGroup, &tbar_group, titletextCol);
  Font::NewCenterWrite(titleEntity, &tbar_entity, titletextCol);
  Font::NewCenterWrite(titleSample, &tbar_sample, titletextCol);
  return true;
}

bool CChangeEntity::drawGroupButtons(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < groupButtons.size(); i++) {
    const SDL_Point* col = (i == group_ID)  ?
                            activeCol : (SDL_PointInRect(m, &groupButtons[i]) ?
                            hovCol    : (CEntity::isGroupUsed(i) ?
                            usedCol   : idleCol));
    if (!CAsset::drawStrBox(&groupButtons[i], b_sz, col)) return false;
    name = CEntityData::getGroupName(i);
    Font::NewCenterWrite(name.c_str(), &groupButtons[i]);
  }
  return true;
}

bool CChangeEntity::drawEntityButtons(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < entityButtons.size(); i++) {
    const SDL_Point* col = (i == entity_ID) ?
                            activeCol : (SDL_PointInRect(m, &entityButtons[i]) ?
                            hovCol    : (CEntity::isEntityUsed(group_ID, i) ?
                            usedCol   : idleCol));
    if (!CAsset::drawStrBox(&entityButtons[i], b_sz, col)) return false;
    name = CEntityData::getEntityName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &entityButtons[i]);
  }
  return true;
}

bool CChangeEntity::drawConfirmButtons(const SDL_Point* m) {
  // using namespace defs;

  if (!CAsset::drawStrBox(&okButton, b_sz, SDL_PointInRect(m, &okButton) ? confirmCol : idleCol)) return false;
  if (!CAsset::drawStrBox(&caButton, b_sz, SDL_PointInRect(m, &caButton) ? confirmCol : idleCol)) return false;
  Font::NewCenterWrite(okText, &okButton);
  Font::NewCenterWrite(caText, &caButton);

  return true;
}

bool CChangeEntity::drawSampleEntity(const SDL_Point* m) {
  CAsset::drawBoxFill(&sampleCanv, sampCanvCol);

  SDL_Rect tRec = {enList_x, enList_y, but_w, entityButtons.size() * but_h};
  if (SDL_PointInRect(m, &tRec)) {
    for (int i = 0; i < entityButtons.size(); i++) {
      if (SDL_PointInRect(m, &entityButtons[i])) {
        tRec = CEntityData::getEntityDims(group_ID, i);
      }
    }
  }
  else {
    tRec = CEntityData::getEntityDims(group_ID, entity_ID);
  }
  if (tRec.w > samp_sz) tRec.w = samp_sz;
  if (tRec.h > samp_sz) tRec.h = samp_sz;

  const SDL_Point dstP = {sampleCanv.x, sampleCanv.y};

  return CSurface::OnDraw(Group_Tex, &tRec, &dstP);
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
  // using namespace defs;
  entityButtons.clear();
  for (int i = 0; i < CEntityData::getNumEntities(group_ID); i++) {
    entityButtons.push_back(CAsset::getRect(enList_x, enList_y + (i * but_h), but_w, but_h));
  }
  entity_ID = 0;
}
