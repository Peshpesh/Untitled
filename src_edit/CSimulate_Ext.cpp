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
  namespace draft {
    const SDL_Rect r_draftname = CAsset::getRect(x_main + w_main + 20, y_main, 140, h_main);
    const SDL_Point p_draftname_title = {r_draftname.x + (r_draftname.w / 2), r_draftname.y - (r_draftname.h / 2)};
    const char* const draftname_title = "Current Draft";

    const SDL_Rect r_newdraft = CAsset::getRect(r_draftname.x, r_draftname.y + (r_draftname.h * 2), r_draftname.w, r_draftname.h);
    const SDL_Point p_newdraft_title = {r_newdraft.x + (r_newdraft.w / 2), r_newdraft.y - (r_newdraft.h / 2)};
    const char* const newdraft_title = "Load New Draft";

    const short w_opts = w_main;
    const short h_opts = h_main;
    const short x_opts = r_draftname.x + r_draftname.w + 20;
    const short y_opts = r_draftname.y;

    const char* const opts_title = "Draft Options";
    const SDL_Point p_opts_title = {x_opts + (w_opts / 2), y_opts - (h_opts / 2)};
    const SDL_Rect r_clear = CAsset::getRect(x_opts, y_opts, w_opts, h_opts);
    const SDL_Rect r_show  = CAsset::getRect(x_opts, y_opts + h_opts, w_opts, h_opts);
    const SDL_Rect r_zpos  = CAsset::getRect(x_opts, y_opts + (h_opts * 2), w_opts, h_opts);

    const short bsiz          = 2;
    const SDL_Point* in_col   = &palette::dark_gray;
    const SDL_Point* off_col  = &palette::light_gray;
    const SDL_Point* off_hcol = &palette::white;
    const SDL_Point* on_col   = &palette::green;
  }
  namespace camera {
    const short max_edit_dig = 4;
    const short w_mode  = w_main;
    const short h_mode  = h_main;
    const short x_mode  = WWIDTH + ((EWIDTH - WWIDTH - w_mode) / 2);
    const short y_mode  = 20;
    const char* const modes[] = {
      "Manual",
      "Center",
      "Follow",
    };
    const char* const modes_title = "Cam Mode";
    const SDL_Point p_modes_title = {x_mode + (w_mode / 2), y_mode - (h_mode / 2)};
    const SDL_Rect r_modes[] = {
      CAsset::getRect(x_mode, y_mode, w_mode, h_mode),
      CAsset::getRect(x_mode, y_mode + h_mode, w_mode, h_mode),
      CAsset::getRect(x_mode, y_mode + (h_mode * 2), w_mode, h_mode),
    };

    const short w_manual = 90;
    const short h_manual = h_mode;
    const short x_manual = WWIDTH + ((EWIDTH - WWIDTH - w_manual) / 2);
    const short y_manual = y_mode + (h_mode * 3) + 20;
    const char* const manual_title = "Manual Position";
    const SDL_Point p_manual_title = {x_manual + (w_manual / 2), y_manual - (h_manual / 2)};
    const SDL_Rect r_cam_x = CAsset::getRect(x_manual, y_manual, w_manual / 2, h_manual);
    const SDL_Rect r_cam_y = CAsset::getRect(x_manual + (w_manual / 2), y_manual, w_manual / 2, h_manual);

    const short w_follow = w_manual;
    const short h_follow = h_manual;
    const short x_follow = x_manual;
    const short y_follow = y_manual + (h_manual * 2);
    const char* const follow_title = "Follow Bounds";
    const SDL_Point p_follow_title = {x_follow + (w_follow / 2), y_follow - (h_follow / 2)};
    const SDL_Rect r_follow_w = CAsset::getRect(x_follow, y_follow, w_follow / 2, h_follow);
    const SDL_Rect r_follow_h = CAsset::getRect(x_follow + (w_follow / 2), y_follow, w_follow / 2, h_follow);

    const short w_app_mf = w_follow;
    const short h_app_mf = h_follow;
    const short x_app_mf = x_follow;
    const short y_app_mf = y_follow + h_follow + 20;
    const char* const app_mf_title = "Apply XYWH";
    const SDL_Rect r_app_mf = CAsset::getRect(x_app_mf, y_app_mf, w_app_mf, h_app_mf);

    const short bsiz          = 2;
    const SDL_Point* in_col   = &palette::dark_gray;
    const SDL_Point* off_col  = &palette::light_gray;
    const SDL_Point* off_hcol = &palette::white;
    const SDL_Point* on_col   = &palette::green;
  }
}
