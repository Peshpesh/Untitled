#include "CApp.h"
// #include "CHUD.h"

void CApp::OnRender()
{
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
	CArea::AreaControl.OnRender(Map_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	CArea::AreaControl.OnRender(Map_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	CArea::AreaControl.OnRenderType(Map_Renderer, Type_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	CArea::AreaControl.OnRenderSlope(Map_Renderer, Slope_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

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

	int tX = -CCamera::CameraControl.GetX() + (32 * (mouseX / 32));
	int tY = -CCamera::CameraControl.GetY() + (32 * (mouseY / 32));
	if (mouseX < 0)
	{
		tX -= 32;
	}
	if (mouseY < 0)
	{
		tY -= 32;
	}

	if (mouseX != -404404 && mouseY != -404404)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, tX, tY, 300, 448, 32, 32);
	}
	SDL_RenderPresent(Map_Renderer);
}

bool CApp::RenderMAPedit()
{
	// Write a button name for changing tiles within a tileset
	Font::CenterWrite(Map_Renderer, Font, "CHANGE", TILE_CHG_BUT_X + (TILE_CHG_BUT_W / 2), TILE_CHG_BUT_Y + (TILE_CHG_BUT_H / 2) - (CHAR_HEIGHT / 2));
	Font::CenterWrite(Map_Renderer, Font, "TILE", TILE_CHG_BUT_X + (TILE_CHG_BUT_W / 2), TILE_CHG_BUT_Y + (TILE_CHG_BUT_H / 2) + (CHAR_HEIGHT / 2));

	// Draws active background tile
	CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_BTILE_X, DISP_BTILE_Y,
		(Current_Tile % TilesetWidth) * TILE_SIZE,
		(Current_Tile / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile before active background tile
	if (Current_Tile != 0)
		CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_BTILE_X - TILE_SIZE, DISP_BTILE_Y,
			((Current_Tile - 1) % TilesetWidth) * TILE_SIZE,
			((Current_Tile - 1) / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile after active background tile
	if (Current_Tile != TilesetWidth * TilesetHeight - 1)
		CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_BTILE_X + TILE_SIZE, DISP_BTILE_Y,
			((Current_Tile + 1) % TilesetWidth) * TILE_SIZE,
			((Current_Tile + 1) / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws active foreground tile
	CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_FTILE_X, DISP_FTILE_Y,
		(Current_Fore % TilesetWidth) * TILE_SIZE,
		(Current_Fore / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile before active foreground tile
	if (Current_Fore != 0)
		CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_FTILE_X - TILE_SIZE, DISP_FTILE_Y,
			((Current_Fore - 1) % TilesetWidth) * TILE_SIZE,
			((Current_Fore - 1) / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile after active foreground tile
	if (Current_Fore != TilesetWidth * TilesetHeight - 1)
		CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_FTILE_X + TILE_SIZE, DISP_FTILE_Y,
			((Current_Fore + 1) % TilesetWidth) * TILE_SIZE,
			((Current_Fore + 1) / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws active tile type
	CSurface::OnDraw(Map_Renderer, Type_Tileset, DISP_TYPE_X, DISP_TYPE_Y,
		(Current_Type % TypesetWidth) * TILE_SIZE,
		(Current_Type / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws type before active type
	if (Current_Type != 0)
		CSurface::OnDraw(Map_Renderer, Type_Tileset, DISP_TYPE_X - TILE_SIZE, DISP_TYPE_Y,
			((Current_Type - 1) % TypesetWidth) * TILE_SIZE,
			((Current_Type - 1) / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws type after active type
	if (Current_Type != TypesetWidth * TypesetHeight - 1)
		CSurface::OnDraw(Map_Renderer, Type_Tileset, DISP_TYPE_X + TILE_SIZE, DISP_TYPE_Y,
			((Current_Type + 1) % TypesetWidth) * TILE_SIZE,
			((Current_Type + 1) / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Writes out the active type
	switch (Current_Type)
	{
		case TILE_TYPE_NONE: Font::CenterWrite(Map_Renderer, Font, "NONE", EWIDTH - 50, 447); break;
		case TILE_TYPE_HOLLOW: Font::CenterWrite(Map_Renderer, Font, "HOLLO", EWIDTH - 50, 447); break;
		case TILE_TYPE_NORMAL: Font::CenterWrite(Map_Renderer, Font, "NORM", EWIDTH - 50, 447); break;
		case TILE_TYPE_BLOCK: Font::CenterWrite(Map_Renderer, Font, "BLOCK", EWIDTH - 50, 447); break;
		case TILE_TYPE_WATER: Font::CenterWrite(Map_Renderer, Font, "WATER", EWIDTH - 50, 447); break;
		case TILE_TYPE_ICE: Font::CenterWrite(Map_Renderer, Font, "ICE", EWIDTH - 50, 447); break;
		case TILE_TYPE_FIRE: Font::CenterWrite(Map_Renderer, Font, "FIRE", EWIDTH - 50, 447); break;
		default: break;
	}

	// Draws active tile slope
	CSurface::OnDraw(Map_Renderer, Slope_Tileset, DISP_SLOPE_X, DISP_SLOPE_Y,
		(Current_Slope % SlopesetWidth) * TILE_SIZE,
		(Current_Slope / SlopesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws slope before active slope
	if (Current_Slope != 0)
		CSurface::OnDraw(Map_Renderer, Slope_Tileset, DISP_SLOPE_X - TILE_SIZE, DISP_SLOPE_Y,
			((Current_Slope - 1) % SlopesetWidth) * TILE_SIZE,
			((Current_Slope - 1) / SlopesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws slope after active slope
	if (Current_Slope != SlopesetWidth * SlopesetHeight - 1)
		CSurface::OnDraw(Map_Renderer, Slope_Tileset, DISP_SLOPE_X + TILE_SIZE, DISP_SLOPE_Y,
			((Current_Slope + 1) % SlopesetWidth) * TILE_SIZE,
			((Current_Slope + 1) / SlopesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Writes out the active slope
	switch (Current_Slope)
	{
	case SLOPE_FLAT: Font::CenterWrite(Map_Renderer, Font, "FLAT", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_ASC: Font::CenterWrite(Map_Renderer, Font, "ASC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_ASCE: Font::CenterWrite(Map_Renderer, Font, "ASCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_DSC: Font::CenterWrite(Map_Renderer, Font, "DSC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_DSCE: Font::CenterWrite(Map_Renderer, Font, "DSCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_ASC: Font::CenterWrite(Map_Renderer, Font, "SASC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_DSC: Font::CenterWrite(Map_Renderer, Font, "SDSC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_ASCE: Font::CenterWrite(Map_Renderer, Font, "SASCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_DSCE: Font::CenterWrite(Map_Renderer, Font, "SDSCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	default: break;
	}

	return true;
}

bool CApp::RenderNPCedit()
{
	if (Active_Mod == MODIFY_NPC)
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 33, WWIDTH - 100 - 32, WHEIGHT - 67, 100, 33);
	else
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 33, WWIDTH - 100 - 32, WHEIGHT - 134, 100, 33);

	if (CEntityEdit::NPCControl.UseCommon)
		tabl_name_W = Font::Write(Map_Renderer, Font, "COMMON", TABL_NAME_X, TABL_NAME_Y);
	else
		tabl_name_W = Font::Write(Map_Renderer, Font, "UNIQUE", TABL_NAME_X, TABL_NAME_Y);

	CSurface::OnDraw(Map_Renderer, Map_Interface, TABL_NAME_X - ARROW_SIZE - 5, TABL_NAME_Y, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, TABL_NAME_X + tabl_name_W + 5, TABL_NAME_Y, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Draw working NPC name
	if (!CEntityEdit::NPCControl.CWrite_Name(Map_Renderer, Font, ENT_NAME_X, ENT_NAME_Y))
		return false;

	// Print # of NPCs in the area
	Font::Write(Map_Renderer, Font, " NPCS", Font::Write(Map_Renderer, Font,
		CEntityEdit::NPCControl.EntityList.size(), 5, EHEIGHT - 20) + 5, EHEIGHT - 20);

	// Print "NPC Tables" crap-button
	CSurface::OnDraw(Map_Renderer, Map_Interface, TBL_CHG_BUTTON_X, TBL_CHG_BUTTON_Y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	Font::Write(Map_Renderer, Font, "NPC TABLES", TBL_CHG_BUTTON_X + SWITCH_SIZE + SYM_SPACING, TBL_CHG_BUTTON_Y);

	return true;
}

bool CApp::RenderSCNedit()
{
	if (Active_Mod == MODIFY_SCENE)
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 66, WWIDTH - 100 - 32, WHEIGHT - 34, 100, 34);
	else
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 66, WWIDTH - 100 - 32, 312, 100, 34);

	if (!CSurface::OnDraw(Map_Renderer, Map_Interface, SCN_NAME_X - ARROW_SIZE - SYM_SPACING, SCN_NAME_Y, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE)) return false;
	if (!CSurface::OnDraw(Map_Renderer, Map_Interface, SCN_NAME_X + SCN_NAME_W + SYM_SPACING, SCN_NAME_Y, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE)) return false;
	if (!CSceneryEdit::ScnControl.RenderName(Map_Renderer, Font, SCN_NAME_X, SCN_NAME_Y)) return false;
	if (!RenderSCNswitch()) return false;
	if (!RenderSCNdepth()) return false;

	return true;
}

bool CApp::RenderSCNdepth()
{
	int Z_magnified = CSceneryEdit::ScnControl.Z * Z_MAGNIFIER;
	int truncator = Z_MAGNIFIER;
	int Xp = DEPTH_COMBO_X;
	int Y_up = DEPTH_COMBO_Y - (CHAR_HEIGHT + SYM_SPACING);
	int Y_dw = DEPTH_COMBO_Y + CHAR_HEIGHT + SYM_SPACING;

	// print each digit of the magnified Z value
	while (truncator != 0)
	{
		int Z_display = (Z_magnified % (truncator * 10)) / truncator;
		Font::Write(Map_Renderer, Font, Z_display, Xp, DEPTH_COMBO_Y);
		CSurface::OnDraw(Map_Renderer, Map_Interface, Xp, Y_up, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
		CSurface::OnDraw(Map_Renderer, Map_Interface, Xp, Y_dw, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
		Xp += CHAR_WIDTH;
		truncator /= 10;
	}
	if (Active_Mod == REMOVE_SCENE)
	{
		truncator = Z_MAGNIFIER;
		int Zl_magnified = CSceneryEdit::ScnControl.Zl * Z_MAGNIFIER;
		int Zu_magnified = CSceneryEdit::ScnControl.Zu * Z_MAGNIFIER;
		int Xl = DEPTH_LOWER_X;
		int Xu = DEPTH_UPPER_X;
		while (truncator != 0)
		{
			int Zl_display = (Zl_magnified % (truncator * 10)) / truncator;
			int Zu_display = (Zu_magnified % (truncator * 10)) / truncator;
			Font::Write(Map_Renderer, Font, Zl_display, Xl, DEPTH_COMBO_Y);
			Font::Write(Map_Renderer, Font, Zu_display, Xu, DEPTH_COMBO_Y);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xl, Y_up, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xl, Y_dw, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xu, Y_up, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xu, Y_dw, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			Xl += CHAR_WIDTH; Xu += CHAR_WIDTH;
			truncator /= 10;
		}
	}
	return true;
}

bool CApp::RenderSCNswitch()
{
	if (!CSceneryEdit::ScnControl.hori_repeat)
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface, SWITCHLIST_X, SWITCHLIST_Y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
			return false;
	}
	else
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface, SWITCHLIST_X, SWITCHLIST_Y, SWITCH_XO, ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
			return false;
	}
	Font::Write(Map_Renderer, Font, "HREP", SWITCHLIST_X + SWITCH_SIZE + SYM_SPACING, SWITCHLIST_Y);
	if (!CSceneryEdit::ScnControl.vert_repeat)
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			SWITCHLIST_X, SWITCHLIST_Y + SWITCH_SIZE + SYM_SPACING, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	else
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			SWITCHLIST_X, SWITCHLIST_Y + SWITCH_SIZE + SYM_SPACING, SWITCH_XO, ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	Font::Write(Map_Renderer, Font, "VREP", SWITCHLIST_X + SWITCH_SIZE + SYM_SPACING, SWITCHLIST_Y + SWITCH_SIZE + SYM_SPACING);
	if (!CSceneryEdit::ScnControl.permanent)
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			SWITCHLIST_X, SWITCHLIST_Y + (2*(SWITCH_SIZE + SYM_SPACING)), SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	else
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			SWITCHLIST_X, SWITCHLIST_Y + (2*(SWITCH_SIZE + SYM_SPACING)), SWITCH_XO, ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	Font::Write(Map_Renderer, Font, "PERM", SWITCHLIST_X + SWITCH_SIZE + SYM_SPACING, SWITCHLIST_Y + (2*(SWITCH_SIZE + SYM_SPACING)));
	return true;
}
