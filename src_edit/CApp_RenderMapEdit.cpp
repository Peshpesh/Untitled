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
	{
		using namespace but_tset;
		if (!RenderButton(x, y, w, h, BUT_BORDER_SIZ, BLUE_X, COLOR_PURE_Y, true))
			return false;

		// Write a button name for changing a tileset
		Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE", x + (w / 2), y + (h / 2) - MINI_CHAR_SIZE);
		Font::CenterWrite(Map_Renderer, FONT_MINI, "TILESET", x + (w / 2), y + (h / 2) + MINI_CHAR_SIZE);
	}
	{
		using namespace disp_t;
		// Draw complete active tile with dummy entity & outline (for depth clarity)
		Font::CenterWrite(Map_Renderer, FONT_MINI, "WORKING TILE", EWIDTH - 50, bgfg_y - name_offset);
		if (!no_bg)
		{
			CSurface::OnDraw(Map_Renderer, Main_Tileset, bgfg_x, bgfg_y,
				(active_bg % tset_w) * TILE_SIZE, (active_bg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
		CSurface::OnDraw(Map_Renderer, Map_Interface, bgfg_x, bgfg_y,
			dummy_x, dummy_y, TILE_SIZE, TILE_SIZE);
		if (!no_fg)
		{
			CSurface::OnDraw(Map_Renderer, Main_Tileset, bgfg_x, bgfg_y,
				(active_fg % tset_w) * TILE_SIZE, (active_fg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
		}
		CSurface::OnDraw(Map_Renderer, Map_Interface, bgfg_x, bgfg_y,
			dummy_x, dummy_y + TILE_SIZE, TILE_SIZE, TILE_SIZE);

		// Draws active background tile
		Font::CenterWrite(Map_Renderer, FONT_MINI, "BACKGROUND", EWIDTH - 50, bg_y - name_offset);
		CSurface::OnDraw(Map_Renderer, Main_Tileset, bg_x, bg_y,
			(active_bg % tset_w) * TILE_SIZE,
			(active_bg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

		// Draws background tile arrows
		CSurface::OnDraw(Map_Renderer, Map_Interface, bg_x - ((TILE_SIZE+ARR_SZ)/2),
				bg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
		CSurface::OnDraw(Map_Renderer, Map_Interface, bg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
				bg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

		// Foreground tile header & switch
		Font::CenterWrite(Map_Renderer, FONT_MINI, "FOREGROUND", EWIDTH - 50, fg_y - name_offset);

		// Draws active foreground tile
		CSurface::OnDraw(Map_Renderer, Main_Tileset, fg_x, fg_y,
			(active_fg % tset_w) * TILE_SIZE,
			(active_fg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

		// Draws foreground tile arrows
		CSurface::OnDraw(Map_Renderer, Map_Interface, fg_x - ((TILE_SIZE+ARR_SZ)/2),
				fg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
		CSurface::OnDraw(Map_Renderer, Map_Interface, fg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
				fg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

		// Draws active tile type
		CSurface::OnDraw(Map_Renderer, Type_Tileset, ty_x, ty_y,
			(active_type % type_w) * TILE_SIZE,
			(active_type / type_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

		// Draws tile type arrows
		CSurface::OnDraw(Map_Renderer, Map_Interface, ty_x - ((TILE_SIZE+ARR_SZ)/2),
			ty_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
		CSurface::OnDraw(Map_Renderer, Map_Interface, ty_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			ty_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

		// Writes out the active type
		switch (active_type)
		{
			case TILE_TYPE_NORMAL: Font::CenterWrite(Map_Renderer, FONT_MINI, "NORMAL", EWIDTH - 50, ty_y - name_offset); break;
			case TILE_TYPE_WATER: Font::CenterWrite(Map_Renderer, FONT_MINI, "WATER", EWIDTH - 50, ty_y - name_offset); break;
			case TILE_TYPE_ICE: Font::CenterWrite(Map_Renderer, FONT_MINI, "ICE", EWIDTH - 50, ty_y - name_offset); break;
			case TILE_TYPE_FIRE: Font::CenterWrite(Map_Renderer, FONT_MINI, "FIRE", EWIDTH - 50, ty_y - name_offset); break;
			default: break;
		}

		// Draws active collision tile
		CSurface::OnDraw(Map_Renderer, Coll_Tileset, co_x, co_y,
			(active_coll % coll_w) * TILE_SIZE,
			(active_coll / coll_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

		// Draws collision tile arrows
		CSurface::OnDraw(Map_Renderer, Map_Interface, co_x - ((TILE_SIZE+ARR_SZ)/2),
				co_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
		CSurface::OnDraw(Map_Renderer, Map_Interface, co_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
				co_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

		// Writes out the active collision type
		switch (active_coll)
		{
			case SOLID_NONE: Font::CenterWrite(Map_Renderer, FONT_MINI, "NONE", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_ALL: Font::CenterWrite(Map_Renderer, FONT_MINI, "FULL", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_U_BL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UBLMR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_U_ML_TR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UMLTR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_U_TL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UTLMR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_U_ML_BR: Font::CenterWrite(Map_Renderer, FONT_MINI, "UMLBR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_A_BL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "ABLMR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_A_ML_TR: Font::CenterWrite(Map_Renderer, FONT_MINI, "AMLTR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_A_TL_MR: Font::CenterWrite(Map_Renderer, FONT_MINI, "ATLMR", EWIDTH - 50, co_y - name_offset); break;
			case SOLID_A_ML_BR: Font::CenterWrite(Map_Renderer, FONT_MINI, "AMLBR", EWIDTH - 50, co_y - name_offset); break;
			default: break;
		}
	}
	{
		using namespace rm_flip;
		CSurface::OnDraw(Map_Renderer, Map_Interface, bg_x, bg_y, SWITCH_XO, no_bg ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		CSurface::OnDraw(Map_Renderer, Map_Interface, fg_x, fg_y, SWITCH_XO, no_fg ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	{
		using namespace opac;
		// Draw an opacity meter for Type overlay
		int opacity_W = w * ((double)(type_alpha) / (double)(MAX_RGBA));
		CSurface::OnDraw(Map_Renderer, Map_Interface, x, ty_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, h);
		CSurface::OnDraw(Map_Renderer, Map_Interface, x + opacity_W, ty_y, DARKS_X, COLOR_PURE_Y, 1, 1, w - opacity_W, h);

		// Draw an opacity meter for Collision overlay
		opacity_W = w * ((double)(coll_alpha) / (double)(MAX_RGBA));
		CSurface::OnDraw(Map_Renderer, Map_Interface, x, co_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, h);
		CSurface::OnDraw(Map_Renderer, Map_Interface, x + opacity_W, co_y, DARKS_X, COLOR_PURE_Y, 1, 1, w - opacity_W, h);
	}
	return true;
}

bool CApp::RenderMAPbottom()
{
	bool hl = !(intrpt ^ INTRPT_NONE);
	int colX;
	{
		using namespace but_t;
		// render button for picking background tiles
		if (intrpt & INTRPT_CH_BTILE) colX = RED_X;
		else colX = BLUE_X;

		if (!RenderButton(bg_x, bg_y, bg_w, bg_h, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
			return false;
		Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE B.TILE", bg_x + (bg_w / 2), bg_y + (bg_h / 2));

		// render button for picking foreground tiles
		if (intrpt & INTRPT_CH_FTILE) colX = RED_X;
		else colX = BLUE_X;
		if (!RenderButton(fg_x, fg_y, fg_w, fg_h, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
			return false;
		Font::CenterWrite(Map_Renderer, FONT_MINI, "CHANGE F.TILE", fg_x + (fg_w / 2), fg_y + (fg_h / 2));
	}
	{
		using namespace view_flip;
		// Menu/Options list for viewing various overlays
		int sY = y - (SWITCH_SIZE + SYM_SPACING);
		int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
		int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
		Font::Write(Map_Renderer, FONT_MINI, "Overlay Switches", x, sY + tY_offset);
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(Map_Renderer, FONT_MINI, "Foreground", x + tX_offset, sY + tY_offset);
		if (show_fg)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(Map_Renderer, FONT_MINI, "Tile Types", x + tX_offset, sY + tY_offset);
		if (show_ty)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(Map_Renderer, FONT_MINI, "Collisions", x + tX_offset, sY + tY_offset);
		if (show_co)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
	}
	{
		using namespace place_flip;
		// Menu/Options list for active tile attributes on placement
		int sY = y;
		int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
		int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
		Font::Write(Map_Renderer, FONT_MINI, "Use B.Tile", x + tX_offset, sY + tY_offset);
		if (OnTiles & ENABLE_BTILE)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(Map_Renderer, FONT_MINI, "Use F.Tile", x + tX_offset, sY + tY_offset);
		if (OnTiles & ENABLE_FTILE)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(Map_Renderer, FONT_MINI, "Use Type", x + tX_offset, sY + tY_offset);
		if (OnTiles & ENABLE_TYPE)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(Map_Renderer, FONT_MINI, "Use Collision", x + tX_offset, sY + tY_offset);
		if (OnTiles & ENABLE_COLL)
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(Map_Renderer, Map_Interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
	}
	return true;
}
