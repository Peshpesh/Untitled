#include "CSimulate.h"

void CSimulate::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

void CSimulate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CSimulate::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleStartSim(&m)) return;
  if (handleSuspendSim(&m)) return;
  if (handleStopSim(&m)) return;
  if (handleCameraOption(&m)) return;
}

bool CSimulate::handleStartSim(const SDL_Point* m) {
  if (status != PLACE) {
    if (SDL_PointInRect(m, &simulator::r_start)) {
      if (status == ACTIVE || status == SUSPENDED) stopSim();
      hero.OnLoad();
      status = PLACE;
      return true;
    }
  } else if (CAsset::inWorkspace(m)) {
    hero.Flags |= Entityflags::GRAVITY;
    CCamera::CameraControl.TargetMode = TARGET_MODE_FOLLOW;
    CCamera::CameraControl.SetTarget(&hero.X, &hero.Y, &hero.spriteR.w, &hero.spriteR.h);
    status = ACTIVE;
    return true;
  }
  return false;
}

bool CSimulate::handleSuspendSim(const SDL_Point* m) {
  if (SDL_PointInRect(m, &simulator::r_suspend)) {
    if      (status == ACTIVE)    status = SUSPENDED;
    else if (status == SUSPENDED) status = ACTIVE;
    return true;
  }
  return false;
}

bool CSimulate::handleStopSim(const SDL_Point* m) {
  if (status != INACTIVE && SDL_PointInRect(m, &simulator::r_stop)) {
    stopSim();
    return true;
  }
  return false;
}

bool CSimulate::handleCameraOption(const SDL_Point* m) {
  using namespace simulator::camera;
  if (status != INACTIVE && status != PLACE) {
    for (int i = 0; i <= TARGET_MODE_FOLLOW; i++) {
      if (i != cam_option && SDL_PointInRect(m, &r_modes[i])) {
        cam_option = i;
        return true;
      }
    }
  }
  return false;
}

void CSimulate::OnRButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
}

bool CSimulate::handleInterr(SDL_Event* Event) {
  return false;
}
