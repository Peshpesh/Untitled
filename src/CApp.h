#ifndef _C_APP_H_
#define _C_APP_H_

// Critical dependencies
#include <SDL.h>
#include "Define.h"

// Systematic dependencies
#include "CEvent.h"
#include "CSurface.h"
#include "CSound.h"

// Utility dependencies
#include "CAsset.h"
#include "CType.h"

// Mechanical dependencies
#include "CControls.h"
#include "CCamera.h"

// Structural dependencies
#include "CMode.h"
#include "CTitle.h"


// #include "CArea.h"
// #include "CEntity.h"

// #include "CAnimation.h"
// #include "CPlayer.h"
// #include "CHUD.h"
// #include "CEntityMod.h"
// #include "CCinema.h"
// #include "CTransport.h"
// #include "CGamedata.h"
// #include "CMenu.h"
// #include "Config.h"
// #include "CInventory.h"
// #include "CPause.h"
// #include "CEntityRes.h"
// #include "CSceneryMod.h"

namespace gen {
	extern const char* const quit_msg;
	extern const short quit_msg_f;
	extern const SDL_Point quit_msg_p;
	extern const SDL_Color* quit_msg_c;
}

class CApp : public CEvent
{
private:
	bool	Running;
	// bool	Paused;
	// bool	Suspend;			// gameplay loop suspension (frozen)
	SDL_Window* Win_Display;    // Main Window
	// SDL_Renderer* Win_Renderer; // Main Renderer

private:
	SDL_Texture* DEBUG_TEXTURE;
	// CPlayer		Player;
	// CPause		PauseMenu;

private:
	int esc_init;
	// int esc_time;

public:

	CApp();

	int	OnExecute();

public:

	// Initializes SDL, main window and renderer, and test/introductory graphics
	bool OnInit();
	// bool InitGame();

	// Handles non-motion events from the user
	void OnEvent(SDL_Event* Event);

	// Terminates the game loop
	void OnExit();

	// Handles looping calculations, such as for idle animations
	void OnLoop();
	void OnPause();
	// void ExitGame();

	// Renders graphics
	void OnRender();

	// Destroys all windows, textures, surfaces, renderers...
	void OnCleanup();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);

	void drawQuitMsg();
};
#endif
