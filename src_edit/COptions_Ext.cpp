#include "COptions.h"

namespace g_options {
  const short w_cam             = 70;
  const short h_cam             = 15;
  const short x_camxlim         = 40;
  const short y_camxlim         = WHEIGHT + (EHEIGHT - WHEIGHT - (h_cam * 3)) / 2;
  const short x_camylim         = 40;
  const short y_camylim         = y_camxlim + (h_cam * 2);

  const char* const camxlim_title = "Camera X Limits";
  const SDL_Point p_camxlim_title = {x_camxlim + w_cam, y_camxlim - (h_cam / 2)};
  const char* const camylim_title = "Camera Y Limits";
  const SDL_Point p_camylim_title = {x_camylim + w_cam, y_camylim - (h_cam / 2)};

  const SDL_Rect r_cam_xmin = CAsset::getRect(x_camxlim, y_camxlim, w_cam, h_cam);
  const SDL_Rect r_cam_ymin = CAsset::getRect(x_camylim, y_camylim, w_cam, h_cam);
  const SDL_Rect r_cam_xmax = CAsset::getRect(x_camxlim + w_cam, y_camxlim, w_cam, h_cam);
  const SDL_Rect r_cam_ymax = CAsset::getRect(x_camylim + w_cam, y_camylim, w_cam, h_cam);

  const short w_app_camlim  = w_cam;
  const short h_app_camlim  = h_cam * 2;
  const short x_app_camlim  = r_cam_xmax.x + r_cam_xmax.w + 20;
  const short y_app_camlim  = WHEIGHT + (EHEIGHT - WHEIGHT - h_app_camlim - h_limswitch) / 2;
  const short w_limswitch   = w_app_camlim / 2;
  const short h_limswitch   = h_cam;
  const short x_limswitch   = x_app_camlim;
  const short y_limswitch   = y_app_camlim + h_app_camlim;

  const char* const app_camlim_title  = "Apply Limits";
  const char* const showlim_title     = "Show";
  const char* const uselim_title      = "Use";
  const SDL_Rect r_app_camlim = CAsset::getRect(x_app_camlim, y_app_camlim, w_app_camlim, h_app_camlim);
  const SDL_Rect r_showlim    = CAsset::getRect(x_limswitch, y_limswitch, w_limswitch, h_limswitch);
  const SDL_Rect r_uselim     = CAsset::getRect(x_limswitch + w_limswitch, y_limswitch, w_limswitch, h_limswitch);

  const short bsiz          = 2;
  const SDL_Point* in_col   = &palette::dark_gray;
  const SDL_Point* off_col  = &palette::light_gray;
  const SDL_Point* off_hcol = &palette::white;
  const SDL_Point* on_col   = &palette::green;
  const short max_edit_dig = 4;
}
