#include "CAnchorScenery.h"

CAnchorScenery CAnchorScenery::Control;

namespace {
  const SDL_Color* col_anch = &rgb::light_red;
  const SDL_Color* col_disp = &rgb::light_orange;
}

CAnchorScenery::CAnchorScenery() {
  anch_x = anch_y = 0.0;
  anch_z = 1.0;
  disp_x = disp_y = 64;
  layer = 0;
}

void CAnchorScenery::OnInit(const unsigned short& layer) {
  this->layer = layer;
  anch_z = CScenery::layerList[layer];
}

void CAnchorScenery::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

bool CAnchorScenery::OnRender() {
  double rel_x, rel_y;
  SDL_Point p;

  rel_x = CCamera::CameraControl.trueXToRel(anch_x, anch_z);
  rel_y = CCamera::CameraControl.trueYToRel(anch_y, anch_z);
  p = CCamera::CameraControl.GetWinRelPoint(rel_x, rel_y);
  Font::NewCenterWrite(FONT_MINI, "X", &p, col_anch);

  rel_x += disp_x;
  rel_y += disp_y;
  p = CCamera::CameraControl.GetWinRelPoint(rel_x, rel_y);
  Font::NewCenterWrite(FONT_MINI, "X", &p, col_disp);

  return true;
}

void CAnchorScenery::advanceAnchor() {
  double rel_x = CCamera::CameraControl.trueXToRel(anch_x, anch_z) + disp_x;
  double rel_y = CCamera::CameraControl.trueYToRel(anch_y, anch_z) + disp_y;
  anch_x = CCamera::CameraControl.relXToTrue(rel_x, anch_z);
  anch_y = CCamera::CameraControl.relYToTrue(rel_y, anch_z);
}

void CAnchorScenery::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: CInterrupt::removeFlag(INTRPT_GRAB_ANCH | INTRPT_MAKE_ANCH); break;
    case SDLK_ESCAPE: CInterrupt::removeFlag(INTRPT_GRAB_ANCH | INTRPT_MAKE_ANCH); break;
    default: break;
  }
}

void CAnchorScenery::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (!CAsset::inWorkspace(&m)) return;

  if (CInterrupt::isFlagOn(INTRPT_GRAB_ANCH)) handleGrabAnchor(&m);
  else handleMakeAnchor(&m);
}

void CAnchorScenery::handleGrabAnchor(const SDL_Point* m) {
  for (int i = CScenery::sceneryList.size() - 1; i >= 0; i--) {
    if (layer == CScenery::sceneryList[i].layer) {
      double rel_x = CCamera::CameraControl.trueXToRel(CScenery::sceneryList[i].true_x, anch_z);
      double rel_y = CCamera::CameraControl.trueYToRel(CScenery::sceneryList[i].true_y, anch_z);
      int w = CScenery::sceneryList[i].srcR.w;
      int h = CScenery::sceneryList[i].srcR.h;
      SDL_Point w_pos = CCamera::CameraControl.GetWinRelPoint(rel_x, rel_y);
      SDL_Rect w_rec = CAsset::getRect(w_pos.x, w_pos.y, w, h);
      if (SDL_PointInRect(m, &w_rec)) {
        anch_x = CScenery::sceneryList[i].true_x;
        anch_y = CScenery::sceneryList[i].true_y;
        break;
      }
    }
  }
  CInterrupt::removeFlag(INTRPT_GRAB_ANCH);
}

void CAnchorScenery::handleMakeAnchor(const SDL_Point* m) {
  // clicks are RELATIVE to a true x, y given some depth z.
  // We must convert these relative coordinates to true x, y and
  // store its associated z value
  SDL_Point r_pos = CCamera::CameraControl.GetCamRelPoint(m);
  anch_x = CCamera::CameraControl.relXToTrue(r_pos.x, anch_z);
  anch_y = CCamera::CameraControl.relYToTrue(r_pos.y, anch_z);
  CInterrupt::removeFlag(INTRPT_MAKE_ANCH);
}
