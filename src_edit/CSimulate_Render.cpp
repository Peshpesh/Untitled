#include "CSimulate.h"

bool CSimulate::OnRender(const SDL_Point* m) {
  bool intrpt = !(CInterrupt::isNone());

  if (!CAsset::drawAppFrame()) return false;

  if (!drawMain(intrpt ? NULL : m)) return false;
  if (!drawCamera(intrpt ? NULL : m)) return false;
  if (!drawManualCam(intrpt ? NULL : m)) return false;
  if (!drawFollowCam(intrpt ? NULL : m)) return false;

  if (intrpt && !drawIntrpt(m)) return false;
  return true;
}

bool CSimulate::drawMain(const SDL_Point* m) {
  using namespace simulator;

	CAsset::drawStrBox(&r_start, bsiz, (m && SDL_PointInRect(m, &r_start)) ?
    ((status == INACTIVE) ? start_hcol : reset_hcol) :
    ((status == INACTIVE) ? start_col : reset_col)
  );

  if (status == ACTIVE || status == SUSPENDED) {
    CAsset::drawStrBox(&r_suspend, bsiz, (m && SDL_PointInRect(m, &r_suspend)) ? suspend_hcol : suspend_col);
    CAsset::drawStrBox(&r_stop, bsiz, (m && SDL_PointInRect(m, &r_stop)) ? stop_hcol : stop_col);
  } else {
    CAsset::drawStrBox(&r_suspend, bsiz, off_col);
    CAsset::drawStrBox(&r_stop, bsiz, off_col);
  }

  Font::NewCenterWrite((status == ACTIVE || status == SUSPENDED) ? reset_lab : start_lab, &r_start);
  Font::NewCenterWrite(suspend_lab, &r_suspend);
  Font::NewCenterWrite(stop_lab, &r_stop);

  return true;
}

bool CSimulate::drawCamera(const SDL_Point* m) {
  using namespace simulator::camera;
  bool retval = true;

  Font::NewCenterWrite(modes_title, &p_modes_title);

  if (status == ACTIVE || status == SUSPENDED) {
    for (int i = 0; i <= TARGET_MODE_FOLLOW; i++) {
      retval *= CAsset::drawStrBox(&r_modes[i], bsiz, (i == cam_option) ? on_col :
        ((m && SDL_PointInRect(m, &r_modes[i])) ? off_hcol : off_col)
      );
      Font::NewCenterWrite(modes[i], &r_modes[i]);
    }
  } else {
    for (int i = 0; i <= TARGET_MODE_FOLLOW; i++) {
      retval *= CAsset::drawStrBox(&r_modes[i], bsiz, in_col);
      Font::NewCenterWrite(modes[i], &r_modes[i]);
    }
  }
  return retval;
}

bool CSimulate::drawManualCam(const SDL_Point* m) {
  using namespace simulator::camera;
  bool retval = true;

  Font::NewCenterWrite(manual_title, &p_manual_title);

  if (status == ACTIVE || status == SUSPENDED) {
    retval *= CAsset::drawStrBox(&r_cam_x, bsiz, (m && SDL_PointInRect(m, &r_cam_x)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_cam_y, bsiz, (m && SDL_PointInRect(m, &r_cam_y)) ? off_hcol : off_col);
  } else {
    retval *= CAsset::drawStrBox(&r_cam_x, bsiz, in_col);
    retval *= CAsset::drawStrBox(&r_cam_y, bsiz, in_col);
  }

  std::string x_s = "X " + Font::intToStr(cam_x);
  std::string y_s = "Y " + Font::intToStr(cam_y);
  Font::NewCenterWrite(x_s.c_str(), &r_cam_x);
  Font::NewCenterWrite(y_s.c_str(), &r_cam_y);
  return retval;
}

bool CSimulate::drawFollowCam(const SDL_Point* m) {
  using namespace simulator::camera;
  bool retval = true;

  Font::NewCenterWrite(follow_title, &p_follow_title);

  if (status == ACTIVE || status == SUSPENDED) {
    retval *= CAsset::drawStrBox(&r_follow_w, bsiz, (m && SDL_PointInRect(m, &r_follow_w)) ? off_hcol : off_col);
    retval *= CAsset::drawStrBox(&r_follow_h, bsiz, (m && SDL_PointInRect(m, &r_follow_h)) ? off_hcol : off_col);
  } else {
    retval *= CAsset::drawStrBox(&r_follow_w, bsiz, in_col);
    retval *= CAsset::drawStrBox(&r_follow_h, bsiz, in_col);
  }

  std::string w_s = "W " + Font::intToStr(follow_w);
  std::string h_s = "H " + Font::intToStr(follow_h);
  Font::NewCenterWrite(w_s.c_str(), &r_follow_w);
  Font::NewCenterWrite(h_s.c_str(), &r_follow_h);

  return retval;
}

bool CSimulate::drawHero() {
  if (status != INACTIVE) {
    return hero.OnRender();
  } return true;
}

bool CSimulate::drawIntrpt(const SDL_Point* m) {
  return true;
}
