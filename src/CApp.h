#ifndef _CAPP_H_
#define _CAPP_H_

#include <SDL.h>

#include "Define.h"
#include "CArea.h"
#include "CCamera.h"
#include "CEntity.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAnimation.h"
#include "CPlayer.h"
#include "CHUD.h"
#include "CEntityMod.h"
#include "CCinema.h"
#include "CTransport.h"
#include "CGamedata.h"
#include "CMenu.h"
#include "CTitle.h"
#include "Config.h"
#include "CInventory.h"
#include "CPause.h"
#include "CEntityRes.h"
#include "CSceneryMod.h"

#include "CMapEdit.h"

class CApp : public CEvent
{
private:
	bool	Running;
	bool	Paused;
	bool	Suspend;			// gameplay loop suspension (frozen)
//	bool	Killgame;			// call to end the game
	SDL_Window* Win_Display;    // Main Window
	SDL_Renderer* Win_Renderer; // Main Renderer

private:
	SDL_Texture* TESTSFC;
	CPlayer		Player;
	CPause		PauseMenu;

public:

	CApp();

	int	OnExecute();

public:

//	CAnimation Yoshi;

	// Initializes SDL, main window and renderer, and test/introductory graphics
	bool OnInit();
	bool InitGame();

	// Handles non-motion events from the user
	void OnEvent(SDL_Event* Event);

	// Terminates the game loop
	void OnExit();

	// Handles looping calculations, such as for idle animations
	void OnLoop();
	void OnPause();
	void ExitGame();

	// Uses keyboard state to detect directional input from user for moving focus
	void OnMotion();

	// Renders graphics
	void OnRender();

	// Destroys all windows, textures, surfaces, renderers...
	void OnCleanup();

	const Uint8 *state = SDL_GetKeyboardState(NULL);

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);
};
#endif
