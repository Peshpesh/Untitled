#include "CGame.h"

bool CGame::OnInit() {
  diff = CGameinfo::infolist[CGameIO::control.getActiveSlot()]->diff;
  suspend_flag = (diff != BRUTAL) ?
                  INTRPT_PAUSE | INTRPT_VIEW_MAP | INTRPT_INVENTORY :
                  INTRPT_PAUSE;

  CInventory::control.reinit();

  if (!CEntityIO::Init()) {
    // ERROR
    return false;
  } initHero();

  CHud::control.assignHp(&Hero.Health, &Hero.MaxHealth);
  // CHud::control.assignEn(&Hero., &Hero.);
  // CHud::control.assignSp(&., &.);

	// complete transition
  if (!handleTransit()) {
    return false;
  }
  return true;
}

void CGame::initHero() {
  // initialize hero
  using namespace Entities;

  Hero.Permanent  = true;
  Hero.X          = CGamedata::control.data_hero.X;
  Hero.Y          = CGamedata::control.data_hero.Y;
  Hero.MaxHealth  = CGamedata::control.data_hero.max_health;
  Hero.Health     = CGamedata::control.data_hero.health;

  Hero.OnLoad(CEntityIO::getSrcTexture(groups::GLOBAL),
              CEntityData::getEntityDims(groups::GLOBAL, global::PLAYER),
              CEntityData::getHitboxDims(groups::GLOBAL, global::PLAYER));

  CCamera::CameraControl.SetTarget(&Hero.X, &Hero.Y, &Hero.spriteR.w, &Hero.spriteR.h);
  CCamera::CameraControl.TargetMode = TARGET_MODE_FOLLOW;

  // TESTING/DEBUGGING
  // CCamera::CameraControl.SetLimits(0,0,1050,MAP_HEIGHT*TILE_SIZE);
  // CCamera::CameraControl.EnableLim();

  CEntity::EntityList.push_back(&Hero); // GOOD LUCK //
}
