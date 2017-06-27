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
	if (!CInterrupt::isNone())
	{
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_BG) || CInterrupt::isFlagOn(INTRPT_CHANGE_FG))
		{
			if (!CChangeTile::PickTile.OnRender(interface, Tileset, mouse)) return false;
		}
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_TS))
		{
			if (!CTileset::PickTS.OnRender()) return false;
		}
	}
	return true;
}

bool CEditMap::drawTileShadow(const SDL_Point* mouse, const SDL_Point* mapPos)
{
	if (!CInterrupt::isNone()) return true;

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
	// if (intrpt ^ INTRPT_NONE) return true;
	if (!CInterrupt::isNone()) return true;

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
	CTile* ShowTile = getModTile();

	if (!drawButtonTileset(interface, mouse)) return false;
  if (!drawActiveTiles(interface)) return false;
  if (!drawActive_bg(ShowTile, mouse)) return false;
  if (!drawActive_fg(ShowTile, mouse)) return false;
  if (!drawActive_ty(ShowTile, mouse)) return false;
  if (!drawActive_co(ShowTile, mouse)) return false;
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
	using namespace mapEngine::but_tset;

	// const SDL_Rect dstrect = CAsset::getRect(x, y, w, h);
	const SDL_Point* color = SDL_PointInRect(mouse, &button) ? hoverColor : offCol;
	if (!CAsset::drawStrBox(&button, bsiz, color)) return false;

	// Write a button name for changing a tileset
	Font::NewCenterWrite(FONT_MINI, "CHANGE TILESET", &button);

	return true;
}

bool CEditMap::drawActiveTiles(SDL_Texture* interface)
{
	// Draw complete active tile with dummy entity & outline (for depth clarity)
	using namespace mapEngine::disp_t;

	SDL_Rect srcR = CAsset::getRect(0, 0, TILE_SIZE, TILE_SIZE);
	SDL_Rect dstR = CAsset::getRect(0, 0, TILE_SIZE, TILE_SIZE);
	SDL_Point tpos = CAsset::getPos(EWIDTH - 50, sample_y - name_offset);
	Font::NewCenterWrite(FONT_MINI, "SAMPLE", &tpos);

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

	using namespace mapEngine::disp_t;

	SDL_Rect srcR = {0, 0, TILE_SIZE, TILE_SIZE};

	srcR.x = (ShowTile->bg_ID % tset_w) * TILE_SIZE;
	srcR.y = (ShowTile->bg_ID / tset_w) * TILE_SIZE;
	CSurface::OnDraw(Tileset, &srcR, dstR);
	CSurface::OnDraw(interface, &dummyEntity, dstR);

	srcR.x = (ShowTile->fg_ID % tset_w) * TILE_SIZE;
	srcR.y = (ShowTile->fg_ID / tset_w) * TILE_SIZE;
	CSurface::OnDraw(Tileset, &srcR, dstR);
	CSurface::OnDraw(interface, &dummyOutline, dstR);

	return true;
}

