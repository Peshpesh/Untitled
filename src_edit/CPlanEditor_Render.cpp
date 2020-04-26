#include "CPlanEditor.h"

void CPlanEditor::RenderMap() {
  // render the area's layers in order from bottom to top
  for (int k = 0; k < CPlanArea::control.LayerList.size(); k++) {
    CPlanArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), k, visflag);
    CInform::InfoControl.pushInform("testing");
  }
}
