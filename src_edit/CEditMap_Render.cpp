#include "CEditMap.h"

bool CEditMap::RenderMap() {
  // Draw the working area
	if (show_bg) CArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	if (show_fg) CArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	if (show_ty) CArea::control.OnRenderType(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	if (show_co) CArea::control.OnRenderColl(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

  return true;
}

bool CEditMap::OnRender(const SDL_Point* mouse) {
	if (!RenderWkspc(mouse)) return false;
	if (!CAsset::drawAppFrame()) return false;
  if (!RenderSidebar(mouse)) return false;
  if (!RenderBottom(mouse)) return false;

  return true;
}

bool CEditMap::RenderWkspc(const SDL_Point* mouse) {
	SDL_Point mapPos = CCamera::CameraControl.GetCamRelPoint(*mouse);

  if (!drawTileShadow(mouse, &mapPos)) return false;
	if (!drawPlaceDomain(mouse, &mapPos)) return false;
	if (!drawIntrpt(mouse)) return false;

	return true;
}

bool CEditMap::drawIntrpt(const SDL_Point* mouse) {
	if (!CInterrupt::isNone()) {
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_BG)) {
			if (!CChangeTile::PickTile.OnRender(mouse)) return false;
			CChangeTile::PickTile.hilightID(TileTL.bg_ID, TileTR.bg_ID, TileBL.bg_ID, TileBR.bg_ID);
		}
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_FG)) {
			if (!CChangeTile::PickTile.OnRender(mouse)) return false;
			CChangeTile::PickTile.hilightID(TileTL.fg_ID, TileTR.fg_ID, TileBL.fg_ID, TileBR.fg_ID);
		}
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_TS)) {
			if (!CTileset::TSControl.OnRender(mouse)) return false;
		}
	}
	return true;
}

