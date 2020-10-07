#include "CSimEntity.h"

CSimEntity::CSimEntity() {
  sprtSrc = NULL;
  X = Y = 0.0f;

  Flags = Entityflags::GRAVITY | Entityflags::HOLLOW;
  // Flags = Entityflags::HOLLOW;
  Dead = false;

  jump_timer = 0;
  jump_timer_max = 125;
  jump_timer_init = 0;

  Jumper = false;
  Grounded = false;

  move_left = false;
  move_right = false;

  SpeedX = SpeedY = AccelX = AccelY = 0.0f;
  MaxSpeedX = 6.5f;
  MaxSpeedY = 8.5f;
  MaxAccelX = 0.5f;
  MaxAccelY = 0.75f;
}

void CSimEntity::OnLoad() {
  sprtSrc = CEntity::getSrcTexture(Entities::groups::GLOBAL);
  spriteR = CEntityData::getEntityDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
  hitboxR = CEntityData::getHitboxDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
}

void CSimEntity::OnLoop() {
  if (jump_timer_init) {
    jump_timer = SDL_GetTicks() - jump_timer_init;
    if (jump_timer >= jump_timer_max) {
      SpeedY = -MaxSpeedY;
      jump_timer_init = 0;
    } else {
      SpeedY = -(MaxSpeedY / 2.0) * (1.0 + ((float)(jump_timer)/(float)(jump_timer_max)));
    }
  }

  if (move_left == false && move_right == false) stopMove();
  else if (move_left) AccelX = -MaxAccelX;
  else if (move_right) AccelX = MaxAccelX;

  if (Flags & Entityflags::GRAVITY) AccelY = MaxAccelY;

  SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
  SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

  // Make sure we're not overstepping our boundaries,
  // so to speak...
  if (SpeedX > MaxSpeedX) SpeedX = MaxSpeedX;
  if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
  if (SpeedY > MaxSpeedY) SpeedY = MaxSpeedY;
  if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

  OnMove(SpeedX, SpeedY);
}

bool CSimEntity::Jump() {
  if (Jumper == false) return false;
  jump_timer_init = SDL_GetTicks();
  return true;
}

void CSimEntity::JumpRelease() {
  jump_timer_init = false;
}

void CSimEntity::stopMove() {
  if (SpeedX > 0) AccelX = -MaxAccelX * 1.5;
  if (SpeedX < 0) AccelX = MaxAccelX * 1.5;
  if (SpeedX < 2.0f && SpeedX > -2.0f) {
    AccelX = 0;
    SpeedX = 0;
  }
}

bool CSimEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  SDL_Rect sprFrame = {
    spriteR.x,
    spriteR.y,
    spriteR.w,
    spriteR.h};
  return CSurface::OnDraw(sprtSrc, &sprFrame, &dstWinPos);
}

void CSimEntity::OnCleanup() {

}
