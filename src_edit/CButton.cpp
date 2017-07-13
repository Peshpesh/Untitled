#include "CButton.h"

namespace button_defaults {
  const short bsiz        = 2;
  const SDL_Point* defCol = &palette::blue;
  const SDL_Point* hovCol = &palette::light_blue;
  const SDL_Point* onCol  = &palette::red;
}

CButton::CButton() {
  dstR.x = dstR.y = dstR.w = dstR.h = 0;

  bsiz    = button_defaults::bsiz;
  defCol  = button_defaults::defCol;
  hovCol  = button_defaults::hovCol;
  onCol   = button_defaults::onCol;
}

CButton::CButton(const int& x, const int& y, const unsigned int& w, const unsigned int& h) {
  dstR.x = x;
  dstR.y = y;
  dstR.w = w;
  dstR.h = h;

  bsiz    = button_defaults::bsiz;
  defCol  = button_defaults::defCol;
  hovCol  = button_defaults::hovCol;
  onCol   = button_defaults::onCol;
}

CButton::CButton(const SDL_Rect& dstR) {
  this->dstR = dstR;

  bsiz    = button_defaults::bsiz;
  defCol  = button_defaults::defCol;
  hovCol  = button_defaults::hovCol;
  onCol   = button_defaults::onCol;
}

bool CButton::OnRender(const SDL_Point* m, bool useHov, bool on) {
  return CAsset::drawStrBox(&dstR,
                            bsiz,
                            on ? onCol : ((useHov && SDL_PointInRect(m, &dstR)) ? hovCol : defCol));
}

bool CButton::OnRender(const SDL_Point* m, bool useHov) {
  return CAsset::drawStrBox(&dstR,
                            bsiz,
                            (useHov && SDL_PointInRect(m, &dstR)) ? hovCol : defCol);
}

bool CButton::OnRender(const SDL_Point* m) {
  return CAsset::drawStrBox(&dstR,
                            bsiz,
                            SDL_PointInRect(m, &dstR) ? hovCol : defCol);
}
