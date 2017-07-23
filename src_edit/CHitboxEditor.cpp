#include "CHitboxEditor.h"

CHitboxEditor CHitboxEditor::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(440, 320);
  const short subcanv_w         = canv.w / 3;
  const short but_w             = 120;
  const short but_h             = 11;
  const short b_sz              = 2;
  const short enList_x          = canv.x + (subcanv_w - but_w) / 2;
  const short enList_y          = canv.y + 30;
  const SDL_Point* canvCol      = &palette::dark_violet;
}

CHitboxEditor::CHitboxEditor() {
  group_ID = 0;
  entity_ID = 0;
}

bool CHitboxEditor::OnInit(const int& group, const int& entity) {
  int N = CEntityData::getNumEntities(group);
  if (N <= 0) return false;

  if (!hitboxList.empty()) hitboxList.clear();

  for (int i = 0; i < N; i++) {
    SDL_Rect hitR = CEntityData::getHitboxDims(group, i);
    hitboxList.push_back(hitR);
  }
  group_ID = group;
  entity_ID = entity;
  return true;
}

void CHitboxEditor::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CHitboxEditor::OnLButtonDown(int mX, int mY) {

}

void CHitboxEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: {
      CEntityData::save_phb(group_ID);
      CInterrupt::removeFlag(INTRPT_MODIFY_HB);
      break;
    }
    case SDLK_ESCAPE: {
      CInterrupt::removeFlag(INTRPT_MODIFY_HB);
      break;
    }
    default: break;
  }
}

bool CHitboxEditor::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  Font::FontControl.SetFont(FONT_MINI);
  CAsset::drawStrBox(&canv, b_sz, canvCol);

  return true;
}
