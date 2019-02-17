#include "CSimulate.h"

namespace simulator {
  const char* const start_lab   = "Start";
  const char* const reset_lab   = "Reset";
  const char* const suspend_lab = "Suspend";
  const char* const stop_lab    = "Stop";
  const SDL_Point* off_col      = &palette::silver;
  const SDL_Point* start_col    = &palette::green;
  const SDL_Point* start_hcol   = &palette::light_green;
  const SDL_Point* reset_col    = &palette::cyan;
  const SDL_Point* reset_hcol   = &palette::light_cyan;
  const SDL_Point* suspend_col  = &palette::orange;
  const SDL_Point* suspend_hcol = &palette::light_orange;
  const SDL_Point* stop_col     = &palette::red;
  const SDL_Point* stop_hcol    = &palette::light_red;
}
