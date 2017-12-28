#include "CApp.h"

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;

	if ((Win_Display = SDL_CreateWindow("abc",
																			SDL_WINDOWPOS_CENTERED,
																			SDL_WINDOWPOS_CENTERED,
																			WWIDTH,
																			WHEIGHT,
																			SDL_WINDOW_SHOWN)) == NULL) return false;

	if (!CSurface::OnInit(Win_Display)) {
		return false;
	}

	if (!CAsset::OnInit()) {
		return false;
	}

	if (Font::FontControl.OnInit(Win_Renderer) == false)
		return false;
	if (CHUD::HUDControl.OnInit(Win_Renderer) == false)
		return false;
	if (!CEntityInfo::LoadCommon())
		return false;
	if (CEntityRes::OnInit(Win_Renderer) == false)
		return false;
	if (CGameData::GameControl.OnInit() == false)
		return false;
	if (Config::ConfControl.OnInit() == false)
		return false;
	if (CInventory::InvControl.OnInit(Win_Renderer) == false)
		return false;
	if (CSound::SoundSys.OnInit() == false)
		return false;

	///TESTING SOUND SYSTEM
	// Mix_Music* tmpmus = NULL;
	// tmpmus = CSound::SoundSys.LoadMUS(MUS_HOLLOW);
	// if (tmpmus == NULL) return false;
	// if (CSound::SoundSys.PlayMusic(tmpmus) == false)
	// 	return false;

	////
	if ((DEBUG_TEXTURE = CSurface::OnLoad("../res/palette.png", Win_Renderer)) == NULL)	return false;
	// SDL_SetTextureBlendMode(DEBUG_TEXTURE, SDL_BLENDMODE_MOD);
	////
	if (!CSceneryMod::LoadScenery("../data/maps/ARENA.scn", Win_Renderer))
		return false;
	////

	return true;
}

bool CApp::InitGame()
{
	CTitle::MainMenu.Submit = false;
	CTitle::MainMenu.Active = false;
	PauseMenu.OnInit();

	Player.Reset();
	if (Player.OnLoad(CEntityRes::Com_Texture, 0, 128, 32, 32, 8) == false)
		return false;

	CEntity::EntityList.push_back(&Player);
	CItemProcess::OnInit(&Player);

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
	CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);
	return true;
}
