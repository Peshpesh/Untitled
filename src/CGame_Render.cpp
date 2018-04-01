#include "CGame.h"

void CGame::OnRender() {
  if (CEntity::EntityList.size() == 0) return;
  CArea::control.OnRender(0, 0, true);

	// Render entities
	for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
		if (!CEntity::EntityList[i]) continue;
		CEntity::EntityList[i]->OnRender();
	}

  CArea::control.OnRender(0, 0, false);
}
