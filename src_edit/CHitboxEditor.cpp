#include "CHitboxEditor.h"

CHitboxEditor CHitboxEditor::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(600, 440);
  const short subcanv_w         = canv.w / 4;
  const short but_w             = 120;
  const short but_h             = 11;
  const short b_sz              = 2;
  const short hitbox_sz         = 2;
  const short enList_x          = canv.x + (subcanv_w - but_w) / 2;
  const short enList_y          = canv.y + 30;
  const SDL_Point* canvCol      = &palette::dark_violet;
  const SDL_Point* enCanvCol    = &palette::white;
  const SDL_Point* hitboxCol    = &palette::light_red;
  const SDL_Point* offCol       = &palette::silver;
  const SDL_Point* onCol        = &palette::dark_cyan;
  const SDL_Point* editCol      = &palette::light_violet;
  const SDL_Point* hovCol       = &palette::light_cyan;
  enum {
    ANCHOR_LEFT     = 0x01,
    ANCHOR_RIGHT    = 0x02,
    ANCHOR_TOP      = 0x04,
    ANCHOR_BOTTOM   = 0x08,
    ANCHOR_CENTER_X = 0x10,
    ANCHOR_CENTER_Y = 0x20,
  };
}
namespace dial {
  const short label_w = 45;
  const short label_h = 11;
  const short label_y = canv.y + canv.h - 30;
  const short button_sz = 11;
  const SDL_Point* labCol   = &palette::black;
  const SDL_Point* dialCol  = &palette::dark_gray;
  const SDL_Point* mnCol    = &palette::dark_red;
  const SDL_Point* plCol    = &palette::dark_blue;
  const SDL_Point* mnHovCol = &palette::light_red;
  const SDL_Point* plHovCol = &palette::light_blue;
  const SDL_Color* textCol  = &rgb::white;
  const SDL_Rect labels[] = {
    {275, label_y, label_w, label_h},
    {325, label_y, label_w, label_h},
    {375, label_y, label_w, label_h},
    {425, label_y, label_w, label_h}
  };
  const SDL_Rect dials[] = {
    {275, label_y + label_h, label_w, label_h},
    {325, label_y + label_h, label_w, label_h},
    {375, label_y + label_h, label_w, label_h},
    {425, label_y + label_h, label_w, label_h}
  };
  const char* const info[] = {
    "X Off",
    "Y Off",
    "Width",
    "Height"
  };
}


CHitboxEditor::CHitboxEditor() {
  Group_Tex = NULL;
  group_ID = 0;
  entity_ID = 0;
  anchors = 0;
}

bool CHitboxEditor::OnInit(const int& group, const int& entity) {
  int N = CEntityData::getNumEntities(group);
  if (N <= 0) return false;

  if (!hitboxList.empty()) hitboxList.clear();
  if (!entityList.empty()) entityList.clear();

  for (int i = 0; i < N; i++) {
    SDL_Rect hitR = CEntityData::getHitboxDims(group, i);
    hitboxList.push_back(hitR);
  }

  for (int i = 0; i < CEntityData::getNumEntities(group); i++) {
    entityList.push_back(CAsset::getRect(enList_x, enList_y + (i * but_h), but_w, but_h));
  }

  Group_Tex = CEntity::getSrcTexture(group);
  group_ID = group;
  entity_ID = entity;
  anchors = 0;
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
      hitboxList.clear();
      break;
    }
    case SDLK_ESCAPE: {
      CInterrupt::removeFlag(INTRPT_MODIFY_HB);
      hitboxList.clear();
      break;
    }
    default: break;
  }
}

bool CHitboxEditor::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  Font::FontControl.SetFont(FONT_MINI);
  CAsset::drawStrBox(&canv, b_sz, canvCol);

  if (!drawList(m)) return false;
  if (!drawEntity()) return false;
  if (!drawHitbox()) return false;
  if (!drawDials(m)) return false;

  return true;
}

bool CHitboxEditor::drawList(const SDL_Point* m) {
  std::string name;
  for (int i = 0; i < entityList.size(); i++) {
    const SDL_Point* col = (i == entity_ID) ?
                            onCol     : (SDL_PointInRect(m, &entityList[i]) ?
                            hovCol    : (CAsset::compRect(hitboxList[i], CEntityData::getHitboxDims(group_ID, i)) ?
                            offCol    : editCol));
    if (!CAsset::drawStrBox(&entityList[i], b_sz, col)) return false;
    name = CEntityData::getEntityName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &entityList[i]);
  }
  return true;
}

bool CHitboxEditor::drawEntity() {
  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  SDL_Rect dstR = CAsset::getRect(0, 0, srcR.w, srcR.h);

  CAsset::drawBoxFill(&dstR, enCanvCol);
  return CSurface::OnDraw(Group_Tex, &srcR, &dstR);
}

bool CHitboxEditor::drawHitbox() {
  SDL_Rect dstR = CAsset::getRect(0, 0, hitboxList[entity_ID].w, hitboxList[entity_ID].h);
  return CAsset::drawBox(&dstR, hitboxCol, hitbox_sz);
}

bool CHitboxEditor::drawDials(const SDL_Point* m) {
  using namespace dial;

  std::string vals[] = {
    Font::intToStr(hitboxList[entity_ID].x),
    Font::intToStr(hitboxList[entity_ID].y),
    Font::intToStr(hitboxList[entity_ID].w),
    Font::intToStr(hitboxList[entity_ID].h)
  };

  Font::FontControl.SetFont(FONT_MINI);

  for (int i = 0; i < sizeof(labels)/sizeof(labels[0]); i++) {
    SDL_Rect minusR = CAsset::getRect(dials[i].x, dials[i].y, button_sz, button_sz);
    SDL_Rect plusR  = CAsset::getRect(dials[i].x + dials[i].w - button_sz, dials[i].y, button_sz, button_sz);

    CAsset::drawBoxFill(&labels[i], labCol);
    Font::NewCenterWrite(info[i], &labels[i], textCol);

    CAsset::drawBoxFill(&dials[i], dialCol);
    Font::NewCenterWrite(vals[i].c_str(), &dials[i], textCol);

    CAsset::drawBoxFill(&minusR, SDL_PointInRect(m, &minusR) ? mnHovCol : mnCol);
    Font::NewCenterWrite("-", &minusR, textCol);

    CAsset::drawBoxFill(&plusR, SDL_PointInRect(m, &plusR) ? plHovCol : plCol);
    Font::NewCenterWrite("+", &plusR, textCol);
  }
  return true;
}
