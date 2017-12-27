#include "CModel.h"

CModel CModel::Control;

namespace model {
  const short info_sz = 200;
  const short mod_t_sz = 2;
  const short b_sz = 2;
  const SDL_Point* b_col = &palette::black;
  const SDL_Point* canv_col = &palette::dark_cyan;
}

CModel::CModel() {
  using namespace model;

  aW = aW = 0;
  mW = mH = 0;

  infoFrame.w = infoFrame.h = info_sz + (b_sz * 2);
  infoFrame.x = (WWIDTH  / 2) - infoFrame.w;
  infoFrame.y = (WHEIGHT / 2) - infoFrame.h;

  infoCanvas  = CAsset::getRect(infoFrame.x + b_sz, infoFrame.y + b_sz, info_sz, info_sz);

  visCanvas   = CAsset::getRect(0, 0, 0, 0);
  typeCanvas  = CAsset::getRect(0, 0, 0, 0);
  collCanvas  = CAsset::getRect(0, 0, 0, 0);

  visFrame    = CAsset::getRect(0, 0, 0, 0);
  typeFrame   = CAsset::getRect(0, 0, 0, 0);
  collFrame   = CAsset::getRect(0, 0, 0, 0);
}

void CModel::OnInit() {
  using namespace model;

  aW = aH = 0;
  mW = mH = 0;
  CArea::AreaControl.GetDims(aW, aH);

  mW = aW * MAP_WIDTH * mod_t_sz;
  mH = aH * MAP_HEIGHT * mod_t_sz;

  visCanvas.w = typeCanvas.w = collCanvas.w = mW;
  visCanvas.h = typeCanvas.h = collCanvas.h = mH;
  visFrame.w  = typeFrame.w  = collFrame.w  = mW + (b_sz * 2);
  visFrame.h  = typeFrame.h  = collFrame.h  = mH + (b_sz * 2);

  visFrame.x  = (WWIDTH  / 2);
  visFrame.y  = (WHEIGHT / 2) - visFrame.h;
  typeFrame.x = (WWIDTH  / 2) - collFrame.w;
  typeFrame.y = (WHEIGHT / 2);
  collFrame.x = (WWIDTH  / 2);
  collFrame.y = (WHEIGHT / 2);

  visCanvas.x   = visFrame.x  + b_sz;
  visCanvas.y   = visFrame.y  + b_sz;
  typeCanvas.x  = typeFrame.x + b_sz;
  typeCanvas.y  = typeFrame.y + b_sz;
  collCanvas.x  = collFrame.x + b_sz;
  collCanvas.y  = collFrame.y + b_sz;
}

void CModel::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CModel::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (sym == SDLK_ESCAPE || sym == SDLK_RETURN) {
    CInterrupt::removeFlag(INTRPT_MAP_MODEL);
  }
}

void CModel::OnLButtonDown(int mX, int mY) {
  //
}

bool CModel::OnRender(const SDL_Point* m) {

  if (!renderInfoWindow()) return false;
  if (!renderVisWindow()) return false;
  if (!renderTypeWindow()) return false;
  if (!renderCollWindow()) return false;

  if (!renderInfo()) return false;

  if (!renderArea()) return false;

  return true;
}

bool CModel::renderInfo() {
  Font::FontControl.SetFont(FONT_MINI);

  std::string info;
  info += "Stage - " + CFileIO::IOhandle.getPrevName() + "\n\n";
  info += "Tileset - " + CTileset::TSControl.getFileName() + "\n\n";
  info += "Area Width - " + Font::intToStr(aW) + "\n\n";
  info += "Area Height - " + Font::intToStr(aH) + "\n\n";
  info += "Entities - " + Font::intToStr(CEntity::entityList.size()) + "\n\n";
  info += "Scenery Objects - " + Font::intToStr(CScenery::sceneryList.size());
  Font::NewCenterWrite(info.c_str(), &infoCanvas);

  return true;
}

bool CModel::renderArea() {
  using namespace model;

  int ID = 0;
  int x_rel = 0;
  int y_rel = 0;

  for (int i = 0; i < aW; i++)
  {
    for (int j = 0; j < aH; j++)
    {
      ID = i + (j * aW);
      x_rel = i * mod_t_sz * MAP_WIDTH;
      y_rel = j * mod_t_sz * MAP_HEIGHT;
      if (!renderMap(&CArea::AreaControl.MapList[ID], x_rel, y_rel)) return false;
    }
  }
  return true;
}

