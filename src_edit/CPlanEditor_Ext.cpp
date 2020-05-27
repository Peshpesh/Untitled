#include "CPlanEditor.h"

namespace pvmEditor {
  const short stroke_sz = 2;  // px thickness of common borders (e.g., for buttons)
  const SDL_Point* btn_col = &palette::cyan;        // default button color
  const SDL_Point* hov_col = &palette::light_cyan;  // default hover-over-button color
  const SDL_Point* on_col  = &palette::green;       // default button-on color
  const SDL_Point* off_col = &palette::red;         // default button-off color
  const SDL_Color* btn_fcol = &rgb::black;          // default button text color
  namespace tileOpts {
    const short w = 80;
    const short tset_h = 32;  // height of change-tileset button
    const short tile_h = 16;  // height of change-tile button
    const short spac = 4; // spacing between buttons
    const short x = 180;
    const short tset_y = WHEIGHT + ((EHEIGHT - WHEIGHT) - (tset_h + tile_h + spac)) / 2;
    const short tile_y = tset_y + tset_h + spac;
    const SDL_Rect ts_button = CAsset::getRect(x, tset_y, w, tset_h);
    const SDL_Rect tile_button = CAsset::getRect(x, tile_y, w, tile_h);
    const SDL_Color* title_fcol = &rgb::black;
    const char* const ts_title = "Change Tileset";
    const char* const tile_title = "Select Tile";
  }
  namespace visOpts {
    const short nOpts = 4;    // number of visible-module options
    const short opts[] = {
      pvm_visflags::MAP,
      pvm_visflags::SOLID,
      pvm_visflags::TYPE,
      pvm_visflags::FILL
    };
    const short w = 64;      // visible-module width
    const short h = 80;
    const short opt_h = h / (nOpts + 1);
    const short x = 20;
    const short y = WHEIGHT + ((EHEIGHT - WHEIGHT) - h) / 2;
    const SDL_Rect title_r = CAsset::getRect(x, y, w, opt_h);
    const SDL_Rect buttons[] = {
      CAsset::getRect(x, y + opt_h, w, opt_h),
      CAsset::getRect(x, y + opt_h * 2, w, opt_h),
      CAsset::getRect(x, y + opt_h * 3, w, opt_h),
      CAsset::getRect(x, y + opt_h * 4, w, opt_h)
    };
    const SDL_Color* title_fcol = &rgb::black;
    const char* const title = "Visibility";
    const char* const labels[] = {
      "Tile", "Solid", "Type", "Fill"
    };
  }
  namespace placeOpts {
    const short nOpts = 3;    // number of placement-module options
    const short opts[] = {
      ENABLE_BG,
      ENABLE_COLL,
      ENABLE_TYPE
    };
    const short w = 64;
    const short h = 64;
    const short opt_h = h / (nOpts + 1);
    const short x = 100;
    const short y = WHEIGHT + ((EHEIGHT - WHEIGHT) - h) / 2;
    const SDL_Rect title_r = CAsset::getRect(x, y, w, opt_h);
    const SDL_Rect buttons[] = {
      CAsset::getRect(x, y + opt_h, w, opt_h),
      CAsset::getRect(x, y + opt_h * 2, w, opt_h),
      CAsset::getRect(x, y + opt_h * 3, w, opt_h)
    };
    const SDL_Color* title_fcol = &rgb::black;
    const char* const title = "Placement";
    const char* const labels[] = {
      "Tile", "Solid", "Type"
    };
  }
  namespace solidOpts {
    const short w = 64;
    const short h = 16;
    const short x = WWIDTH + ((EWIDTH - WWIDTH - w) / 2);
    const short y = WHEIGHT - 20 - h;
    const SDL_Rect button = CAsset::getRect(x, y, w, h);
    const char* const labels[] = {
      "Solid Off", "Solid On"
    };
  }
  namespace typeOpts {
    const short type_sz = 16; // w/h of type icon
    const short cols = 4;     // N of icons in a row (N of columns)
    const short spac = 2;     // spacing between icons
    const short x = WWIDTH + ((EWIDTH - WWIDTH - (type_sz * cols) - (spac * (cols - 1))) / 2);
    const short y = WHEIGHT - 100;
    const SDL_Point pos = CAsset::getPos(x, y);
    const SDL_Point* hl_col = &palette::red;
  }
} // planview map editor namespaces //
