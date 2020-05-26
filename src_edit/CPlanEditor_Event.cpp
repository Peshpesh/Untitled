#include "CPlanEditor.h"

void CPlanEditor::OnEvent(SDL_Event* Event) {
  // if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

void CPlanEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CAsset::inWorkspace(m)) {
    if (handlePlaceTile(m)) return;
  } else {
    if (handleSolidOpts(m)) return;
    if (handleTypeOpts(m)) return;
    if (handlePlaceOpts(m)) return;
    if (handleVisOpts(m)) return;
  }
}

bool CPlanEditor::handlePlaceTile(const SDL_Point& m) {
  if (CAsset::inWorkspace(m)) {
    int mX = CCamera::CameraControl.GetX() + m.x;
    int mY = CCamera::CameraControl.GetY() + m.y;
    placeTile(mX, mY);
    return true;
  }
  return false;
}

void CPlanEditor::placeTile(const int& x, const int &y) {
  CPlanArea::control.changeTile(x, y, Z, workTile, placeflag);
}

bool CPlanEditor::handleVisOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace visOpts;

  for (int i = 0; i < nOpts; i++) {
    if (SDL_PointInRect(&m, &buttons[i])) {
      visflag ^= opts[i]; // toggle flag (on -> off, off -> on)
      return true;
    }
  }
  return false;
}

bool CPlanEditor::handlePlaceOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace placeOpts;

  for (int i = 0; i < nOpts; i++) {
    if (SDL_PointInRect(&m, &buttons[i])) {
      placeflag ^= opts[i]; // toggle flag (on -> off, off -> on)
      return true;
    }
  }
  return false;
}

bool CPlanEditor::handleSolidOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace solidOpts;

  if (SDL_PointInRect(&m, &button)) {
    workTile.solid = !(workTile.solid);
    return true;
  }
  return false;
}

bool CPlanEditor::handleTypeOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace typeOpts;

  SDL_Rect targetR = {0, 0, type_sz, type_sz};
  int k = 0;
  for (int j = 0; j < CTileset::TSControl.type_h; j++) {
    for (int i = 0; i < CTileset::TSControl.type_w; i++) {
      targetR.x = pos.x + ((k % cols) * (type_sz + spac));
      targetR.y = pos.y + ((k / cols) * (type_sz + spac));
      if (SDL_PointInRect(&m, &targetR)) {
        workTile.type = k;
        return true;
      }
      k++;
    }
  }
  return false;
}

void CPlanEditor::extendMap_R() {

}

void CPlanEditor::extendMap_L() {

}

void CPlanEditor::extendMap_D() {

}

void CPlanEditor::extendMap_U() {

}

void CPlanEditor::removeMap_R() {

}

void CPlanEditor::removeMap_L() {

}

void CPlanEditor::removeMap_D() {

}

void CPlanEditor::removeMap_U() {

}
