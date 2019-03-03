#include "CSimulate.h"

CSimulate CSimulate::control;

CSimulate::CSimulate() {
  status = INACTIVE;
}

bool CSimulate::OnInit() {
  //
}

simstate CSimulate::getStatus() {
  return status;
}

void CSimulate::stopSim() {
  hero.Flags &= ~Entityflags::GRAVITY;
  CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
  CCamera::CameraControl.FreeTarget();
  status = INACTIVE;
}

void CSimulate::OnTerminate() {
  //
}
