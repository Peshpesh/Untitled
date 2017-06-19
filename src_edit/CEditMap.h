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
    // Change Tileset button info
    extern const SDL_Rect button;
    extern const short bsiz;
    extern const SDL_Point* offCol;
    extern const SDL_Point* hoverColor;
    extern const SDL_Point* onCol;
  }
  namespace but_t
  {
    extern const SDL_Rect bg_button;
    extern const SDL_Rect fg_button;
    extern const short bsiz;
    extern const SDL_Point* offCol;
    extern const SDL_Point* hoverColor;
    extern const SDL_Point* onCol;
  }
  namespace but_act_t
  {
    extern const char* const onTitle;
    extern const char* const offTitle;
    extern const SDL_Rect button;
    extern const short bsiz;
    extern const SDL_Point* offCol;
    extern const SDL_Point* offhvCol;
    extern const SDL_Point* onCol;
    extern const SDL_Point* onhvCol;
  }
  namespace but_quad_t
  {
    extern const char* const name_TL;
    extern const char* const name_TR;
    extern const char* const name_BL;
    extern const char* const name_BR;
    extern const short left_x;       //
    extern const short right_x;      //
    extern const short top_y;        //
    extern const short bottom_y;     //
    extern const short w;             //
    extern const short h;             //
    extern const short bsiz;
    extern const SDL_Point* offCol;
    extern const SDL_Point* offhvCol;
    extern const SDL_Point* onCol;
    extern const SDL_Point* onhvCol;
    extern const SDL_Point* editCol;
  }
  namespace disp_t
  {
    extern const short name_offset;
    extern const short sample_x;
    extern const short sample_y;
    extern const short bgfg_x;         // Displayed (current) Tile info
    extern const short bgfg_y;         //
    extern const short bg_x;           // "..." background Tile info
    extern const short bg_y;           //
    extern const short fg_x;           // "..." foreground Tile info
    extern const short fg_y;           //
    extern const short ty_x;           // "..." Tile type info
    extern const short ty_y;           //
    extern const short co_x;           // "..." Tile collision info
    extern const short co_y;           //
    extern const SDL_Rect dummyEntity;
    extern const SDL_Rect dummyOutline;
  }
  namespace opac    // opacity meters
  {
    extern const short w;
    extern const short h;
    extern const short x;
    extern const short ty_y;
    extern const short co_y;
    extern const SDL_Rect typeBar;
    extern const SDL_Rect collBar;
    extern const SDL_Point* fillCol;
    extern const SDL_Point* emptyCol;
  }
  namespace but_rm
  {
    extern const short bg_x;
    extern const short bg_y;
    extern const short fg_x;
    extern const short fg_y;
    extern const short ty_x;
    extern const short ty_y;
    extern const short co_x;
    extern const short co_y;
  }
  namespace view_flip
  {
    extern const short x;
    extern const short y;
  }
  namespace place_flip
  {
    extern const short x;
    extern const short y;
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
  bool handlePlaceDomain(const SDL_Point* mouse);
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
  bool handleQuadrant_lc(const SDL_Point* mouse);

private:
  void placeBlock(const int& x, const int& y);

public:
  bool OnRClick(const SDL_Point* mouse);

private:
  bool handleMakeDomain(const SDL_Point* mouse);
  bool handleQuadrant_rc(const SDL_Point* mouse);
  SDL_Rect getTileDomain(const SDL_Point* A, const SDL_Point* B);
  void resetRClick();

public:
  bool OnRender(SDL_Texture* interface, const SDL_Point* mouse);

private:
  bool RenderWkspc(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawIntrpt(SDL_Texture* interface, const SDL_Point* mouse);
  bool drawTileShadow(const SDL_Point* mouse, const SDL_Point* mapPos);
  bool drawPlaceDomain(const SDL_Point* mouse, const SDL_Point* mapPos);

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

};

#endif
