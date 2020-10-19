#include "CChangeScenery.h"

CChangeScenery CChangeScenery::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(440, 320);
  const short subcanv_w         = canv.w / 3;
  const short but_w             = 120;
  const short but_h             = 11;
  const short grList_x          = canv.x + (subcanv_w - but_w) / 2;
  const short grList_y          = canv.y + 30;
  const short scList_x          = canv.x + subcanv_w + (subcanv_w - but_w) / 2;
  const short scList_y          = canv.y + 30;
  const short samp_sz           = 128;
  const SDL_Rect sampleCanv     = CAsset::getRect(canv.x + (2 * subcanv_w) + (subcanv_w - samp_sz) / 2,
                                                  canv.y + (canv.h - samp_sz) / 2,
                                                  samp_sz,
                                                  samp_sz);
  const SDL_Rect sample_w       = CAsset::getRect(sampleCanv.x, sampleCanv.y + samp_sz, samp_sz, but_h);
  const SDL_Rect sample_h       = CAsset::getRect(sample_w.x, sample_w.y + but_h, samp_sz, but_h);

  const SDL_Rect title_bar      = CAsset::getRect(canv.x, canv.y + 9, canv.w, 11);
  const SDL_Rect tbar_group     = CAsset::getRect(title_bar.x,                      title_bar.y, title_bar.w / 3, title_bar.h);
  const SDL_Rect tbar_scenery    = CAsset::getRect(tbar_group.x  + title_bar.w / 3,  title_bar.y, title_bar.w / 3, title_bar.h);
  const SDL_Rect tbar_sample    = CAsset::getRect(tbar_scenery.x + title_bar.w / 3,  title_bar.y, title_bar.w / 3, title_bar.h);
  const char* const titleGroup  = "Groups";
  const char* const titleScenery  = "Group Scenery";
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

CChangeScenery::CChangeScenery() {
  Group_Tex   = NULL;
  succ        = false;
  group_ID    = 0;
  decor_ID    = 0;
}

void CChangeScenery::OnInit(const short& group_ID, const short& decor_ID) {
  this->group_ID  = group_ID;
  Group_Tex = CScenery::fetchTexture(group_ID);
  updateSceneryButtons();
  this->decor_ID = decor_ID;

  if (groupButtons.empty()) {
    for (int i = 0; i < CSceneryData::getNumGroups(); i++) {
      groupButtons.push_back(CAsset::getRect(grList_x, grList_y + (i * but_h), but_w, but_h));
    }
  }
}

void CChangeScenery::handleChanges(short& group_ID, short& decor_ID) {
  if (!succ) {
    if (!CScenery::isTextureLoaded(group_ID)) {
      CScenery::loadTexInfo(group_ID);
    }
    return;
  }
  group_ID  = this->group_ID;
  decor_ID = this->decor_ID;
  succ = false;
}

void CChangeScenery::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CChangeScenery::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: CInterrupt::removeFlag(INTRPT_CHANGE_SC); succ = true; break;
    case SDLK_ESCAPE: CInterrupt::removeFlag(INTRPT_CHANGE_SC); succ = false; break;
    default: break;
  }
}

void CChangeScenery::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (!SDL_PointInRect(&m, &canv)) return;

  if (handleConfirm(&m)) return;
  if (handleCancel(&m)) return;
  if (handleGroup(&m)) return;
  if (handleScenery(&m)) return;
}

bool CChangeScenery::handleConfirm(const SDL_Point* m) {
  if (SDL_PointInRect(m, &okButton)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_SC);
    succ = true;
    decorButtons.clear();
    return true;
  }
  return false;
}

bool CChangeScenery::handleCancel(const SDL_Point* m) {
  if (SDL_PointInRect(m, &caButton)) {
    CInterrupt::removeFlag(INTRPT_CHANGE_SC);
    succ = false;
    decorButtons.clear();
    return true;
  }
  return false;
}

bool CChangeScenery::handleGroup(const SDL_Point* m) {
  for (int i = 0; i < groupButtons.size(); i++) {
    if (i != group_ID && SDL_PointInRect(m, &groupButtons[i])) {
      group_ID = i;
      Group_Tex = updateTexture();
      updateSceneryButtons();
      return true;
    }
  }
  return false;
}

bool CChangeScenery::handleScenery(const SDL_Point* m) {
  for (int i = 0; i < decorButtons.size(); i++) {
    if (i != decor_ID && SDL_PointInRect(m, &decorButtons[i])) {
      decor_ID = i;
      return true;
    }
  }
  return false;
}

