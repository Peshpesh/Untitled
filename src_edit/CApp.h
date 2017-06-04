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
#include "DefineNpcEdit.h"
#include "DefineScnEdit.h"

enum
{
  INTRPT_NONE = 0,								// No interrupt
  INTRPT_CH_BTILE = 0x00000001,		// interrupt via bg tile change
  INTRPT_CH_FTILE = 0x00000002,		// interrupt via fg tile change
  INTRPT_MODEL = 0x00000004,
};

namespace map_editor
{
  namespace but_tset
  {
    const unsigned short w = 50;              // #define TS_CHG_BUT_W 50     // Change Tileset button info
    const unsigned short h = 40;              // #define TS_CHG_BUT_H 40     //
    const short x = 665;              // #define TS_CHG_BUT_X 665    //
    const short y = 50;              // #define TS_CHG_BUT_Y 50     //
  }
  namespace but_t
  {
    const short bg_x = 260;      // #define BTILE_CHG_BUT_W 100   // Change Tile button info
    const short bg_y = 510;      // #define BTILE_CHG_BUT_H 20   //
    const short bg_w = 100;      // #define BTILE_CHG_BUT_X 260  //
    const short bg_h = 20;      // #define BTILE_CHG_BUT_Y 510  //
    const short fg_x = 260;      // #define FTILE_CHG_BUT_W 100   // Change Tile button info
    const short fg_y = 540;      // #define FTILE_CHG_BUT_H 20   //
    const short fg_w = 100;      // #define FTILE_CHG_BUT_X 260  //
    const short fg_h = 20;      // #define FTILE_CHG_BUT_Y 540  //
  }
  namespace disp_t
  {
    const short bgfg_x = 674;        // #define DISP_TILE_X 674     // Displayed (current) Tile info
    const short bgfg_y = 140;        // #define DISP_TILE_Y 140     //
            // #define DISP_NAME_OFFSET 10
    const short bg_x = 674;        // #define DISP_BTILE_X 674    // "..." background Tile info
    const short bg_y = 210;        // #define DISP_BTILE_Y 210    //
    const short fg_x = 674;        // #define DISP_FTILE_X 674    // "..." foreground Tile info
    const short fg_y = 280;        // #define DISP_FTILE_Y 280    //
    const short ty_x = 674;        // #define DISP_TYPE_X 674     // "..." Tile type info
    const short ty_y = 350;        // #define DISP_TYPE_Y 350     //
    const short co_x = 674;        // #define DISP_COLL_X 674    // "..." Tile collision info
    const short co_y = 420;        // #define DISP_COLL_Y 420    //
  }
  namespace opac
  {
    const short w = 90;    // #define ALPH_TYPE_Y 390
    const short h = 4;    // #define ALPH_COLL_Y 460
    const short x = 645;    // #define ALPH_BAR_X 645
    const short ty_y = 390;    // #define ALPH_BAR_W 90
    const short co_y = 460;    // #define ALPH_BAR_H 4
  }
  namespace erase_flip
  {
    const short bg_x = 642;              // #define BACK_SWIT_X 642
    const short bg_y = 192;              // #define BACK_SWIT_Y 192
    const short fg_x = 642;              // #define FORE_SWIT_X 642
    const short fg_y = 262;              // #define FORE_SWIT_Y 262
    const short ty_x = 642;
    const short ty_y = 332;
    const short co_x = 642;
    const short co_y = 402;
  }
  namespace view_flip
  {
    // #define VIEWOPTS_X 20
    // #define VIEWOPTS_Y 510
    const short x = 20;
    const short y = 510;
  }
  namespace place_flip
  {
    // #define TILEOPTS_X 150
    // #define TILEOPTS_Y 495
    const short x = 150;
    const short y = 495;
  }
  // Map Editor definitions (application static)
                // #define DUMMY_ENTITY_X 522
                // #define DUMMY_ENTITY_Y 0
  const unsigned short dummy_x = 522;
  const unsigned short dummy_y = 0;
}

// namespace npc_editor
// {
//
// }
//
// namespace scn_editor
// {
//
// }

class CApp : public CEvent {
private:
	SDL_Window* Map_Display;    // Edit Window
	SDL_Renderer* Map_Renderer; // Edit Renderer
	SDL_Texture* Type_Tileset;  // Tileset showing tile type
	SDL_Texture* Coll_Tileset;	// Tileset showing collision type
	SDL_Texture* Main_Tileset;  // The actual tileset in use
	SDL_Texture* Map_Interface; // Bordering interface for editor

	bool Running;

	int Current_Tile;           // Active tileID
	int Current_Fore;						// Active foreID
	bool NoBack, NoFore;				// If true, use -1 as a tile number (render nothing)
	int Current_Type;           // Active typeID
	int Type_Alpha;							// Current Opacity of the Type overlay
	int Current_Coll;					  // Active tile collision ID
	int Coll_Alpha;						  // Current Opacity of the Collision overlay
	bool View_Fore, View_Type, View_Coll;
	int TypesetWidth, TypesetHeight;  	// Typeset texture dimension (tiles)
	int CollsetWidth, CollsetHeight; 	// Collset texture dimension (tiles)
	int TilesetWidth, TilesetHeight;  	// Tileset texture dimension (tiles)
	CChangeTile PickTile;

	int mouseX;
	int mouseY;

public:
	char* Tileset_Path;
	char* Entity_Path;

	int Active_Mod;
	int Interrupt;
  int OnTiles;
	int tabl_name_W;

	enum
	{
		MODIFY_MAP = 0,
		MODIFY_NPC,
		REMOVE_NPC,
		MODIFY_SCENE,
		REMOVE_SCENE,
	};

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
