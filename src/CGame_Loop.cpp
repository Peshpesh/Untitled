#include "CGame.h"

void CGame::OnLoop() {
	CTransition::control.OnLoop();
	if (CTransition::control.activated) {     // complete transition
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
	}

	for (int i = 0; i < CEntity::EntityList.size(); i++) {
		if (!CEntity::EntityList[i]) continue;

		// This should trigger AFTER a death animation.
		// if (CEntity::EntityList[i]->Dead == true && i != 0) {
		// 	delete CEntity::EntityList[i];
		// 	CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
		// 	continue;
		// }
		CEntity::EntityList[i]->OnLoop();
	}
}
