#include "CGame.h"

CGame CGame::control;

CGame::CGame() {
  //
}

bool CGame::OnInit() {
  if (!CEntityIO::Init()) {
    // ERROR
  }

  initHero();

	// complete transition
  using namespace location;
  if (!CArea::control.Load(abbrname[CTransition::control.locationID])) {
    // ERROR LOADING AREA
  }
  //  Entities
  if (!CEntityIO::Load(abbrname[CTransition::control.locationID])) {
    // ERROR LOADING ENTITIES
  }
  //  Scenery
  if (!CSceneryIO::Load(abbrname[CTransition::control.locationID])) {
    // ERROR LOADING SCENERY
  }
  // transition complete
  CTransition::control.activated = false;
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

  // TESTING/DEBUGGING
  CCamera::CameraControl.SetTarget(&Hero.X, &Hero.Y);
  CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;

  CEntity::EntityList.push_back(&Hero); // GOOD LUCK //
}

void CGame::OnCleanup() {

}

void CGame::OnExit() {

}
