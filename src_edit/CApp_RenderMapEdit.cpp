#include "CApp.h"

using namespace map_editor;

bool CApp::RenderMAPedit()
{
	if (!RenderMAPside()) return false;
	if (!RenderMAPbottom()) return false;
	return true;
}

bool CApp::RenderMAPside()
{
	if (!RenderButton(but_tset::x, but_tset::y, but_tset::w, but_tset::h, BUT_BORDER_SIZ, BLUE_X, COLOR_PURE_Y, true))
		return false;

	// Write a button name for changing a tileset
	Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE", but_tset::x + (but_tset::w / 2), but_tset::y + (but_tset::h / 2) - MINI_CHAR_SIZE);
	Font::CenterWrite(Map_Renderer, FONT_MINI, "TILESET", but_tset::x + (but_tset::w / 2), but_tset::y + (but_tset::h / 2) + MINI_CHAR_SIZE);

	// Draw complete active tile with dummy entity & outline (for depth clarity)
	Font::CenterWrite(Map_Renderer, FONT_MINI, "WORKING TILE", EWIDTH - 50, disp_t::bgfg_y - disp_t::name_offset);
	if (!NoBack)
	{
		CSurface::OnDraw(Map_Renderer, Main_Tileset, disp_t::bgfg_x, disp_t::bgfg_y,
			(Current_Tile % TilesetWidth) * TILE_SIZE, (Current_Tile / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::bgfg_x, disp_t::bgfg_y,
		dummy_x, dummy_y, TILE_SIZE, TILE_SIZE);
	if (!NoFore)
	{
		CSurface::OnDraw(Map_Renderer, Main_Tileset, disp_t::bgfg_x, disp_t::bgfg_y,
			(Current_Fore % TilesetWidth) * TILE_SIZE, (Current_Fore / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::bgfg_x, disp_t::bgfg_y,
		dummy_x, dummy_y + TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws active background tile
	Font::CenterWrite(Map_Renderer, FONT_MINI, "BACKGROUND", EWIDTH - 50, disp_t::bg_y - disp_t::name_offset);
	CSurface::OnDraw(Map_Renderer, Map_Interface, rm_flip::bg_x, rm_flip::bg_y, SWITCH_XO, NoBack ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	CSurface::OnDraw(Map_Renderer, Main_Tileset, disp_t::bg_x, disp_t::bg_y,
		(Current_Tile % TilesetWidth) * TILE_SIZE,
		(Current_Tile / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws background tile arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::bg_x - ((TILE_SIZE+ARROW_SIZE)/2),
			disp_t::bg_y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::bg_x + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			disp_t::bg_y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Foreground tile header & switch
	Font::CenterWrite(Map_Renderer, FONT_MINI, "FOREGROUND", EWIDTH - 50, disp_t::fg_y - disp_t::name_offset);
	CSurface::OnDraw(Map_Renderer, Map_Interface, rm_flip::fg_x, rm_flip::fg_y, SWITCH_XO, NoFore ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	// Draws active foreground tile
	CSurface::OnDraw(Map_Renderer, Main_Tileset, disp_t::fg_x, disp_t::fg_y,
		(Current_Fore % TilesetWidth) * TILE_SIZE,
		(Current_Fore / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws foreground tile arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::fg_x - ((TILE_SIZE+ARROW_SIZE)/2),
			disp_t::fg_y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::fg_x + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			disp_t::fg_y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Draws active tile type
	CSurface::OnDraw(Map_Renderer, Type_Tileset, disp_t::ty_x, disp_t::ty_y,
		(Current_Type % TypesetWidth) * TILE_SIZE,
		(Current_Type / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile type arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::ty_x - ((TILE_SIZE+ARROW_SIZE)/2),
			disp_t::ty_y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::ty_x + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			disp_t::ty_y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Writes out the active type
	switch (Current_Type)
	{
		case TILE_TYPE_NORMAL: Font::CenterWrite(Map_Renderer, FONT_MINI, "NORMAL", EWIDTH - 50, disp_t::ty_y - disp_t::name_offset); break;
		case TILE_TYPE_WATER: Font::CenterWrite(Map_Renderer, FONT_MINI, "WATER", EWIDTH - 50, disp_t::ty_y - disp_t::name_offset); break;
		case TILE_TYPE_ICE: Font::CenterWrite(Map_Renderer, FONT_MINI, "ICE", EWIDTH - 50, disp_t::ty_y - disp_t::name_offset); break;
		case TILE_TYPE_FIRE: Font::CenterWrite(Map_Renderer, FONT_MINI, "FIRE", EWIDTH - 50, disp_t::ty_y - disp_t::name_offset); break;
		default: break;
	}

	// Draw an opacity bar for Type overlay
	int opacity_W = opac::w*((double)(Type_Alpha)/(double)(MAX_RGBA));
	CSurface::OnDraw(Map_Renderer, Map_Interface, opac::x, opac::ty_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, opac::h);
	CSurface::OnDraw(Map_Renderer, Map_Interface, opac::x + opacity_W, opac::ty_y, DARKS_X, COLOR_PURE_Y, 1, 1, opac::w - opacity_W, opac::h);

	// Draws active collision tile
	CSurface::OnDraw(Map_Renderer, Coll_Tileset, disp_t::co_x, disp_t::co_y,
		(Current_Coll % CollsetWidth) * TILE_SIZE,
		(Current_Coll / CollsetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws collision tile arrows
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::co_x - ((TILE_SIZE+ARROW_SIZE)/2),
			disp_t::co_y + ((TILE_SIZE-ARROW_SIZE)/2), L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, disp_t::co_x + TILE_SIZE + ((TILE_SIZE-ARROW_SIZE)/2),
			disp_t::co_y + ((TILE_SIZE-ARROW_SIZE)/2), R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Writes out the active collision type
	switch (Current_Coll)
	{
	case SOLID_NONE: Font::CenterWrite(Map_Renderer, FONT_MINI, "NONE", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_ALL: Font::CenterWrite(Map_Renderer, FONT_MINI, "FULL", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_U_BL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UBLMR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_U_ML_TR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UMLTR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_U_TL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UTLMR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_U_ML_BR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UMLBR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_A_BL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "ABLMR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_A_ML_TR: Font::CenterWrite(Map_Renderer, FONT_MINI, "AMLTR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_A_TL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "ATLMR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	case SOLID_A_ML_BR: Font::CenterWrite(Map_Renderer, FONT_MINI, "AMLBR", EWIDTH - 50, disp_t::co_y - disp_t::name_offset); break;
	default: break;
	}

	// Draw an opacity bar for collision overlay
	opacity_W = opac::w*((double)(Coll_Alpha)/(double)(MAX_RGBA));
	CSurface::OnDraw(Map_Renderer, Map_Interface, opac::x, opac::co_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, opac::h);
	CSurface::OnDraw(Map_Renderer, Map_Interface, opac::x + opacity_W, opac::co_y, DARKS_X, COLOR_PURE_Y, 1, 1, opac::w - opacity_W, opac::h);

	return true;
}

bool CApp::RenderMAPbottom()
{
	bool hl = !(Interrupt ^ INTRPT_NONE);
	int colX;

	// render button for picking background tiles
	if (Interrupt & INTRPT_CH_BTILE) colX = RED_X;
	else colX = BLUE_X;

	if (!RenderButton(but_t::bg_x, but_t::bg_y, but_t::bg_w, but_t::bg_h, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
		return false;
	Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE B.TILE", but_t::bg_x + (but_t::bg_w / 2), but_t::bg_y + (but_t::bg_h / 2));

	// render button for picking foreground tiles
	if (Interrupt & INTRPT_CH_FTILE) colX = RED_X;
	else colX = BLUE_X;
	if (!RenderButton(but_t::fg_x, but_t::fg_y, but_t::fg_w, but_t::fg_h, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
		return false;
	Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE F.TILE", but_t::fg_x + (but_t::fg_w / 2), but_t::fg_y + (but_t::fg_h / 2));

	// Menu/Options list for viewing various overlays
	int sY = view_flip::y - (SWITCH_SIZE + SYM_SPACING);
	int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
	int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
	Font::Write(Map_Renderer, FONT_MINI, "Overlay Switches", view_flip::x, sY + tY_offset);
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Foreground", view_flip::x + tX_offset, sY + tY_offset);
	if (View_Fore)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, view_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, view_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Tile Types", view_flip::x + tX_offset, sY + tY_offset);
	if (View_Type)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, view_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, view_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Collisions", view_flip::x + tX_offset, sY + tY_offset);
	if (View_Coll)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, view_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, view_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}

	// Menu/Options list for active tile attributes on placement
	sY = place_flip::y;
	tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
	tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
	Font::Write(Map_Renderer, FONT_MINI, "Use B.Tile", place_flip::x + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_BTILE)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Use F.Tile", place_flip::x + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_FTILE)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Use Type", place_flip::x + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_TYPE)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(Map_Renderer, FONT_MINI, "Use Collision", place_flip::x + tX_offset, sY + tY_offset);
	if (OnTiles & ENABLE_COLL)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, place_flip::x, sY, SWITCH_XO,
			OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	return true;
}
