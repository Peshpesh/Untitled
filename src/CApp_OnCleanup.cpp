#include "CApp.h"

void CApp::OnCleanup() {
	SDL_DestroyWindow(Win_Display);

	CSurface::OnCleanup();

	SDL_Quit();
}

// void CApp::OnCleanup()
// {
// 	CGameData::GameControl.OnCleanup();
//
// 	SDL_DestroyWindow(Win_Display);
// 	SDL_DestroyRenderer(Win_Renderer);
//
// 	for (int i = 0; i < CEntity::EntityList.size(); i++)
// 	{
// 		if (!CEntity::EntityList[i]) continue;
// 		CEntity::EntityList[i]->OnCleanup();
// 	}
// 	CEntity::EntityList.clear();
// 	CArea::AreaControl.OnCleanup();
// 	SDL_Quit();
// }
