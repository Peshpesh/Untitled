#ifndef _C_EDITMAP_H_
#define _C_EDITMAP_H_

#include "CInterrupt.h"
#include "CInform.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
#include "CArea.h"
#include "CCamera.h"
#include "CChangeTile.h"
#include "CTileset.h"
#include "Define.h"

enum
{
  MODIFY_TILE_TL = 0,
  MODIFY_TILE_TR,
  MODIFY_TILE_BL,
  MODIFY_TILE_BR,
};

// Map engine namespaces //
namespace mapEngine
{
  namespace but_tset
  {
    // Change Tileset button info
    extern const char* const label;
    extern const SDL_Rect button;
    extern const short bsiz;
    extern const SDL_Point* offCol;
    extern const SDL_Point* hoverColor;
    extern const SDL_Point* onCol;
  }
  namespace but_t
  {
    extern const char* const bg_label;
    extern const char* const fg_label;
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
    extern const char* const labels[];
    extern const SDL_Rect buttons[];
    extern const short bsiz;
    extern const SDL_Point* offCol;
    extern const SDL_Point* offhvCol;
    extern const SDL_Point* onCol;
    extern const SDL_Point* onhvCol;
    extern const SDL_Point* editCol;
  }
  namespace disp_t
  {
    extern const short namePos_x;
    extern const short nameOffset_y;
    extern const SDL_Point stage_pos;
    extern const SDL_Point bg_pos;
    extern const SDL_Point fg_pos;
    extern const SDL_Point ty_pos;
    extern const SDL_Point co_pos;
    extern const short arrSpac;
    extern const short rmOffset_x;
    extern const short rmOffset_y;
    extern const short rm_sz;
    extern const short rm_bsiz;
    extern const SDL_Color* arrCol;
    extern const SDL_Color* arrHovCol;
    extern const SDL_Point* rmCol;
    extern const SDL_Point* rmHovCol;
  }
  namespace opac    // opacity meters
  {
    extern const SDL_Rect typeBar;
    extern const SDL_Rect collBar;
    extern const SDL_Point* fillCol;
    extern const SDL_Point* emptyCol;
  }
  namespace view_flip
  {
    extern const SDL_Point* onCol;
    extern const SDL_Point* offCol;
    extern const short x;
    extern const short y;
    extern const short w;
    extern const short h;
    extern const short bsiz;
    extern const short col_h;
    extern const short list_x;
    extern const short list_y;
    extern const char* labels[];
  }
  namespace place_flip
  {
    extern const SDL_Point* onCol;
    extern const SDL_Point* offCol;
    extern const short x;
    extern const short y;
    extern const short w;
    extern const short h;
    extern const short bsiz;
    extern const short col_h;
    extern const short list_x;
    extern const short list_y;
    extern const char* labels[];
  }
} // Map engine namespaces //

class CEditMap : public CEvent {
public:
	static CEditMap	MapEditor;

private:
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

  bool show_bg, show_fg, show_ty, show_co;

  int type_w, type_h;  	// Typeset texture dimension (tiles)
  int coll_w, coll_h; 	// Collset texture dimension (tiles)

  int onTiles;          // bitwise flag for tiles to place

private:
  SDL_Point* rClickA;
  SDL_Point* rClickB;
  const SDL_Point* flexAreaColor;
  const SDL_Point* fixAreaColor;
  const SDL_Point* hoverAreaColor;
  unsigned short rc_area_w;

public:
  CEditMap();

  bool OnInit();

  void OnTerminate();

  bool RenderMap();

public:
  void OnEvent(SDL_Event* Event);

private:
  bool handleInterr(SDL_Event* Event);
  void handleChangeTS(SDL_Event* Event);
  void handleChangeTile(SDL_Event* Event, int intrpt);
  CTile* getModTile();

public:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

private:
  bool handleAreaModify(SDL_Keycode sym, Uint16 mod);

public:
  void OnLButtonDown(int mX, int mY);

private:
  bool handlePlaceDomain(const SDL_Point* mouse);
  bool handleNewTile(const SDL_Point* mouse);
  bool handleGetSet(const SDL_Point* mouse);
  bool handleGetTile(const SDL_Point* mouse);

  bool handleScroll_bg(const SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_fg(const SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_ty(const SDL_Point* mouse, CTile* EditTile);
  bool handleScroll_co(const SDL_Point* mouse, CTile* EditTile);
  char getScrollDir(const SDL_Point* tPos, const SDL_Point* mouse);

  bool handleTileReset(const SDL_Point* mouse, CTile* EditTile);

  bool handleOpac_ty(const SDL_Point* mouse);
  bool handleOpac_co(const SDL_Point* mouse);

  bool handleLayers(const SDL_Point* mouse);
  bool handlePlace(const SDL_Point* mouse);
  bool handleActTile(const SDL_Point* mouse, bool& active);
  bool handleQuadrant_lc(const SDL_Point* mouse);

private:
  void placeBlock(const int& x, const int& y);

public:
  void OnRButtonDown(int mX, int mY);

private:
  bool handleMakeDomain(const SDL_Point* mouse);
  bool handleQuadrant_rc(const SDL_Point* mouse);
  SDL_Rect getTileDomain(const SDL_Point* A, const SDL_Point* B);
  void resetRClick();

public:
  bool OnRender(const SDL_Point* mouse);

private:
  bool RenderWkspc(const SDL_Point* mouse);
  bool drawIntrpt(const SDL_Point* mouse);
  bool drawTileShadow(const SDL_Point* mouse, const SDL_Point* mapPos);
  bool drawPlaceDomain(const SDL_Point* mouse, const SDL_Point* mapPos);

private:
  bool RenderSidebar(const SDL_Point* mouse);
  bool drawButtonTileset(const SDL_Point* mouse);
  bool drawActiveTiles();
  bool drawSampleTile(const CTile* ShowTile, const SDL_Rect* dstR);
  bool drawActive_bg(const CTile* ShowTile, const SDL_Point* mouse);
  bool drawActive_fg(const CTile* ShowTile, const SDL_Point* mouse);
  bool drawActive_ty(const CTile* ShowTile, const SDL_Point* mouse);
  bool drawActive_co(const CTile* ShowTile, const SDL_Point* mouse);
  bool drawTileButtons(const SDL_Point* tPos, const SDL_Point* mouse);
  bool drawOpac_ty();
  bool drawOpac_co();

private:
  bool RenderBottom(const SDL_Point* mouse);
  bool drawButton_bg(const SDL_Point* mouse);
  bool drawButton_fg(const SDL_Point* mouse);
  bool drawOverlayList();
  bool drawPlacementList();
  bool drawButtonActive(const SDL_Point* mouse);
  bool drawQuadrants(const SDL_Point* mouse);
};

#endif
