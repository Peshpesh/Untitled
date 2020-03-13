#include "CApp.h"

bool CApp::OnInit()
{
	CCamera::CameraControl.SetTarget(NULL, NULL);
	CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
	CCamera::CameraControl.SetPos(0, 0);

	if ((Map_Display = SDL_CreateWindow("Map Editor",
																			SDL_WINDOWPOS_CENTERED,
																			SDL_WINDOWPOS_CENTERED,
																			EWIDTH,
																			EHEIGHT,
																			SDL_WINDOW_SHOWN)) == NULL)
	{
		return false;
	}

	if (!CSurface::OnInit(Map_Display)) {
		return false;
	}

	if (!CAsset::OnInit()) {
		return false;
	}

	if (!Font::FontControl.OnInit()) {
		return false;
	}

  if (!CTileset::TSControl.OnInit()) {
		return false;
	}

	if (CEditMap::MapEditor.OnInit() == false) {
		return false;
	}

	if (CEntityEditor::Control.OnInit() == false) {
		return false;
	}

	if (CSceneryEditor::control.OnInit() == false) {
		return false;
	}

	COptions::control.OnInit();

	///////////////////////
	// Debugging section //
	///////////////////////

	return true;
}
