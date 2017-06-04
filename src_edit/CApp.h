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
#include "DefineMapEdit.h"

enum
{
  INTRPT_NONE = 0,								// No interrupt
  INTRPT_CH_BTILE = 0x00000001,		// interrupt via bg tile change
  INTRPT_CH_FTILE = 0x00000002,		// interrupt via fg tile change
  INTRPT_MODEL = 0x00000004,
};

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
