#include "CApp.h"

using namespace map_editor;

bool CApp::EventMAPedit(int mX, int mY)
{
	// Click on "Change Tileset" button. This displays a prompt to change tilesets,
	// and the function within the loop performs a change if requested.
	if (mX >= but_tset::x && mX < but_tset::x + but_tset::w)
	{
		if (mY >= but_tset::y && mY < but_tset::y + but_tset::h)
		{
			if ((Main_Tileset = CUI::UIControl.OnChange(Map_Renderer, Map_Interface, Tileset_Path)) != NULL)
			{
				CArea::AreaControl.ChangeSet(Main_Tileset);
				active_bg = 0;
				QueryTileset();
				return true;
			}
		}
	}

	// Click on "Change Tile" buttons. A display of all tiles is rendered,
	// and clicking a tile will update the active tile to use the clicked tile.
	if (mX >= but_t::bg_x && mX < but_t::bg_x + but_t::bg_w)
	{
		if (mY >= but_t::bg_y && mY < but_t::bg_y + but_t::bg_h)
		{
			PickTile.Init(tset_w, tset_h);
			intrpt = INTRPT_CH_BTILE;
			return true;
		}
	}
	if (mX >= but_t::fg_x && mX < but_t::fg_x + but_t::fg_w)
	{
		if (mY >= but_t::fg_y && mY < but_t::fg_y + but_t::fg_h)
		{
			PickTile.Init(tset_w, tset_h);
			intrpt = INTRPT_CH_FTILE;
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active background tile.
	// Changes the active tile to previous or next index.
	if (mY >= disp_t::bg_y && mY < disp_t::bg_y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= disp_t::bg_x - TILE_SIZE && mX < disp_t::bg_x)
		{
				if (active_bg != 0) active_bg -= 1;
				else active_bg = (tset_w * tset_h) - 1;
				return true;
		}
		// Right Arrow
		if (mX >= disp_t::bg_x + TILE_SIZE && mX < disp_t::bg_x + (TILE_SIZE * 2))
		{
				if (active_bg != (tset_w * tset_h) - 1) active_bg += 1;
				else active_bg = 0;
				return true;
		}
	}

	// Click on background activity switch.
	// Turn the background tile on/off.
	if (mY >= rm_flip::bg_y && mY < rm_flip::bg_y + SWITCH_SIZE)
	{
		if (mX >= rm_flip::bg_x && mX < rm_flip::bg_x + SWITCH_SIZE)
		{
			if (!no_bg) no_bg = true;
			else no_bg = false;
			return true;
		}
	}

	// Click on foreground activity switch.
	// Turn the foreground tile on/off.
	if (mY >= rm_flip::fg_y && mY < rm_flip::fg_y + SWITCH_SIZE)
	{
		if (mX >= rm_flip::fg_x && mX < rm_flip::fg_x + SWITCH_SIZE)
		{
			if (no_fg) no_fg = false;
			else no_fg = true;
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active foreground tile.
	// Changes the active tile to previous or next index.
	if (mY >= disp_t::fg_y && mY < disp_t::fg_y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= disp_t::fg_x - TILE_SIZE && mX < disp_t::fg_x)
		{
				if (active_fg != 0) active_fg -= 1;
				else active_fg = (tset_w * tset_h) - 1;
				return true;
		}
		// Right Arrow
		if (mX >= disp_t::fg_x + TILE_SIZE && mX < disp_t::fg_x + (TILE_SIZE * 2))
		{
				if (active_fg != (tset_w * tset_h) - 1) active_fg += 1;
				else active_fg = 0;
				return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active tile type.
	// Changes the active tile type to previous or next type index.
	if (mY >= disp_t::ty_y && mY < disp_t::ty_y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= disp_t::ty_x - TILE_SIZE && mX < disp_t::ty_x)
		{
				if (active_type != 0) active_type -= 1;
				else active_type = TILE_TYPE_FIRE;
				return true;
		}
		// Right Arrow
		if (mX >= disp_t::ty_x + TILE_SIZE && mX < disp_t::ty_x + (TILE_SIZE * 2))
		{
				if (active_type != TILE_TYPE_FIRE) active_type += 1;
				else active_type = 0;
				return true;
		}
	}

	// Click on opacity bar for tile type overlay
	if (mY >= opac::ty_y && mY < opac::ty_y + opac::h)
	{
		if (mX >= opac::x && mX < opac::x + opac::w)
		{
			double barfract = (double)(mX - opac::x) / (double)(opac::w - 1);
			type_alpha = MAX_RGBA * barfract;
			SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active collision.
	// Changes the active collision to previous or next collision index.
	if (mY >= disp_t::co_y && mY < disp_t::co_y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= disp_t::co_x - TILE_SIZE && mX < disp_t::co_x)
		{
				if (active_coll != 0) active_coll -= 1;
				else active_coll = SOLID_A_ML_BR;
				return true;
		}
		// Right Arrow
		if (mX >= disp_t::co_x + TILE_SIZE && mX < disp_t::co_x + (TILE_SIZE * 2))
		{
				if (active_coll != SOLID_A_ML_BR) active_coll += 1;
				else active_coll = 0;
				return true;
		}
	}

	// Click on opacity bar for tile collision overlay
	if (mY >= opac::co_y && mY < opac::co_y + opac::h)
	{
		if (mX >= opac::x && mX < opac::x + opac::w)
		{
			double barfract = (double)(mX - opac::x) / (double)(opac::w - 1);
			coll_alpha = MAX_RGBA * barfract;
			SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);
			return true;
		}
	}

	// Click on View overlay buttons
	if (mX >= view_flip::x && mX < view_flip::x + SWITCH_SIZE)
	{
		int Yi = view_flip::y;
		int Yf = view_flip::y + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (show_fg) show_fg = false;
			else show_fg = true;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (show_ty) show_ty = false;
			else show_ty = true;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (show_co) show_co = false;
			else show_co = true;
			return true;
		}
	}

	// Click on active tile attribute switches
	if (mX >= place_flip::x && mX < place_flip::x + SWITCH_SIZE)
	{
		int Yi = place_flip::y;
		int Yf = place_flip::y + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (OnTiles & ENABLE_BTILE) OnTiles ^= ENABLE_BTILE;
			else OnTiles |= ENABLE_BTILE;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (OnTiles & ENABLE_FTILE) OnTiles ^= ENABLE_FTILE;
			else OnTiles |= ENABLE_FTILE;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (OnTiles & ENABLE_TYPE) OnTiles ^= ENABLE_TYPE;
			else OnTiles |= ENABLE_TYPE;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (OnTiles & ENABLE_COLL) OnTiles ^= ENABLE_COLL;
			else OnTiles |= ENABLE_COLL;
			return true;
		}
	}

	return true;
}
