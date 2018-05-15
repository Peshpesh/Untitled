#include "CPause.h"

namespace pausemenu {
  const SDL_Color* f_def = &rgb::black;
  const SDL_Color* f_hov = &rgb::white;
  const SDL_Point* o_def = &palette::white;
  const SDL_Point* o_hov = &palette::red;
	const short num_options = 4;
	const short opt_w = 100;
	const short opt_h = 30;
	const short w = 150;
	const short h = opt_h * 4;
	const short x = 100;
	const short y = 100;
	const short stroke_w = 2;
	const char* const opt_list[] = {"Resume","Adjust Audio","Adjust Video","Quit"};
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
