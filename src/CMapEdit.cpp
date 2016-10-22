#include "CMapEdit.h"

/* The constructor initializes the Running Program flag */
CMapEdit::CMapEdit()
{
	Running = true;
	Map_Display = NULL;
	Map_Renderer = NULL;
	Map_Interface = NULL;
	Type_Tileset = NULL;
	Slope_Tileset = NULL;
	Main_Tileset = NULL;
	Font = NULL;
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
void CMapEdit::OnExecute(const Uint8 *keystate)
{
	// If our initialization function fails, the program will end here.
	if (OnStart() == false)
	{
		return;
	}

	state = keystate;
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
		OnMotion();    // For repeating user input (i.e. holding directional button)
		OnClick();     // For holding a mouse button down
		OnLoop();      // Perform necessary manipulations
		OnRender();    // Render updated info
	}

	OnCleanup();       // Clean up the program before exiting
	return;
}

int CMapEdit::GetIntBigO(const int& X)
{
	int order = 1;
	// How big is the number (order)?
	while (X / (order * 10) != 0)
	{
		// if the loop condition is nonzero, then that means the denominator
		// isn't large enough to reduce the fraction to zero...
		// The fraction reduces to zero IF the denominator exceeds
		// the numerator, which is what we're looking for.
		// EX: First loop does N / 10. If zero, then abs(N) is less than 10 (Magnitude of 10^0, or 1).
		//     Otherwise, next loop does N / 100. If zero, then abs(N) is less than 100. (Mag 10^1, or 10)
		//     Next loop would be N / 1000... And on until the loop ends.
		order *= 10;
	}
	return order;
}
