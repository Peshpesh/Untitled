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
    // const short num_config = 4;
    const short w = opt_w;
    const short h = opt_h * (num_options + 1);
    const short x = (WWIDTH - w) / 3;
    const short y = ((WHEIGHT - h) / 5) * 3;
    const short bar_w = w - 40;
    const short bar_h = opt_h / 3;
    const char* const header = "Audio Settings";
    const char* const opt_list[] = {
      "SFX Volume",
      "BGM Volume",
      "Type Volume",
      "Output",
      "Default Settings",
      "Back",
    };
    // const Configflag config_list[] = {
    //   CONFIG_SFX,
    //   CONFIG_BGM,
    //   CONFIG_TEX,
    //   CONFIG_AUDIOOUT,
    // };
	};
	namespace videomenu {
    const short num_options = 2;
    const short w = opt_w;
    const short h = opt_h * (num_options + 1);
    const short x = (WWIDTH - w) / 3;
    const short y = ((WHEIGHT - h) / 5) * 3;
    const char* const header = "Video Settings";
    const char* const opt_list[] = {
      "Display",
      "Back",
    };
	};
	namespace quitmenu {
    const short num_options = 2;
    const short w = opt_w;
    const short h = opt_h * (num_options + 1);
    const short x = (WWIDTH - w) / 3;
    const short y = ((WHEIGHT - h) / 5) * 3;
		const char* const header = "Return to Title?";
    const char* const opt_list[] = {"No","Yes"};
	};
};
