#include "CPause.h"

namespace pausemenu {
  const SDL_Color* f_def = &rgb::white;
  const SDL_Color* f_hov = &rgb::cyan;
  const SDL_Point* c_col = &palette::black;
  const SDL_Point* s_col = &palette::light_cyan;
	const short num_options = 4;
	const short w = 250;
  const short opt_w = w;
  const short opt_h = 40;
	const short h = opt_h * num_options;
	const short x = (WWIDTH - w) / 3;
	const short y = ((WHEIGHT - h) / 5) * 3;
	const short stroke_w = 2;
	const char* const opt_list[] = {"Resume","Audio","Video","Quit"};
	namespace audiomenu {
    const short num_options = 6;
    const short w = 350;
    const short h = opt_h * (num_options + 1);
    const short x = (WWIDTH - w) / 3;
    const short y = ((WHEIGHT - h) / 5) * 3;
    const short name_w = w / 3;
    const short val_w = w / 2;
    const short name_x = x;
    const short val_x = name_x + name_w + (w - name_w - val_w) / 2;
    const short val_h = opt_h / 2;
    const SDL_Point* empty_col = &palette::gray;
    const SDL_Point* fill_col = &palette::dark_cyan;
    const SDL_Point* mod_col = &palette::green;
    const SDL_Color* ftex_col = &rgb::black;
    const char* const header = "Audio Settings";
    const char* const opt_list[] = {
      "Back",
      "SFX Volume",
      "BGM Volume",
      "Type Volume",
      "Output",
      "Default Settings",
    };
	};
	namespace videomenu {
    const short num_options = 2;
    const short w = 300;
    const short h = opt_h * (num_options + 1);
    const short x = (WWIDTH - w) / 3;
    const short y = ((WHEIGHT - h) / 5) * 3;
    const short name_w = w / 2;
    const short val_w = w / 2;
    const short name_x = x;
    const short val_x = name_x + name_w + (w - name_w - val_w) / 2;
    const char* const header = "Video Settings";
    const char* const opt_list[] = {
      "Back",
      "Display",
    };
	};
	namespace quitmenu {
    const SDL_Color* f_def = &rgb::white;
    const SDL_Color* f_hov = &rgb::light_red;
    const SDL_Point* c_col = &palette::black;
    const SDL_Point* s_col = &palette::red;
    const short num_options = 2;
    const short w = opt_w;
    const short h = opt_h * (num_options + 1);
    const short x = (WWIDTH - w) / 3;
    const short y = ((WHEIGHT - h) / 5) * 3;
		const char* const header = "Return to Title?";
    const char* const opt_list[] = {"No","Yes"};
	};
};
