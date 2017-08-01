#include "CHitboxEditor.h"

CHitboxEditor CHitboxEditor::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(600, 440);
  const short subcanv_w         = canv.w / 4;
  const SDL_Rect workCanv       = CAsset::getRect(canv.x + subcanv_w, canv.y, canv.w - subcanv_w, canv.h);
  const short b_sz              = 2;
  const short hitbox_sz         = 2;
  const SDL_Point* canvCol      = &palette::dark_cyan;
  const SDL_Point* workCanvCol  = &palette::dark_violet;
  const SDL_Point* enCanvCol    = &palette::white;
  const SDL_Point* hitboxCol    = &palette::light_red;
}
namespace options {
  const short but_w = 100;
  const short but_h = 13;
  const short but_x = canv.x + (subcanv_w - but_w) / 2;
  const short but_y = canv.y + canv.h - 60;
  enum {
    SAVE_HITBOX_LIST = 0,
    SAVE_HITBOX_EXIT,
    CANCEL,
  };
  const char* const info[] = {
    "SAVE",
    "SAVE + EXIT",
    "CANCEL"
  };
  const SDL_Rect buttons[] = {
    {but_x, but_y     , but_w, but_h},
    {but_x, but_y + 15, but_w, but_h},
    {but_x, but_y + 30, but_w, but_h}
  };
  const SDL_Point* hovCol[] = {
    &palette::green,
    &palette::green,
    &palette::red
  };
  const SDL_Point* col      = &palette::silver;
  const SDL_Color* textCol  = &rgb::black;
}
namespace list {
  const short but_w             = 120;
  const short but_h             = 11;
  const short enList_x          = canv.x + (subcanv_w - but_w) / 2;
  const short enList_y          = canv.y + 30;
  const SDL_Point* offCol       = &palette::silver;
  const SDL_Point* onCol        = &palette::dark_green;
  const SDL_Point* editCol      = &palette::light_violet;
  const SDL_Point* hovCol       = &palette::light_cyan;
}
namespace anchor {
  const short spac = 5;
  const short label_y = canv.y + canv.h - 60;
  const short label_w = 44;
  const short label_h = 11;
  const short i_label_x = workCanv.x + ((workCanv.w - (label_w * 4) - (spac * 3)) / 2);
  const short button_sz = 11;
  const char* const info[] = {
    "H Align",
    "V Align",
    "Frame W",
    "Frame H"
  };
  const SDL_Rect labels[] = {
    {i_label_x                        , label_y, label_w, label_h},
    {i_label_x + (label_w + spac)     , label_y, label_w, label_h},
    {i_label_x + (label_w + spac) * 2 , label_y, label_w, label_h},
    {i_label_x + (label_w + spac) * 3 , label_y, label_w, label_h}
  };
  const SDL_Rect hAnchors[] = {
    {labels[0].x                  , label_y + label_h, button_sz, button_sz},
    {labels[0].x + (button_sz)    , label_y + label_h, button_sz, button_sz},
    {labels[0].x + (button_sz) * 2, label_y + label_h, button_sz, button_sz},
    {labels[0].x + (button_sz) * 3, label_y + label_h, button_sz, button_sz}
  };
  const SDL_Rect vAnchors[] = {
    {labels[1].x                  , label_y + label_h, button_sz, button_sz},
    {labels[1].x + (button_sz)    , label_y + label_h, button_sz, button_sz},
    {labels[1].x + (button_sz) * 2, label_y + label_h, button_sz, button_sz},
    {labels[1].x + (button_sz) * 3, label_y + label_h, button_sz, button_sz}
  };
  const SDL_Rect frameW = {labels[2].x, label_y + label_h, label_w, label_h};
  const SDL_Rect frameH = {labels[3].x, label_y + label_h, label_w, label_h};
  const char* const hAnchInfo[] = {
    "X",    // No alignment
    "L",    // left-aligned
    "C",    // center-aligned
    "R"     // right-aligned
  };
  const char* const vAnchInfo[] = {
    "X",    // No alignment
    "T",    // top-aligned
    "C",    // center-aligned
    "B"     // bottom-aligned
  };
  const SDL_Point* labCol   = &palette::black;
  const SDL_Point* valCol   = &palette::dark_gray;
  const SDL_Point* onCol    = &palette::dark_green;
  const SDL_Point* hovCol   = &palette::gray;
  const SDL_Point* offCol   = &palette::dark_gray;
  const SDL_Color* textCol  = &rgb::white;
  enum {
    ANCHOR_NONE     = 0,
    ANCHOR_LEFT     = 1,
    ANCHOR_TOP      = 1,
    ANCHOR_CENTER   = 2,
    ANCHOR_RIGHT    = 3,
    ANCHOR_BOTTOM   = 3,
  };
}
namespace dial {
  const short spac = 5;
  const short label_w = 45;
  const short label_h = 11;
  const short label_x = workCanv.x + ((workCanv.w - (label_w * 4) - (spac * 3)) / 2);
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
    {label_x                        , label_y, label_w, label_h},
    {label_x + (label_w + spac)     , label_y, label_w, label_h},
    {label_x + (label_w + spac) * 2 , label_y, label_w, label_h},
    {label_x + (label_w + spac) * 3 , label_y, label_w, label_h}
  };
  const SDL_Rect dials[] = {
    {label_x                        , label_y + label_h, label_w, label_h},
    {label_x + (label_w + spac)     , label_y + label_h, label_w, label_h},
    {label_x + (label_w + spac) * 2 , label_y + label_h, label_w, label_h},
    {label_x + (label_w + spac) * 3 , label_y + label_h, label_w, label_h}
  };
  const SDL_Rect minus[] = {
    {label_x                        , label_y + label_h, button_sz, button_sz},
    {label_x + (label_w + spac)     , label_y + label_h, button_sz, button_sz},
    {label_x + (label_w + spac) * 2 , label_y + label_h, button_sz, button_sz},
    {label_x + (label_w + spac) * 3 , label_y + label_h, button_sz, button_sz}
  };
  const SDL_Rect plus[] = {
    {label_x + label_w - button_sz                        , label_y + label_h, button_sz, button_sz},
    {label_x + label_w - button_sz + (label_w + spac)     , label_y + label_h, button_sz, button_sz},
    {label_x + label_w - button_sz + (label_w + spac) * 2 , label_y + label_h, button_sz, button_sz},
    {label_x + label_w - button_sz + (label_w + spac) * 3 , label_y + label_h, button_sz, button_sz}
  };
  const char* const info[] = {
    "X Off",
    "Y Off",
    "Width",
    "Height"
  };
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

