#ifndef _C_BUTTON_H_
#define _C_BUTTON_H_

#include "CAsset.h"
#include "CSurface.h"

namespace button_defaults {
  extern const short bsiz;
  extern const SDL_Point* defCol;
  extern const SDL_Point* hovCol;
  extern const SDL_Point* onCol;
}

class CButton {
public:
  CButton();
  CButton(const int& x, const int& y, const unsigned int& w, const unsigned int& h);
  CButton(const SDL_Rect& dstR);

  bool OnRender(const SDL_Point* m, bool useHov, bool on);
  bool OnRender(const SDL_Point* m, bool useHov);
  bool OnRender(const SDL_Point* m);

public:
  SDL_Rect dstR;
  short bsiz;
  const SDL_Point* defCol;
  const SDL_Point* hovCol;
  const SDL_Point* onCol;
};

#endif
