#include "CApp.h"

void CApp::OnRender()
{
	static const bool debug = true;

	CSurface::Clear();

	// Draw background scenery
	int s_i = 0;
	while (s_i < CSceneryEdit::SceneList.size())
	{
		float Z = CSceneryEdit::SceneList[s_i]->Z;
		if (Z <= 1.0f) break;
		if (active_mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
		{
			CSceneryEdit::SceneList[s_i]->OnRender();
		}
		s_i++;
	}

	// Draw the working area
	CEditMap::MapEditor.RenderMap();

	// Draw the entities in the area
	// ...

	// Draw foreground scenery
	while (s_i < CSceneryEdit::SceneList.size())
	{
		float Z = CSceneryEdit::SceneList[s_i]->Z;
		if (active_mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
		{
			CSceneryEdit::SceneList[s_i]->OnRender();
		}
		s_i++;
	}

	if (active_mod == MODIFY_NPC || active_mod == REMOVE_NPC)
	{
		CAsset::drawAppFrame();
		// RenderNPCedit();
	}
	else if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
	{
		CAsset::drawAppFrame();
		RenderSCNedit();
	}
	else {
		CEditMap::MapEditor.OnRender(&mouse);
	}

	renderEngSwitch();
	renderModelButton();
	renderIOButtons();

	CInform::InfoControl.OnRender();

	if (CInterrupt::isFlagOn(INTRPT_MAP_MODEL)) {
		CModel::Control.OnRender(&mouse);
	}

	// if (CInterrupt::isFlagOn(INTRPT_NEW) || CInterrupt::isFlagOn(INTRPT_LOAD) || CInterrupt::isFlagOn(INTRPT_SAVE)) {
	if (CInterrupt::isFlagOn(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE)) {
		CFileIO::IOhandle.OnRender(&mouse);
	}

	//	DEBUGGING
	if (debug)
	{
		Font::Write(FONT_MINI, CFPS::FPSControl.GetFPS(), WWIDTH + 1, 1);
	}

	CSurface::Present();
}

bool CApp::renderEngSwitch()
{
	using namespace engineSwitch;

	bool canHilight = CInterrupt::isNone();
	bool noHov;

	const SDL_Point* color = NULL;
	for (int i = MODIFY_MAP; i <= REMOVE_SCENE; i++)
	{
		noHov = (!canHilight || !SDL_PointInRect(&mouse, &engineButton[i]));
		color = (active_mod == i) ? engineOnCol : (noHov ? engineOffCol : engineHvCol);
		CAsset::drawStrBox(&engineButton[i], bsiz, color);
		Font::NewCenterWrite(FONT_MINI, engineName[i], &engineButton[i]);
	}

	return true;
}

bool CApp::renderModelButton()
{
	using namespace modelSwitch;

	bool active = CInterrupt::isFlagOn(INTRPT_MAP_MODEL);
	bool canHov = active ? false : CInterrupt::isNone();
	bool hov = (!canHov) ? false : SDL_PointInRect(&mouse, &button);

	CAsset::drawStrBox(&button, bsiz, active ? onCol : (hov ? hovCol : offCol));
	Font::NewCenterWrite(FONT_MINI, label, &button);

	return true;
}

bool CApp::renderIOButtons()
{
	using namespace io_ui;

	bool hov = CInterrupt::isNone();

	CAsset::drawStrBox(&newButton, bsiz, (hov && SDL_PointInRect(&mouse, &newButton)) ? newHovCol : newButCol);
	CAsset::drawStrBox(&loadButton, bsiz, (hov && SDL_PointInRect(&mouse, &loadButton)) ? loadHovCol : loadButCol);
	CAsset::drawStrBox(&saveButton, bsiz, (hov && SDL_PointInRect(&mouse, &saveButton)) ? saveHovCol : saveButCol);

	Font::FontControl.SetFont(FONT_MINI);
	Font::NewCenterWrite(new_label, &newButton);
	Font::NewCenterWrite(load_label, &loadButton);
	Font::NewCenterWrite(save_label, &saveButton);

	return true;
}
