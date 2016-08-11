#include "CApp.h"

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return false;
	if ((Win_Display = SDL_CreateWindow("f9iunhdsufdsF(*#$JR#(JR(@#R(J@(J#RJ(Ej9fgdsfSD(JGJ",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN)) == NULL)
	{
		return false;
	}
	if ((Win_Renderer = SDL_CreateRenderer(Win_Display, -1,
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		return false;
	}
	if (Font::FontControl.OnInit(Win_Renderer) == false)
		return false;
	if (CHUD::HUDControl.OnInit(Win_Renderer) == false)
		return false;
	if (CEntityMod::EntityControl.OnInit(Win_Renderer) == false)
		return false;
	if (CGameData::GameControl.OnInit() == false)
		return false;
	if (Config::ConfControl.OnInit() == false)
		return false;
	if (CInventory::InvControl.OnInit(Win_Renderer) == false)
		return false;
	////
	if ((TESTSFC = CSurface::OnLoad("../res/palette.png", Win_Renderer)) == NULL)	return false;
	SDL_SetTextureBlendMode(TESTSFC, SDL_BLENDMODE_MOD);
	return true;
}

bool CApp::InitGame()
{
	CTitle::MainMenu.Submit = false;
	CTitle::MainMenu.Active = false;
	PauseMenu.OnInit();

	Player.Reset();
	if (Player.OnLoad(CEntityMod::EntityControl.Com_Texture, 0, 128, 32, 32, 8) == false)
		return false;

	CEntity::EntityList.push_back(&Player);
	CItemProcess::OnInit(&Player);

	CCamera::CameraControl.TargetMode = TARGET_MODE_CENTER;
	CCamera::CameraControl.SetTarget(&Player.X, &Player.Y);

	return true;
}
