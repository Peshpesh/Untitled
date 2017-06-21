#include "CEditMap.h"

// Map engine namespaces //
namespace mapEngine
{
  namespace but_tset
  {
    // Change Tileset button info
    const SDL_Rect button = {665, 50, 50, 40};
    const short bsiz = 2;
    const SDL_Point* offCol = &color::blue;
    const SDL_Point* hoverColor = &color::light_blue;
    const SDL_Point* onCol = &color::red;
  }
  namespace but_t
  {
    const SDL_Rect bg_button = {325, 510, 100, 24};
    const SDL_Rect fg_button = {325, 534, 100, 24};
    const short bsiz = 2;
    const SDL_Point* offCol = &color::blue;
    const SDL_Point* hoverColor = &color::light_blue;
    const SDL_Point* onCol = &color::red;
  }
  namespace but_act_t
  {
    const char* const onTitle = "active";
    const char* const offTitle = "idle";
    const SDL_Rect button = {260, 490, 48, 16};
    const short bsiz = 2;
    const SDL_Point* offCol = &color::red;
    const SDL_Point* offhvCol = &color::light_red;
    const SDL_Point* onCol = &color::green;
    const SDL_Point* onhvCol = &color::light_green;
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
    const SDL_Point* offCol = &color::red;
    const SDL_Point* offhvCol = &color::light_red;
    const SDL_Point* onCol = &color::green;
    const SDL_Point* onhvCol = &color::light_green;
    const SDL_Point* editCol = &color::yellow;
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
    const SDL_Rect dummyEntity = {522, 0, TILE_SIZE, TILE_SIZE};
    const SDL_Rect dummyOutline = {522, 32, TILE_SIZE, TILE_SIZE};
  }
  namespace opac    // opacity meters
  {
    const SDL_Rect typeBar = {645, 390, 90, 4};
    const SDL_Rect collBar = {645, 460, 90, 4};
    const SDL_Point* fillCol = &color::dark_green;
    const SDL_Point* emptyCol = &color::black;

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
    const short x = 20;
    const short y = 510;
  }
  namespace place_flip
  {
    const short x = 150;
    const short y = 495;
  }
}
// Map engine namespaces //
