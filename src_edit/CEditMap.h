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
};
namespace map_editor
{
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
    const short bg_x = 260;   // Change Tile button info
    const short bg_y = 510;   //
    const short bg_w = 100;   //
    const short bg_h = 20;    //
    const short fg_x = 260;   // Change Tile button info
    const short fg_y = 540;   //
    const short fg_w = 100;   //
    const short fg_h = 20;    //
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
  namespace rm_flip
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
class CEditMap {
public:
	static CEditMap	MapEditor;

private:
  SDL_Texture* Main_Tileset;  // The actual tileset in use
  SDL_Texture* Type_Tileset;  // Tileset showing tile type
  SDL_Texture* Coll_Tileset;	// Tileset showing collision type

private:
  int active_bg;            // Active tileID
  int active_fg;						// Active foreID
  bool no_bg, no_fg;				// If true, use -1 as a tile number (render nothing)

  int active_type;          // Active typeID
  int type_alpha;						// Current Opacity of the Type overlay

  int active_coll;					// Active tile collision ID
  int coll_alpha;						// Current Opacity of the Collision overlay

  bool show_fg, show_ty, show_co;

  int type_w, type_h;  	// Typeset texture dimension (tiles)
  int coll_w, coll_h; 	// Collset texture dimension (tiles)
  int tset_w, tset_h;  	// Tileset texture dimension (tiles)

  int onTiles;          // bitwise flag for tiles to place
  int intrpt;           // bitwise flag for interruptions

public:
  CEditMap();

  bool OnInit(SDL_Renderer* renderer);

  bool RenderMap(SDL_Renderer* renderer);

	// bool OnEvent(int mX, int mY);
  bool OnEvent(SDL_Point* mouse);
  bool handleInterr(SDL_Point* mouse);
  bool handleNewTile(SDL_Point* mouse);
  bool handleGetSet(SDL_Point* mouse);
  bool handleGetTile(SDL_Point* mouse);
  bool handleScroll_bg(SDL_Point* mouse);
  bool handleScroll_fg(SDL_Point* mouse);
  bool handleScroll_ty(SDL_Point* mouse);
  bool handleScroll_co(SDL_Point* mouse);
  bool handleRemove_bg(SDL_Point* mouse);
  bool handleRemove_fg(SDL_Point* mouse);
  bool handleOpac_ty(SDL_Point* mouse);
  bool handleOpac_co(SDL_Point* mouse);
  bool handleLayers(SDL_Point* mouse);
  bool handlePlace(SDL_Point* mouse);

  bool OnRender(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Point* mouse);
  bool RenderWkspc(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Point* mouse);
  bool RenderSidebar(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Point* mouse);
  bool RenderBottom(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Point* mouse);
  bool RenderButton(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Point* mouse, SDL_Rect* button, int bsiz, int colX, int colY, bool hl);
};

#endif
