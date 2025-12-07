#include "CApp.h"

void CApp::OnLoop() {
  if (CInterrupt::isNone() && (CSimulate::control.getStatus() == pfmsimulator::INACTIVE || CSimulate::control.getStatus() == pfmsimulator::PLACE)) {
    if (pan_l) CCamera::CameraControl.OnMove(-6, 0);
    if (pan_r) CCamera::CameraControl.OnMove(6, 0);
    if (pan_u) CCamera::CameraControl.OnMove(0, -6);
    if (pan_d) CCamera::CameraControl.OnMove(0, 6);
  }

  CInform::InfoControl.OnLoop();

  SDL_GetMouseState(&mouseX, &mouseY);
  mouse.x = mouseX;
  mouse.y = mouseY;

  CCamera::CameraControl.OnLoop();

  CStage::control.OnLoop(mouse);

  if (SDL_GetWindowFlags(Map_Display) & SDL_WINDOW_MINIMIZED) {
    SDL_RestoreWindow(Map_Display);
  }

  CFPS::FPSControl.OnLoop();
}
