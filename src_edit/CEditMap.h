#ifndef _C_EDITMAP_H_
#define _C_EDITMAP_H_

#include "CSurface.h"
#include "CAsset.h"
#include "CFont.h"
#include "CArea.h"
#include "CCamera.h"
#include "CChangeTile.h"
#include "Define.h"

enum interrupts
{
  INTRPT_NONE = 0,
  INTRPT_CHANGE_BG = 0x00000001,		// intrpt via bg tile change
  INTRPT_CHANGE_FG = 0x00000002,		// intrpt via fg tile change
  INTRPT_MODEL = 0x00000004,
};

enum
{
  MODIFY_TILE_TL = 0,
  MODIFY_TILE_TR,
  MODIFY_TILE_BL,
  MODIFY_TILE_BR,
};

// Map engine namespaces //
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
    const short y = 490;
    const short w = 48;
    const short h = 16;
    const short bsiz = 2;
  }
  namespace but_quad_t
  {
    static const char* name_TL = "TL";
    static const char* name_TR = "TR";
    static const char* name_BL = "BL";
    static const char* name_BR = "BR";
    const short left_x = 260;       //
    const short right_x = 284;      //
    const short top_y = 510;        //
    const short bottom_y = 534;     //
    const short w = 24;             //
    const short h = 24;             //
    const short bsiz = 2;
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
    static const SDL_Rect dummyEntity = {522, 0, TILE_SIZE, TILE_SIZE};
    static const SDL_Rect dummyOutline = {522, 32, TILE_SIZE, TILE_SIZE};
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
// Map engine namespaces //

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
  const SDL_Point* shadowColor;
  unsigned int shadow_w;

private:
  int type_alpha;						// Current Opacity of the Type overlay
  int coll_alpha;						// Current Opacity of the Collision overlay

  bool show_fg, show_ty, show_co;

  int type_w, type_h;  	// Typeset texture dimension (tiles)
  int coll_w, coll_h; 	// Collset texture dimension (tiles)
  int tset_w, tset_h;  	// Tileset texture dimension (tiles)

  int onTiles;          // bitwise flag for tiles to place
  int intrpt;           // bitwise flag for interruptions

private:
  SDL_Point* rClickA;
  SDL_Point* rClickB;
  const SDL_Point* flexAreaColor;
  const SDL_Point* fixAreaColor;
  const SDL_Point* hoverAreaColor;
  unsigned int rc_area_w;

public:
  CEditMap();

  bool OnInit();
  void OnTerminate();

  bool RenderMap();

public:
  bool OnLClick(const SDL_Point* mouse);

private:
  bool handleNewRegion(const SDL_Point* mouse);
  bool handleInterr(const SDL_Point* mouse, CTile* EditTile);
  bool handleNewTile(const SDL_Point* mouse);
  bool handleGetSet(const SDL_Point* mouse);
  bool handleGetTile(const SDL_Point* mouse);
  bool handleScroll_bg(const SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_fg(const SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_ty(const SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_co(const SDL_Point* mouse, CTile* EditTile);
  bool handleRemove_bg(const SDL_Point* mouse, CTile* EditTile);
  bool handleRemove_fg(const SDL_Point* mouse, CTile* EditTile);
  bool handleOpac_ty(const SDL_Point* mouse);
  bool handleOpac_co(const SDL_Point* mouse);
  bool handleLayers(const SDL_Point* mouse);
  bool handlePlace(const SDL_Point* mouse);
  bool handleActTile(const SDL_Point* mouse, bool& active);
  bool handleQuadrant(const SDL_Point* mouse);

public:
  bool OnRClick(const SDL_Point* mouse);
  void resetRClick();

private:

public:
  bool OnRender(SDL_Texture* interface, const SDL_Point* mouse);

private:
  bool RenderWkspc(SDL_Texture* interface, const SDL_Point* mouse);

private:
  bool RenderSidebar(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawButtonTileset(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawActiveTiles(SDL_Texture* interface);
  bool drawSampleTile(SDL_Texture* interface, CTile* ShowTile, const SDL_Rect* dstR);
  bool drawActive_bg(SDL_Texture* interface, CTile* ShowTile);
  bool drawActive_fg(SDL_Texture* interface, CTile* ShowTile);
  bool drawActive_ty(SDL_Texture* interface, CTile* ShowTile);
  bool drawActive_co(SDL_Texture* interface, CTile* ShowTile);
  bool drawOpac_ty(SDL_Texture* interface);
  bool drawOpac_co(SDL_Texture* interface);

private:
  bool RenderBottom(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawButton_bg(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawButton_fg(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawOverlayList(SDL_Texture* interface);
  bool drawPlacementList(SDL_Texture* interface);
  bool drawButtonActive(SDL_Texture* interface, const SDL_Point* mouse, bool active);
  bool drawQuadrants(SDL_Texture* interface, const SDL_Point* mouse);

public:
  bool RenderButton(SDL_Texture* interface, const SDL_Point* mouse, SDL_Rect* button, int bsiz, int colX, int colY, bool hl);
};

#endif
