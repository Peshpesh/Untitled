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
		// Draws the surrounding interface containing current info and accessible buttons
		// CSurface::OnDraw(Map_Interface, WWIDTH, 0, WWIDTH, 0, EWIDTH - WWIDTH, EHEIGHT);
		// CSurface::OnDraw(Map_Interface, 0, WHEIGHT, 0, WHEIGHT, EWIDTH, EHEIGHT - WHEIGHT);
		CAsset::drawAppFrame();
		RenderNPCedit();
	}
	else if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
	{
		// Draws the surrounding interface containing current info and accessible buttons
		// CSurface::OnDraw(Map_Interface, WWIDTH, 0, WWIDTH, 0, EWIDTH - WWIDTH, EHEIGHT);
		// CSurface::OnDraw(Map_Interface, 0, WHEIGHT, 0, WHEIGHT, EWIDTH, EHEIGHT - WHEIGHT);
		CAsset::drawAppFrame();
		RenderSCNedit();
	}
	else
	{
		CEditMap::MapEditor.OnRender(&mouse);
		// CEditMap::MapEditor.OnRender(Map_Interface, &mouse);
	}

	RenderEngine();

	//	DEBUGGING
	if (debug)
	{
		Font::Write(FONT_MINI, CFPS::FPSControl.GetFPS(), WWIDTH + 1, 1);
	}
	CSurface::Present();
}

// bool CApp::RenderButton(int X, int Y, int W, int H, int bsiz, int colX, int colY, bool hl)
// {
// 	bool but_glow = false;
// 	if (hl)
// 	{
// 		if (mouseX >= X && mouseX < X + W)
// 		{
// 			if (mouseY >= Y && mouseY < Y + H)
// 			{
// 				but_glow = true;
// 			}
// 		}
// 	}
//
// 	if (!CSurface::OnDraw(Map_Interface, X, Y, DARKS_X, COLOR_PURE_Y, 1, 1, W, H))
// 		return false;
// 	if (!CSurface::OnDraw(Map_Interface, X + bsiz, Y + bsiz, colX, colY - but_glow, 1, 1, W - (bsiz * 2), H - (bsiz * 2)))
// 		return false;
//
// 	return true;
// }

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