bool CChangeScenery::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  Font::FontControl.SetFont(FONT_MINI);
  CAsset::drawStrBox(&canv, b_sz, canvCol);

  if (!drawTitle()) return false;
  if (!drawGroupButtons(m)) return false;
  if (!drawSceneryButtons(m)) return false;
  if (!drawSampleScenery(m)) return false;
  if (!drawConfirmButtons(m)) return false;

  return true;
}

bool CChangeScenery::drawTitle() {
  if (!CAsset::drawBoxFill(&title_bar, titleCol)) return false;
  Font::NewCenterWrite(titleGroup, &tbar_group, titletextCol);
  Font::NewCenterWrite(titleScenery, &tbar_scenery, titletextCol);
  Font::NewCenterWrite(titleSample, &tbar_sample, titletextCol);
  return true;
}

bool CChangeScenery::drawGroupButtons(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < groupButtons.size(); i++) {
    const SDL_Point* col = (i == group_ID)  ?
                            activeCol : (SDL_PointInRect(m, &groupButtons[i]) ?
                            hovCol    : (CScenery::isGroupUsed(i) ?
                            usedCol   : idleCol));
    if (!CAsset::drawStrBox(&groupButtons[i], b_sz, col)) return false;
    name = CSceneryData::getGroupName(i);
    Font::NewCenterWrite(name.c_str(), &groupButtons[i]);
  }
  return true;
}

bool CChangeScenery::drawSceneryButtons(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < decorButtons.size(); i++) {
    const SDL_Point* col = (i == decor_ID) ?
                            activeCol : (SDL_PointInRect(m, &decorButtons[i]) ?
                            hovCol    : (CScenery::isSceneryUsed(group_ID, i) ?
                            usedCol   : idleCol));
    if (!CAsset::drawStrBox(&decorButtons[i], b_sz, col)) return false;
    name = CSceneryData::getDecorName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &decorButtons[i]);
  }
  return true;
}

bool CChangeScenery::drawConfirmButtons(const SDL_Point* m) {
  if (!CAsset::drawStrBox(&okButton, b_sz, SDL_PointInRect(m, &okButton) ? confirmCol : idleCol)) return false;
  if (!CAsset::drawStrBox(&caButton, b_sz, SDL_PointInRect(m, &caButton) ? confirmCol : idleCol)) return false;
  Font::NewCenterWrite(okText, &okButton);
  Font::NewCenterWrite(caText, &caButton);

  return true;
}

bool CChangeScenery::drawSampleScenery(const SDL_Point* m) {
  std::string dims = "";

  CAsset::drawBoxFill(&sampleCanv, sampCanvCol);

  SDL_Rect tRec = {scList_x, scList_y, but_w, decorButtons.size() * but_h};
  if (SDL_PointInRect(m, &tRec)) {
    for (int i = 0; i < decorButtons.size(); i++) {
      if (SDL_PointInRect(m, &decorButtons[i])) {
        tRec = CSceneryData::getDecorDims(group_ID, i);
      }
    }
  } else {
    tRec = CSceneryData::getDecorDims(group_ID, decor_ID);
  }

  dims = "Width - " + Font::intToStr(tRec.w); Font::NewCenterWrite(dims.c_str(), &sample_w);
  dims = "Height - " + Font::intToStr(tRec.h); Font::NewCenterWrite(dims.c_str(), &sample_h);

  // if (tRec.w > samp_sz) tRec.w = samp_sz;
  // if (tRec.h > samp_sz) tRec.h = samp_sz;

  int max_dim = (tRec.w > tRec.h) ? tRec.w : tRec.h;
  int samp_w = tRec.w;
  int samp_h = tRec.h;
  if (max_dim > samp_sz) {
    double reduce_frac = (double)(samp_sz) / (double)(max_dim);
    samp_w *= reduce_frac;
    samp_h *= reduce_frac;
  }

  const SDL_Rect dstR = {sampleCanv.x, sampleCanv.y, samp_w, samp_h};

  return CSurface::OnDraw(Group_Tex, &tRec, &dstR);
}

SDL_Texture* CChangeScenery::updateTexture() {
  CScenery::purgeStaleTextures();
  if (CScenery::isGroupUsed(group_ID)) {
    return CScenery::fetchTexture(group_ID);
  }
  else
  {
    return CScenery::loadTexInfo(group_ID);
  }
}

void CChangeScenery::updateSceneryButtons() {
  decorButtons.clear();
  for (int i = 0; i < CSceneryData::getNumDecor(group_ID); i++) {
    decorButtons.push_back(CAsset::getRect(scList_x, scList_y + (i * but_h), but_w, but_h));
  }
  decor_ID = 0;
}