bool CModel::renderMap(CMap* map, const int& x_rel, const int& y_rel) {
  using namespace model;

  int mX = 0;
  int mY = 0;
  int rX = 0;
  int rY = 0;
  for (int i = 0; i < MAP_WIDTH; i++)
  {
    for (int j = 0; j < MAP_HEIGHT; j++)
    {
      mX = i * TILE_SIZE;
      mY = j * TILE_SIZE;
      CTile* maptile = map->GetTile(mX, mY);

      rX = x_rel + (i * mod_t_sz);
      rY = y_rel + (j * mod_t_sz);

      if (!drawVisTile(rX, rY, maptile->bg_ID, maptile->fg_ID)) return false;
      if (!drawTypeTile(rX, rY, maptile->TypeID)) return false;
      if (!drawCollTile(rX, rY, maptile->CollID)) return false;
    }
  }
  return true;
}

bool CModel::drawVisTile(const int& x_rel, const int& y_rel, const int& bg_ID, const int& fg_ID) {
  using namespace model;

  SDL_Rect srcR;
  SDL_Rect dstR = {visCanvas.x + x_rel, visCanvas.y + y_rel, mod_t_sz, mod_t_sz};

  srcR = CTileset::TSControl.getTileSrcR(bg_ID);
  CSurface::OnDraw(CTileset::TSControl.tileset, &srcR, &dstR);

  srcR = CTileset::TSControl.getTileSrcR(fg_ID);
  CSurface::OnDraw(CTileset::TSControl.tileset, &srcR, &dstR);

  return true;
}

bool CModel::drawTypeTile(const int& x_rel, const int& y_rel, const int& typeID) {
  using namespace model;

  SDL_Rect dstR = {typeCanvas.x + x_rel, typeCanvas.y + y_rel, mod_t_sz, mod_t_sz};

  switch (typeID) {
    case TILE_TYPE_NORMAL:  break;
    case TILE_TYPE_WATER:   CAsset::drawBoxFill(&dstR, &palette::light_blue);       break;
    case TILE_TYPE_ICE:     CAsset::drawBoxFill(&dstR, &palette::light_cyan);         break;
    case TILE_TYPE_FIRE:    CAsset::drawBoxFill(&dstR, &palette::light_orange);       break;
    default: CInform::InfoControl.pushInform("---CMODEL draw---\nunknown tile type"); break;
  }

  return true;
}

bool CModel::drawCollTile(const int& x_rel, const int& y_rel, const int& collID) {
  using namespace model;

  SDL_Rect dstR = {0, 0, 0, 0};

  switch (collID) {
    case SOLID_NONE: {
      break;
    }
    case SOLID_ALL: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz;
      break;
    }
    case SOLID_U_BL_MR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel + (mod_t_sz / 2);
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz / 2;
      break;
    }
    case SOLID_U_ML_TR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz;
      break;
    }
    case SOLID_U_TL_MR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz;
      break;
    }
    case SOLID_U_ML_BR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel + (mod_t_sz / 2);
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz / 2;
      break;
    }
    case SOLID_A_BL_MR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz;
      break;
    }
    case SOLID_A_ML_TR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz / 2;
      break;
    }
    case SOLID_A_TL_MR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz / 2;
      break;
    }
    case SOLID_A_ML_BR: {
      dstR.x = collCanvas.x + x_rel;
      dstR.y = collCanvas.y + y_rel;
      dstR.w = mod_t_sz;
      dstR.h = mod_t_sz;
      break;
    }
    default: CInform::InfoControl.pushInform("---CMODEL draw---\nunknown collision"); break;
  }

  CAsset::drawBoxFill(&dstR, &palette::white);

  return true;
}

bool CModel::renderInfoWindow() {
  using namespace model;

  CAsset::drawBoxFill(&infoFrame, b_col);
  CAsset::drawBoxFill(&infoCanvas, canv_col);

  return true;
}

bool CModel::renderVisWindow() {
  using namespace model;

  CAsset::drawBoxFill(&visFrame, b_col);
  CAsset::drawBoxFill(&visCanvas, canv_col);

  return true;
}

bool CModel::renderTypeWindow() {
  using namespace model;

  CAsset::drawBoxFill(&typeFrame, b_col);
  CAsset::drawBoxFill(&typeCanvas, canv_col);
  return true;
}

bool CModel::renderCollWindow() {
  using namespace model;

  CAsset::drawBoxFill(&collFrame, b_col);
  CAsset::drawBoxFill(&collCanvas, canv_col);
  return true;
}
