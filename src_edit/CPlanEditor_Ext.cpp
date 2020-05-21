#include "CPlanEditor.h"

namespace pvmEditor {
  const short stroke_sz = 2;  // px thickness of common borders (e.g., for buttons)
  const SDL_Point* btn_col = &palette::cyan;        // default button color
  const SDL_Point* hov_col = &palette::light_cyan;  // default hover-over-button color
  const SDL_Point* on_col  = &palette::green;       // default button-on color
  const SDL_Point* off_col = &palette::red;         // default button-off color
  namespace visOpts {
    const short nOpts = 3;    // number of visible-module options
    const short w = 120;      // visible-module width
    const short h = 80;
    const short opt_h = h / (nOpts + 1);
    const short x = 50;
    const short y = WHEIGHT + ((EHEIGHT - WHEIGHT) - h) / 2;
    const SDL_Rect title_r = CAsset::getRect(x, y, w, opt_h);
    const SDL_Rect buttons[] = {
      CAsset::getRect(x, y + opt_h, w, opt_h),
      CAsset::getRect(x, y + opt_h * 2, w, opt_h),
      CAsset::getRect(x, y + opt_h * 3, w, opt_h)
    };
    const char* const title = "Visibility";
    const char* const labels[] = {
      "Tile", "Type", "Solid"
    };
  }
} // planview map editor namespaces //