bool CEditMap::drawTileShadow(const SDL_Point* mouse, const SDL_Point* mapPos) {
	if (!CInterrupt::isNone()) return true;

	int tX = -CCamera::CameraControl.GetX() + (TILE_SIZE * (mapPos->x / TILE_SIZE));
	int tY = -CCamera::CameraControl.GetY() + (TILE_SIZE * (mapPos->y / TILE_SIZE));
	if (mapPos->x < 0)	tX -= TILE_SIZE;
	if (mapPos->y < 0)	tY -= TILE_SIZE;

	if (CAsset::inWorkspace(mouse)) {
		SDL_Rect dstR = {0, 0, TILE_SIZE, TILE_SIZE};
		if (active_TL) {
			dstR.x = tX;
			dstR.y = tY;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
		if (active_BL) {
			dstR.x = tX;
			dstR.y = tY + TILE_SIZE;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
		if (active_TR) {
			dstR.x = tX + TILE_SIZE;
			dstR.y = tY;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
		if (active_BR) {
			dstR.x = tX + TILE_SIZE;
			dstR.y = tY + TILE_SIZE;
			if (!CAsset::drawBox(&dstR, shadowColor, shadow_w)) return false;
		}
	}
	return true;
}

bool CEditMap::drawPlaceDomain(const SDL_Point* mouse, const SDL_Point* mapPos) {
	if (!CInterrupt::isNone()) return true;

	if (rClickA != NULL) {
		if (rClickB == NULL) {
			SDL_Rect box = getTileDomain(rClickA, mapPos);
			CCamera::CameraControl.MakeWinRel(box.x, box.y);
			if (!CAsset::drawBox(&box, flexAreaColor, rc_area_w)) return false;
		} else {
			SDL_Rect box = getTileDomain(rClickA, rClickB);
			CCamera::CameraControl.MakeWinRel(box.x, box.y);
			const SDL_Point* color = SDL_PointInRect(mouse, &box) ? hoverAreaColor : fixAreaColor;
			if (!CAsset::drawBox(&box, color, rc_area_w)) return false;
		}
	}
	return true;
}

bool CEditMap::RenderSidebar(const SDL_Point* mouse) {
	const CTile* ShowTile = getModTile();

	if (!drawAreaExpand(mouse)) return false;
  if (!drawActiveTiles()) return false;
  if (!drawActive_bg(ShowTile, mouse)) return false;
  if (!drawActive_fg(ShowTile, mouse)) return false;
  // if (!drawActive_ty(ShowTile, mouse)) return false;
	if (!drawTypeTiles(ShowTile, mouse)) return false;
	if (!drawCollTiles(ShowTile, mouse)) return false;
  // if (!drawActive_co(ShowTile, mouse)) return false;
  if (!drawOpac_ty()) return false;
  if (!drawOpac_co()) return false;

  return true;
}

bool CEditMap::RenderBottom(const SDL_Point* mouse) {
	if (!drawButton_bg(mouse)) return false;
  if (!drawButton_fg(mouse)) return false;
	if (!drawButtonTileset(mouse)) return false;
	if (!drawButtonActive(mouse)) return false;
	if (!drawQuadrants(mouse)) return false;
  if (!drawOverlayList()) return false;
  if (!drawPlacementList()) return false;

  return true;
}

bool CEditMap::drawAreaExpand(const SDL_Point* mouse) {
	using namespace mapEngine::but_quad_map;

	for (int i = 0; i <= DOWN; i++) {
		if (!CAsset::drawStrBox(&buttons[i], bsiz, SDL_PointInRect(mouse, &buttons[i]) ? hvCol : col)) {
			return false;
		}
		Font::NewCenterWrite(FONT_MINI, labels[i], &buttons[i]);
	}
	return true;
}

bool CEditMap::drawButtonTileset(const SDL_Point* mouse) {
	using namespace mapEngine::but_tset;

	const SDL_Point* color = SDL_PointInRect(mouse, &button) ? hoverColor : offCol;
	if (!CAsset::drawStrBox(&button, bsiz, color)) return false;

	// Write a button name for changing a tileset
	Font::NewCenterWrite(FONT_MINI, label, &button);

	return true;
}

bool CEditMap::drawActiveTiles() {
	// Draw complete active tile with dummy entity & outline (for depth clarity)
	using namespace mapEngine::disp_t;

	SDL_Rect dstR = CAsset::getRect(0, 0, TILE_SIZE, TILE_SIZE);

	const bool flags[] = {
		active_TL,
		active_TR,
		active_BL,
		active_BR
	};

	const CTile* tiles[] = {
		&TileTL,
		&TileTR,
		&TileBL,
		&TileBR
	};

	for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
		if (flags[i]) {
			dstR.x = stage_pos.x + (TILE_SIZE * (i % 2));
			dstR.y = stage_pos.y + (TILE_SIZE * (i / 2));
			drawSampleTile(tiles[i], &dstR);
		}
	}

	SDL_Point tPos = CAsset::getPos(namePos_x, stage_pos.y + nameOffset_y);
	Font::NewCenterWrite(FONT_MINI, "Example", &tPos);

	return true;
}

bool CEditMap::drawSampleTile(const CTile* ShowTile, const SDL_Rect* dstR) {
	if (ShowTile == NULL || dstR == NULL) return false;

	using namespace mapEngine::disp_t;

	SDL_Rect srcR = {0, 0, TILE_SIZE, TILE_SIZE};

	srcR.x = (ShowTile->bg_ID % CTileset::TSControl.ts_w) * TILE_SIZE;
	srcR.y = (ShowTile->bg_ID / CTileset::TSControl.ts_w) * TILE_SIZE;
	if (!CSurface::OnDraw(CTileset::TSControl.tileset, &srcR, dstR)) return false;
	if (!CAsset::drawDummy(dstR)) return false;

	srcR.x = (ShowTile->fg_ID % CTileset::TSControl.ts_w) * TILE_SIZE;
	srcR.y = (ShowTile->fg_ID / CTileset::TSControl.ts_w) * TILE_SIZE;
	if (!CSurface::OnDraw(CTileset::TSControl.tileset, &srcR, dstR)) return false;
	if (!CAsset::drawDummyGhost(dstR)) return false;

	return true;
}

bool CEditMap::drawActive_bg(const CTile* ShowTile, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

	// Background tile header
	{
		const char* tName = "BACKGROUND";
		SDL_Point tpos = CAsset::getPos(namePos_x, bg_pos.y + nameOffset_y);
		Font::NewCenterWrite(FONT_MINI, tName, &tpos);
	}

	// Draws active background tile
	{
		int tX = (ShowTile->bg_ID % CTileset::TSControl.ts_w) * TILE_SIZE;
		int tY = (ShowTile->bg_ID / CTileset::TSControl.ts_w) * TILE_SIZE;
		SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
		CSurface::OnDraw(CTileset::TSControl.tileset, &srcR, &bg_pos);
	}

	// Draws background tile arrows
	drawTileButtons(&bg_pos, mouse);

	return true;
}

bool CEditMap::drawActive_fg(const CTile* ShowTile, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

	// Foreground tile header
	{
		const char* tName = "FOREGROUND";
		SDL_Point tpos = CAsset::getPos(namePos_x, fg_pos.y + nameOffset_y);
		Font::NewCenterWrite(FONT_MINI, tName, &tpos);
	}

	// Draws active foreground tile
	{
		int tX = (ShowTile->fg_ID % CTileset::TSControl.ts_w) * TILE_SIZE;
		int tY = (ShowTile->fg_ID / CTileset::TSControl.ts_w) * TILE_SIZE;
		SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
		CSurface::OnDraw(CTileset::TSControl.tileset, &srcR, &fg_pos);
	}

	// Draws foreground tile arrows
	drawTileButtons(&fg_pos, mouse);

  // CSurface::OnDraw(interface, mapEngine::but_rm::fg_x, mapEngine::but_rm::fg_y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);

	return true;
}

bool CEditMap::drawActive_ty(const CTile* ShowTile, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

	// Draws active tile type
	int tX = (ShowTile->TypeID % CTileset::TSControl.type_w) * TILE_SIZE;
	int tY = (ShowTile->TypeID / CTileset::TSControl.type_w) * TILE_SIZE;
	SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
	CSurface::OnDraw(CTileset::TSControl.type_tileset, &srcR, &ty_pos);

	// Draws tile type arrows
	drawTileButtons(&ty_pos, mouse);

	std::string tName;

	// Writes out the active type
	switch (ShowTile->TypeID) {
		case TILE_TYPE_NORMAL: 	tName = "NORMAL"; break;
		case TILE_TYPE_WATER: 	tName = "WATER"; break;
		case TILE_TYPE_ICE: 		tName = "ICE"; break;
		case TILE_TYPE_FIRE: 		tName = "FIRE"; break;
		default: break;
	}

	SDL_Point tpos = CAsset::getPos(namePos_x, ty_pos.y + nameOffset_y);
	Font::NewCenterWrite(FONT_MINI, tName.c_str(), &tpos);

	return true;
}

bool CEditMap::drawTypeTiles(const CTile* ShowTile, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

	// SDL_SetTextureAlphaMod(CTileset::TSControl.type_tileset, MAX_RGBA);
	CTileset::TSControl.maxTypeAlpha();

	SDL_Rect dstR = {0, 0, ty_t_size, ty_t_size};
	int k = 0;
	for (int j = 0; j < CTileset::TSControl.type_h; j++) {
		for (int i = 0; i < CTileset::TSControl.type_w; i++) {
			int tX = i * TILE_SIZE;
			int tY = j * TILE_SIZE;
			SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
			dstR.x = ty_pos.x + ((k % ty_w) * (ty_t_size + ty_spac));
			dstR.y = ty_pos.y + ((k / ty_w) * (ty_t_size + ty_spac));
			CSurface::OnDraw(CTileset::TSControl.type_tileset, &srcR, &dstR);
			if (k == ShowTile->TypeID) {
				CAsset::drawBox(&dstR, &palette::red);
			}
			k++;
		}
	}
	// SDL_SetTextureAlphaMod(CTileset::TSControl.type_tileset, type_alpha);
	CTileset::TSControl.refreshTypeAlpha();
	return true;
}

bool CEditMap::drawCollTiles(const CTile* ShowTile, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

	// SDL_SetTextureAlphaMod(CTileset::TSControl.coll_tileset, MAX_RGBA);
	CTileset::TSControl.maxCollAlpha();

	SDL_Rect dstR = {0, 0, co_t_size, co_t_size};
	int k = 0;
	for (int j = 0; j < CTileset::TSControl.coll_h; j++) {
		for (int i = 0; i < CTileset::TSControl.coll_w; i++) {
			int tX = i * TILE_SIZE;
			int tY = j * TILE_SIZE;
			SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
			dstR.x = co_pos.x + ((k % co_w) * (co_t_size + co_spac));
			dstR.y = co_pos.y + ((k / co_w) * (co_t_size + co_spac));
			CSurface::OnDraw(CTileset::TSControl.coll_tileset, &srcR, &dstR);
			if (k == ShowTile->CollID) {
				CAsset::drawBox(&dstR, &palette::red);
			}
			k++;
		}
	}
	// SDL_SetTextureAlphaMod(CTileset::TSControl.coll_tileset, coll_alpha);
	CTileset::TSControl.refreshCollAlpha();
	return true;
}

bool CEditMap::drawActive_co(const CTile* ShowTile, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

	// Draws active collision tile
	int tX = (ShowTile->CollID % CTileset::TSControl.coll_w) * TILE_SIZE;
	int tY = (ShowTile->CollID / CTileset::TSControl.coll_w) * TILE_SIZE;
	SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
	CSurface::OnDraw(CTileset::TSControl.coll_tileset, &srcR, &co_pos);

	// Draws collision tile arrows
	drawTileButtons(&co_pos, mouse);

	std::string tName;

	// Writes out the active collision type
	switch (ShowTile->CollID) {
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

	SDL_Point tpos = CAsset::getPos(namePos_x, co_pos.y + nameOffset_y);
	Font::NewCenterWrite(FONT_MINI, tName.c_str(), &tpos);

	return true;
}

bool CEditMap::drawTileButtons(const SDL_Point* tPos, const SDL_Point* mouse) {
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

	// Draw reset button
	dstR = CAsset::getRect(tPos->x + rmOffset_x, tPos->y + rmOffset_y, rm_sz, rm_sz);
	CAsset::drawStrBox(&dstR, rm_bsiz, SDL_PointInRect(mouse, &dstR) ? rmHovCol : rmCol);

	return true;
}

bool CEditMap::drawOpac_ty() {
	using namespace mapEngine::opac;
	// Draw an opacity meter for Type overlay
	int opacity_W = typeBar.w * ((double)(CTileset::TSControl.type_alpha) / (double)(MAX_RGBA));
	SDL_Rect fill = {typeBar.x, typeBar.y, opacity_W, typeBar.h};

	CAsset::drawBoxFill(&typeBar, emptyCol);
	CAsset::drawBoxFill(&fill, fillCol);
	CAsset::drawBox(&typeBar, emptyCol);

	return true;
}

bool CEditMap::drawOpac_co() {
	using namespace mapEngine::opac;
	// Draw an opacity meter for Collision overlay
	int opacity_W = collBar.w * ((double)(CTileset::TSControl.coll_alpha) / (double)(MAX_RGBA));
	SDL_Rect fill = {collBar.x, collBar.y, opacity_W, collBar.h};

	CAsset::drawBoxFill(&collBar, emptyCol);
	CAsset::drawBoxFill(&fill, fillCol);
	CAsset::drawBox(&collBar, emptyCol);

	return true;
}

bool CEditMap::drawButton_bg(const SDL_Point* mouse) {
	using namespace mapEngine::but_t;

	const SDL_Point* color = NULL;

	if (CInterrupt::isNone()) {
		color = SDL_PointInRect(mouse, &bg_button) ? hoverColor : offCol;
	} else {
		color = CInterrupt::isFlagOn(INTRPT_CHANGE_BG) ? onCol : offCol;
	}

	if (!CAsset::drawStrBox(&bg_button, bsiz, color)) return false;

	Font::NewCenterWrite(FONT_MINI, bg_label, &bg_button);
	return true;
}

bool CEditMap::drawButton_fg(const SDL_Point* mouse) {
	using namespace mapEngine::but_t;

	const SDL_Point* color = NULL;

	if (CInterrupt::isNone()) {
		color = SDL_PointInRect(mouse, &fg_button) ? hoverColor : offCol;
	} else {
		color = CInterrupt::isFlagOn(INTRPT_CHANGE_FG) ? onCol : offCol;
	}

	if (!CAsset::drawStrBox(&fg_button, bsiz, color)) return false;

	Font::NewCenterWrite(FONT_MINI, fg_label, &fg_button);
	return true;
}

bool CEditMap::drawOverlayList() {
	using namespace mapEngine::view_flip;

	const bool flags[] = {
		show_bg,
		show_fg,
		show_ty,
		show_co
	};

	// Menu/Options list for viewing various overlays
	SDL_Rect dstR = CAsset::getRect(x, y, w, h);
	SDL_Point tPos = CAsset::getPos(list_x, list_y);
	for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
		Font::Write(FONT_MINI, labels[i], &tPos);
		CAsset::drawStrBox(&dstR, bsiz, flags[i] ? onCol : offCol);
		dstR.y += col_h;
		tPos.y += col_h;
	}
	return true;
}

bool CEditMap::drawPlacementList() {
	using namespace mapEngine::place_flip;

	const bool flags[] = {
		(onTiles & ENABLE_BG),
		(onTiles & ENABLE_FG),
		(onTiles & ENABLE_TYPE),
		(onTiles & ENABLE_COLL)
	};

	SDL_Rect dstR = CAsset::getRect(x, y, w, h);
	SDL_Point tPos = CAsset::getPos(list_x, list_y);
	for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
		Font::Write(FONT_MINI, labels[i], &tPos);
		CAsset::drawStrBox(&dstR, bsiz, flags[i] ? onCol : offCol);
		dstR.y += col_h;
		tPos.y += col_h;
	}
	return true;
}

bool CEditMap::drawButtonActive(const SDL_Point* mouse) {
	using namespace mapEngine::but_act_t;

	bool active = false;
	switch (modifyTile) {
		case MODIFY_TILE_TL: active = active_TL; break;
		case MODIFY_TILE_TR: active = active_TR; break;
		case MODIFY_TILE_BL: active = active_BL; break;
		case MODIFY_TILE_BR: active = active_BR; break;
		default: break;
	}

	const char* name = active ? onTitle : offTitle;

	const SDL_Point* color = NULL;

	if (!CInterrupt::isNone() || !SDL_PointInRect(mouse, &button)) {
		color = active ? onCol : offCol;
	}	else {
		color = active ? onhvCol : offhvCol;
	}

	if (!CAsset::drawStrBox(&button, bsiz, color)) return false;
	Font::NewCenterWrite(FONT_MINI, name, &button);
	return true;
}

bool CEditMap::drawQuadrants(const SDL_Point* mouse) {
	using namespace mapEngine::but_quad_t;

	bool canHilight = CInterrupt::isNone();
	bool noHov;
	const SDL_Point* color = NULL;

	const bool aFlag[] = {
		active_TL,
		active_TR,
		active_BL,
		active_BR
	};

	const short w = buttons[0].w;
	const short h = buttons[0].h;

	SDL_Point tPos;

	for (int i = MODIFY_TILE_TL; i <= MODIFY_TILE_BR; i++) {
		if (modifyTile != i) {
			noHov = (!canHilight || !SDL_PointInRect(mouse, &buttons[i]));
			color = (noHov) ? (aFlag[i] ? onCol : offCol) : (aFlag[i] ? onhvCol : offhvCol);
		} else {
			color = editCol;
		}

		if (!CAsset::drawStrBox(&buttons[i], bsiz, color)) return false;

		tPos = CAsset::getPos(buttons[i].x + (w / 2), buttons[i].y + (h / 2));
		Font::NewCenterWrite(FONT_MINI, labels[i], &tPos);
	}
	return true;
}
