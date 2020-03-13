#include "CInventory.h"

namespace items {
  const short max_items = 27;
}

namespace invinterface {
  const short row_items = 9;
  const short buff_sp = 8;
  const short canv_w = 400;
  const short canv_h = 100 + 150 + 120;
  const short menu_w = 96;
  const short str_w = 2;
  const SDL_Rect canvas_r = {(WWIDTH - canv_w) / 2, (WHEIGHT - canv_h) / 2, canv_w, canv_h};
  const SDL_Rect equip_r = {(WWIDTH - canv_w) / 2, (WHEIGHT - canv_h) / 2, canv_w, 100};
  const SDL_Rect items_r = {(WWIDTH - canv_w) / 2, equip_r.y + equip_r.h, canv_w, 150};
  const SDL_Rect title_r = {menu_w + (WWIDTH - canv_w) / 2, items_r.y + items_r.h, canv_w - menu_w, 36};
  const SDL_Rect about_r = {menu_w + (WWIDTH - canv_w) / 2, items_r.y + items_r.h, canv_w - menu_w, 120};
  const SDL_Color* f_col = &rgb::green;
  const SDL_Point* c_col = &palette::black;
  const SDL_Point* s_col = &palette::light_green;
  const SDL_Color* cursor_col = &rgb::light_cyan;
  const short cursor_w = 2;
  namespace optmenu {
    const SDL_Rect menu_r = {(WWIDTH - canv_w) / 2, about_r.y, menu_w, about_r.h};
    const SDL_Point* c_col = &palette::black;
    const SDL_Color* f_inactive = &rgb::dark_gray;
    const SDL_Color* f_col = &rgb::white;
    const SDL_Color* f_hov = &rgb::green;
    const short str_w = 2;
    const SDL_Point* s_col = &palette::light_green;
    const short num_options = 3;
    const short opts_h = menu_r.h / num_options;
    const char* const opt_list[] = {
      "Use",
      "Drop",
      "Cancel",
    };
  }
}
