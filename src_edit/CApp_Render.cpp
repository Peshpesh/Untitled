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
	for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
	{
		if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
		CEntityEdit::NPCControl.EntityList[i].OnRender();
	}
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
		RenderNPCedit();
	}
	else if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
	{
		CAsset::drawAppFrame();
		RenderSCNedit();
	}
	else {
		CEditMap::MapEditor.OnRender(&mouse);
	}

	RenderEngine();

	CInform::InfoControl.OnRender();

	if (CInterrupt::isFlagOn(INTRPT_LOAD) || CInterrupt::isFlagOn(INTRPT_SAVE))
	{
		CFileIO::IOhandle.OnRender(&mouse);
	}

	//	DEBUGGING
	if (debug)
	{
		Font::Write(FONT_MINI, CFPS::FPSControl.GetFPS(), WWIDTH + 1, 1);
	}

	CSurface::Present();
}

bool CApp::RenderEngine()
{
	using namespace io_ui;

	bool canHilight = !(bool)(intrpt);
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
