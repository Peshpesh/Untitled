#include "CModel.h"

CModel CModel::Control;

namespace model {
  const short mod_t_sz = 2;
  const short b_sz = 2;
  const SDL_Point* b_col = &palette::black;
  const SDL_Point* canv_col = &palette::dark_cyan;
}

CModel::CModel() {
  mW = mH = 0;
  infoCanvas  = CAsset::getRect((WWIDTH / 2) - 100, (WHEIGHT / 2) - 100, 100, 100);
  visCanvas   = CAsset::getRect(0, 0, 0, 0);
  typeCanvas  = CAsset::getRect(0, 0, 0, 0);
  collCanvas  = CAsset::getRect(0, 0, 0, 0);
}

void CModel::OnInit() {
  using namespace model;

  mW = mH = 0;
  CArea::AreaControl.GetDims(mW, mH);

  mW *= MAP_WIDTH * mod_t_sz;
  mH *= MAP_HEIGHT * mod_t_sz;

  visCanvas.x   = (WWIDTH / 2)      ;
  visCanvas.y   = (WHEIGHT / 2) - mH;
  typeCanvas.x  = (WWIDTH / 2)  - mW;
  typeCanvas.y  = (WHEIGHT / 2)     ;
  collCanvas.x  = (WWIDTH / 2)      ;
  collCanvas.y  = (WHEIGHT / 2)     ;

  visCanvas.w = typeCanvas.w = collCanvas.w = mW;
  visCanvas.h = typeCanvas.h = collCanvas.h = mH;
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

  return true;
}

bool CModel::renderInfoWindow() {
  using namespace model;

  CAsset::drawStrBox(&infoCanvas, b_sz, canv_col, b_col);

  return true;
}

bool CModel::renderVisWindow() {
  using namespace model;

  CAsset::drawStrBox(&visCanvas, b_sz, canv_col, b_col);

  return true;
}

bool CModel::renderTypeWindow() {
  using namespace model;

  CAsset::drawStrBox(&typeCanvas, b_sz, canv_col, b_col);
  return true;
}

bool CModel::renderCollWindow() {
  using namespace model;

  CAsset::drawStrBox(&collCanvas, b_sz, canv_col, b_col);
  return true;
}