CHitboxEditor::CHitboxEditor() {
  Group_Tex = NULL;
  group_ID = 0;
  entity_ID = 0;
  hAnchor = vAnchor = 0;
  repos = false;
  spriteR.x = spriteR.y = spriteR.w = spriteR.h = 0;
}

bool CHitboxEditor::OnInit(const int& group, const int& entity) {
  resetLists(group);

  group_ID = group;
  entity_ID = entity;
  Group_Tex = CEntity::getSrcTexture(group_ID);
  updateEntity();
  hAnchor = vAnchor = 0;
  return true;
}

void CHitboxEditor::resetLists(const int& group) {
  using namespace list;

  int N = CEntityData::getNumEntities(group);
  if (N <= 0) return;

  if (!hitboxList.empty()) hitboxList.clear();
  if (!entityList.empty()) entityList.clear();

  for (int i = 0; i < N; i++) {
    SDL_Rect hitR = CEntityData::getHitboxDims(group, i);
    hitboxList.push_back(hitR);
    entityList.push_back(CAsset::getRect(enList_x, enList_y + (i * but_h), but_w, but_h));
  }
}

void CHitboxEditor::updateEntity() {
  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  spriteR.x = workCanv.x + ((workCanv.w - srcR.w) / 2);
  spriteR.y = workCanv.y + ((workCanv.h - srcR.h) / 2);
  spriteR.w = srcR.w;
  spriteR.h = srcR.h;
}

