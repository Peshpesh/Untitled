#include "CApp.h"

bool CApp::RenderMAPedit()
{
	if (!RenderMAPside()) return false;
	if (!RenderMAPbottom()) return false;
	return true;
}

bool CApp::RenderMAPside()
{
	if (!RenderButton(TS_CHG_BUT_X, TS_CHG_BUT_Y, TS_CHG_BUT_W, TS_CHG_BUT_H, BUT_BORDER_SIZ, BLUE_X, COLOR_PURE_Y, true))
		return false;

	// Write a button name for changing a tileset
	Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE", TS_CHG_BUT_X + (TS_CHG_BUT_W / 2), TS_CHG_BUT_Y + (TS_CHG_BUT_H / 2) - MINI_CHAR_SIZE);
	Font::CenterWrite(Map_Renderer, FONT_MINI, "TILESET", TS_CHG_BUT_X + (TS_CHG_BUT_W / 2), TS_CHG_BUT_Y + (TS_CHG_BUT_H / 2) + MINI_CHAR_SIZE);

	// Draw complete active tile with dummy entity & outline (for depth clarity)
	Font::CenterWrite(Map_Renderer, FONT_MINI, "WORKING TILE", EWIDTH - 50, DISP_TILE_Y - DISP_NAME_OFFSET);
	if (!NoBack)
	{
		CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_TILE_X, DISP_TILE_Y,
			(Current_Tile % TilesetWidth) * TILE_SIZE, (Current_Tile / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_TILE_X, DISP_TILE_Y,
		DUMMY_ENTITY_X, DUMMY_ENTITY_Y, TILE_SIZE, TILE_SIZE);
	if (!NoFore)
	{
		CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_TILE_X, DISP_TILE_Y,
			(Current_Fore % TilesetWidth) * TILE_SIZE, (Current_Fore / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_TILE_X, DISP_TILE_Y,
		DUMMY_ENTITY_X, DUMMY_ENTITY_Y + TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws active background tile
	Font::CenterWrite(Map_Renderer, FONT_MINI, "BACKGROUND", EWIDTH - 50, DISP_BTILE_Y - DISP_NAME_OFFSET);
	CSurface::OnDraw(Map_Renderer, Map_Interface, BACK_SWIT_X, BACK_SWIT_Y, SWITCH_XO, NoBack ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_BTILE_X, DISP_BTILE_Y,
		(Current_Tile % TilesetWidth) * TILE_SIZE,
		(Current_Tile / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws background tile arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_BTILE_X - ((TILE_SIZE+ARROW_SIZE)/2),
			DISP_BTILE_Y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_BTILE_X + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			DISP_BTILE_Y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Foreground tile header & switch
	Font::CenterWrite(Map_Renderer, FONT_MINI, "FOREGROUND", EWIDTH - 50, DISP_FTILE_Y - DISP_NAME_OFFSET);
	CSurface::OnDraw(Map_Renderer, Map_Interface, FORE_SWIT_X, FORE_SWIT_Y, SWITCH_XO, NoFore ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	// Draws active foreground tile
	CSurface::OnDraw(Map_Renderer, Main_Tileset, DISP_FTILE_X, DISP_FTILE_Y,
		(Current_Fore % TilesetWidth) * TILE_SIZE,
		(Current_Fore / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws foreground tile arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_FTILE_X - ((TILE_SIZE+ARROW_SIZE)/2),
			DISP_FTILE_Y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_FTILE_X + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			DISP_FTILE_Y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Draws active tile type
	CSurface::OnDraw(Map_Renderer, Type_Tileset, DISP_TYPE_X, DISP_TYPE_Y,
		(Current_Type % TypesetWidth) * TILE_SIZE,
		(Current_Type / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile type arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_TYPE_X - ((TILE_SIZE+ARROW_SIZE)/2),
			DISP_TYPE_Y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_TYPE_X + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			DISP_TYPE_Y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Writes out the active type
	switch (Current_Type)
	{
		case TILE_TYPE_NORMAL: Font::CenterWrite(Map_Renderer, FONT_MINI, "NORMAL", EWIDTH - 50, DISP_TYPE_Y - DISP_NAME_OFFSET); break;
		case TILE_TYPE_WATER: Font::CenterWrite(Map_Renderer, FONT_MINI, "WATER", EWIDTH - 50, DISP_TYPE_Y - DISP_NAME_OFFSET); break;
		case TILE_TYPE_ICE: Font::CenterWrite(Map_Renderer, FONT_MINI, "ICE", EWIDTH - 50, DISP_TYPE_Y - DISP_NAME_OFFSET); break;
		case TILE_TYPE_FIRE: Font::CenterWrite(Map_Renderer, FONT_MINI, "FIRE", EWIDTH - 50, DISP_TYPE_Y - DISP_NAME_OFFSET); break;
		default: break;
	}

	// Draw an opacity bar for Type overlay
	int opacity_W = ALPH_BAR_W*((double)(Type_Alpha)/(double)(MAX_RGBA));
	CSurface::OnDraw(Map_Renderer, Map_Interface, ALPH_BAR_X, ALPH_TYPE_Y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, ALPH_BAR_H);
	CSurface::OnDraw(Map_Renderer, Map_Interface, ALPH_BAR_X + opacity_W, ALPH_TYPE_Y, DARKS_X, COLOR_PURE_Y, 1, 1, ALPH_BAR_W - opacity_W, ALPH_BAR_H);

	// Draws active collision tile
	CSurface::OnDraw(Map_Renderer, Coll_Tileset, DISP_COLL_X, DISP_COLL_Y,
		(Current_Coll % CollsetWidth) * TILE_SIZE,
		(Current_Coll / CollsetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws collision tile arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_COLL_X - ((TILE_SIZE+ARROW_SIZE)/2),
			DISP_COLL_Y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, DISP_COLL_X + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			DISP_COLL_Y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Writes out the active collision type
	switch (Current_Coll)
	{
	case SOLID_NONE: Font::CenterWrite(Map_Renderer, FONT_MINI, "NONE", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_ALL: Font::CenterWrite(Map_Renderer, FONT_MINI, "FULL", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_U_BL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UBLMR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_U_ML_TR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UMLTR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_U_TL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UTLMR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_U_ML_BR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UMLBR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_A_BL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "ABLMR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_A_ML_TR: Font::CenterWrite(Map_Renderer, FONT_MINI, "AMLTR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_A_TL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "ATLMR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	case SOLID_A_ML_BR: Font::CenterWrite(Map_Renderer, FONT_MINI, "AMLBR", EWIDTH - 50, DISP_COLL_Y - DISP_NAME_OFFSET); break;
	default: break;
	}

	// Draw an opacity bar for collision overlay
	opacity_W = ALPH_BAR_W*((double)(Coll_Alpha)/(double)(MAX_RGBA));
	CSurface::OnDraw(Map_Renderer, Map_Interface, ALPH_BAR_X, ALPH_COLL_Y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, ALPH_BAR_H);
	CSurface::OnDraw(Map_Renderer, Map_Interface, ALPH_BAR_X + opacity_W, ALPH_COLL_Y, DARKS_X, COLOR_PURE_Y, 1, 1, ALPH_BAR_W - opacity_W, ALPH_BAR_H);

	return true;
}

bool CApp::RenderMAPbottom()
{
	bool hl = !(Interrupt ^ INTRPT_NONE);
	int colX;

	// render button for picking background tiles
	if (Interrupt & INTRPT_CH_BTILE) colX = RED_X;
	else colX = BLUE_X;

	if (!RenderButton(BTILE_CHG_BUT_X, BTILE_CHG_BUT_Y, BTILE_CHG_BUT_W, BTILE_CHG_BUT_H, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
		return false;
	Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE B.TILE", BTILE_CHG_BUT_X + (BTILE_CHG_BUT_W / 2), BTILE_CHG_BUT_Y + (BTILE_CHG_BUT_H / 2));

	// render button for picking foreground tiles
	if (Interrupt & INTRPT_CH_FTILE) colX = RED_X;
	else colX = BLUE_X;
	if (!RenderButton(FTILE_CHG_BUT_X, FTILE_CHG_BUT_Y, FTILE_CHG_BUT_W, FTILE_CHG_BUT_H, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
		return false;
	Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE F.TILE", FTILE_CHG_BUT_X + (FTILE_CHG_BUT_W / 2), FTILE_CHG_BUT_Y + (FTILE_CHG_BUT_H / 2));

	// Menu/Options list for viewing various overlays
	int sY = VIEWOPTS_Y - (SWITCH_SIZE + SYM_SPACING);
	int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
	int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
	Font::Write(Map_Renderer, FONT_MINI, "Overlay Switches", VIEWOPTS_X, sY + tY_offset);
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Foreground", VIEWOPTS_X + tX_offset, sY + tY_offset);
	if (View_Fore)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, VIEWOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, VIEWOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Tile Types", VIEWOPTS_X + tX_offset, sY + tY_offset);
	if (View_Type)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, VIEWOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, VIEWOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Collisions", VIEWOPTS_X + tX_offset, sY + tY_offset);
	if (View_Coll)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, VIEWOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, VIEWOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}

	// Menu/Options list for active tile attributes on placement
	sY = TILEOPTS_Y;
	tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
	tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
	Font::Write(Map_Renderer, FONT_MINI, "Use B.Tile", TILEOPTS_X + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_BTILE)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Use F.Tile", TILEOPTS_X + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_FTILE)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Use Type", TILEOPTS_X + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_TYPE)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Use Collision", TILEOPTS_X + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_COLL)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, TILEOPTS_X, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	return true;
}
