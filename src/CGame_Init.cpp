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
  // CPhrase test("This is just a test.",3.0,100);
  // test.setResponses("Yea","noop");
  // CDialogue::control.convo.push_back(test);
  // CDialogue::control.resetTimer();
  // CDialogue::control.convo.push_back(CPhrase("Peri.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("Our blue star.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("The beginning and end of all cycles.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("My only constant.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("Every cycle, this rock is born of your fire.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("From the earth springs life, and water nurtures this life to its end.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("Dusts of the dead scatter to the wind, until there is no more life to give.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("With a Cataclysm, this rock is returned to you and born again - all the same.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("I know life is never exactly the same from cycle to cycle but...",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("... This one is different.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("Life possesses power that I have never known it to possess.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("Its power has made days unpredictable.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("I can no longer see the end...",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("... nor a new beginning.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("Just nothing.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("I do not know what to do.",16.0,3000));
  // CDialogue::control.convo.push_back(CPhrase("I am scared, Peri...",16.0,3000));
  // CDialogue::control.resetTimer();
  // CInterrupt::appendFlag(INTRPT_DIALOGUE);
  // CDialogue::control.setReceiver(&test_resp);
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
