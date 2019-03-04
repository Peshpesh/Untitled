#include "CSimulate.h"

namespace simulator {
  const char* const start_lab   = "Start";
  const char* const reset_lab   = "Reset";
  const char* const suspend_lab = "Suspend";
  const char* const stop_lab    = "Stop";
  const short w_main            = 70;
  const short h_main            = 15;
  const short x_main            = 20;
  const short y_main            = WHEIGHT + (EHEIGHT - WHEIGHT - (h_main * 3)) / 2;
  const SDL_Rect r_start        = CAsset::getRect(x_main, y_main, w_main, h_main);
  const SDL_Rect r_suspend      = CAsset::getRect(x_main, r_start.y + h_main, w_main, h_main);
  const SDL_Rect r_stop         = CAsset::getRect(x_main, r_suspend.y + h_main, w_main, h_main);
  const short bsiz              = 2;
  const SDL_Point* off_col      = &palette::dark_gray;
  const SDL_Point* start_col    = &palette::green;
  const SDL_Point* start_hcol   = &palette::light_green;
  const SDL_Point* reset_col    = &palette::cyan;
  const SDL_Point* reset_hcol   = &palette::light_cyan;
  const SDL_Point* suspend_col  = &palette::orange;
  const SDL_Point* suspend_hcol = &palette::light_orange;
  const SDL_Point* stop_col     = &palette::red;
  const SDL_Point* stop_hcol    = &palette::light_red;
  namespace camera {
    const short w_mode  = w_main;
    const short h_mode  = h_main;
    const short x_mode  = x_main + w_main + 10;
    const short y_mode  = y_main;
    const char* const modes[] = {
      "Manual",
      "Center",
      "Follow",
    };
    const SDL_Rect r_modes[] = {
      CAsset::getRect(x_mode, y_mode, w_mode, h_mode),
      CAsset::getRect(x_mode, y_mode + h_mode, w_mode, h_mode),
      CAsset::getRect(x_mode, y_mode + (h_mode * 2), w_mode, h_mode),
    };
    const short bsiz          = 2;
    const SDL_Point* in_col   = &palette::dark_gray;
    const SDL_Point* off_col  = &palette::light_gray;
    const SDL_Point* off_hcol = &palette::white;
    const SDL_Point* on_col   = &palette::green;
  }
}
