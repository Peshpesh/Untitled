#include "CSceneryEditor.h"

namespace sceneryEngine
{
  namespace buttons {
    namespace chScenery
    { // Change entity button
      const char* const label = "Scenery Menu";
      CButton button(355, 510, 100, 24);
    }
    namespace chLayer
    { // Change layer button
      const char* const label = "Layers Menu";
      CButton button(355, 534, 100, 24);
    }
    namespace placeRelPos {
      const SDL_Point* offCol = &palette::silver;
      const SDL_Point* hovCol = &palette::light_yellow;
      const SDL_Point* onCol  = &palette::green;
      const short x = 20;
      const short y = 500;
      const short sz = 20;
      CButton buttons[] = {
        CButton(CAsset::getRect(x,            y,            sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x + sz,       y,            sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x + sz + sz,  y,            sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x,            y + sz,       sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x + sz,       y + sz,       sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x + sz + sz,  y + sz,       sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x,            y + sz + sz,  sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x + sz,       y + sz + sz,  sz, sz), offCol, hovCol, onCol),
        CButton(CAsset::getRect(x + sz + sz,  y + sz + sz,  sz, sz), offCol, hovCol, onCol)
      };
    }
  }
  namespace switches {
    const short sz = 11;
    const short lab_x_offset = 15;
    const short lab_y_offset = (sz - Font::GetSymH(FONT_MINI)) / 2;
    namespace view {
      const SDL_Point* offCol = &palette::red;
      const SDL_Point* onCol  = &palette::green;
      const short x = 100;
      const char* const labels[] = {
        "View Scenery",
        "Show Working Scenery",
      };
      CButton buttons[] = {
        CButton(CAsset::getRect(x, 500, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 515, sz, sz), offCol, onCol),
      };
    }
    namespace place {
      const SDL_Point* offCol = &palette::red;
      const SDL_Point* onCol  = &palette::green;
      const short x = 235;
      const char* const labels[] = {
        "Snap to Scenery"
      };
      CButton buttons[] = {
        CButton(CAsset::getRect(x, 500, sz, sz), offCol, onCol),
      };
    }
  }
  namespace meters {
    namespace opacLayer
    {
      const char* const label = "Layer Opacity";
      CMeter meter(645, 420, 90, 4);
    }
    namespace opacOther
    {
      const char* const label = "Other Opacity";
      CMeter meter(645, 460, 90, 4);
    }
  }
  namespace misc {
    namespace sceneryButtons {
      const SDL_Point* offCol = &palette::silver;
      const SDL_Point* onCol  = &palette::green;
      const SDL_Point* hovCol = &palette::light_yellow;
      const short list_x = 645;
      const short list_y = 20;
      const short button_w = 90;
      const short button_h = 20;
      const short max_buttons = 20;
    }
    namespace placeRelPos {
      const short numpos_x = 3;
      const short numpos_y = 3;
    }
  }
} // Scenery engine namespaces //
