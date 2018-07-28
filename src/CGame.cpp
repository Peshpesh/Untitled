#include "CGame.h"

CGame CGame::control;

CGame::CGame() {
  //
}

bool CGame::handleTransit() {
	if (CTransition::control.getMode() != APP_MODE_GAME) return false;

  switch (CTransition::control.locationID) {
    case location::DEFAULT: {
      CStage::stage = &CDebug_Stage::anch;
      break;
    }
  }
  CStage::stage->OnLoad();

	// using namespace location;
	// if (!CArea::control.Load(CTransition::control.locationID)) {
	// 	// ERROR LOADING AREA
	// }
	// //  Entities
	// if (!CEntityIO::Load(abbrname[CTransition::control.locationID])) {
	// 	// ERROR LOADING ENTITIES
	// }
	// //  Scenery
	// if (!CSceneryIO::Load(abbrname[CTransition::control.locationID])) {
	// 	// ERROR LOADING SCENERY
	// }
	// CTransition::control.activated = false;
	return true;
}

// For quitting the game
void CGame::OnCleanup() {
  CArea::control.OnCleanup();
  CEntityIO::Cleanup();
  CSceneryIO::Cleanup();
}

// For terminating the application
void CGame::OnExit() {
  OnCleanup();
}
