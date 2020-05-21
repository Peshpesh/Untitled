#include "CPlanEditor.h"

void CPlanEditor::OnEvent(SDL_Event* Event) {
  // if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

void CPlanEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (handlePlaceTile(m)) return;
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
  CPlanArea::control.changeTile(x, y, Z, workTile, onTiles);
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
