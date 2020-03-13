#include "CMapModel.h"

CMapModel CMapModel::control;

namespace mapmodel {
  const short mod_t_sz = 2;
  const short b_sz = 2;
  const SDL_Point* b_col = &palette::black;
  const SDL_Point* canv_col = &palette::dark_cyan;
  const SDL_Point* hero_col = &palette::silver;
  const SDL_Color* f_col = &rgb::white;
  const short title_h = 64;
}

CMapModel::CMapModel() {
  using namespace mapmodel;
  aW = aW = 0;
  mW = mH = 0;
  visCanvas   = CAsset::getRect(0,0,0,0);
  visFrame    = CAsset::getRect(0,0,0,0);
  visTitle    = CAsset::getRect(0,0,0,0);
}

void CMapModel::OnInit() {
  using namespace mapmodel;

  aW = aH = 0;
  mW = mH = 0;
  CArea::control.GetDims(aW, aH);

  mW = aW * MAP_WIDTH * mod_t_sz;
  mH = aH * MAP_HEIGHT * mod_t_sz;

  visCanvas.w = mW;
  visCanvas.h = mH;
  visFrame.w  = mW + (b_sz * 2);
  visFrame.h  = mH + (b_sz * 2);

  visFrame.x    = (WWIDTH  - visFrame.w) / 2;
  visFrame.y    = (WHEIGHT - visFrame.h) / 2;
  visCanvas.x   = visFrame.x  + b_sz;
  visCanvas.y   = visFrame.y  + b_sz;
  visTitle.x    = visFrame.x;
  visTitle.y    = visFrame.y - title_h;
  visTitle.w    = visFrame.w;
  visTitle.h    = title_h;
}

void CMapModel::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CMapModel::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  Gamecon action = CControls::handler.getAction(sym, mod);
  switch (action) {
    case CON_ATTACK: CInterrupt::removeFlag(INTRPT_VIEW_MAP); break;
    case CON_DEFEND: CInterrupt::removeFlag(INTRPT_VIEW_MAP); break;
    case CON_MAP:    CInterrupt::removeFlag(INTRPT_VIEW_MAP); break;
    case CON_INVENTORY: {
      CInterrupt::removeFlag(INTRPT_VIEW_MAP);
      CInterrupt::appendFlag(INTRPT_INVENTORY);
      break;
    }
    case CON_PAUSE: {
      CInterrupt::removeFlag(INTRPT_VIEW_MAP);
      CInterrupt::appendFlag(INTRPT_PAUSE);
      break;
    }
    default: break;
  }
}

bool CMapModel::OnRender() {
  if (!renderVisWindow()) return false;
  if (!renderTitle()) return false;
  if (!renderArea()) return false;
  return true;
}

bool CMapModel::OnRender(const float& hero_x, const float& hero_y) {
  if (!OnRender()) return false;
  if (!renderPosition(hero_x, hero_y)) return false;
  return true;
}

bool CMapModel::renderVisWindow() {
  using namespace mapmodel;

  if (!CAsset::drawBoxFill(visFrame, b_col)) return false;
  if (!CAsset::drawBoxFill(visCanvas, canv_col)) return false;

  return true;
}

bool CMapModel::renderTitle() {
  using namespace mapmodel;

  std::string name = CLocation::getFullname(CArea::control.location_ID);
  if (name.empty()) return false;
  CType::CenterWrite(name.c_str(), visTitle, f_col);

  return true;
}

bool CMapModel::renderArea() {
  using namespace mapmodel;

  int ID = 0;
  int x_rel = 0;
  int y_rel = 0;

  for (int i = 0; i < aW; i++) {
    for (int j = 0; j < aH; j++) {
      ID = i + (j * aW);
      x_rel = i * mod_t_sz * MAP_WIDTH;
      y_rel = j * mod_t_sz * MAP_HEIGHT;
      if (!renderMap(&CArea::control.MapList[ID], x_rel, y_rel)) return false;
    }
  }
  return true;
}

bool CMapModel::renderMap(CMap* map, const int& x_rel, const int& y_rel) {
  using namespace mapmodel;

  int mX = 0;
  int mY = 0;
  int rX = 0;
  int rY = 0;
  for (int i = 0; i < MAP_WIDTH; i++) {
    for (int j = 0; j < MAP_HEIGHT; j++) {
      mX = i * TILE_SIZE;
      mY = j * TILE_SIZE;
      CTile* maptile = map->GetTile(mX, mY);

      rX = x_rel + (i * mod_t_sz);
      rY = y_rel + (j * mod_t_sz);

      if (!drawVisTile(rX, rY, maptile->bg_ID, maptile->fg_ID)) return false;
    }
  }
  return true;
}

bool CMapModel::drawVisTile(const int& x_rel, const int& y_rel, const int& bg_ID, const int& fg_ID) {
  using namespace mapmodel;

  SDL_Rect dstR = {visCanvas.x + x_rel, visCanvas.y + y_rel, mod_t_sz, mod_t_sz};
  SDL_Rect srcR = {0, 0, TILE_SIZE, TILE_SIZE};

  if (bg_ID >= 0) {
    srcR.x = (bg_ID % CMap::Tileset.w) * TILE_SIZE;
    srcR.y = (bg_ID / CMap::Tileset.w) * TILE_SIZE;
    if (!CSurface::OnDraw(CMap::Tileset.img, srcR, dstR)) return false;
  }
  if (fg_ID >= 0) {
    srcR.x = (fg_ID % CMap::Tileset.w) * TILE_SIZE;
    srcR.y = (fg_ID / CMap::Tileset.w) * TILE_SIZE;
    if (!CSurface::OnDraw(CMap::Tileset.img, srcR, dstR)) return false;
  }
  return true;
}

bool CMapModel::renderPosition(const float& x, const float& y) {
  using namespace mapmodel;
  SDL_Rect dstR = {
    visCanvas.x + (int)(x / TILE_SIZE) * mod_t_sz,
    visCanvas.y + (int)(y / TILE_SIZE) * mod_t_sz,
    mod_t_sz,
    mod_t_sz};
  return CAsset::drawBoxFill(dstR, hero_col);
}
