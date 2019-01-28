#include "CEntity.h"

std::vector<EntityTexInfo> CEntity::TextureList;
std::vector<CEntity*> CEntity::EntityList;

namespace {
  const std::string io_path = "../data/maps/";
  const std::string io_ext = ".ent";
}

CEntity::CEntity() {
	sprtSrc = NULL;
	X = Y = 0.0f;
	move_left = move_right = false;
  Permanent = false;

  jump_timer = 0;
  jump_timer_max = 125;

	// Type = ENTITY_TYPE_GENERIC;

	MaxHealth = Health = Damage = 0;
	Dead = false;

	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;
  Stat  = STAT_NONE;

	SpeedX = SpeedY = AccelX = AccelY = 0.0f;
	MaxSpeedX = 10.0f;
	MaxSpeedY = 10.0f;
	MaxAccelX = 0.5f;
	MaxAccelY = 0.75f;

	Jumper = false;
	Grounded = false;

	CurrentFrameCol = 0;
	CurrentFrameRow = 0;
}

CEntity::~CEntity() {
	//
}

void CEntity::OnLoad(SDL_Texture* img, const SDL_Rect& sprR, const SDL_Rect& hitR) {
	sprtSrc = img;
	this->spriteR = sprR;
	this->hitboxR = hitR;
}

void CEntity::OnLoop() {
	// ChkEnviro();
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

	if (Flags & ENTITY_FLAG_GRAVITY) AccelY = MaxAccelY;

	// if (Icy) AccelX = AccelX / 3.0f;

	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	// if (Wet) {
	// 	SpeedX = SpeedX / 1.66f;
	// 	SpeedY = SpeedY / 1.66f;
	// }

	// Make sure we're not overstepping our boundaries,
	// so to speak...
	if (SpeedX > MaxSpeedX) SpeedX = MaxSpeedX;
	if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
	if (SpeedY > MaxSpeedY) SpeedY = MaxSpeedY;
	if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	OnAnimate();
	OnMove(SpeedX, SpeedY);
}

void CEntity::OnAnimate() {
	Anim_Control.OnAnimate();
}

void CEntity::OnRender() {
	SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X, Y);
  // CSurface::OnDraw(Surf_Dest, Tex_Entity, X - CCamera::CameraControl.GetX(),
  //   Y - CCamera::CameraControl.GetY(), Xo + (CurrentFrameCol + Anim_Control.GetCurrentFrame()) * Width,
  //   Yo + CurrentFrameRow * Height, Width, Height);
  SDL_Rect sprFrame = {
    spriteR.x + (CurrentFrameCol + Anim_Control.GetCurrentFrame()) * spriteR.w,
    spriteR.y + CurrentFrameRow * spriteR.h,
    spriteR.w,
    spriteR.h};
  CSurface::OnDraw(sprtSrc, sprFrame, dstWinPos);
}

void CEntity::OnRenderHitbox() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(X + hitboxR.x, Y + hitboxR.y);
  SDL_Rect dHitbox = {dstWinPos.x, dstWinPos.y, hitboxR.w, hitboxR.h};
  CAsset::drawBox(dHitbox, &palette::red);
}

// void CEntity::ChkEnviro()
// {
// 	// at initialization, cX is the center of the hitbox in X,
// 	// and cY is a location inside the hitbox in Y
// 	// (the final quantity in cY is a 0 to 1 ratio;
// 	// a larger ratio leads to a larger Y, and a ratio of
// 	// 0.5 corresponds to the hitbox center in Y)
// 	// uY is Y of the pixel under the hitbox.
// 	int cX = X + Col_X + (Col_Width / 2);
// 	int cY = Y + Col_Y + (Col_Height / 2);
// 	int uY = Y + Col_Y + Col_Height;
// 	int bY = uY - 1;
//
// 	CTile* WTile = CArea::AreaControl.GetTile(cX * TILE_SIZE, cY * TILE_SIZE);
// 	if (WTile == NULL) return;
// 	if (Wet && WTile->TypeID != TILE_TYPE_WATER)
// 	{
// 		Wet = false;
// 	}
// 	if (WTile->TypeID == TILE_TYPE_WATER && !Wet)
// 	{
// 		Wet = true;
// 	}
// 	if (!Wet)
// 	{
// 		CTile* ITile = CArea::AreaControl.GetTile(cX * TILE_SIZE, uY * TILE_SIZE);
// 		if (Icy && ITile->TypeID != TILE_TYPE_ICE)
// 		{
// 			Icy = false;
// 		}
// 		if (ITile->TypeID == TILE_TYPE_ICE && !Icy)
// 		{
// 			Icy = true;
// 		}
// 	}
// }

bool CEntity::Jump() {
	if (Jumper == false) return false;
  jump_timer_init = SDL_GetTicks();
	// SpeedY = -MaxSpeedY;
	return true;
}

void CEntity::JumpRelease() {
  jump_timer_init = false;
}

// bool CEntity::PosValidEntity(CEntity* Entity, int NewX, int NewY)
// {
// 	if (this != Entity && Entity != NULL && Entity->Dead == false &&
// 		Entity->Flags ^ ENTITY_FLAG_MAPONLY &&
// 		Entity->Collides(NewX + Col_X, NewY + Col_Y, Width - Col_Width, Height - Col_Height) == true)
// 	{
// 		CEntityCol EntityCol;
// 		EntityCol.EntityA = this;
// 		EntityCol.EntityB = Entity;
// 		CEntityCol::EntityColList.push_back(EntityCol);
//
// 		// If the entity is NOT hollow, then the requested position is denied.
// 		// Otherwise, return true (i.e., the entities don't stop each other,
// 		// but a collision is still triggered).
// 		if (!(Entity->Flags & ENTITY_FLAG_HOLLOW)) return false;
// 	}
// 	return true;
// }

bool CEntity::Collides(const SDL_Point& tl, const SDL_Point& br) {
	int Xl = (int)(X) + hitboxR.x;
	int Yt = (int)(Y) + hitboxR.y;
	int Xr = Xl + hitboxR.w - 1;
	int Yb = Yt + hitboxR.h - 1;

	if (Yb < br.y) return false;
	if (tl.y < Yt) return false;
	if (Xr < br.x) return false;
	if (tl.x < Xl) return false;

	return true;
}

void CEntity::stopMove() {
	if (SpeedX > 0) AccelX = -MaxAccelX * 1.5;
	if (SpeedX < 0) AccelX = MaxAccelX * 1.5;
	// if (!Icy) {
		if (SpeedX < 2.0f && SpeedX > -2.0f)
		{
			AccelX = 0;
			SpeedX = 0;
		}
	// }
// 	else
// 	{
// 		if (SpeedX < 0.1f && SpeedX > -0.1f)
// 		{
// 			AccelX = 0;
// 			SpeedX = 0;
// 		}
// 	}
}

bool CEntity::OnCollision(CEntity* Entity)
{
	//
	return true;
}

bool CEntity::OnInteract()
{
	return false;
}

void CEntity::OnCleanup()
{

}

//*************************************************************
//*************************************************************
//*************************************************************

void CEntity::GetPos(float& X, float& Y) {
	X = this->X;
	Y = this->Y;
}