void CHitboxEditor::save() {
  for (int i = 0; i < hitboxList.size(); i++) {
    if (!CAsset::compRect(hitboxList[i], CEntityData::getHitboxDims(group_ID, i))) {
      CEntityData::updateHitbox(group_ID, i, hitboxList[i]);
    }
  }
  CEntityData::save_phb(group_ID);
}

void CHitboxEditor::terminate() {
  CInterrupt::removeFlag(INTRPT_MODIFY_HB);
  hitboxList.clear();
  entityList.clear();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CHitboxEditor::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CHitboxEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleList(&m)) return;
  if (handleDims(&m)) return;
  if (handleAnchors(&m)) return;
  if (handleOptions(&m)) return;
}

void CHitboxEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: {
      save();
      terminate();
      break;
    }
    case SDLK_ESCAPE: {
      terminate();
      break;
    }
    default: break;
  }
}

bool CHitboxEditor::handleList(const SDL_Point* m) {
  for (int i = 0; i < entityList.size(); i++) {
    if (SDL_PointInRect(m, &entityList[i])) {
      entity_ID = i;
      updateEntity();
      repos = true;
      return true;
    }
  }
  return false;
}

bool CHitboxEditor::handleDims(const SDL_Point* m) {
  using namespace dial;

  enum {
    MODIFY_X = 0,
    MODIFY_Y = 1,
    MODIFY_W = 2,
    MODIFY_H = 3,
  };

  for (int i = MODIFY_X; i <= MODIFY_H; i++) {
    if (SDL_PointInRect(m, &plus[i])) {
      if (repos) reposHitbox();
      switch (i) {
        case MODIFY_X:  increaseX();  break;
        case MODIFY_Y:  increaseY();  break;
        case MODIFY_W:  increaseW();  break;
        case MODIFY_H:  increaseH();  break;
        default:        break;
      }
      return true;
    }
    if (SDL_PointInRect(m, &minus[i])) {
      if (repos) reposHitbox();
      switch (i) {
        case MODIFY_X:  decreaseX();  break;
        case MODIFY_Y:  decreaseY();  break;
        case MODIFY_W:  decreaseW();  break;
        case MODIFY_H:  decreaseH();  break;
        default:        break;
      }
      return true;
    }
  }
  return false;
}

bool CHitboxEditor::handleAnchors(const SDL_Point* m) {
  using namespace anchor;

  for (int i = 0; i < sizeof(hAnchors)/sizeof(hAnchors[0]); i++) {
    if (SDL_PointInRect(m, &hAnchors[i])) {
      hAnchor = i;
      repos = true;
      return true;
    }
  }
  for (int i = 0; i < sizeof(vAnchors)/sizeof(vAnchors[0]); i++) {
    if (SDL_PointInRect(m, &vAnchors[i])) {
      vAnchor = i;
      repos = true;
      return true;
    }
  }
  return false;
}

bool CHitboxEditor::handleOptions(const SDL_Point* m) {
  using namespace options;

  if (SDL_PointInRect(m, &buttons[SAVE_HITBOX_LIST])) {
    save();
    return true;
  }
  if (SDL_PointInRect(m, &buttons[SAVE_HITBOX_EXIT])) {
    save();
    terminate();
    return true;
  }
  if (SDL_PointInRect(m, &buttons[CANCEL])) {
    terminate();
    return true;
  }
  return false;
}

