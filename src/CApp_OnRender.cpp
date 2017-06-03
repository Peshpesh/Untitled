#include "CApp.h"

void CApp::OnRender()
{
	bool DEBUG = true;
	SDL_RenderClear(Win_Renderer);

	// Title Screen Rendering
	if (CTitle::MainMenu.Active)
	{
		CTitle::MainMenu.OnRender(Win_Renderer);
	}
	else
	{
		int s_i = 0;
		while (s_i < CScenery::SceneList.size())
		{
			if (CScenery::SceneList[s_i]->Z <= 1.0f) break;

			CScenery::SceneList[s_i]->OnRender(Win_Renderer);
			s_i++;
		}
		CArea::AreaControl.OnRender(Win_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
		// Render non-player entities
		for (int i = 1; i < CEntity::EntityList.size(); i++)
		{
			if (!CEntity::EntityList[i]) continue;
			CEntity::EntityList[i]->OnRender(Win_Renderer);
		}
		// Render Player
		CEntity::EntityList[0]->OnRender(Win_Renderer);

		CArea::AreaControl.OnRender(Win_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);

		while (s_i < CScenery::SceneList.size())
		{
			CScenery::SceneList[s_i]->OnRender(Win_Renderer);
			s_i++;
		}

		// Render menus
		if (CInventory::InvControl.active) CInventory::InvControl.OnRender(Win_Renderer);
		for (int i = 0; i < CMenu::MenuList.size(); i++)
		{
			if (!CMenu::MenuList[i]) continue;
			CMenu::MenuList[i]->OnRender(Win_Renderer);
		}
		if (PauseMenu.Active) PauseMenu.OnRender(Win_Renderer);

		if (DEBUG)
		{
			int colX, colY, colW, colH;
			float pX, pY;
			CEntity::EntityList[0]->GetColInfo(colX, colY, colW, colH);
			CEntity::EntityList[0]->GetPos(pX, pY);
			Font::Writef(Win_Renderer, FONT_DEFAULT, pX, 3, 0, 10, 10);
			Font::Writef(Win_Renderer, FONT_DEFAULT, pY+TILE_SIZE-1, 3, 0, 210, 10);
			pX += colX - CCamera::CameraControl.GetX();
			pY += colY - CCamera::CameraControl.GetY();
			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, pX, pY, 0, 0, 1, 1, colW, 1);
			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, pX, pY, 0, 0, 1, 1, 1, colH);
			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, pX + colW - 1, pY, 0, 0, 1, 1, 1, colH);
			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, pX, pY + colH - 1, 0, 0, 1, 1, colW, 1);
		}
	}
	SDL_RenderPresent(Win_Renderer);
}
