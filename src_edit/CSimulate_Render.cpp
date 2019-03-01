#include "CSimulate.h"

bool CSimulate::OnRender(const SDL_Point* m) {
  bool intrpt = !(CInterrupt::isNone());
  if (!CAsset::drawAppFrame()) return false;

  if (!drawMain(intrpt ? NULL : m)) return false;

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

bool CSimulate::drawIntrpt(const SDL_Point* m) {
  return true;
}
