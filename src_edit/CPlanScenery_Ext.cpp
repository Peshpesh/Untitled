#include "CPlanScenery.h"

namespace pvmScenery
{
  namespace ybase {
    extern const SDL_Color* work_col = &rgb::light_green;
    extern const SDL_Color* back_col = &rgb::light_blue;
    extern const SDL_Color* front_col = &rgb::white;
    extern const SDL_Point* back_col_pt = &palette::light_blue;
    extern const SDL_Point* front_col_pt = &palette::white;
  }
  namespace buttons {
    namespace chScenery
    { // Change scenery button
      const char* const label = "Scenery Menu";
      CButton button(645, 20, 90, 24);
    }
    namespace chLayer
    { // Change layer buttons
      const char* const label = "Layers Menu";
      CButton button(405, 534, 100, 24);
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
        "Show Y Base",
        "View Scenery",
        "Show Working Scenery",
      };
      CButton buttons[] = {
        CButton(CAsset::getRect(x, 500, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 515, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 530, sz, sz), offCol, onCol),
      };
    }
    namespace place {
      const SDL_Point* offCol = &palette::red;
      const SDL_Point* onCol  = &palette::green;
      const short x = 235;
      const char* const labels[] = {
        "Draw With Map",
        "Lock To Grid",
        "Use Anchor",
        "Show Anchor",
      };
      CButton buttons[] = {
        CButton(CAsset::getRect(x, 500, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 515, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 530, sz, sz), offCol, onCol),
        CButton(CAsset::getRect(x, 545, sz, sz), offCol, onCol),
      };
    }
  }
  namespace anchor {
    const short but_w = 50;
    const short but_h = 24;
    const short x_grab = 100;
    const short y_grab = 534;
    const short x_make = x_grab + but_w;
    const short y_make = y_grab;
    const short x_adv = x_make + but_w;
    const short y_adv = y_make;
    CButton grab_anch(x_grab, y_grab, but_w, but_h);
    const char* const label_grab = "Grab Anchor";
    CButton make_anch(x_make, y_make, but_w, but_h);
    const char* const label_make = "Make Anchor";
    CButton adv_anch(x_adv, y_adv, but_w, but_h);
    const char* const label_adv = "Advance Anchor";

    namespace disp {
      const short field_w = 100;
      const short field_h = 12;
      const short lr_but_sz = 12;
      const short x_disp = x_adv + but_w + lr_but_sz;
      const short y_h_disp = y_adv;
      const short y_v_disp = y_adv + (but_h / 2);
      const SDL_Point* fieldCol = &palette::silver;
      const SDL_Point* butCol = &palette::blue;
      const SDL_Point* hovCol = &palette::light_blue;
      const SDL_Rect field_h_disp = CAsset::getRect(x_disp, y_h_disp, field_w, field_h);
      const SDL_Rect field_v_disp = CAsset::getRect(x_disp, y_v_disp, field_w, field_h);
      const char* const label_h_disp = "X Disp - ";
      const char* const label_v_disp = "Y Disp - ";
      const SDL_Rect lr_buttons[] = {
        CAsset::getRect(x_disp - lr_but_sz, y_h_disp, lr_but_sz, lr_but_sz),
        CAsset::getRect(x_disp + field_w, y_h_disp, lr_but_sz, lr_but_sz),
        CAsset::getRect(x_disp - lr_but_sz, y_v_disp, lr_but_sz, lr_but_sz),
        CAsset::getRect(x_disp + field_w, y_v_disp, lr_but_sz, lr_but_sz),
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
      const short pg_button_x = 645;
      const short pg_button_y = 50;
      const short button_w = 90;
      const short button_h = 20;
      const short pg_button_w = button_w / 3;
      const short pg_button_h = 1 + (button_h / 2);
      const SDL_Rect prev_pg = CAsset::getRect(pg_button_x, pg_button_y, pg_button_w, pg_button_h);
      const SDL_Rect curr_pg = CAsset::getRect(prev_pg.x + pg_button_w, pg_button_y, pg_button_w, pg_button_h);
      const SDL_Rect next_pg = CAsset::getRect(curr_pg.x + pg_button_w, pg_button_y, pg_button_w, pg_button_h);
      const short list_x = pg_button_x;
      const short list_y = pg_button_y + pg_button_h;
      const short max_buttons = 16;
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
    namespace placeRelPos {
      const short numpos_x = 3;
      const short numpos_y = 3;
    }
  }
} // Scenery engine namespaces //
