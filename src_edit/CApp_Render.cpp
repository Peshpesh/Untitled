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
		if (Active_Mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
		{
			CSceneryEdit::SceneList[s_i]->OnRender(Map_Renderer);
		}
		s_i++;
	}

	// Draw the working area
	CArea::AreaControl.OnRender(Map_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	if (View_Fore) CArea::AreaControl.OnRender(Map_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	if (View_Type) CArea::AreaControl.OnRenderType(Map_Renderer, Type_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	if (View_Coll) CArea::AreaControl.OnRenderColl(Map_Renderer, Coll_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

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
		if (Active_Mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
		{
			CSceneryEdit::SceneList[s_i]->OnRender(Map_Renderer);
		}
		s_i++;
	}

	// Draws the surrounding interface containing current info and accessible buttons
	CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH, 0, WWIDTH, 0, EWIDTH - WWIDTH, EHEIGHT);
	CSurface::OnDraw(Map_Renderer, Map_Interface, 0, WHEIGHT, 0, WHEIGHT, EWIDTH, EHEIGHT - WHEIGHT);

	switch (Active_Mod)
	{
	case MODIFY_MAP:
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT, WWIDTH - 100 - 32, WHEIGHT - 100, 100, 33);
		break;
	}
	default: break;
	}

	if (Active_Mod == MODIFY_NPC || Active_Mod == REMOVE_NPC)
	{
		RenderNPCedit();
	}
	else if (Active_Mod == MODIFY_SCENE || Active_Mod == REMOVE_SCENE)
	{
		RenderSCNedit();
	}
	else
	{
		RenderMAPedit();
	}
	int mX = mouseX + CCamera::CameraControl.GetX();
	int mY = mouseY + CCamera::CameraControl.GetY();
	int tX = -CCamera::CameraControl.GetX() + (TILE_SIZE * (mX / TILE_SIZE));
	int tY = -CCamera::CameraControl.GetY() + (TILE_SIZE * (mY / TILE_SIZE));
	if (mX < 0)
	{
		tX -= TILE_SIZE;
	}
	if (mY < 0)
	{
		tY -= TILE_SIZE;
	}

	if (Interrupt ^ INTRPT_NONE)
	{
		if (Interrupt & INTRPT_CH_BTILE || Interrupt & INTRPT_CH_FTILE)
		{
			PickTile.RenderTileset(Map_Renderer, Map_Interface, Main_Tileset, mouseX, mouseY);
		}
	}
	else
	{
		if (mouseX >= 0 && mouseX < WWIDTH && mouseY >= 0 && mouseY < WHEIGHT)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, tX, tY, TILE_HILIGHT_X, TILE_HILIGHT_Y, TILE_SIZE, TILE_SIZE);
		}
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