bool CEditMap::drawActive_bg(CTile* ShowTile, const SDL_Point* mouse)
{
	using namespace mapEngine::disp_t;

	SDL_Point tpos = CAsset::getPos(EWIDTH - 50, bg_y - name_offset);

	Font::NewCenterWrite(FONT_MINI, "BACKGROUND", &tpos);

	// Draws active background tile
	{
		int tX = (ShowTile->bg_ID % tset_w) * TILE_SIZE;
		int tY = (ShowTile->bg_ID / tset_w) * TILE_SIZE;
		SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
		CSurface::OnDraw(Tileset, &srcR, &bg_pos);
	}

	// Draws background tile arrows
	drawTileArrows(&bg_pos, mouse);

  // CSurface::OnDraw(interface, mapEngine::but_rm::bg_x, mapEngine::but_rm::bg_y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_fg(CTile* ShowTile, const SDL_Point* mouse)
{
	using namespace mapEngine::disp_t;

	SDL_Point tpos = CAsset::getPos(EWIDTH - 50, fg_y - name_offset);

	// Foreground tile header
	Font::NewCenterWrite(FONT_MINI, "FOREGROUND", &tpos);

	// Draws active foreground tile
	{
		int tX = (ShowTile->fg_ID % tset_w) * TILE_SIZE;
		int tY = (ShowTile->fg_ID / tset_w) * TILE_SIZE;
		SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
		CSurface::OnDraw(Tileset, &srcR, &fg_pos);
	}

	// Draws foreground tile arrows
	drawTileArrows(&fg_pos, mouse);

  // CSurface::OnDraw(interface, mapEngine::but_rm::fg_x, mapEngine::but_rm::fg_y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_ty(CTile* ShowTile, const SDL_Point* mouse)
{
	using namespace mapEngine::disp_t;

	// Draws active tile type
	{
		int tX = (ShowTile->TypeID % type_w) * TILE_SIZE;
		int tY = (ShowTile->TypeID / type_w) * TILE_SIZE;
		SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
		CSurface::OnDraw(Type_Tileset, &srcR, &ty_pos);
	}

	// Draws tile type arrows
	drawTileArrows(&ty_pos, mouse);

	std::string tName;

	// Writes out the active type
	switch (ShowTile->TypeID)
	{
		case TILE_TYPE_NORMAL: 	tName = "NORMAL"; break;
		case TILE_TYPE_WATER: 	tName = "WATER"; break;
		case TILE_TYPE_ICE: 		tName = "ICE"; break;
		case TILE_TYPE_FIRE: 		tName = "FIRE"; break;
		default: break;
	}

	SDL_Point tpos = CAsset::getPos(EWIDTH - 50, ty_y - name_offset);
	Font::NewCenterWrite(FONT_MINI, tName.c_str(), &tpos);

	return true;
}

bool CEditMap::drawActive_co(CTile* ShowTile, const SDL_Point* mouse)
{
	using namespace mapEngine::disp_t;

	{
		// Draws active collision tile
		int tX = (ShowTile->CollID % coll_w) * TILE_SIZE;
		int tY = (ShowTile->CollID / coll_w) * TILE_SIZE;
		SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
		CSurface::OnDraw(Coll_Tileset, &srcR, &co_pos);
	}

	// Draws collision tile arrows
	drawTileArrows(&co_pos, mouse);

	std::string tName;

	// Writes out the active collision type
	switch (ShowTile->CollID)
	{
		case SOLID_NONE: 		tName = "NONE"; break;
		case SOLID_ALL: 		tName = "FULL"; break;
		case SOLID_U_BL_MR: tName = "U-BL-MR"; break;
		case SOLID_U_ML_TR: tName = "U-ML-TR"; break;
		case SOLID_U_TL_MR: tName = "U-TL-MR"; break;
		case SOLID_U_ML_BR: tName = "U-ML-BR"; break;
		case SOLID_A_BL_MR: tName = "A-BL-MR"; break;
		case SOLID_A_ML_TR: tName = "A-ML-TR"; break;
		case SOLID_A_TL_MR: tName = "A-TL-MR"; break;
		case SOLID_A_ML_BR: tName = "A-ML-BR"; break;
		default: break;
	}

	SDL_Point tpos = CAsset::getPos(EWIDTH - 50, co_y - name_offset);
	Font::NewCenterWrite(FONT_MINI, tName.c_str(), &tpos);

	return true;
}

bool CEditMap::drawTileArrows(const SDL_Point* tPos, const SDL_Point* mouse)
{
	using namespace mapEngine::disp_t;

	// Draw left + right arrows next to active tile settings
	bool noInt = CInterrupt::isNone();
	SDL_Rect dstR;

	dstR.x = tPos->x - (arrSpac + ARR_SZ);
	dstR.y = tPos->y + (TILE_SIZE - ARR_SZ) / 2;
	dstR.w = dstR.h = ARR_SZ;
	CAsset::drawStrArrow(&dstR, 'L', noInt && SDL_PointInRect(mouse, &dstR) ? arrHovCol : arrCol);

	dstR.x = tPos->x + TILE_SIZE + arrSpac;
	CAsset::drawStrArrow(&dstR, 'R', noInt && SDL_PointInRect(mouse, &dstR) ? arrHovCol : arrCol);

	return true;
}

bool CEditMap::drawOpac_ty(SDL_Texture* interface)
{
	using namespace mapEngine::opac;
	// Draw an opacity meter for Type overlay
	int opacity_W = typeBar.w * ((double)(type_alpha) / (double)(MAX_RGBA));
	SDL_Rect fill = {typeBar.x, typeBar.y, opacity_W, typeBar.h};

	CAsset::drawBoxFill(&typeBar, emptyCol);
	CAsset::drawBoxFill(&fill, fillCol);

	return true;
}

bool CEditMap::drawOpac_co(SDL_Texture* interface)
{
	using namespace mapEngine::opac;
	// Draw an opacity meter for Collision overlay
	int opacity_W = collBar.w * ((double)(coll_alpha) / (double)(MAX_RGBA));
	SDL_Rect fill = {collBar.x, collBar.y, opacity_W, collBar.h};

	CAsset::drawBoxFill(&collBar, emptyCol);
	CAsset::drawBoxFill(&fill, fillCol);

	return true;
}

bool CEditMap::drawButton_bg(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace mapEngine::but_t;

	const SDL_Point* color = NULL;

	if (CInterrupt::isNone())
	{
		color = SDL_PointInRect(mouse, &bg_button) ? hoverColor : offCol;
	}
	else
	{
		color = CInterrupt::isFlagOn(INTRPT_CHANGE_BG) ? onCol : offCol;
	}

	if (!CAsset::drawStrBox(&bg_button, bsiz, color)) return false;

	Font::NewCenterWrite(FONT_MINI, "CHANGE B.TILE", &bg_button);
	return true;
}

bool CEditMap::drawButton_fg(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace mapEngine::but_t;

	const SDL_Point* color = NULL;

	if (CInterrupt::isNone())
	{
		color = SDL_PointInRect(mouse, &fg_button) ? hoverColor : offCol;
	}
	else
	{
		color = CInterrupt::isFlagOn(INTRPT_CHANGE_FG) ? onCol : offCol;
	}

	if (!CAsset::drawStrBox(&fg_button, bsiz, color)) return false;

	Font::NewCenterWrite(FONT_MINI, "CHANGE F.TILE", &fg_button);

	return true;
}

bool CEditMap::drawOverlayList(SDL_Texture* interface)
{
	using namespace mapEngine::view_flip;

	const bool flags[] = {
		show_fg,
		show_ty,
		show_co
	};

	// Menu/Options list for viewing various overlays
	SDL_Rect dstR = CAsset::getRect(x, y, w, h);
	SDL_Point tPos = CAsset::getPos(list_x, list_y);
	for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		Font::Write(FONT_MINI, labels[i], &tPos);
		CAsset::drawStrBox(&dstR, bsiz, flags[i] ? onCol : offCol);
		dstR.y += col_h;
		tPos.y += col_h;
	}

	return true;
}

bool CEditMap::drawPlacementList(SDL_Texture* interface)
{
	using namespace mapEngine::place_flip;

	const bool flags[] = {
		(onTiles & ENABLE_BG),
		(onTiles & ENABLE_FG),
		(onTiles & ENABLE_TYPE),
		(onTiles & ENABLE_COLL)
	};

	SDL_Rect dstR = CAsset::getRect(x, y, w, h);
	SDL_Point tPos = CAsset::getPos(list_x, list_y);
	for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++)
	{
		Font::Write(FONT_MINI, labels[i], &tPos);
		CAsset::drawStrBox(&dstR, bsiz, flags[i] ? onCol : offCol);
		dstR.y += col_h;
		tPos.y += col_h;
	}
	return true;
}

