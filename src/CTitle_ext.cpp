#include "CTitle.h"

namespace Title {
  const SDL_Color* f_def = &rgb::black;
  const SDL_Color* f_hov = &rgb::black;
  const SDL_Color* f_lock = &rgb::gray;
  const SDL_Point* o_def = &palette::white;
  const SDL_Point* o_hov = &palette::light_green;
  const SDL_Point* o_lock = &palette::light_gray;
  const short num_options = 4;
  const char* const opt_list[] = {
    "New",
    "Load",
    "Options",
    "Quit",
  };
  const short dx = 5;       // horizontal offset for each menu option
  const short dy = 30;      // vertical offset for each menu option
  const short w = 200;                // menu width
  const short h = dy * num_options;   // menu height
  const short x = (WWIDTH - w) / 2;   // menu x position
  const short y = 200;                // menu y position
  const short stroke_w = 2;

  namespace new_game {
    //
  };
  namespace load_game {
    //
  };
  namespace options {
    //
  };
};
