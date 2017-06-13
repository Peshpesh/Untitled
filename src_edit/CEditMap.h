#ifndef _C_EDITMAP_H_
#define _C_EDITMAP_H_

#include "CSurface.h"
#include "CFont.h"
#include "CArea.h"
#include "CCamera.h"
#include "CChangeTile.h"
#include "Define.h"

enum interrupts
{
  INTRPT_NONE = 0,
  INTRPT_CH_BTILE = 0x00000001,		// intrpt via bg tile change
  INTRPT_CH_FTILE = 0x00000002,		// intrpt via fg tile change
  INTRPT_MODEL = 0x00000004,
  INTRPT_CH_TL = 0x00000008,
  INTRPT_CH_TR = 0x00000010,
  INTRPT_CH_BL = 0x00000020,
  INTRPT_CH_BR = 0x00000040,
};

enum
{
  MODIFY_TILE_TL = 0,
  MODIFY_TILE_TR,
  MODIFY_TILE_BL,
  MODIFY_TILE_BR,
};

namespace but_tset
{
  // const SDL_Rect button_tset = {665, 50, 50, 40};
  const unsigned short w = 50;    // Change Tileset button info
  const unsigned short h = 40;    //
  const short x = 665;            //
  const short y = 50;             //
}
namespace but_t
{
  // const SDL_Rect button_bg = {260, 510, 100, 20};
  // const SDL_Rect button_fg = {260, 540, 100, 20};
  const short bg_x = 325;   // Change Tile button info
  const short bg_y = 510;   //
  const short bg_w = 100;   //
  const short bg_h = 24;    //
  const short fg_x = 325;   // Change Tile button info
  const short fg_y = 534;   //
  const short fg_w = 100;   //
  const short fg_h = 24;    //
}
namespace but_act_t
{
  static const char* onTitle = "active";
  static const char* offTitle = "idle";
  
  const short x = 260;
  const short y = 486;
  const short w = 48;
  const short h = 16;
  const short bsiz = 2;
}
namespace but_quad_t
{
  const short left_x = 260;       // Change Tile button info
  const short right_x = 284;      //
  const short top_y = 510;        //
  const short bottom_y = 534;     //
  const short w = 24;             //
  const short h = 24;             //
  const short bsiz = 2;
}
namespace disp_t
{
  const short bgfg_x = 674;         // Displayed (current) Tile info
  const short bgfg_y = 140;         //
  const short name_offset = 10;
  const short bg_x = 674;           // "..." background Tile info
  const short bg_y = 210;           //
  const short fg_x = 674;           // "..." foreground Tile info
  const short fg_y = 280;           //
  const short ty_x = 674;           // "..." Tile type info
  const short ty_y = 350;           //
  const short co_x = 674;           // "..." Tile collision info
  const short co_y = 420;           //
  const unsigned short dummy_x = 522;
  const unsigned short dummy_y = 0;
}
namespace opac    // opacity meters
{
  const short w = 90;
  const short h = 4;
  const short x = 645;
  const short ty_y = 390;
  const short co_y = 460;
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

class CEditMap {
public:
	static CEditMap	MapEditor;

private:
  SDL_Texture* Main_Tileset;  // The actual tileset in use
  SDL_Texture* Type_Tileset;  // Tileset showing tile type
  SDL_Texture* Coll_Tileset;	// Tileset showing collision type

private:
  CTile TileTL;
  CTile TileTR;
  CTile TileBL;
  CTile TileBR;
  bool active_TL, active_TR, active_BL, active_BR;
  int modifyTile;

private:
  // bool no_bg, no_fg;				// If true, use -1 as a tile number (render nothing)

  int type_alpha;						// Current Opacity of the Type overlay
  int coll_alpha;						// Current Opacity of the Collision overlay

  bool show_fg, show_ty, show_co;

  int type_w, type_h;  	// Typeset texture dimension (tiles)
  int coll_w, coll_h; 	// Collset texture dimension (tiles)
  int tset_w, tset_h;  	// Tileset texture dimension (tiles)

  int onTiles;          // bitwise flag for tiles to place
  int intrpt;           // bitwise flag for interruptions

public:
  CEditMap();

  bool OnInit();
  void OnTerminate();

  bool RenderMap();

public:
  bool OnEvent(SDL_Point* mouse);

private:
  bool handleInterr(SDL_Point* mouse);
  bool handleNewTile(SDL_Point* mouse);
  bool handleGetSet(SDL_Point* mouse);
  bool handleGetTile(SDL_Point* mouse);
  bool handleScroll_bg(SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_fg(SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_ty(SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_co(SDL_Point* mouse, CTile* EditTile);
  bool handleRemove_bg(SDL_Point* mouse, CTile* EditTile);
  bool handleRemove_fg(SDL_Point* mouse, CTile* EditTile);
  bool handleOpac_ty(SDL_Point* mouse);
  bool handleOpac_co(SDL_Point* mouse);
  bool handleLayers(SDL_Point* mouse);
  bool handlePlace(SDL_Point* mouse);
  bool handleQuadrant(SDL_Point* mouse);

public:
  bool OnRender(SDL_Texture* interface, SDL_Point* mouse);

private:
  bool RenderWkspc(SDL_Texture* interface, SDL_Point* mouse);

private:
  bool RenderSidebar(SDL_Texture* interface, SDL_Point* mouse);
  bool drawButtonTileset(SDL_Texture* interface, SDL_Point* mouse);
  bool drawTile(SDL_Texture* interface);
  bool drawActive_bg(SDL_Texture* interface, CTile* ShowTile);
  bool drawActive_fg(SDL_Texture* interface, CTile* ShowTile);
  bool drawActive_ty(SDL_Texture* interface, CTile* ShowTile);
  bool drawActive_co(SDL_Texture* interface, CTile* ShowTile);
  bool drawOpac_ty(SDL_Texture* interface);
  bool drawOpac_co(SDL_Texture* interface);

private:
  bool RenderBottom(SDL_Texture* interface, SDL_Point* mouse);
  bool drawButton_bg(SDL_Texture* interface, SDL_Point* mouse);
  bool drawButton_fg(SDL_Texture* interface, SDL_Point* mouse);
  bool drawOverlayList(SDL_Texture* interface);
  bool drawPlacementList(SDL_Texture* interface);
  bool drawButtonActive(SDL_Texture* interface, SDL_Point* mouse, bool active);
  bool drawQuadrants(SDL_Texture* interface, SDL_Point* mouse);

public:
  bool RenderButton(SDL_Texture* interface, SDL_Point* mouse, SDL_Rect* button, int bsiz, int colX, int colY, bool hl);
};

#endif
