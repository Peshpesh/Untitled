#include "CEditMap.h"

// Map engine namespaces //
namespace mapEngine
{
  namespace but_quad_map
  {
    const char* const labels[] = {
      "$L$L",
      "$R$R",
      "$U$U",
      "$D$D"
    };
    const short w = 25;
    const short h = 25;
    const short Xl = WWIDTH + ((EWIDTH - WWIDTH - (w * 3)) / 2);
    const short Yt = 24;
    const SDL_Rect buttons[] = {
      {Xl, Yt + h, w, h},
      {Xl + w + w, Yt + h, w, h},
      {Xl + w, Yt, w, h},
      {Xl + w, Yt + h + h, w, h}
    };
    const short bsiz = 2;
    const SDL_Point* col    = &palette::cyan;
    const SDL_Point* hvCol  = &palette::light_cyan;
  }
  namespace but_tset
  {
    // Change Tileset button info
    const char* const label = "Change Tileset";
    const SDL_Rect button = {435, 510, 50, 48};
    const short bsiz = 2;
    const SDL_Point* offCol = &palette::blue;
    const SDL_Point* hoverColor = &palette::light_blue;
    const SDL_Point* onCol = &palette::red;
  }
  namespace but_t
  {
    const char* const bg_label = "Grab Background";
    const char* const fg_label = "Grab Foreground";
    const SDL_Rect bg_button = {325, 510, 100, 24};
    const SDL_Rect fg_button = {325, 534, 100, 24};
    const short bsiz = 2;
    const SDL_Point* offCol = &palette::blue;
    const SDL_Point* hoverColor = &palette::light_blue;
    const SDL_Point* onCol = &palette::red;
  }
  namespace but_act_t
  {
    const char* const onTitle = "active";
    const char* const offTitle = "idle";
    const SDL_Rect button = {260, 490, 48, 16};
    const short bsiz = 2;
    const SDL_Point* offCol = &palette::red;
    const SDL_Point* offhvCol = &palette::light_red;
    const SDL_Point* onCol = &palette::green;
    const SDL_Point* onhvCol = &palette::light_green;
  }
  namespace but_quad_t
  {
    const char* const labels[] = {
      "TL",
      "TR",
      "BL",
      "BR"
    };
    const SDL_Rect buttons[] = {
      {260, 510, 24, 24},
      {284, 510, 24, 24},
      {260, 534, 24, 24},
      {284, 534, 24, 24}
    };
    const short bsiz = 2;
    const SDL_Point* offCol = &palette::red;
    const SDL_Point* offhvCol = &palette::light_red;
    const SDL_Point* onCol = &palette::green;
    const SDL_Point* onhvCol = &palette::light_green;
    const SDL_Point* editCol = &palette::yellow;
  }
  namespace disp_t
  {
    const short namePos_x = WWIDTH + (EWIDTH - WWIDTH) / 2;
    const short nameOffset_y = -10;
    const SDL_Point stage_pos = {658, 120};
    const SDL_Point bg_pos = {674, 210};
    const SDL_Point fg_pos = {674, 280};
    const SDL_Point ty_pos = {674, 350};
    const SDL_Point co_pos = {674, 420};
    const short arrSpac = 8;
    const short rmOffset_x = -28;
    const short rmOffset_y = -15;
    const short rm_sz = 10;
    const short rm_bsiz = 1;
    const SDL_Color* arrCol = &rgb::dark_orange;
    const SDL_Color* arrHovCol = &rgb::light_orange;
    const SDL_Point* rmCol = &palette::dark_red;
    const SDL_Point* rmHovCol = &palette::light_red;
  }
  namespace opac    // opacity meters
  {
    const SDL_Rect typeBar = {645, 390, 90, 4};
    const SDL_Rect collBar = {645, 460, 90, 4};
    const SDL_Point* fillCol = &palette::light_green;
    const SDL_Point* emptyCol = &palette::black;
  }
  namespace view_flip
  {
    const SDL_Point* onCol = &palette::green;
    const SDL_Point* offCol = &palette::red;
    const short x = 20;
    const short y = 500;
    const short w = 12;
    const short h = 12;
    const short bsiz = 2;
    const short col_h = 16;
    const short list_x = x + 16;
    const short list_y = y + ((h - Font::GetSymH(FONT_MINI)) / 2) + ((h - Font::GetSymH(FONT_MINI)) % 2);
    const char* labels[] = {
      "View BG",
      "View FG",
      "View Type",
      "View Coll"
    };
  }
  namespace place_flip
  {
    const SDL_Point* onCol = &palette::green;
    const SDL_Point* offCol = &palette::red;
    const short x = 150;
    const short y = 500;
    const short w = 12;
    const short h = 12;
    const short bsiz = 2;
    const short col_h = 16;
    const short list_x = x + 16;
    const short list_y = y + ((h - Font::GetSymH(FONT_MINI)) / 2) + ((h - Font::GetSymH(FONT_MINI)) % 2);
    const char* labels[] = {
      "Place BG",
      "Place FG",
      "Place Type",
      "Place Coll"
    };
  }
}
// Map engine namespaces //
