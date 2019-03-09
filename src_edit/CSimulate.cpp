#include "CSimulate.h"

CSimulate CSimulate::control;

CSimulate::CSimulate() {
  status = INACTIVE;
  cam_option = TARGET_MODE_NORMAL;
  follow_w = 60;
  follow_h = 50;
  cam_x = 0;
  cam_y = 0;
  edit_xywh = 0;
  edit_sval = "";
}

simstate CSimulate::getStatus() {
  return status;
}

void CSimulate::stopSim() {
  // hero.Flags &= ~Entityflags::GRAVITY;
  CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
  CCamera::CameraControl.FreeTarget();
  status = INACTIVE;
  edit_xywh = simulator::camera::EDIT_NONE;
}

void CSimulate::updateCamera() {
  CCamera::CameraControl.TargetMode = cam_option;
  edit_xywh = simulator::camera::EDIT_NONE;
  switch (cam_option) {
    case TARGET_MODE_NORMAL: {
      CCamera::CameraControl.FreeTarget();
      CCamera::CameraControl.SetPos(cam_x, cam_y);
      break;
    }
    case TARGET_MODE_CENTER: {
      CCamera::CameraControl.SetTarget(&hero.X, &hero.Y, &hero.spriteR.w, &hero.spriteR.h);
      break;
    }
    case TARGET_MODE_FOLLOW: {
      CCamera::CameraControl.SetTarget(&hero.X, &hero.Y, &hero.spriteR.w, &hero.spriteR.h);
      CCamera::CameraControl.SetFollow(follow_w, follow_h);
      break;
    }
    default: break;
  }
}

void CSimulate::OnTerminate() {
  //
}