void CHitboxEditor::reposHitbox() {
  using namespace anchor;
  repos = false;

  if (hAnchor != ANCHOR_NONE) {
    if (hAnchor == ANCHOR_LEFT) {
      hitboxList[entity_ID].x = 0;
    }
    else if (hAnchor == ANCHOR_CENTER) {
      hitboxList[entity_ID].x = (spriteR.w - hitboxList[entity_ID].w) / 2;
    }
    else if (hAnchor == ANCHOR_RIGHT) {
      hitboxList[entity_ID].x = spriteR.w - hitboxList[entity_ID].w;
    }
  }
  if (vAnchor != ANCHOR_NONE) {
    if (vAnchor == ANCHOR_TOP) {
      hitboxList[entity_ID].y = 0;
    }
    else if (vAnchor == ANCHOR_CENTER) {
      hitboxList[entity_ID].y = (spriteR.h - hitboxList[entity_ID].h) / 2;
    }
    else if (vAnchor == ANCHOR_BOTTOM) {
      hitboxList[entity_ID].y = spriteR.h - hitboxList[entity_ID].h;
    }
  }
}

void CHitboxEditor::increaseX() {
  if (hAnchor == anchor::ANCHOR_NONE) {
    if (hitboxList[entity_ID].x + hitboxList[entity_ID].w < spriteR.w) {
      hitboxList[entity_ID].x++;
    }
  }
}

void CHitboxEditor::increaseY() {
  if (vAnchor == anchor::ANCHOR_NONE) {
    if (hitboxList[entity_ID].y + hitboxList[entity_ID].h < spriteR.h) {
      hitboxList[entity_ID].y++;
    }
  }
}

void CHitboxEditor::increaseW() {
  if (hitboxList[entity_ID].w < spriteR.w) {
    hitboxList[entity_ID].w++;
    if (hAnchor == anchor::ANCHOR_CENTER) {
      if ((spriteR.w - hitboxList[entity_ID].w) % 2) {
        hitboxList[entity_ID].x--;
        hitboxList[entity_ID].w++;
      }
    }
    else if (hAnchor == anchor::ANCHOR_RIGHT) {
      hitboxList[entity_ID].x--;
    }
    if (hitboxList[entity_ID].x + hitboxList[entity_ID].w > spriteR.w) {
      hitboxList[entity_ID].x--;
    }
  }
}

void CHitboxEditor::increaseH() {
  if (hitboxList[entity_ID].h < spriteR.h) {
    hitboxList[entity_ID].h++;
    if (vAnchor == anchor::ANCHOR_CENTER) {
      if ((spriteR.h - hitboxList[entity_ID].h) % 2) {
        hitboxList[entity_ID].y--;
        hitboxList[entity_ID].h++;
      }
    }
    else if (vAnchor == anchor::ANCHOR_BOTTOM) {
      hitboxList[entity_ID].y--;
    }
    if (hitboxList[entity_ID].y + hitboxList[entity_ID].h > spriteR.h) {
      hitboxList[entity_ID].y--;
    }
  }
}

void CHitboxEditor::decreaseX() {
  if (hAnchor == anchor::ANCHOR_NONE) {
    if (hitboxList[entity_ID].x > 0) {
      hitboxList[entity_ID].x--;
    }
  }
}

void CHitboxEditor::decreaseY() {
  if (vAnchor == anchor::ANCHOR_NONE) {
    if (hitboxList[entity_ID].y > 0) {
      hitboxList[entity_ID].y--;
    }
  }
}

void CHitboxEditor::decreaseW() {
  if (hitboxList[entity_ID].w > 0) {
    hitboxList[entity_ID].w--;
    if (hAnchor == anchor::ANCHOR_CENTER) {
      if ((spriteR.w - hitboxList[entity_ID].w) % 2) {
        hitboxList[entity_ID].x++;
        hitboxList[entity_ID].w--;
      }
    }
    else if (hAnchor == anchor::ANCHOR_RIGHT) {
      hitboxList[entity_ID].x++;
    }
  }
}

