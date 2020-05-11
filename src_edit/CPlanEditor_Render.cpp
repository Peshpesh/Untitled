#include "CPlanEditor.h"

bool CPlanEditor::OnRender(const SDL_Point& m) {
  // if (!RenderWkspc(mouse)) return false;
  if (!CAsset::drawAppFrame()) return false;
  // if (!RenderSidebar(mouse)) return false;
  // if (!RenderBottom(mouse)) return false;
  return true;
}

void CPlanEditor::RenderMap() {
  // render the area's layers in order from bottom to top
  for (int k = 0; k < CPlanArea::control.LayerList.size(); k++) {
    CPlanArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), k);
    // CInform::InfoControl.pushInform("testing");
  }
}
