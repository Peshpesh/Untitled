#ifndef _C_APP_H_
#define _C_APP_H_

// Critical dependencies
#include <SDL.h>
#include "Define.h"

// Systematic dependencies
#include "CEvent.h"
#include "CSurface.h"
#include "CSound.h"
#include "CError.h"

// Utility dependencies
#include "CAsset.h"
#include "CType.h"
#include "CUtil.h"

// Mechanical dependencies
#include "CControls.h"
#include "CConfig.h"
#include "CCamera.h"

// Structural dependencies
#include "CGameIO.h"
#include "CMode.h"
#include "CTitle.h"
#include "CGame.h"
#include "CTransition.h"

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
	SDL_Window* Win_Display;    // Main Window

private:
	SDL_Texture* DEBUG_TEXTURE;

private:
	int esc_init;

public:

	CApp();

	int	OnExecute();

public:
	// Initializes SDL, main window and renderer, and test/introductory graphics
	bool OnInit();

	// Handles non-motion events from the user
	void OnEvent(SDL_Event* Event);

	// Terminates the game loop
	void OnExit();

	// Handles looping calculations, such as for idle animations
	void OnLoop();
	void OnPause();

	// Renders graphics
	void OnRender();

	// Destroys all windows, textures, surfaces, renderers...
	void OnCleanup();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void OnKeyUp(SDL_Keycode sym, Uint16 mod);

	void drawQuitMsg();
};
#endif
