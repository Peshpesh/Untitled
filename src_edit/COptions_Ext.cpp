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

  const short bsiz          = 2;
  const SDL_Point* in_col   = &palette::dark_gray;
  const SDL_Point* off_col  = &palette::light_gray;
  const SDL_Point* off_hcol = &palette::white;
  const SDL_Point* on_col   = &palette::green;
  const short max_edit_dig = 4;
}
