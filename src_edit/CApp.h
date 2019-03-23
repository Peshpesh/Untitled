#ifndef _C_APP_H_
#define _C_APP_H_

#include <SDL.h>
#include <vector>

#include "CInterrupt.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CCamera.h"
#include "CArea.h"
#include "CChangeTile.h"
#include "CFileIO.h"
#include "CModel.h"
#include "CTerminate.h"
#include "Define.h"

#include "CEditMap.h"
#include "CEntityEditor.h"
#include "CSceneryEditor.h"
#include "CSimulate.h"
#include "COptions.h"

enum {
  MODIFY_MAP = 0,
  MODIFY_NPC,
  MODIFY_SCENE,
  MODIFY_SIM,
  MODIFY_OPTIONS,
};

namespace io_ui
{
  // IO button info
  extern const char* const new_label;
  extern const char* const load_label;
  extern const char* const save_label;
  extern const SDL_Rect newButton;
  extern const SDL_Rect loadButton;
  extern const SDL_Rect saveButton;
  extern const SDL_Point* newButCol;
  extern const SDL_Point* loadButCol;
  extern const SDL_Point* saveButCol;
  extern const SDL_Point* newHovCol;
  extern const SDL_Point* loadHovCol;
  extern const SDL_Point* saveHovCol;
  extern const short bsiz;
}

namespace modelSwitch
{
  extern const SDL_Rect button;
  extern const SDL_Point* offCol;
  extern const SDL_Point* onCol;
  extern const SDL_Point* hovCol;
  extern const short bsiz;
  extern const char* const label;
}

namespace engineSwitch
{
  extern const char* engineName[];
  extern const SDL_Rect engineButton[];
  extern const SDL_Point* engineOnCol;
  extern const SDL_Point* engineOffCol;
  extern const SDL_Point* engineHvCol;
  extern const short bsiz;
}

class CApp : public CEvent {
private:
	SDL_Window* Map_Display;    // Edit Window

	bool Running;

  SDL_Point mouse;
	int mouseX;
	int mouseY;

  bool pan_l, pan_r, pan_u, pan_d;

public:
	int active_mod;

public:
	CApp();

	int OnExecute();

	void OnEvent(SDL_Event* Event);
  bool handleInterr(SDL_Event* Event);

	bool handleEngSwitch(const SDL_Point* m);
  bool handleModelSwitch(const SDL_Point* m);
  bool handleIO(const SDL_Point* m);

	bool OnInit();
	void OnExit();

	// Handles looping calculations
	void OnLoop();

	// Uses keyboard state to detect directional input from user for moving camera
	void OnMotion(const Uint8 *state);

	// Renders graphics
	void OnRender();
  bool renderEngSwitch();
  bool renderModelButton();
  bool renderIOButtons();

	// Destroys all windows, textures, surfaces, renderers...
	void OnTerminate();

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnKeyUp(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	void OnRButtonDown(int mX, int mY);
};

#endif
