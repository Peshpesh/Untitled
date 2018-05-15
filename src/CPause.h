#ifndef _C_PAUSE_H_
#define _C_PAUSE_H_

#include "CAsset.h"
#include "CType.h"
#include "CEvent.h"
#include "CControls.h"
#include "CConfig.h"
#include "CInterrupt.h"
#include "Define.h"

namespace pausemenu {
	enum menus {
    MAIN = 0,
    ADJUST_AUDIO,
    ADJUST_VIDEO,
    QUIT_GAME,
  };
	enum decision {
		RESUME = 0,
		AUDIO_MENU,
		VIDEO_MENU,
		QUIT_MENU,
	};
	extern const SDL_Color* f_def;
	extern const SDL_Color* f_hov;
	extern const SDL_Point* o_def;
	extern const SDL_Point* o_hov;
	extern const short num_options;
	extern const short opt_w;
	extern const short opt_h;
	extern const short w;
	extern const short h;
	extern const short x;
	extern const short y;
	extern const short stroke_w;
	extern const char* const opt_list[];
	namespace audiomenu {
		//
	};
	namespace videomenu {
		//
	};
	namespace quitmenu {
		//
	};
};

class CPause : public CEvent {
	CPause();

  short menu_kind;
  short pos;

public:
  static CPause control;
  bool call_quit;

  void OnEvent(SDL_Event* Event);

  bool OnRender();

private:
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void eventMain(const Gamecon& action);
	void eventAudio(const Gamecon& action);
	void eventVideo(const Gamecon& action);
	void eventQuit(const Gamecon& action);

	void unpause();
	void reinit();
};
#endif
