#include "CGame.h"

bool CGame::OnInit() {
  CDiff::setDiff(CGameinfo::infolist[CGameIO::control.getActiveSlot()]->diff);
  if (CDiff::getDiff() != BRUTAL) {
    CInterrupt::setSuspend(INTRPT_PAUSE | INTRPT_VIEW_MAP | INTRPT_INVENTORY);
  } else {
    CInterrupt::setSuspend(INTRPT_PAUSE);
  }

  CInventory::control.reinit();

  if (!CEntityIO::Init()) {
    // ERROR
    return false;
  } initHero();

  CHud::control.assignHp(&CHero::Hero.Health, &CHero::Hero.MaxHealth);
  // CHud::control.assignEn(&Hero., &Hero.);
  // CHud::control.assignSp(&., &.);

	// complete transition
  if (!handleTransit()) {
    return false;
  }
  // testing
  CPhrase test("This is just a test. This is just a test. This is just a test. This is just a test.",16.0,5000);
  CDialogue::control.convo.push_back(test);
  CDialogue::control.resetTimer();
  CInterrupt::appendFlag(INTRPT_DIALOGUE);
  return true;
}

void CGame::initHero() {
  // initialize hero
  using namespace Entities;

  CHero::Hero.Permanent  = true;
  CHero::Hero.X          = CGamedata::control.data_hero.X;
  CHero::Hero.Y          = CGamedata::control.data_hero.Y;
  CHero::Hero.MaxHealth  = CGamedata::control.data_hero.max_health;
  CHero::Hero.Health     = CGamedata::control.data_hero.health;

  CHero::Hero.OnLoad(CEntityIO::getSrcTexture(groups::GLOBAL),
              CEntityData::getEntityDims(groups::GLOBAL, global::PLAYER),
              CEntityData::getHitboxDims(groups::GLOBAL, global::PLAYER));

  CCamera::CameraControl.SetTarget(&CHero::Hero.X, &CHero::Hero.Y, &CHero::Hero.spriteR.w, &CHero::Hero.spriteR.h);
  CCamera::CameraControl.TargetMode = TARGET_MODE_FOLLOW;

  // TESTING/DEBUGGING
  // CCamera::CameraControl.SetLimits(0,0,1050,MAP_HEIGHT*TILE_SIZE);
  // CCamera::CameraControl.EnableLim();

  CEntity::EntityList.push_back(&CHero::Hero); // GOOD LUCK //
}
