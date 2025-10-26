#include "CSimPlanEntity.h"

// TODO: all of this

CSimPlanEntity::CSimPlanEntity() {
  sprtSrc = NULL;
  X = Y = 0.0f;

  Flags = PlanEntityflags::HOLLOW;
  // Dead = false;

  direction = 'D';
  ismoving = false;

  SpeedX = SpeedY = 0.0f;
  MaxSpeed = 6.5f;
}

void CSimPlanEntity::OnLoad() {
  // sprtSrc = CEntity::getSrcTexture(Entities::groups::GLOBAL);
  // spriteR = CEntityData::getEntityDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
  // hitboxR = CEntityData::getHitboxDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
}

void CSimPlanEntity::OnLoop() {
  // if ()

  // SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
  // SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

  // OnMove(SpeedX, SpeedY);
}

bool CSimPlanEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  SDL_Rect sprFrame = {
    spriteR.x,
    spriteR.y,
    spriteR.w,
    spriteR.h};
  return CSurface::OnDraw(sprtSrc, &sprFrame, &dstWinPos);
}

void CSimPlanEntity::OnCleanup() {

}
