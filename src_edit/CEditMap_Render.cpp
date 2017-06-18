#include "CEditMap.h"

bool CEditMap::RenderMap()
{
  // Draw the working area
	CArea::AreaControl.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	if (show_fg) CArea::AreaControl.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	if (show_ty) CArea::AreaControl.OnRenderType(Type_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	if (show_co) CArea::AreaControl.OnRenderColl(Coll_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

  return true;
}

bool CEditMap::OnRender(SDL_Texture* interface, const SDL_Point* mouse)
{
	if (!RenderWkspc(interface, mouse)) return false;
	CSurface::OnDraw(interface, WWIDTH, 0, WWIDTH, 0, EWIDTH - WWIDTH, EHEIGHT);
	CSurface::OnDraw(interface, 0, WHEIGHT, 0, WHEIGHT, EWIDTH, EHEIGHT - WHEIGHT);
  if (!RenderSidebar(interface, mouse)) return false;
  if (!RenderBottom(interface, mouse)) return false;

  return true;
}

bool CEditMap::RenderWkspc(SDL_Texture* interface, const SDL_Point* mouse)
{
	SDL_Point mapPos = CCamera::CameraControl.GetCamRelPoint(mouse);

  if (!drawTileShadow(mouse, &mapPos)) return false;
	if (!drawPlaceDomain(mouse, &mapPos)) return false;
	if (!drawIntrpt(interface, mouse)) return false;

	return true;
}

bool CEditMap::drawIntrpt(SDL_Texture* interface, const SDL_Point* mouse)
{
	if (intrpt ^ INTRPT_NONE)
	{
		if (intrpt & INTRPT_CHANGE_BG || intrpt & INTRPT_CHANGE_FG)
		{
			CChangeTile::PickTile.RenderTileset(interface, Main_Tileset, mouse->x, mouse->y);
		}
	}
	return true;
}

bool CEditMap::drawTileShadow(const SDL_Point* mouse, const SDL_Point* mapPos)
{
	if (intrpt ^ INTRPT_NONE) return true;

	int tX = -CCamera::CameraControl.GetX() + (TILE_SIZE * (mapPos->x / TILE_SIZE));
	int tY = -CCamera::CameraControl.GetY() + (TILE_SIZE * (mapPos->y / TILE_SIZE));
	if (mapPos->x < 0)	tX -= TILE_SIZE;
	if (mapPos->y < 0)	tY -= TILE_SIZE;

	if (CAsset::inWorkspace(mouse))
	{
		SDL_Rect dstR = {0, 0, TILE_SIZE, TILE_SIZE};
		if (active_TL)
		{
			dstR.x = tX;
			dstR.y = tY;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
		if (active_BL)
		{
			dstR.x = tX;
			dstR.y = tY + TILE_SIZE;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
		if (active_TR)
		{
			dstR.x = tX + TILE_SIZE;
			dstR.y = tY;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
		if (active_BR)
		{
			dstR.x = tX + TILE_SIZE;
			dstR.y = tY + TILE_SIZE;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
	}
	return true;
}

bool CEditMap::drawPlaceDomain(const SDL_Point* mouse, const SDL_Point* mapPos)
{
	if (intrpt ^ INTRPT_NONE) return true;

	if (rClickA != NULL)
	{
		if (rClickB == NULL)
		{
			SDL_Rect box = getTileDomain(rClickA, mapPos);
			CCamera::CameraControl.MakeWinRel(box.x, box.y);
			if (!CAsset::drawBox(&box, flexAreaColor, rc_area_w)) return false;
		}
		else
		{
			SDL_Rect box = getTileDomain(rClickA, rClickB);
			CCamera::CameraControl.MakeWinRel(box.x, box.y);
			const SDL_Point* color = SDL_PointInRect(mouse, &box) ? hoverAreaColor : fixAreaColor;
			if (!CAsset::drawBox(&box, color, rc_area_w)) return false;
		}
	}
	return true;
}

bool CEditMap::RenderSidebar(SDL_Texture* interface, const SDL_Point* mouse)
{
	CTile* ShowTile;
	switch (modifyTile)
	{
		case MODIFY_TILE_TL: 	ShowTile = &TileTL; break;
		case MODIFY_TILE_TR: 	ShowTile = &TileTR; break;
		case MODIFY_TILE_BL: 	ShowTile = &TileBL; break;
		case MODIFY_TILE_BR: 	ShowTile = &TileBR; break;
		default: 							ShowTile = &TileTL; break;
	}

	if (!drawButtonTileset(interface, mouse)) return false;
  if (!drawActiveTiles(interface)) return false;
  if (!drawActive_bg(interface, ShowTile)) return false;
  if (!drawActive_fg(interface, ShowTile)) return false;
  if (!drawActive_ty(interface, ShowTile)) return false;
  if (!drawActive_co(interface, ShowTile)) return false;
  if (!drawOpac_ty(interface)) return false;
  if (!drawOpac_co(interface)) return false;

  return true;
}

bool CEditMap::RenderBottom(SDL_Texture* interface, const SDL_Point* mouse)
{
	bool activeTile = false;
	switch (modifyTile)
	{
		case MODIFY_TILE_TL: activeTile = active_TL; break;
		case MODIFY_TILE_TR: activeTile = active_TR; break;
		case MODIFY_TILE_BL: activeTile = active_BL; break;
		case MODIFY_TILE_BR: activeTile = active_BR; break;
		default: break;
	}

	if (!drawButton_bg(interface, mouse)) return false;
  if (!drawButton_fg(interface, mouse)) return false;
	if (!drawButtonActive(interface, mouse, activeTile)) return false;
	if (!drawQuadrants(interface, mouse)) return false;
  if (!drawOverlayList(interface)) return false;
  if (!drawPlacementList(interface)) return false;

  return true;
}

bool CEditMap::drawButtonTileset(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace but_tset;

	// const SDL_Rect dstrect = CAsset::getRect(x, y, w, h);
	const SDL_Point* color = SDL_PointInRect(mouse, &button) ? hoverColor : offCol;
	if (!CAsset::drawButton(&button, bsiz, color)) return false;

	// Write a button name for changing a tileset
	Font::CenterWrite(FONT_MINI, "CHANGE", button.x + (button.w / 2), button.y + (button.h / 2) - MINI_CHAR_SIZE);
	Font::CenterWrite(FONT_MINI, "TILESET", button.x + (button.w / 2), button.y + (button.h / 2) + MINI_CHAR_SIZE);

	return true;
}

bool CEditMap::drawActiveTiles(SDL_Texture* interface)
{
	// Draw complete active tile with dummy entity & outline (for depth clarity)
	using namespace disp_t;

	SDL_Rect srcR = {0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstR = {0, 0, TILE_SIZE, TILE_SIZE};

	Font::CenterWrite(FONT_MINI, "SAMPLE", EWIDTH - 50, sample_y - name_offset);

	if (active_TL)
	{
		dstR.x = sample_x;
		dstR.y = sample_y;
		drawSampleTile(interface, &TileTL, &dstR);
	}
	if (active_TR)
	{
		dstR.x = sample_x + TILE_SIZE;
		dstR.y = sample_y;
		drawSampleTile(interface, &TileTR, &dstR);
	}
	if (active_BL)
	{
		dstR.x = sample_x;
		dstR.y = sample_y + TILE_SIZE;
		drawSampleTile(interface, &TileBL, &dstR);
	}
	if (active_BR)
	{
		dstR.x = sample_x + TILE_SIZE;
		dstR.y = sample_y + TILE_SIZE;
		drawSampleTile(interface, &TileBR, &dstR);
	}

	return true;
}

bool CEditMap::drawSampleTile(SDL_Texture* interface, CTile* ShowTile, const SDL_Rect* dstR)
{
	if (interface == NULL || ShowTile == NULL || dstR == NULL) return false;

	using namespace disp_t;

	SDL_Rect srcR = {0, 0, TILE_SIZE, TILE_SIZE};

	srcR.x = (ShowTile->bg_ID % tset_w) * TILE_SIZE;
	srcR.y = (ShowTile->bg_ID / tset_w) * TILE_SIZE;
	CSurface::OnDraw(Main_Tileset, &srcR, dstR);
	CSurface::OnDraw(interface, &dummyEntity, dstR);

	srcR.x = (ShowTile->fg_ID % tset_w) * TILE_SIZE;
	srcR.y = (ShowTile->fg_ID / tset_w) * TILE_SIZE;
	CSurface::OnDraw(Main_Tileset, &srcR, dstR);
	CSurface::OnDraw(interface, &dummyOutline, dstR);

	return true;
}

bool CEditMap::drawActive_bg(SDL_Texture* interface, CTile* ShowTile)
{
	using namespace disp_t;

	// Draws active background tile
	Font::CenterWrite(FONT_MINI, "BACKGROUND", EWIDTH - 50, bg_y - name_offset);

	CSurface::OnDraw(Main_Tileset, bg_x, bg_y,
		(ShowTile->bg_ID % tset_w) * TILE_SIZE,
		(ShowTile->bg_ID / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws background tile arrows
	CSurface::OnDraw(interface, bg_x - ((TILE_SIZE+ARR_SZ)/2),
			bg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, bg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			bg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

  CSurface::OnDraw(interface, but_rm::bg_x, but_rm::bg_y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_fg(SDL_Texture* interface, CTile* ShowTile)
{
	using namespace disp_t;

	// Foreground tile header
	Font::CenterWrite(FONT_MINI, "FOREGROUND", EWIDTH - 50, fg_y - name_offset);

	// Draws active foreground tile
	CSurface::OnDraw(Main_Tileset, fg_x, fg_y,
		(ShowTile->fg_ID % tset_w) * TILE_SIZE,
		(ShowTile->fg_ID / tset_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws foreground tile arrows
	CSurface::OnDraw(interface, fg_x - ((TILE_SIZE+ARR_SZ)/2),
			fg_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, fg_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			fg_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

  CSurface::OnDraw(interface, but_rm::fg_x, but_rm::fg_y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_ty(SDL_Texture* interface, CTile* ShowTile)
{
	using namespace disp_t;

	// Draws active tile type
	CSurface::OnDraw(Type_Tileset, ty_x, ty_y,
		(ShowTile->TypeID % type_w) * TILE_SIZE,
		(ShowTile->TypeID / type_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile type arrows
	CSurface::OnDraw(interface, ty_x - ((TILE_SIZE+ARR_SZ)/2),
		ty_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, ty_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
		ty_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

	// Writes out the active type
	switch (ShowTile->TypeID)
	{
		case TILE_TYPE_NORMAL: Font::CenterWrite(FONT_MINI, "NORMAL", EWIDTH - 50, ty_y - name_offset); break;
		case TILE_TYPE_WATER: Font::CenterWrite(FONT_MINI, "WATER", EWIDTH - 50, ty_y - name_offset); break;
		case TILE_TYPE_ICE: Font::CenterWrite(FONT_MINI, "ICE", EWIDTH - 50, ty_y - name_offset); break;
		case TILE_TYPE_FIRE: Font::CenterWrite(FONT_MINI, "FIRE", EWIDTH - 50, ty_y - name_offset); break;
		default: break;
	}

	return true;
}

bool CEditMap::drawActive_co(SDL_Texture* interface, CTile* ShowTile)
{
	using namespace disp_t;

	// Draws active collision tile
	CSurface::OnDraw(Coll_Tileset, co_x, co_y,
		(ShowTile->CollID % coll_w) * TILE_SIZE,
		(ShowTile->CollID / coll_w) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws collision tile arrows
	CSurface::OnDraw(interface, co_x - ((TILE_SIZE+ARR_SZ)/2),
			co_y + ((TILE_SIZE-ARR_SZ)/2), L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	CSurface::OnDraw(interface, co_x + TILE_SIZE + ((TILE_SIZE-ARR_SZ)/2),
			co_y + ((TILE_SIZE-ARR_SZ)/2), R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

	// Writes out the active collision type
	switch (ShowTile->CollID)
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

bool CEditMap::drawButton_bg(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace but_t;

	const SDL_Point* color = NULL;

	if (!(bool)(intrpt))
	{
		color = SDL_PointInRect(mouse, &bg_button) ? hoverColor : offCol;
	}
	else
	{
		color = (intrpt & INTRPT_CHANGE_BG) ? onCol : offCol;
	}

	if (!CAsset::drawButton(&bg_button, bsiz, color)) return false;

	Font::CenterWrite(FONT_MINI, "CHANGE B.TILE", bg_button.x + (bg_button.w / 2), bg_button.y + (bg_button.h / 2));

	return true;
}

bool CEditMap::drawButton_fg(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace but_t;

	const SDL_Point* color = NULL;

	if (!(bool)(intrpt))
	{
		color = SDL_PointInRect(mouse, &fg_button) ? hoverColor : offCol;
	}
	else
	{
		color = (intrpt & INTRPT_CHANGE_FG) ? onCol : offCol;
	}

	if (!CAsset::drawButton(&fg_button, bsiz, color)) return false;

	Font::CenterWrite(FONT_MINI, "CHANGE F.TILE", fg_button.x + (fg_button.w / 2), fg_button.y + (fg_button.h / 2));

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

bool CEditMap::drawButtonActive(SDL_Texture* interface, const SDL_Point* mouse, bool active)
{
	using namespace but_act_t;

	const char* name = active ? onTitle : offTitle;

	const SDL_Point* color = NULL;
	if ((bool)(intrpt) || !SDL_PointInRect(mouse, &button))
	{
		color = active ? onCol : offCol;
	}
	else
	{
		color = active ? onhvCol : offhvCol;
	}

	if (!CAsset::drawButton(&button, bsiz, color)) return false;
	Font::CenterWrite(FONT_MINI, name, button.x + (button.w / 2), button.y + (button.h / 2));

	return true;
}

bool CEditMap::drawQuadrants(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace but_quad_t;

	bool canHilight = !(bool)(intrpt);
	bool noHov;
	const SDL_Point* color = NULL;
	SDL_Rect dstrect;



	dstrect = CAsset::getRect(left_x, top_y, w, h);
	if (modifyTile != MODIFY_TILE_TL)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_TL ? onCol : offCol) : (active_TL ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}

	if (!CAsset::drawButton(&dstrect, bsiz, color)) return false;
	Font::CenterWrite(FONT_MINI, name_TL, left_x + (w / 2), top_y + (h / 2));



	dstrect.x = right_x;
	if (modifyTile != MODIFY_TILE_TR)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_TR ? onCol : offCol) : (active_TR ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}
	if (!CAsset::drawButton(&dstrect, bsiz, color)) return false;
	Font::CenterWrite(FONT_MINI, name_TR, right_x + (w / 2), top_y + (h / 2));



	dstrect.y = bottom_y;
	if (modifyTile != MODIFY_TILE_BR)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_BR ? onCol : offCol) : (active_BR ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}
	if (!CAsset::drawButton(&dstrect, bsiz, color)) return false;
	Font::CenterWrite(FONT_MINI, name_BR, right_x + (w / 2), bottom_y + (h / 2));



	dstrect.x = left_x;
	if (modifyTile != MODIFY_TILE_BL)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_BL ? onCol : offCol) : (active_BL ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}
	if (!CAsset::drawButton(&dstrect, bsiz, color)) return false;
	Font::CenterWrite(FONT_MINI, name_BL, left_x + (w / 2), bottom_y + (h / 2));

	return true;
}
