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
		CArea::AreaControl.OnRender(Win_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
		// Render non-player entities
		for (int i = 1; i < CEntity::EntityList.size(); i++)
		{
			if (!CEntity::EntityList[i]) continue;
			CEntity::EntityList[i]->OnRender(Win_Renderer);
		}
		// Render Player
		CEntity::EntityList[0]->OnRender(Win_Renderer);

		CArea::AreaControl.OnRender(Win_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);

		while (s_i < CScenery::SceneList.size())
		{
			CScenery::SceneList[s_i]->OnRender(Win_Renderer);
			s_i++;
		}

//	if (CCinema::CinemaControl->Scene)
//		CCinema::CinemaControl->OnRender(Win_Renderer);

	if (DEBUG)
	{
		Font::Write(Win_Renderer, Font::FontControl.Tex_Font, CCamera::CameraControl.GetX() + 100000, WWIDTH - 100, 100);
		Font::Write(Win_Renderer, Font::FontControl.Tex_Font, &CGameData::GameControl.Slot, 260, 25);
		Font::Write(Win_Renderer, Font::FontControl.Tex_Font, CTransport::Transporter.Destination, 360, 25);
		Font::Write(Win_Renderer, Font::FontControl.Tex_Font, CMenu::MenuList.size(), 520, 55);
		// Font::Write(Win_Renderer, Font::FontControl.Tex_Font, *CCinema::CinemaControl->Progress, 460, 25);
		// Font::Write(Win_Renderer, Font::FontControl.Tex_Font, CGameData::GameControl.ProgressList[0], 510, 25);
		if (CItem::Inventory.size() == 0)
			Font::Write(Win_Renderer, Font::FontControl.Tex_Font, 99, 570, 25);

		if (Player.Engaged)
			Font::Write(Win_Renderer, Font::FontControl.Tex_Font, 1, 540, 25);
		else
			Font::Write(Win_Renderer, Font::FontControl.Tex_Font, 0, 540, 25);
		}
		// Render menus
		if (CInventory::InvControl.active) CInventory::InvControl.OnRender(Win_Renderer);
		for (int i = 0; i < CMenu::MenuList.size(); i++)
		{
			if (!CMenu::MenuList[i]) continue;
			CMenu::MenuList[i]->OnRender(Win_Renderer);
		}
		if (PauseMenu.Active) PauseMenu.OnRender(Win_Renderer);
	}
	SDL_RenderPresent(Win_Renderer);
}
