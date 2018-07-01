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
	extern const SDL_Point* c_col;
	extern const SDL_Point* s_col;
	extern const short num_options;
	extern const short opt_w;
	extern const short opt_h;
	extern const short w;
	extern const short h;
	extern const short x;
	extern const short y;
	extern const short stroke_w;
	extern const char* const opt_list[];
	extern const short fill_A;
	namespace audiomenu {
		extern const short num_options;
		extern const short w;
		extern const short h;
		extern const short x;
		extern const short y;
		extern const short name_w;
		extern const short val_w;
		extern const short name_x;
		extern const short val_x;
		extern const short val_h;
  	extern const SDL_Point* empty_col;
		extern const SDL_Point* fill_col;
		extern const SDL_Point* mod_col;
  	extern const SDL_Color* ftex_col;
		extern const char* const header;
		extern const char* const opt_list[];
		enum decision {
			RESUME = 0,
			SFX_VOLUME,
			BGM_VOLUME,
			TYPE_VOLUME,
			AUDIO_OUT,
			SET_DEFAULT,
		};
	};
	namespace videomenu {
		extern const short num_options;
		extern const short w;
		extern const short h;
		extern const short x;
		extern const short y;
		extern const short name_w;
		extern const short val_w;
		extern const short name_x;
		extern const short val_x;
		extern const char* const header;
		extern const char* const opt_list[];
		enum decision {
			RESUME = 0,
			VIDEO_OUT,
		};
	};
	namespace quitmenu {
		extern const SDL_Color* f_def;
		extern const SDL_Color* f_hov;
		extern const SDL_Point* c_col;
		extern const SDL_Point* s_col;
		extern const short num_options;
		extern const short w;
		extern const short h;
		extern const short x;
		extern const short y;
		extern const char* const header;
		extern const char* const opt_list[];
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
private:
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
	void eventMain(const Gamecon& action);
	void eventAudio(const Gamecon& action);
	void eventVideo(const Gamecon& action);
	void eventQuit(const Gamecon& action);

public:
  bool OnRender();
private:
	bool drawMain();
	bool drawAudio();
	bool drawVideo();
	bool drawQuit();
private:
	bool drawVolume(const SDL_Rect& val_bar, const Configflag& vol_type, std::string& val);
public:
	void unpause();
private:
	void reinit();
};
#endif
