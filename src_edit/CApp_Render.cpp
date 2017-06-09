#include "CApp.h"

void CApp::OnRender()
{
	bool debug = true;
	SDL_RenderClear(Map_Renderer);

	// Draw background scenery
	int s_i = 0;
	while (s_i < CSceneryEdit::SceneList.size())
	{
		float Z = CSceneryEdit::SceneList[s_i]->Z;
		if (Z <= 1.0f) break;
		if (active_mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
		{
			CSceneryEdit::SceneList[s_i]->OnRender(Map_Renderer);
		}
		s_i++;
	}

	// Draw the working area
	CEditMap::MapEditor.RenderMap(Map_Renderer);

	// Draw the entities in the area
	for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
	{
		if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
		CEntityEdit::NPCControl.EntityList[i].OnRender(Map_Renderer);
	}
	// Draw foreground scenery
	while (s_i < CSceneryEdit::SceneList.size())
	{
		float Z = CSceneryEdit::SceneList[s_i]->Z;
		if (active_mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
		{
			CSceneryEdit::SceneList[s_i]->OnRender(Map_Renderer);
		}
		s_i++;
	}

	// Draws the surrounding interface containing current info and accessible buttons
	CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH, 0, WWIDTH, 0, EWIDTH - WWIDTH, EHEIGHT);
	CSurface::OnDraw(Map_Renderer, Map_Interface, 0, WHEIGHT, 0, WHEIGHT, EWIDTH, EHEIGHT - WHEIGHT);

	switch (active_mod)
	{
	case MODIFY_MAP:
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT, WWIDTH - 100 - 32, WHEIGHT - 100, 100, 33);
		break;
	}
	default: break;
	}

	if (active_mod == MODIFY_NPC || active_mod == REMOVE_NPC)
	{
		RenderNPCedit();
	}
	else if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
	{
		RenderSCNedit();
	}
	else
	{
		CEditMap::MapEditor.OnRender(Map_Renderer, Map_Interface, &mouse);
	}

	//	DEBUGGING
	if (debug)
	{
		Font::Write(Map_Renderer, FONT_MINI, CFPS::FPSControl.GetFPS(), WWIDTH + 1, 1);
	}
	SDL_RenderPresent(Map_Renderer);
}

bool CApp::RenderButton(int X, int Y, int W, int H, int bsiz, int colX, int colY, bool hl)
{
	bool but_glow = false;
	if (hl)
	{
		if (mouseX >= X && mouseX < X + W)
		{
			if (mouseY >= Y && mouseY < Y + H)
			{
				but_glow = true;
			}
		}
	}

	if (!CSurface::OnDraw(Map_Renderer, Map_Interface, X, Y, DARKS_X, COLOR_PURE_Y, 1, 1, W, H))
		return false;
	if (!CSurface::OnDraw(Map_Renderer, Map_Interface, X + bsiz, Y + bsiz, colX, colY - but_glow, 1, 1, W - (bsiz * 2), H - (bsiz * 2)))
		return false;

	return true;
}
