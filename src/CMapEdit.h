#ifndef _CMAPEDIT_H_
#define _CMAPEDIT_H_

#include <SDL.h>
#include <vector>

#include "CSurface.h"
#include "CEvent.h"
#include "CCamera.h"
#include "CArea.h"
#include "CMEUI.h"
#include "CME_ChTile.h"
#include "CME_IO.h"
#include "CME_NPC.h"
#include "CDialogue.h"
#include "CHUD.h"
#include "CME_Resource.h"

class CMapEdit : public CEvent {
private:
	SDL_Window* Map_Display;    // Edit Window
	SDL_Renderer* Map_Renderer; // Edit Renderer
	SDL_Texture* Type_Tileset;  // Tileset showing tile type
	SDL_Texture* Slope_Tileset;	// Tileset showing slope type
	SDL_Texture* Main_Tileset;  // The actual tileset in use
	SDL_Texture* Map_Interface; // Bordering interface for editor
	SDL_Texture* Font;

	bool Running;

	int Current_Tile;           // Active tileID
	int Current_Fore;			// Active foreID
	int Current_Type;           // Active typeID
	int Current_Slope;			// Active tile slope
	int TypesetWidth, TypesetHeight;  // Typeset texture dimension (tiles)
	int SlopesetWidth, SlopesetHeight; // Slopeset texture dimension (tiles)
	int TilesetWidth, TilesetHeight;  // Tileset texture dimension (tiles)

	int mouseX;
	int mouseY;

public:
	char* Tileset_Path;
	char* Entity_Path;

	int Active_Mod;
	int tabl_name_W;

	enum
	{
		MODIFY_MAP = 0,
		MODIFY_NPC,
		REMOVE_NPC,
		MODIFY_SCENE
	};

public:
	CMapEdit();

	void OnExecute(const Uint8 *keystate);

	void OnEvent(SDL_Event* Event);

	bool OnStart();

	// Terminates the Map Editor loop
	void OnExit();

	// Handles looping calculations
	void OnLoop();

	// Uses keyboard state to detect directional input from user for moving camera
	void OnMotion();

	void OnClick();

	// Renders graphics
	void OnRender();
	bool RenderNPCedit();
	bool RenderSCNedit();

	// Destroys all windows, textures, surfaces, renderers...
	void OnCleanup();

	void ModEntity(int mX, int mY);

	bool AddEntity(int Xo, int Yo);

	void QueryTileset();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	void OnRButtonDown(int mX, int mY);

	const Uint8 *state;
};

#endif
