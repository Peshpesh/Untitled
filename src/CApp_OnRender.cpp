#include "CApp.h"

void CApp::OnRender() {
	static bool DEBUG = true;

	CSurface::Clear();

	if (CMode::isFlagOn(APP_MODE_GAME)) {
		CGame::control.OnRender();
	} else if (CMode::isFlagOn(APP_MODE_TITLE)) {
    CTitle::control.OnRender();
	}	else if (CMode::isFlagOn(APP_MODE_FATAL)) {
		//
	}

	if (!CTransition::control.OnRender()) {
		// ERROR
	}

	if (DEBUG) {
		std::string fps_str = CAsset::intToStr(CFPS::FPSControl.GetFPS()) + " fps";
		std::string speedfactor_str = CAsset::doubleToStr(CFPS::FPSControl.GetSpeedFactor(),10) + " SF";
		const SDL_Point fps_pos = {1,1};
		const SDL_Point sf_pos = {100,1};
		CType::Write(FONT_MINI, fps_str.c_str(), fps_pos, &rgb::white);
		CType::Write(FONT_MINI, speedfactor_str.c_str(), sf_pos, &rgb::white);
	}

	if (esc_init) drawQuitMsg();

	CSurface::Present();
}

void CApp::drawQuitMsg() {
	using namespace gen;
	int msg_A = ((double)(SDL_GetTicks() - esc_init) / ESC_THRESH) * MAX_RGBA;
	if (CType::control.SetOpacity(msg_A)) {
		CType::Write(quit_msg_f, quit_msg, quit_msg_p, quit_msg_c);
	}
	CType::control.SetOpacity(MAX_RGBA);
}

// void CApp::OnRender()
// {
// 	bool DEBUG = true;
//
// 	CSurface::Clear();
// 	// SDL_RenderClear(Win_Renderer);
//
// 	if (CMode::isFlagOn(APP_MODE_GAME)) {
// 		// CGame::control.OnRender();
// 	} else if (CMode::isFlagOn(APP_MODE_TITLE) && !CTitle::control.OnRender()) {
//     // error
// 	}	else if (CMode::isFlagOn(APP_MODE_FATAL)) {
// 		//
// 	}
//
// 	CSurface::Present();
//
// 	// Title Screen Rendering
// 	if (CTitle::MainMenu.Active)
// 	{
// 		CTitle::MainMenu.OnRender(Win_Renderer);
// 	}
// 	else
// 	{
// 		int s_i = 0;
// 		while (s_i < CScenery::SceneList.size())
// 		{
// 			if (CScenery::SceneList[s_i]->Z <= 1.0f) break;
//
// 			CScenery::SceneList[s_i]->OnRender(Win_Renderer);
// 			s_i++;
// 		}
// 		CArea::AreaControl.OnRender(Win_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
// 		// Render non-player entities
// 		for (int i = 1; i < CEntity::EntityList.size(); i++)
// 		{
// 			if (!CEntity::EntityList[i]) continue;
// 			CEntity::EntityList[i]->OnRender(Win_Renderer);
// 		}
// 		// Render Player
// 		CEntity::EntityList[0]->OnRender(Win_Renderer);
//
// 		CArea::AreaControl.OnRender(Win_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
//
// 		while (s_i < CScenery::SceneList.size())
// 		{
// 			CScenery::SceneList[s_i]->OnRender(Win_Renderer);
// 			s_i++;
// 		}
//
// 		// Render menus
// 		if (CInventory::InvControl.active) CInventory::InvControl.OnRender(Win_Renderer);
// 		for (int i = 0; i < CMenu::MenuList.size(); i++)
// 		{
// 			if (!CMenu::MenuList[i]) continue;
// 			CMenu::MenuList[i]->OnRender(Win_Renderer);
// 		}
// 		if (PauseMenu.Active) PauseMenu.OnRender(Win_Renderer);
//
// 		if (DEBUG)
// 		{
// 			int colX, colY, colW, colH;
// 			float pX, pY;
// 			CEntity::EntityList[0]->GetColInfo(colX, colY, colW, colH);
// 			CEntity::EntityList[0]->GetPos(pX, pY);
// 			Font::Writef(Win_Renderer, FONT_DEFAULT, (int)(pX) % TILE_SIZE, 1, 0, 10, 10);
// 			Font::Writef(Win_Renderer, FONT_DEFAULT, (int)(pY) % TILE_SIZE, 1, 0, 210, 10);
// 			int hX = pX + colX - CCamera::CameraControl.GetX();
// 			int hY = pY + colY - CCamera::CameraControl.GetY();
// 			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, hX, hY, 0, 0, 1, 1, colW, 1);
// 			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, hX, hY, 0, 0, 1, 1, 1, colH);
// 			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, hX + colW - 1, hY, 0, 0, 1, 1, 1, colH);
// 			CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, hX, hY + colH - 1, 0, 0, 1, 1, colW, 1);
// 			int pXi = pX + colX;
// 			int pYi = pY + colY;
// 			int pXf = pXi + colW - 1;
// 			int pYf = pYi + colH - 1;
// 			for (int tY = pYi / TILE_SIZE; tY <= pYf / TILE_SIZE; tY++)
// 			{
// 				for (int tX = pXi / TILE_SIZE; tX <= pXf / TILE_SIZE; tX++)
// 				{
// 					int tileX = (tX * TILE_SIZE) - CCamera::CameraControl.GetX();
// 					int tileY = (tY * TILE_SIZE) - CCamera::CameraControl.GetY();
// 					CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, tileX, tileY, 0, 5, 1, 1, TILE_SIZE, 1);
// 					CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, tileX, tileY, 0, 5, 1, 1, 1, TILE_SIZE);
// 					CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, tileX + TILE_SIZE - 1, tileY, 0, 5, 1, 1, 1, TILE_SIZE);
// 					CSurface::OnDraw(Win_Renderer, DEBUG_TEXTURE, tileX, tileY + TILE_SIZE - 1, 0, 5, 1, 1, TILE_SIZE, 1);
// 				}
// 			}
// 		}
// 	}
// 	CSurface::Present();
// 	// SDL_RenderPresent(Win_Renderer);
// }
