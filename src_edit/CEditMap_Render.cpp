#include "CEditMap.h"

using namespace map_editor;

bool CEditMap::RenderMap()
{
  // Draw the working area
	CArea::AreaControl.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	if (show_fg) CArea::AreaControl.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	if (show_ty) CArea::AreaControl.OnRenderType(Type_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	if (show_co) CArea::AreaControl.OnRenderColl(Coll_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

  return true;
}

bool CEditMap::OnRender(SDL_Texture* interface, SDL_Point* mouse)
{
	if (!RenderWkspc(interface, mouse)) return false;
  if (!RenderSidebar(interface, mouse)) return false;
  if (!RenderBottom(interface, mouse)) return false;

  return true;
}

bool CEditMap::RenderWkspc(SDL_Texture* interface, SDL_Point* mouse)
{
	int mapX = mouse->x + CCamera::CameraControl.GetX();
	int mapY = mouse->y + CCamera::CameraControl.GetY();
	int tX = -CCamera::CameraControl.GetX() + (TILE_SIZE * (mapX / TILE_SIZE));
	int tY = -CCamera::CameraControl.GetY() + (TILE_SIZE * (mapY / TILE_SIZE));
	if (mapX < 0)	tX -= TILE_SIZE;
	if (mapY < 0)	tY -= TILE_SIZE;

	if (intrpt ^ INTRPT_NONE)
	{
		if (intrpt & INTRPT_CH_BTILE || intrpt & INTRPT_CH_FTILE)
		{
			CChangeTile::PickTile.RenderTileset(interface, Main_Tileset, mouse->x, mouse->y);
		}
	}
	else
	{
		if (mouse->x >= 0 && mouse->x < WWIDTH && mouse->y >= 0 && mouse->y < WHEIGHT)
		{
			CSurface::OnDraw(interface, tX, tY, TILE_HILIGHT_X, TILE_HILIGHT_Y, TILE_SIZE, TILE_SIZE);
		}
	}
	return true;
}

bool CEditMap::RenderSidebar(SDL_Texture* interface, SDL_Point* mouse)
{
	if (!drawButtonSet(interface, mouse)) return false;
  if (!drawActiveTile(interface)) return false;
  if (!drawActive_bg(interface)) return false;
  if (!drawActive_fg(interface)) return false;
  if (!drawActive_ty(interface)) return false;
  if (!drawActive_co(interface)) return false;
  if (!drawOpac_ty(interface)) return false;
  if (!drawOpac_co(interface)) return false;

  return true;
}

bool CEditMap::RenderBottom(SDL_Texture* interface, SDL_Point* mouse)
{
	if (!drawButton_bg(interface, mouse)) return false;
  if (!drawButton_fg(interface, mouse)) return false;
  if (!drawOverlayList(interface)) return false;
  if (!drawPlacementList(interface)) return false;

  return true;
}


bool CEditMap::RenderButton(SDL_Texture* interface, SDL_Point* mouse, SDL_Rect* button, int bsiz, int colX, int colY, bool hl)
{
	bool but_glow = false;
  if (hl)
  {
    if (mouse->x >= button->x && mouse->x < button->x + button->w)
  	{
  		if (mouse->y >= button->y && mouse->y < button->y + button->h)
  		{
  			but_glow = true;
  		}
  	}
  }

	SDL_Rect srcR = CSurface::getRect(DARKS_X, COLOR_PURE_Y, 1, 1);
	if (!CSurface::OnDraw(interface, &srcR, button))
		return false;

	srcR.x = colX;
	srcR.y = colY - but_glow;
	SDL_Rect dstR = CSurface::getRect(button->x + bsiz, button->y + bsiz, button->w - (bsiz * 2), button->h - (bsiz * 2));
	if (!CSurface::OnDraw(interface, &srcR, &dstR)) return false;


	return true;
}

bool CEditMap::drawButtonSet(SDL_Texture* interface, SDL_Point* mouse)
{
	using namespace but_tset;
	bool hl = !(bool)(intrpt);

	SDL_Rect dstrect = CSurface::getRect(x, y, w, h);
	if (!RenderButton(interface, mouse, &dstrect, BUT_BORDER_SIZ, BLUE_X, COLOR_PURE_Y, hl))
		return false;

	// Write a button name for changing a tileset
	Font::CenterWrite(FONT_MINI, "CHANGE", x + (w / 2), y + (h / 2) - MINI_CHAR_SIZE);
	Font::CenterWrite(FONT_MINI, "TILESET", x + (w / 2), y + (h / 2) + MINI_CHAR_SIZE);

	return true;
}

bool CEditMap::drawActiveTile(SDL_Texture* interface)
{
	// Draw complete active tile with dummy entity & outline (for depth clarity)
	using namespace disp_t;
	Font::CenterWrite(FONT_MINI, "WORKING TILE", EWIDTH - 50, bgfg_y - name_offset);
	if (!no_bg)
	{
		CSurface::OnDraw(Main_Tileset, bgfg_x, bgfg_y, (ActiveTileTL.bg_ID % tset_w) * TILE_SIZE, (ActiveTileTL.bg_ID / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	CSurface::OnDraw(interface, bgfg_x, bgfg_y, dummy_x, dummy_y, TILE_SIZE, TILE_SIZE);
	if (!no_fg)
	{
		CSurface::OnDraw(Main_Tileset, bgfg_x, bgfg_y, (ActiveTileTL.fg_ID % tset_w) * TILE_SIZE, (ActiveTileTL.fg_ID / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}
	CSurface::OnDraw(interface, bgfg_x, bgfg_y, dummy_x, dummy_y + TILE_SIZE, TILE_SIZE, TILE_SIZE);

	return true;
}

bool CEditMap::drawActive_bg(SDL_Texture* interface)
{
	using namespace disp_t;

	// Draws active background tile
	Font::CenterWrite(FONT_MINI, "BACKGROUND", EWIDTH - 50, bg_y - name_offset);

	CSurface::OnDraw(Main_Tileset, bg_x, bg_y,
		(ActiveTileTL.bg_ID % tset_w) * TILE_SIZE,
		(ActiveTileTL.bg_ID / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws background tile arrows
	CSurface::OnDraw(interface, bg_x - ((TILE_SIZE+ARR_SZ)/2),
			bg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, bg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			bg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

  CSurface::OnDraw(interface, rm_flip::bg_x, rm_flip::bg_y, SWITCH_XO, no_bg ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_fg(SDL_Texture* interface)
{
	using namespace disp_t;

	// Foreground tile header
	Font::CenterWrite(FONT_MINI, "FOREGROUND", EWIDTH - 50, fg_y - name_offset);

	// Draws active foreground tile
	CSurface::OnDraw(Main_Tileset, fg_x, fg_y,
		(ActiveTileTL.fg_ID % tset_w) * TILE_SIZE,
		(ActiveTileTL.fg_ID / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws foreground tile arrows
	CSurface::OnDraw(interface, fg_x - ((TILE_SIZE+ARR_SZ)/2),
			fg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, fg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			fg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

  CSurface::OnDraw(interface, rm_flip::fg_x, rm_flip::fg_y, SWITCH_XO, no_fg ? OFF_SWITCH_YO : ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_ty(SDL_Texture* interface)
{
	using namespace disp_t;

	// Draws active tile type
	CSurface::OnDraw(Type_Tileset, ty_x, ty_y,
		(ActiveTileTL.TypeID % type_w) * TILE_SIZE,
		(ActiveTileTL.TypeID / type_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile type arrows
	CSurface::OnDraw(interface, ty_x - ((TILE_SIZE+ARR_SZ)/2),
		ty_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, ty_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
		ty_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

	// Writes out the active type
	switch (ActiveTileTL.TypeID)
	{
		case TILE_TYPE_NORMAL: Font::CenterWrite(FONT_MINI, "NORMAL", EWIDTH - 50, ty_y - name_offset); break;
		case TILE_TYPE_WATER: Font::CenterWrite(FONT_MINI, "WATER", EWIDTH - 50, ty_y - name_offset); break;
		case TILE_TYPE_ICE: Font::CenterWrite(FONT_MINI, "ICE", EWIDTH - 50, ty_y - name_offset); break;
		case TILE_TYPE_FIRE: Font::CenterWrite(FONT_MINI, "FIRE", EWIDTH - 50, ty_y - name_offset); break;
		default: break;
	}

	return true;
}

bool CEditMap::drawActive_co(SDL_Texture* interface)
{
	using namespace disp_t;

	// Draws active collision tile
	CSurface::OnDraw(Coll_Tileset, co_x, co_y,
		(ActiveTileTL.CollID % coll_w) * TILE_SIZE,
		(ActiveTileTL.CollID / coll_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws collision tile arrows
	CSurface::OnDraw(interface, co_x - ((TILE_SIZE+ARR_SZ)/2),
			co_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, co_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			co_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

	// Writes out the active collision type
	switch (ActiveTileTL.CollID)
	{
		case SOLID_NONE: Font::CenterWrite(FONT_MINI, "NONE", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_ALL: Font::CenterWrite(FONT_MINI, "FULL", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_U_BL_MR: Font::CenterWrite(FONT_MINI, "UBLMR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_U_ML_TR: Font::CenterWrite(FONT_MINI, "UMLTR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_U_TL_MR: Font::CenterWrite(FONT_MINI, "UTLMR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_U_ML_BR: Font::CenterWrite(FONT_MINI, "UMLBR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_A_BL_MR: Font::CenterWrite(FONT_MINI, "ABLMR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_A_ML_TR: Font::CenterWrite(FONT_MINI, "AMLTR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_A_TL_MR: Font::CenterWrite(FONT_MINI, "ATLMR", EWIDTH - 50, co_y - name_offset); break;
		case SOLID_A_ML_BR: Font::CenterWrite(FONT_MINI, "AMLBR", EWIDTH - 50, co_y - name_offset); break;
		default: break;
	}

	return true;
}

bool CEditMap::drawOpac_ty(SDL_Texture* interface)
{
	using namespace opac;
	// Draw an opacity meter for Type overlay
	int opacity_W = w * ((double)(type_alpha) / (double)(MAX_RGBA));
	CSurface::OnDraw(interface, x, ty_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, h);
	CSurface::OnDraw(interface, x + opacity_W, ty_y, DARKS_X, COLOR_PURE_Y, 1, 1, w - opacity_W, h);

	return true;
}

bool CEditMap::drawOpac_co(SDL_Texture* interface)
{
	using namespace opac;
	// Draw an opacity meter for Collision overlay
	int opacity_W = w * ((double)(coll_alpha) / (double)(MAX_RGBA));
	CSurface::OnDraw(interface, x, co_y, YELLOW_X, COLOR_PURE_Y, 1, 1, opacity_W, h);
	CSurface::OnDraw(interface, x + opacity_W, co_y, DARKS_X, COLOR_PURE_Y, 1, 1, w - opacity_W, h);

	return true;
}

bool CEditMap::drawButton_bg(SDL_Texture* interface, SDL_Point* mouse)
{
	using namespace but_t;

	bool hl = !(bool)(intrpt);
	int colX = BLUE_X;

	// render button for picking background tiles
	if (intrpt & INTRPT_CH_BTILE) colX = RED_X;

	SDL_Rect dstrect = CSurface::getRect(bg_x, bg_y, bg_w, bg_h);
	if (!RenderButton(interface, mouse, &dstrect, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
		return false;
	Font::CenterWrite(FONT_MINI, "CHANGE B.TILE", bg_x + (bg_w / 2), bg_y + (bg_h / 2));

	return true;
}

bool CEditMap::drawButton_fg(SDL_Texture* interface, SDL_Point* mouse)
{
	using namespace but_t;

	bool hl = !(bool)(intrpt);
	int colX = BLUE_X;

	// render button for picking foreground tiles
	if (intrpt & INTRPT_CH_FTILE) colX = RED_X;
	else colX = BLUE_X;

	SDL_Rect dstrect = CSurface::getRect(fg_x, fg_y, fg_w, fg_h);
	if (!RenderButton(interface, mouse, &dstrect, BUT_BORDER_SIZ, colX, COLOR_PURE_Y, hl))
		return false;
	Font::CenterWrite(FONT_MINI, "CHANGE F.TILE", fg_x + (fg_w / 2), fg_y + (fg_h / 2));

	return true;
}

bool CEditMap::drawOverlayList(SDL_Texture* interface)
{
	using namespace view_flip;

	// Menu/Options list for viewing various overlays
	int sY = y - (SWITCH_SIZE + SYM_SPACING);
	int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
	int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
	Font::Write(FONT_MINI, "Overlay Switches", x, sY + tY_offset);
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(FONT_MINI, "Foreground", x + tX_offset, sY + tY_offset);
	if (show_fg)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(FONT_MINI, "Tile Types", x + tX_offset, sY + tY_offset);
	if (show_ty)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(FONT_MINI, "Collisions", x + tX_offset, sY + tY_offset);
	if (show_co)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}

	return true;
}

bool CEditMap::drawPlacementList(SDL_Texture* interface)
{
	using namespace place_flip;

	// Menu/Options list for active tile attributes on placement
	int sY = y;
	int tY_offset = (SWITCH_SIZE - MINI_CHAR_SIZE) / 2;
	int tX_offset = SWITCH_SIZE + MINI_CHAR_SIZE;
	Font::Write(FONT_MINI, "Use B.Tile", x + tX_offset, sY + tY_offset);
	if (onTiles & ENABLE_BG)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(FONT_MINI, "Use F.Tile", x + tX_offset, sY + tY_offset);
	if (onTiles & ENABLE_FG)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(FONT_MINI, "Use Type", x + tX_offset, sY + tY_offset);
	if (onTiles & ENABLE_TYPE)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	sY += SWITCH_SIZE + SYM_SPACING;
	Font::Write(FONT_MINI, "Use Collision", x + tX_offset, sY + tY_offset);
	if (onTiles & ENABLE_COLL)
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}
	else
	{
		CSurface::OnDraw(interface, x, sY, SWITCH_XO,	OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	}

	return true;
}
