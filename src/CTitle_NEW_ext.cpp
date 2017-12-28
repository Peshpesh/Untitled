#include "CTitle.h"

namespace Title {
  const SDL_Color* f_def = &rgb::white;
  const SDL_Color* f_hov = &rgb::light_blue;
  const SDL_Color* f_act = &rgb::light_red;
  const short num_options = 4;
  const short w = 200;
  const short h = 30 * num_options;
  const short x = (WWIDTH - w) / 2;
  const short y = 200;
  const char* const opt_list[] = {
    "New",
    "Load",
    "Options",
    "Quit",
  };
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
