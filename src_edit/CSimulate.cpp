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
  did_edit_xywh = false;
}

simstate CSimulate::getStatus() {
  return status;
}

void CSimulate::stopSim() {
  // hero.Flags &= ~Entityflags::GRAVITY;
  // CCamera::CameraControl.ApplyTargetToStatic();
  CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
  CCamera::CameraControl.FreeTarget();
  status = INACTIVE;
  clearxywh();
}

void CSimulate::clearxywh() {
  edit_xywh = 0;
  edit_sval.clear();
}

void CSimulate::resetxywh() {
  clearxywh();
  CCamera::CameraControl.GetNormalXY(cam_x, cam_y);
  CCamera::CameraControl.GetFollowDims(follow_w, follow_h);
  did_edit_xywh = false;
}

void CSimulate::updateCamera() {
  CCamera::CameraControl.TargetMode = cam_option;
  CCamera::CameraControl.SetPos(cam_x, cam_y);
  CCamera::CameraControl.SetFollowDims(follow_w, follow_h);
  if (cam_option == TARGET_MODE_NORMAL) {
    CCamera::CameraControl.FreeTarget();
  } else {
    CCamera::CameraControl.SetTarget(&hero.X, &hero.Y, &hero.spriteR.w, &hero.spriteR.h);
  }
}

void CSimulate::OnTerminate() {
  //
}
