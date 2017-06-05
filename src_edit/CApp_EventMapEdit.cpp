#include "CApp.h"

using namespace map_editor;

bool CApp::EventMAPedit(int mX, int mY)
{
	{
		using namespace but_tset;
		// Click on "Change Tileset" button. This displays a prompt to change tilesets,
		// and the function within the loop performs a change if requested.
		if (mX >= x && mX < x + w)
		{
			if (mY >= y && mY < y + h)
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
	}
	{
		using namespace but_t;
		// Click on "Change Tile" buttons. A display of all tiles is rendered,
		// and clicking a tile will update the active tile to use the clicked tile.
		if (mX >= bg_x && mX < bg_x + bg_w)
		{
			if (mY >= bg_y && mY < bg_y + bg_h)
			{
				PickTile.Init(tset_w, tset_h);
				intrpt = INTRPT_CH_BTILE;
				return true;
			}
		}
		if (mX >= fg_x && mX < fg_x + fg_w)
		{
			if (mY >= fg_y && mY < fg_y + fg_h)
			{
				PickTile.Init(tset_w, tset_h);
				intrpt = INTRPT_CH_FTILE;
				return true;
			}
		}
	}
	{
		using namespace disp_t;
		// Click on arrow LEFT or RIGHT of active background tile.
		// Changes the active tile to previous or next index.
		if (mY >= bg_y && mY < bg_y + TILE_SIZE)
		{
			// Left Arrow
			if (mX >= bg_x - TILE_SIZE && mX < bg_x)
			{
					if (active_bg != 0) active_bg -= 1;
					else active_bg = (tset_w * tset_h) - 1;
					return true;
			}
			// Right Arrow
			if (mX >= bg_x + TILE_SIZE && mX < bg_x + (TILE_SIZE * 2))
			{
					if (active_bg != (tset_w * tset_h) - 1) active_bg += 1;
					else active_bg = 0;
					return true;
			}
		}

		// Click on arrow LEFT or RIGHT of active foreground tile.
		// Changes the active tile to previous or next index.
		if (mY >= fg_y && mY < fg_y + TILE_SIZE)
		{
			// Left Arrow
			if (mX >= fg_x - TILE_SIZE && mX < fg_x)
			{
					if (active_fg != 0) active_fg -= 1;
					else active_fg = (tset_w * tset_h) - 1;
					return true;
			}
			// Right Arrow
			if (mX >= fg_x + TILE_SIZE && mX < fg_x + (TILE_SIZE * 2))
			{
					if (active_fg != (tset_w * tset_h) - 1) active_fg += 1;
					else active_fg = 0;
					return true;
			}
		}

		// Click on arrow LEFT or RIGHT of active tile type.
		// Changes the active tile type to previous or next type index.
		if (mY >= ty_y && mY < ty_y + TILE_SIZE)
		{
			// Left Arrow
			if (mX >= ty_x - TILE_SIZE && mX < ty_x)
			{
					if (active_type != 0) active_type -= 1;
					else active_type = TILE_TYPE_FIRE;
					return true;
			}
			// Right Arrow
			if (mX >= ty_x + TILE_SIZE && mX < ty_x + (TILE_SIZE * 2))
			{
					if (active_type != TILE_TYPE_FIRE) active_type += 1;
					else active_type = 0;
					return true;
			}
		}

		// Click on arrow LEFT or RIGHT of active collision.
		// Changes the active collision to previous or next collision index.
		if (mY >= co_y && mY < co_y + TILE_SIZE)
		{
			// Left Arrow
			if (mX >= co_x - TILE_SIZE && mX < co_x)
			{
					if (active_coll != 0) active_coll -= 1;
					else active_coll = SOLID_A_ML_BR;
					return true;
			}
			// Right Arrow
			if (mX >= co_x + TILE_SIZE && mX < co_x + (TILE_SIZE * 2))
			{
					if (active_coll != SOLID_A_ML_BR) active_coll += 1;
					else active_coll = 0;
					return true;
			}
		}
	}
	{
		using namespace rm_flip;
		// Click on background activity switch.
		// Turn the background tile on/off.
		if (mY >= bg_y && mY < bg_y + SWITCH_SIZE)
		{
			if (mX >= bg_x && mX < bg_x + SWITCH_SIZE)
			{
				if (!no_bg) no_bg = true;
				else no_bg = false;
				return true;
			}
		}

		// Click on foreground activity switch.
		// Turn the foreground tile on/off.
		if (mY >= fg_y && mY < fg_y + SWITCH_SIZE)
		{
			if (mX >= fg_x && mX < fg_x + SWITCH_SIZE)
			{
				if (no_fg) no_fg = false;
				else no_fg = true;
				return true;
			}
		}
	}
	{
		using namespace opac;
		// Click on opacity bar for tile type overlay
		if (mY >= ty_y && mY < ty_y + h)
		{
			if (mX >= x && mX < x + w)
			{
				double barfract = (double)(mX - x) / (double)(w - 1);
				type_alpha = MAX_RGBA * barfract;
				SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);
				return true;
			}
		}
		// Click on opacity bar for tile collision overlay
		if (mY >= co_y && mY < co_y + h)
		{
			if (mX >= x && mX < x + w)
			{
				double barfract = (double)(mX - x) / (double)(w - 1);
				coll_alpha = MAX_RGBA * barfract;
				SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);
				return true;
			}
		}
	}

	{
		using namespace view_flip;
		// Click on View overlay buttons
		if (mX >= x && mX < x + SWITCH_SIZE)
		{
			int Yi = y;
			int Yf = y + SWITCH_SIZE;
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
	}
	{
		using namespace place_flip;
		// Click on active tile attribute switches
		if (mX >= x && mX < x + SWITCH_SIZE)
		{
			int Yi = y;
			int Yf = y + SWITCH_SIZE;
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
	}
	return true;
}
