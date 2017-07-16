#include "CEntityEditor.h"

namespace entityEngine
{
  namespace buttons {
    namespace chGroup
    { // Change entity group button
      const char* const label = "Group Menu";
      CButton button(355, 534, 100, 24);
    }
    namespace chEntity
    { // Change entity button
      const char* const label = "Entity Menu";
      CButton button(355, 510, 100, 24);
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
        "View Entities",
        "View Hitboxes",
        "Show Working Entity",
        "Show Working Hitbox"
      };
      CButton buttons[] = {
        CButton(CAsset::getRect(x, 500, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 515, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 530, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 545, sz, sz), offCol, onCol)
      };
    }
    namespace place {
      const SDL_Point* offCol = &palette::red;
      const SDL_Point* onCol  = &palette::green;
      const short x = 235;
      const char* const labels[] = {
        "Place by Hitbox",
        "Snap to Tile"
      };
      CButton buttons[] = {
        CButton(CAsset::getRect(x, 500, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 515, sz, sz), offCol, onCol)
      };
    }
  }
  namespace meters {
    namespace opacEntity
    {
      const char* const label = "Entity Opacity";
      CMeter meter(645, 420, 90, 4);
    }
    namespace opacHitbox
    {
      const char* const label = "Hitbox Opacity";
      CMeter meter(645, 460, 90, 4);
    }
  }
  namespace misc {
    namespace entityButtons {
      const SDL_Point* offCol = &palette::silver;
      const SDL_Point* onCol = &palette::green;
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
} // Entity engine namespaces //