bool CEditMap::drawButtonActive(SDL_Texture* interface, const SDL_Point* mouse, bool active)
{
	using namespace mapEngine::but_act_t;

	const char* name = active ? onTitle : offTitle;

	const SDL_Point* color = NULL;

	if (!CInterrupt::isNone() || !SDL_PointInRect(mouse, &button))
	{
		color = active ? onCol : offCol;
	}
	else
	{
		color = active ? onhvCol : offhvCol;
	}

	if (!CAsset::drawStrBox(&button, bsiz, color)) return false;
	Font::NewCenterWrite(FONT_MINI, name, &button);

	return true;
}

bool CEditMap::drawQuadrants(SDL_Texture* interface, const SDL_Point* mouse)
{
	using namespace mapEngine::but_quad_t;

	bool canHilight = CInterrupt::isNone();
	bool noHov;
	const SDL_Point* color = NULL;

	SDL_Rect dstrect;
	SDL_Point pos;

	dstrect = CAsset::getRect(left_x, top_y, w, h);
	pos = CAsset::getPos(left_x + (w / 2), top_y + (h / 2));
	if (modifyTile != MODIFY_TILE_TL)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_TL ? onCol : offCol) : (active_TL ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}

	if (!CAsset::drawStrBox(&dstrect, bsiz, color)) return false;
	Font::NewCenterWrite(FONT_MINI, name_TL, &pos);



	dstrect.x = right_x;
	pos.x = right_x + (w / 2);
	if (modifyTile != MODIFY_TILE_TR)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_TR ? onCol : offCol) : (active_TR ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}
	if (!CAsset::drawStrBox(&dstrect, bsiz, color)) return false;
	Font::NewCenterWrite(FONT_MINI, name_TR, &pos);



	dstrect.y = bottom_y;
	pos.y = bottom_y + (h / 2);
	if (modifyTile != MODIFY_TILE_BR)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_BR ? onCol : offCol) : (active_BR ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}
	if (!CAsset::drawStrBox(&dstrect, bsiz, color)) return false;
	Font::NewCenterWrite(FONT_MINI, name_BR, &pos);



	dstrect.x = left_x;
	pos.x = left_x + (w / 2);
	if (modifyTile != MODIFY_TILE_BL)
	{
		noHov = (!canHilight || !SDL_PointInRect(mouse, &dstrect));
		color = (noHov) ? (active_BL ? onCol : offCol) : (active_BL ? onhvCol : offhvCol);
	}
	else
	{
		color = editCol;
	}
	if (!CAsset::drawStrBox(&dstrect, bsiz, color)) return false;
	Font::NewCenterWrite(FONT_MINI, name_BL, &pos);

	return true;
}
