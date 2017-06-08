#include "CEditMap.h"

using namespace map_editor;

bool CEditMap::RenderMap(SDL_Renderer* renderer)
{
  // Draw the working area
	CArea::AreaControl.OnRender(renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	if (show_fg) CArea::AreaControl.OnRender(renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	if (show_ty) CArea::AreaControl.OnRenderType(renderer, Type_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	if (show_co) CArea::AreaControl.OnRenderColl(renderer, Coll_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

  return true;
}

bool CEditMap::OnRender(SDL_Renderer* renderer, SDL_Texture* interface, const int& mX, const int& mY)
{
	if (!RenderWkspc(renderer, interface, mX, mY)) return false;
  if (!RenderSidebar(renderer, interface, mX, mY)) return false;
  if (!RenderBottom(renderer, interface, mX, mY)) return false;

  return true;
}

bool CEditMap::RenderWkspc(SDL_Renderer* renderer, SDL_Texture* interface, const int& mX, const int& mY)
{
	int mapX = mX + CCamera::CameraControl.GetX();
	int mapY = mY + CCamera::CameraControl.GetY();
	int tX = -CCamera::CameraControl.GetX() + (TILE_SIZE * (mapX / TILE_SIZE));
	int tY = -CCamera::CameraControl.GetY() + (TILE_SIZE * (mapY / TILE_SIZE));
	if (mapX < 0)
	{
		tX -= TILE_SIZE;
	}
	if (mapY < 0)
	{
		tY -= TILE_SIZE;
	}

	if (intrpt ^ INTRPT_NONE)
	{
		if (intrpt & INTRPT_CH_BTILE || intrpt & INTRPT_CH_FTILE)
		{
			CChangeTile::PickTile.RenderTileset(renderer, interface, Main_Tileset, mX, mY);
		}
	}
	else
	{
		if (mX >= 0 && mX < WWIDTH && mY >= 0 && mY < WHEIGHT)
		{
			CSurface::OnDraw(renderer, interface, tX, tY, TILE_HILIGHT_X, TILE_HILIGHT_Y, TILE_SIZE, TILE_SIZE);
		}
	}
}

bool CEditMap::RenderSidebar(SDL_Renderer* renderer, SDL_Texture* interface, const int& mX, const int& mY)
{
  {
    using namespace but_tset;
    bool hl = !(bool)(intrpt);
    if (!RenderButton(renderer, interface, mX, mY, x, y, w, h, BUT_BORDER_SIZ, BLUE_X, COLOR_PURE_Y, hl))
      return false;

    // Write a button name for changing a tileset
    Font::CenterWrite(renderer, FONT_MINI, "CHANGE", x + (w / 2), y + (h / 2) - MINI_CHAR_SIZE);
    Font::CenterWrite(renderer, FONT_MINI, "TILESET", x + (w / 2), y + (h / 2) + MINI_CHAR_SIZE);
  }
  {
    using namespace disp_t;
    // Draw complete active tile with dummy entity & outline (for depth clarity)
    Font::CenterWrite(renderer, FONT_MINI, "WORKING TILE", EWIDTH - 50, bgfg_y - name_offset);
    if (!no_bg)
    {
      CSurface::OnDraw(renderer, Main_Tileset, bgfg_x, bgfg_y,
        (active_bg % tset_w) * TILE_SIZE, (active_bg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
    CSurface::OnDraw(renderer, interface, bgfg_x, bgfg_y,
      dummy_x, dummy_y, TILE_SIZE, TILE_SIZE);
    if (!no_fg)
    {
      CSurface::OnDraw(renderer, Main_Tileset, bgfg_x, bgfg_y,
        (active_fg % tset_w) * TILE_SIZE, (active_fg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
    }
    CSurface::OnDraw(renderer, interface, bgfg_x, bgfg_y,
      dummy_x, dummy_y + TILE_SIZE, TILE_SIZE, TILE_SIZE);

    // Draws active background tile
    Font::CenterWrite(renderer, FONT_MINI, "BACKGROUND", EWIDTH - 50, bg_y - name_offset);
    CSurface::OnDraw(renderer, Main_Tileset, bg_x, bg_y,
      (active_bg % tset_w) * TILE_SIZE,
      (active_bg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    // Draws background tile arrows
    CSurface::OnDraw(renderer, interface, bg_x - ((TILE_SIZE+ARR_SZ)/2),
        bg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
    CSurface::OnDraw(renderer, interface, bg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
        bg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

    // Foreground tile header & switch
    Font::CenterWrite(renderer, FONT_MINI, "FOREGROUND", EWIDTH - 50, fg_y - name_offset);

    // Draws active foreground tile
    CSurface::OnDraw(renderer, Main_Tileset, fg_x, fg_y,
      (active_fg % tset_w) * TILE_SIZE,
      (active_fg / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    // Draws foreground tile arrows
    CSurface::OnDraw(renderer, interface, fg_x - ((TILE_SIZE+ARR_SZ)/2),
        fg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
    CSurface::OnDraw(renderer, interface, fg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
        fg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

    // Draws active tile type
    CSurface::OnDraw(renderer, Type_Tileset, ty_x, ty_y,
      (active_type % type_w) * TILE_SIZE,
      (active_type / type_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    // Draws tile type arrows
    CSurface::OnDraw(renderer, interface, ty_x - ((TILE_SIZE+ARR_SZ)/2),
      ty_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
    CSurface::OnDraw(renderer, interface, ty_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
      ty_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

    // Writes out the active type
    switch (active_type)
    {
      case TILE_TYPE_NORMAL: Font::CenterWrite(renderer, FONT_MINI, "NORMAL", EWIDTH - 50, ty_y - name_offset); break;
      case TILE_TYPE_WATER: Font::CenterWrite(renderer, FONT_MINI, "WATER", EWIDTH - 50, ty_y - name_offset); break;
      case TILE_TYPE_ICE: Font::CenterWrite(renderer, FONT_MINI, "ICE", EWIDTH - 50, ty_y - name_offset); break;
      case TILE_TYPE_FIRE: Font::CenterWrite(renderer, FONT_MINI, "FIRE", EWIDTH - 50, ty_y - name_offset); break;
      default: break;
    }

    // Draws active collision tile
    CSurface::OnDraw(renderer, Coll_Tileset, co_x, co_y,
      (active_coll % coll_w) * TILE_SIZE,
      (active_coll / coll_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

    // Draws collision tile arrows
    CSurface::OnDraw(renderer, interface, co_x - ((TILE_SIZE+ARR_SZ)/2),
        co_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
    CSurface::OnDraw(renderer, interface, co_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
        co_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

    // Writes out the active collision type
    switch (active_coll)
    {
      case SOLID_NONE: Font::CenterWrite(renderer, FONT_MINI, "NONE", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_ALL: Font::CenterWrite(renderer, FONT_MINI, "FULL", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_U_BL_MR: Font::CenterWrite(renderer, FONT_MINI, "UBLMR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_U_ML_TR: Font::CenterWrite(renderer, FONT_MINI, "UMLTR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_U_TL_MR: Font::CenterWrite(renderer, FONT_MINI, "UTLMR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_U_ML_BR: Font::CenterWrite(renderer, FONT_MINI, "UMLBR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_A_BL_MR: Font::CenterWrite(renderer, FONT_MINI, "ABLMR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_A_ML_TR: Font::CenterWrite(renderer, FONT_MINI, "AMLTR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_A_TL_MR: Font::CenterWrite(renderer, FONT_MINI, "ATLMR", EWIDTH - 50, co_y - name_offset); break;
      case SOLID_A_ML_BR: Font::CenterWrite(renderer, FONT_MINI, "AMLBR", EWIDTH - 50, co_y - name_offset); break;
      default: break;
    }
  }
  {
    using namespace rm_flip;
    CSurface::OnDraw(renderer, interface, bg_x, bg_y, SWITCH_XO, no_bg ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
    CSurface::OnDraw(renderer, interface, fg_x, fg_y, SWITCH_XO, no_fg ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
  }
  {
    using namespace opac;
    // Draw an opacity meter for Type overlay
    int opacity_W = w * ((double)(type_alpha) / (double)(MAX_RGBA));
    CSurface::OnDraw(renderer, interface, x, ty_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, h);
    CSurface::OnDraw(renderer, interface, x + opacity_W, ty_y, DARKS_X, COLOR_PURE_Y, 1, 1, w - opacity_W, h);

    // Draw an opacity meter for Collision overlay
    opacity_W = w * ((double)(coll_alpha) / (double)(MAX_RGBA));
    CSurface::OnDraw(renderer, interface, x, co_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, h);
    CSurface::OnDraw(renderer, interface, x + opacity_W, co_y, DARKS_X, COLOR_PURE_Y, 1, 1, w - opacity_W, h);
  }
  return true;
}

bool CEditMap::RenderBottom(SDL_Renderer* renderer, SDL_Texture* interface, const int& mX, const int& mY)
{
  bool hl = !(bool)(intrpt);
	int colX = BLUE_X;
	{
		using namespace but_t;
		// render button for picking background tiles
		if (intrpt & INTRPT_CH_BTILE) colX = RED_X;

		if (!RenderButton(renderer, interface, mX, mY, bg_x, bg_y, bg_w, bg_h, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
			return false;
		Font::CenterWrite(renderer, FONT_MINI, "CHANGE B.TILE", bg_x + (bg_w / 2), bg_y + (bg_h / 2));

		// render button for picking foreground tiles
		if (intrpt & INTRPT_CH_FTILE) colX = RED_X;
		else colX = BLUE_X;
		if (!RenderButton(renderer, interface, mX, mY, fg_x, fg_y, fg_w, fg_h, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
			return false;
		Font::CenterWrite(renderer, FONT_MINI, "CHANGE F.TILE", fg_x + (fg_w / 2), fg_y + (fg_h / 2));
	}
	{
		using namespace view_flip;
		// Menu/Options list for viewing various overlays
		int sY = y - (SWITCH_SIZE + SYM_SPACING);
		int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
		int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
		Font::Write(renderer, FONT_MINI, "Overlay Switches", x, sY + tY_offset);
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(renderer, FONT_MINI, "Foreground", x + tX_offset, sY + tY_offset);
		if (show_fg)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(renderer, FONT_MINI, "Tile Types", x + tX_offset, sY + tY_offset);
		if (show_ty)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(renderer, FONT_MINI, "Collisions", x + tX_offset, sY + tY_offset);
		if (show_co)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
	}
	{
		using namespace place_flip;
		// Menu/Options list for active tile attributes on placement
		int sY = y;
		int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
		int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
		Font::Write(renderer, FONT_MINI, "Use B.Tile", x + tX_offset, sY + tY_offset);
		if (onTiles & ENABLE_BTILE)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(renderer, FONT_MINI, "Use F.Tile", x + tX_offset, sY + tY_offset);
		if (onTiles & ENABLE_FTILE)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(renderer, FONT_MINI, "Use Type", x + tX_offset, sY + tY_offset);
		if (onTiles & ENABLE_TYPE)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		sY += SWITCH_SIZE + SYM_SPACING;
		Font::Write(renderer, FONT_MINI, "Use Collision", x + tX_offset, sY + tY_offset);
		if (onTiles & ENABLE_COLL)
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
		else
		{
			CSurface::OnDraw(renderer, interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
		}
	}
  return true;
}

bool CEditMap::RenderButton(SDL_Renderer* renderer, SDL_Texture* interface, const int& mX, const int& mY,
  int X, int Y, int W, int H, int bsiz, int colX, int colY, bool hl)
{
	bool but_glow = false;
  if (hl)
  {
    if (mX >= X && mX < X + W)
  	{
  		if (mY >= Y && mY < Y + H)
  		{
  			but_glow = true;
  		}
  	}
  }

	if (!CSurface::OnDraw(renderer, interface, X, Y, DARKS_X, COLOR_PURE_Y, 1, 1, W, H))
		return false;
	if (!CSurface::OnDraw(renderer, interface, X + bsiz, Y + bsiz, colX, colY - but_glow, 1, 1, W - (bsiz * 2), H - (bsiz * 2)))
		return false;

	return true;
}


bool CEditMap::RenderButton(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Point* cursor, SDL_Rect* button, int bsiz, int colX, int colY, bool hl)
{
	bool but_glow = false;
  if (hl)
  {
    if (cursor->x >= button->x && cursor->x < button->x + button->w)
  	{
  		if (cursor->y >= button->y && cursor->y < button->y + button->h)
  		{
  			but_glow = true;
  		}
  	}
  }

	SDL_Rect srcR;
	srcR.x = DARKS_X;
	srcR.y = COLOR_PURE_Y;
	srcR.w = srcR.h = 1;
	if (!CSurface::OnDraw(renderer, interface, &srcR, button))
		return false;

	// if (!CSurface::OnDraw(renderer, interface, X, Y, DARKS_X, COLOR_PURE_Y, 1, 1, W, H))
	// 	return false;
	// if (!CSurface::OnDraw(renderer, interface, X + bsiz, Y + bsiz, colX, colY - but_glow, 1, 1, W - (bsiz * 2), H - (bsiz * 2)))
	// 	return false;

	return true;
}
