#include "CGame.h"

CGame CGame::control;

CGame::CGame() {
  diff = NORMAL;
  suspend_flag = INTRPT_PAUSE | INTRPT_VIEW_MAP | INTRPT_INVENTORY;
}

bool CGame::handleTransit() {
	if (CTransition::control.getMode() != APP_MODE_GAME) return false;
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
	CTransition::control.activated = false;
	return true;
}

// For terminating the application
void CGame::OnCleanup() {
  OnExit();
}

// For quitting the game
void CGame::OnExit() {
  CArea::control.OnInit();
  CEntityIO::Cleanup();
  CSceneryIO::Cleanup();
}
