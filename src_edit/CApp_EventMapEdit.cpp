#include "CApp.h"

bool CApp::EventMAPedit(int mX, int mY)
{
	using namespace map_editor;
	
	// Click on "Change Tileset" button. This displays a prompt to change tilesets,
	// and the function within the loop performs a change if requested.
	if (mX >= TS_CHG_BUT_X && mX < TS_CHG_BUT_X + TS_CHG_BUT_W)
	{
		if (mY >= TS_CHG_BUT_Y && mY < TS_CHG_BUT_Y + TS_CHG_BUT_H)
		{
			if ((Main_Tileset = CUI::UIControl.OnChange(Map_Renderer, Map_Interface, Tileset_Path)) != NULL)
			{
				CArea::AreaControl.ChangeSet(Main_Tileset);
				Current_Tile = 0;
				QueryTileset();
				return true;
			}
		}
	}

	// Click on "Change Tile" buttons. A display of all tiles is rendered,
	// and clicking a tile will update the active tile to use the clicked tile.
	if (mX >= BTILE_CHG_BUT_X && mX < BTILE_CHG_BUT_X + BTILE_CHG_BUT_W)
	{
		if (mY >= BTILE_CHG_BUT_Y && mY < BTILE_CHG_BUT_Y + BTILE_CHG_BUT_H)
		{
			PickTile.Init(TilesetWidth, TilesetHeight);
			Interrupt = INTRPT_CH_BTILE;
			return true;
		}
	}
	if (mX >= FTILE_CHG_BUT_X && mX < FTILE_CHG_BUT_X + FTILE_CHG_BUT_W)
	{
		if (mY >= FTILE_CHG_BUT_Y && mY < FTILE_CHG_BUT_Y + FTILE_CHG_BUT_H)
		{
			PickTile.Init(TilesetWidth, TilesetHeight);
			Interrupt = INTRPT_CH_FTILE;
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active background tile.
	// Changes the active tile to previous or next index.
	if (mY >= DISP_BTILE_Y && mY < DISP_BTILE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_BTILE_X - TILE_SIZE && mX < DISP_BTILE_X)
		{
				if (Current_Tile != 0) Current_Tile -= 1;
				else Current_Tile = (TilesetWidth * TilesetHeight) - 1;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_BTILE_X + TILE_SIZE && mX < DISP_BTILE_X + (TILE_SIZE * 2))
		{
				if (Current_Tile != (TilesetWidth * TilesetHeight) - 1) Current_Tile += 1;
				else Current_Tile = 0;
				return true;
		}
	}

	// Click on background activity switch.
	// Turn the background tile on/off.
	if (mY >= BACK_SWIT_Y && mY < BACK_SWIT_Y + SWITCH_SIZE)
	{
		if (mX >= BACK_SWIT_X && mX < BACK_SWIT_X + SWITCH_SIZE)
		{
			if (!NoBack) NoBack = true;
			else NoBack = false;
			return true;
		}
	}

	// Click on foreground activity switch.
	// Turn the foreground tile on/off.
	if (mY >= FORE_SWIT_Y && mY < FORE_SWIT_Y + SWITCH_SIZE)
	{
		if (mX >= FORE_SWIT_X && mX < FORE_SWIT_X + SWITCH_SIZE)
		{
			if (NoFore) NoFore = false;
			else NoFore = true;
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active foreground tile.
	// Changes the active tile to previous or next index.
	if (mY >= DISP_FTILE_Y && mY < DISP_FTILE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_FTILE_X - TILE_SIZE && mX < DISP_FTILE_X)
		{
				if (Current_Fore != 0) Current_Fore -= 1;
				else Current_Fore = (TilesetWidth * TilesetHeight) - 1;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_FTILE_X + TILE_SIZE && mX < DISP_FTILE_X + (TILE_SIZE * 2))
		{
				if (Current_Fore != (TilesetWidth * TilesetHeight) - 1) Current_Fore += 1;
				else Current_Fore = 0;
				return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active tile type.
	// Changes the active tile type to previous or next type index.
	if (mY >= DISP_TYPE_Y && mY < DISP_TYPE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_TYPE_X - TILE_SIZE && mX < DISP_TYPE_X)
		{
				if (Current_Type != 0) Current_Type -= 1;
				else Current_Type = TILE_TYPE_FIRE;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_TYPE_X + TILE_SIZE && mX < DISP_TYPE_X + (TILE_SIZE * 2))
		{
				if (Current_Type != TILE_TYPE_FIRE) Current_Type += 1;
				else Current_Type = 0;
				return true;
		}
	}

	// Click on opacity bar for tile type overlay
	if (mY >= ALPH_TYPE_Y && mY < ALPH_TYPE_Y + ALPH_BAR_H)
	{
		if (mX >= ALPH_BAR_X && mX < ALPH_BAR_X + ALPH_BAR_W)
		{
			double barfract = (double)(mX - ALPH_BAR_X) / (double)(ALPH_BAR_W - 1);
			Type_Alpha = MAX_RGBA * barfract;
			SDL_SetTextureAlphaMod(Type_Tileset, Type_Alpha);
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active collision.
	// Changes the active collision to previous or next collision index.
	if (mY >= DISP_COLL_Y && mY < DISP_COLL_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_COLL_X - TILE_SIZE && mX < DISP_COLL_X)
		{
				if (Current_Coll != 0) Current_Coll -= 1;
				else Current_Coll = SOLID_A_ML_BR;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_COLL_X + TILE_SIZE && mX < DISP_COLL_X + (TILE_SIZE * 2))
		{
				if (Current_Coll != SOLID_A_ML_BR) Current_Coll += 1;
				else Current_Coll = 0;
				return true;
		}
	}

	// Click on opacity bar for tile collision overlay
	if (mY >= ALPH_COLL_Y && mY < ALPH_COLL_Y + ALPH_BAR_H)
	{
		if (mX >= ALPH_BAR_X && mX < ALPH_BAR_X + ALPH_BAR_W)
		{
			double barfract = (double)(mX - ALPH_BAR_X) / (double)(ALPH_BAR_W - 1);
			Coll_Alpha = MAX_RGBA * barfract;
			SDL_SetTextureAlphaMod(Coll_Tileset, Coll_Alpha);
			return true;
		}
	}

	// Click on View overlay buttons
	if (mX >= VIEWOPTS_X && mX < VIEWOPTS_X + SWITCH_SIZE)
	{
		int Yi = VIEWOPTS_Y;
		int Yf = VIEWOPTS_Y + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (View_Fore) View_Fore = false;
			else View_Fore = true;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (View_Type) View_Type = false;
			else View_Type = true;
			return true;
		}
		Yi = Yf + SYM_SPACING;
		Yf = Yi + SWITCH_SIZE;
		if (mY >= Yi && mY < Yf)
		{
			if (View_Coll) View_Coll = false;
			else View_Coll = true;
			return true;
		}
	}

	// Click on active tile attribute switches
	if (mX >= TILEOPTS_X && mX < TILEOPTS_X + SWITCH_SIZE)
	{
		int Yi = TILEOPTS_Y;
		int Yf = TILEOPTS_Y + SWITCH_SIZE;
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
