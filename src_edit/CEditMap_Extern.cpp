#include "CEditMap.h"

// Map engine namespaces //
namespace mapEngine
{
  namespace but_tset
  {
    // Change Tileset button info
    const SDL_Rect button = {665, 50, 50, 40};
    const short bsiz = 2;
    const SDL_Point* offCol = &palette::blue;
    const SDL_Point* hoverColor = &palette::light_blue;
    const SDL_Point* onCol = &palette::red;
  }
  namespace but_t
  {
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
    const char* const name_TL = "TL";
    const char* const name_TR = "TR";
    const char* const name_BL = "BL";
    const char* const name_BR = "BR";
    const short left_x = 260;       //
    const short right_x = 284;      //
    const short top_y = 510;        //
    const short bottom_y = 534;     //
    const short w = 24;             //
    const short h = 24;             //
    const short bsiz = 2;
    const SDL_Point* offCol = &palette::red;
    const SDL_Point* offhvCol = &palette::light_red;
    const SDL_Point* onCol = &palette::green;
    const SDL_Point* onhvCol = &palette::light_green;
    const SDL_Point* editCol = &palette::yellow;
  }
  namespace disp_t
  {
    const short name_offset = 10;
    const short sample_x = 658;
    const short sample_y = 120;
    const short bgfg_x = 674;         // Displayed (current) Tile info
    const short bgfg_y = 140;         //
    const short bg_x = 674;           // "..." background Tile info
    const short bg_y = 210;           //
    const short fg_x = 674;           // "..." foreground Tile info
    const short fg_y = 280;           //
    const short ty_x = 674;           // "..." Tile type info
    const short ty_y = 350;           //
    const short co_x = 674;           // "..." Tile collision info
    const short co_y = 420;           //
    const SDL_Point bg_pos = {674, 210};
    const SDL_Point fg_pos = {674, 280};
    const SDL_Point ty_pos = {674, 350};
    const SDL_Point co_pos = {674, 420};
    const short arrSpac = 8;
    const SDL_Color* arrCol = &rgb::dark_orange;
    const SDL_Color* arrHovCol = &rgb::orange;
    const SDL_Rect dummyEntity = {522, 0, TILE_SIZE, TILE_SIZE};
    const SDL_Rect dummyOutline = {522, 32, TILE_SIZE, TILE_SIZE};
  }
  namespace opac    // opacity meters
  {
    const SDL_Rect typeBar = {645, 390, 90, 4};
    const SDL_Rect collBar = {645, 460, 90, 4};
    const SDL_Point* fillCol = &palette::light_green;
    const SDL_Point* emptyCol = &palette::black;
  }
  namespace but_rm
  {
    const short bg_x = 642;
    const short bg_y = 192;
    const short fg_x = 642;
    const short fg_y = 262;
    const short ty_x = 642;
    const short ty_y = 332;
    const short co_x = 642;
    const short co_y = 402;
  }
  namespace view_flip
  {
    const SDL_Point* onCol = &palette::green;
    const SDL_Point* offCol = &palette::red;
    const short x = 20;
    const short y = 510;
    const short w = 12;
    const short h = 12;
    const short bsiz = 2;
    const short col_h = 16;
    const short list_x = x + 16;
    const short list_y = y + ((h - Font::GetSymH(FONT_MINI)) / 2) + ((h - Font::GetSymH(FONT_MINI)) % 2);
    const char* labels[] = {
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
    const short y = 495;
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
