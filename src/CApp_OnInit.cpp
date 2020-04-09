#include "CApp.h"

bool CApp::OnInit() {
	CError::handler.OnInit();

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		CError::handler.ReportSDLErr("FATAL => SDL_Init failed");
		return false;
	}

	if ((Win_Display = SDL_CreateWindow(
											"abc",
											SDL_WINDOWPOS_CENTERED,
											SDL_WINDOWPOS_CENTERED,
											WWIDTH,
											WHEIGHT,
											SDL_WINDOW_SHOWN)) == NULL)
	{
		CError::handler.ReportErr("FATAL => SDL_CreateWindow failed.");
		return false;
	}

	if (!CSurface::OnInit(Win_Display)) {
		CError::handler.ReportErr("FATAL => CSurface failed to initialize.");
		return false;
	}

	if (!CAsset::OnInit()) {
		CError::handler.ReportErr("FATAL => CAsset failed to initialize.");
		return false;
	}

	if (!CType::control.OnInit()) {
		CError::handler.ReportErr("FATAL => CType failed to initialize.");
		return false;
	}

	if (!CGameIO::control.init()) {
		CError::handler.ReportErr("FATAL => CGameIO failed to initialize.");
		return false;
	}

	if (!CEntityData::init()) {
		CError::handler.ReportErr("FATAL => CEntityData failed to initialize.");
		return false;
	}

	if (!CSceneryIO::init()) {
		CError::handler.ReportErr("FATAL => CSceneryIO failed to initialize.");
		return false;
	}

	if (!CInventory::control.init()) {
		return false;
	}

 	// if (!Font::FontControl.OnInit()) 				return false;
	// if (!CHUD::HUDControl.OnInit()) 				return false;
	// if (!CEntityInfo::LoadCommon()) 				return false;
	// if (!CEntityRes::OnInit()) 							return false;
	// if (!CGameData::GameControl.OnInit()) 	return false;
	// if (!Config::ConfControl.OnInit()) 			return false;
	// if (!CInventory::InvControl.OnInit()) 	return false;
	// if (!CSound::SoundSys.OnInit()) 				return false;

	////
	// if ((DEBUG_TEXTURE = CSurface::OnLoad("../res/palette.png")) == NULL)	return false;
	// SDL_SetTextureBlendMode(DEBUG_TEXTURE, SDL_BLENDMODE_MOD);
	////

	// if (!CSceneryMod::LoadScenery("../data/maps/ARENA.scn")) return false;
	////

	return true;
}

// bool CApp::InitGame()
// {
// 	CTitle::MainMenu.Submit = false;
// 	CTitle::MainMenu.Active = false;
// 	PauseMenu.OnInit();
//
// 	Player.Reset();
// 	if (Player.OnLoad(CEntityRes::Com_Texture, 0, 128, 32, 32, 8) == false)
// 		return false;
//
// 	CEntity::EntityList.push_back(&Player);
// 	CItemProcess::OnInit(&Player);
//
// 	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
// 	CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
// 	return true;
// }