void CHitboxEditor::decreaseH() {
  if (hitboxList[entity_ID].h > 0) {
    hitboxList[entity_ID].h--;
    if (vAnchor == anchor::ANCHOR_CENTER) {
      if ((spriteR.h - hitboxList[entity_ID].h) % 2) {
        hitboxList[entity_ID].y++;
        hitboxList[entity_ID].h--;
      }
    }
    else if (vAnchor == anchor::ANCHOR_BOTTOM) {
      hitboxList[entity_ID].y++;
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool CHitboxEditor::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  Font::FontControl.SetFont(FONT_MINI);
  CAsset::drawStrBox(&canv, b_sz, canvCol);
  CAsset::drawStrBox(&workCanv, b_sz, workCanvCol);

  if (!drawList(m)) return false;
  if (!drawEntity()) return false;
  if (!drawHitbox()) return false;
  if (!drawDials(m)) return false;
  if (!drawAnchors(m)) return false;
  if (!drawOptions(m)) return false;

  return true;
}

bool CHitboxEditor::drawList(const SDL_Point* m) {
  using namespace list;

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

  CAsset::drawBoxFill(&spriteR, enCanvCol);
  return CSurface::OnDraw(Group_Tex, &srcR, &spriteR);
}

bool CHitboxEditor::drawHitbox() {
  SDL_Rect dstHitR = CAsset::getRect( spriteR.x + hitboxList[entity_ID].x,
                                      spriteR.y + hitboxList[entity_ID].y,
                                      hitboxList[entity_ID].w,
                                      hitboxList[entity_ID].h);
  return CAsset::drawBox(&dstHitR, hitboxCol, hitbox_sz);
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
    CAsset::drawBoxFill(&labels[i], labCol);
    Font::NewCenterWrite(info[i], &labels[i], textCol);

    CAsset::drawBoxFill(&dials[i], dialCol);
    Font::NewCenterWrite(vals[i].c_str(), &dials[i], textCol);

    CAsset::drawBoxFill(&minus[i], SDL_PointInRect(m, &minus[i]) ? mnHovCol : mnCol);
    Font::NewCenterWrite("-", &minus[i], textCol);

    CAsset::drawBoxFill(&plus[i], SDL_PointInRect(m, &plus[i]) ? plHovCol : plCol);
    Font::NewCenterWrite("+", &plus[i], textCol);
  }
  return true;
}

bool CHitboxEditor::drawAnchors(const SDL_Point* m) {
  using namespace anchor;

  Font::FontControl.SetFont(FONT_MINI);

  for (int i = 0; i < sizeof(labels)/sizeof(labels[0]); i++) {
    CAsset::drawBoxFill(&labels[i], labCol);
    Font::NewCenterWrite(info[i], &labels[i], textCol);
  }

  for (int i = 0; i < sizeof(hAnchors)/sizeof(hAnchors[0]); i++) {
    const SDL_Point* col = (i == hAnchor) ? onCol : (SDL_PointInRect(m, &hAnchors[i]) ? hovCol : offCol);
    CAsset::drawBoxFill(&hAnchors[i], col);
    Font::NewCenterWrite(hAnchInfo[i], &hAnchors[i], textCol);
  }

  for (int i = 0; i < sizeof(vAnchors)/sizeof(vAnchors[0]); i++) {
    const SDL_Point* col = (i == vAnchor) ? onCol : (SDL_PointInRect(m, &vAnchors[i]) ? hovCol : offCol);
    CAsset::drawBoxFill(&vAnchors[i], col);
    Font::NewCenterWrite(vAnchInfo[i], &vAnchors[i], textCol);
  }

  {
    std::string val;
    CAsset::drawBoxFill(&frameW, valCol);
    val = Font::intToStr(spriteR.w);
    Font::NewCenterWrite(val.c_str(), &frameW, textCol);

    CAsset::drawBoxFill(&frameH, valCol);
    val = Font::intToStr(spriteR.h);
    Font::NewCenterWrite(val.c_str(), &frameH, textCol);
  }
  return true;
}

bool CHitboxEditor::drawOptions(const SDL_Point* m) {
  using namespace options;

  Font::FontControl.SetFont(FONT_MINI);

  for (int i = 0; i < sizeof(buttons)/sizeof(buttons[0]); i++) {
    CAsset::drawStrBox(&buttons[i], b_sz, SDL_PointInRect(m, &buttons[i]) ? hovCol[i] : col);
    Font::NewCenterWrite(info[i], &buttons[i], textCol);
  }

  return true;
}
