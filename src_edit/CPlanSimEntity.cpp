#include "CPlanSimEntity.h"

// TODO: all of this

CPlanSimEntity::CPlanSimEntity() {
  sprtSrc = NULL;
  X = Y = 0.0f;

  Flags = PlanEntityflags::HOLLOW;
  // Dead = false;

  direction = 'D';
  idle = true;

  SpeedX = SpeedY = 0.0f;
  MaxSpeed = 6.5f;
}

void CPlanSimEntity::OnLoad() {
  sprtSrc = CEntity::getSrcTexture(Entities::groups::GLOBAL);
  spriteR = CEntityData::getEntityDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
  hitboxR = CEntityData::getHitboxDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
}

void CPlanSimEntity::OnLoop() {
  // if (move_left == false && move_right == false) stopMove();
  // else if (move_left) AccelX = -MaxAccelX;
  // else if (move_right) AccelX = MaxAccelX;
  //
  // SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
  // SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();
  //
  // // Make sure we're not overstepping our boundaries,
  // // so to speak...
  // if (SpeedX > MaxSpeedX) SpeedX = MaxSpeedX;
  // if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
  // if (SpeedY > MaxSpeedY) SpeedY = MaxSpeedY;
  // if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;
  //
  // OnMove(SpeedX, SpeedY);
  // if ()

  // SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
  // SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

  // OnMove(SpeedX, SpeedY);
}

bool CPlanSimEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  SDL_Rect sprFrame = {spriteR.x, spriteR.y, spriteR.w, spriteR.h};
  return CSurface::OnDraw(sprtSrc, &sprFrame, &dstWinPos);
}

void CPlanSimEntity::OnCleanup() {

}
