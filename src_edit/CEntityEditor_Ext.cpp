#include "CEntityEditor.h"

namespace entityEngine
{
  namespace buttons {
    namespace chEntity
    { // Change entity button
      const char* const label = "Entity Menu";
      // CButton button(355, 510, 100, 24);
      CButton button(645, 20, 90, 24);
    }
    namespace editHitbox
    { // edit hitbox button
      const char* const label = "Edit Hitbox";
      CButton button(645, 44, 90, 24);
      // CButton button(355, 534, 100, 24);
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
      CMeter meter(355, 510, 90, 4);
      // CMeter meter(645, 420, 90, 4);
    }
    namespace opacHitbox
    {
      const char* const label = "Hitbox Opacity";
      CMeter meter(355, 550, 90, 4);
      // CMeter meter(645, 460, 90, 4);
    }
  }
  namespace misc {
    namespace entityButtons {
      const SDL_Point* offCol = &palette::silver;
      const SDL_Point* onCol  = &palette::green;
      const SDL_Point* hovCol = &palette::light_yellow;
      const short button_w = 90;
      const short button_h = 20;
      const short pg_button_x = 645;
      const short pg_button_y = 90;
      const short pg_button_w = button_w / 3;
      const short pg_button_h = 1 + (button_h / 2);
      const short list_x = pg_button_x;
      const short list_y = pg_button_y + pg_button_h;
      const short max_buttons = 16;

      const SDL_Rect prev_pg = CAsset::getRect(pg_button_x, pg_button_y, pg_button_w, pg_button_h);
      const SDL_Rect curr_pg = CAsset::getRect(prev_pg.x + pg_button_w, pg_button_y, pg_button_w, pg_button_h);
      const SDL_Rect next_pg = CAsset::getRect(curr_pg.x + pg_button_w, pg_button_y, pg_button_w, pg_button_h);
    }
    namespace placeRelPos {
      const short numpos_x = 3;
      const short numpos_y = 3;
    }
    namespace layerBrief {
      const SDL_Point* fieldCol = &palette::silver;
      const SDL_Point* butCol = &palette::blue;
      const SDL_Point* hovCol = &palette::light_blue;
      const short list_x = 405;
      const short list_y = 494;
      const short field_w = 100;
      const short field_h = 11;
      const short buffer_h = 2;
      const short num_fields = 3;
      const short button_sz = field_h;
      const SDL_Rect fields[] = {
        CAsset::getRect(list_x, list_y                           , field_w, field_h),
        CAsset::getRect(list_x, list_y + (field_h + buffer_h)    , field_w, field_h),
        CAsset::getRect(list_x, list_y + (field_h + buffer_h) * 2, field_w, field_h),
      };
      const char* const labels[] = {
        "Layers - ",
        "Active - ",
        "Z - ",
      };
      const SDL_Rect l_button = CAsset::getRect(fields[1].x, fields[1].y, button_sz, button_sz);
      const SDL_Rect r_button = CAsset::getRect(fields[1].x + field_w - button_sz, fields[1].y, button_sz, button_sz);
    }
  }
} // Entity engine namespaces //
