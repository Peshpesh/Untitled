#ifndef _C_APP_H_
#define _C_APP_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CEvent.h"
#include "CCamera.h"
#include "CArea.h"
#include "CUI.h"
#include "CChangeTile.h"
#include "CIO.h"
#include "CEntityEdit.h"
#include "CSceneryEdit.h"
#include "Define.h"

#include "CEditMap.h"

enum
{
  MODIFY_MAP = 0,
  MODIFY_NPC,
  REMOVE_NPC,
  MODIFY_SCENE,
  REMOVE_SCENE,
};

// enum
// {
//   INTRPT_NONE = 0,								// No intrpt
//   INTRPT_CH_BTILE = 0x00000001,		// intrpt via bg tile change
//   INTRPT_CH_FTILE = 0x00000002,		// intrpt via fg tile change
//   INTRPT_MODEL = 0x00000004,
// };

// namespace map_editor
// {
//   namespace but_tset
//   {
//     const unsigned short w = 50;    // Change Tileset button info
//     const unsigned short h = 40;    //
//     const short x = 665;            //
//     const short y = 50;             //
//   }
//   namespace but_t
//   {
//     const short bg_x = 260;   // Change Tile button info
//     const short bg_y = 510;   //
//     const short bg_w = 100;   //
//     const short bg_h = 20;    //
//     const short fg_x = 260;   // Change Tile button info
//     const short fg_y = 540;   //
//     const short fg_w = 100;   //
//     const short fg_h = 20;    //
//   }
//   namespace disp_t
//   {
//     const short bgfg_x = 674;         // Displayed (current) Tile info
//     const short bgfg_y = 140;         //
//     const short name_offset = 10;
//     const short bg_x = 674;           // "..." background Tile info
//     const short bg_y = 210;           //
//     const short fg_x = 674;           // "..." foreground Tile info
//     const short fg_y = 280;           //
//     const short ty_x = 674;           // "..." Tile type info
//     const short ty_y = 350;           //
//     const short co_x = 674;           // "..." Tile collision info
//     const short co_y = 420;           //
//   }
//   namespace opac    // opacity meters
//   {
//     const short w = 90;
//     const short h = 4;
//     const short x = 645;
//     const short ty_y = 390;
//     const short co_y = 460;
//   }
//   namespace rm_flip
//   {
//     const short bg_x = 642;
//     const short bg_y = 192;
//     const short fg_x = 642;
//     const short fg_y = 262;
//     const short ty_x = 642;
//     const short ty_y = 332;
//     const short co_x = 642;
//     const short co_y = 402;
//   }
//   namespace view_flip
//   {
//     const short x = 20;
//     const short y = 510;
//   }
//   namespace place_flip
//   {
//     const short x = 150;
//     const short y = 495;
//   }
//   // Map Editor definitions (application static)
//   const unsigned short dummy_x = 522;
//   const unsigned short dummy_y = 0;
// }

namespace npc_editor
{
  const short tbl_nm_x = 250;
  const short tbl_nm_y = 490;
  const short ent_nm_x = 250;
  const short ent_nm_y = 510;
  namespace but_nset
  {
    const short x = 5;
    const short y = 540;
    const short w = 75;
    const short h = 50;
  }
  // Entity Editor definitions (application static)
}

namespace scn_editor
{
  namespace popt_flip
  {
    const short x = 20;
    const short y = 510;
  }
  namespace dp_adj
  {
    const short l_x = 150;
    const short c_x = 250;
    const short u_x = 350;
    const short y = 530;
  }
  const short scn_nm_x = 250;
  const short scn_nm_y = 490;
  const unsigned short scn_nm_w = 160;
  // Scenery Editor definitions (application static)
}

class CApp : public CEvent {
private:
	SDL_Window* Map_Display;    // Edit Window
	SDL_Renderer* Map_Renderer; // Edit Renderer
	SDL_Texture* Type_Tileset;  // Tileset showing tile type
	SDL_Texture* Coll_Tileset;	// Tileset showing collision type
	SDL_Texture* Main_Tileset;  // The actual tileset in use
	SDL_Texture* Map_Interface; // Bordering interface for editor

	bool Running;

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
	CChangeTile PickTile;

	int mouseX;
	int mouseY;

public:
	char* Tileset_Path;
	char* Entity_Path;

	int active_mod;
	int intrpt;
  int OnTiles;
	int tabl_name_W;

public:
	CApp();

	int OnExecute();

	void OnEvent(SDL_Event* Event);

	bool EventOPTS(int mX, int mY);

	bool EventMAPedit(int mX, int mY);

	bool EventNPCedit(int mX, int mY);
	void ModEntity(int mX, int mY);
	bool AddEntity(int Xo, int Yo);
	bool SubEntity(int Xo, int Yo);

	bool EventSCNedit(int mX, int mY);
	bool CheckZup(const int& mX);
	bool CheckZdown(const int& mX);
	float GetZincrement(const int& mX, const int& Xo);
	bool CheckSCNswitch(const int& mY);
	bool CheckSCNchange(const int& mX);

	bool OnInit();

	// Terminates the Map Editor loop
	void OnExit();

	// Handles looping calculations
	void OnLoop();

	// Uses keyboard state to detect directional input from user for moving camera
	void OnMotion(const Uint8 *state);

	void OnClick();

	// Renders graphics
	void OnRender();
	bool RenderMAPedit();
	bool RenderMAPside();
	bool RenderMAPbottom();
	bool RenderNPCedit();
	bool RenderSCNedit();
	bool RenderSCNswitch();
	bool RenderSCNdepth();
	bool RenderButton(int X, int Y, int W, int H, int bsiz, int colX, int colY, bool hl);

	// Destroys all windows, textures, surfaces, renderers...
	void OnTerminate();

	void QueryTileset();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	void OnRButtonDown(int mX, int mY);
};

#endif
