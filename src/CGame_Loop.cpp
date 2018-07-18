#include "CGame.h"

void CGame::OnLoop() {
	static bool happened = false;
	if (test_resp == 1 && !happened) {
		happened = true;
		CTransition::control.reqReset();
		CTransition::control.reqMode(APP_MODE_TITLE);
	}
	CTransition::control.OnLoop();
	if (CTransition::control.activated) {     // complete transition
		if (!handleTransit()) return;
	}
	CDialogue::control.OnLoop();
	CStage::stage->OnLoop();

	// if (!CInterrupt::isSuspended()) {
	// 	for (int i = 0; i < CEntity::EntityList.size(); i++) {
	// 		if (!CEntity::EntityList[i]) continue;
	// 		// This should trigger AFTER a death animation.
	// 		// if (CEntity::EntityList[i]->Dead == true && i != 0) {
	// 		// 	delete CEntity::EntityList[i];
	// 		// 	CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
	// 		// 	continue;
	// 		// }
	// 		CEntity::EntityList[i]->OnLoop();
	// 	}
	// }
}
