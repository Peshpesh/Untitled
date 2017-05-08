#include "CApp.h"

/* The constructor initializes the Running Program flag */
CApp::CApp()
{
	Running = true;
	Map_Display = NULL;
	Map_Renderer = NULL;
	Map_Interface = NULL;
	Type_Tileset = NULL;
	Slope_Tileset = NULL;
	Main_Tileset = NULL;
	// Font = NULL;
	mouseX = mouseY = 0;

	Current_Tile = Current_Fore = 0;
	Current_Type = TILE_TYPE_NONE;
	Current_Slope = SLOPE_FLAT;
	TypesetWidth = TypesetHeight = TilesetWidth = TilesetHeight = 0;
	Tileset_Path = "../res/tile/default.png";
	Entity_Path = "../res/npc/debug.png";

	Active_Mod = MODIFY_MAP;
	tabl_name_W = 0;
}

/* This is the executable member that contains the editor's
* critical functions. Initialization, event handling, data manipulation,
* rendering, and house keeping are done within this member.
*/
int CApp::OnExecute()
{
	// If our initialization function fails, the program will end here.
	if (OnInit() == false)
	{
		return -1;
	}

	// state = keystate;
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	SDL_Event Event;
	// This loop will run endlessly until something makes the Running
	// flag false. That will happen, hopefully, by the user's decision.
	while (Running)
	{
		// Check for pending events; handle them
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
		OnMotion(state);    // For repeating user input (i.e. holding directional button)
		OnClick();     // For holding a mouse button down
		OnLoop();      // Perform necessary manipulations
		OnRender();    // Render updated info
	}

	OnTerminate();       // Clean up the program before exiting
	return 0;
}

int main(int argc, char* argv[])
{
	CApp editor;
	return editor.OnExecute();
}
