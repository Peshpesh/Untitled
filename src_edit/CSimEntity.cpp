#include "CSimEntity.h"

CSimEntity::CSimEntity() {
  sprtSrc = NULL;
	X = Y = 0.0f;

  // Flags = Entityflags::GRAVITY | Entityflags::HOLLOW;
  Flags = Entityflags::HOLLOW;
	Dead = false;

	SpeedX = SpeedY = AccelX = AccelY = 0.0f;
	MaxSpeedX = 10.0f;
	MaxSpeedY = 10.0f;
	MaxAccelX = 0.5f;
	MaxAccelY = 0.75f;
}

void CSimEntity::OnLoad() {
  sprtSrc = CEntity::getSrcTexture(Entities::groups::GLOBAL);
  spriteR = CEntityData::getEntityDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
  hitboxR = CEntityData::getHitboxDims(Entities::groups::GLOBAL, Entities::global::PLAYER);
}

void CSimEntity::OnLoop() {
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
