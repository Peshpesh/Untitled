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
  if (handleStopSim(&m)) return;
}

bool CSimulate::handleStartSim(const SDL_Point* m) {
  if (status != PLACE) {
    if (SDL_PointInRect(m, &simulator::r_start)) {
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

bool CSimulate::handleStopSim(const SDL_Point* m) {
  if (status != INACTIVE && SDL_PointInRect(m, &simulator::r_stop)) {
    stopSim();
    return true;
  }
  return false;
}

void CSimulate::OnRButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
}

bool CSimulate::handleInterr(SDL_Event* Event) {
  return false;
}
