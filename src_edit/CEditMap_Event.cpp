#include "CEditMap.h"

void CEditMap::OnEvent(SDL_Event* Event)
{
  if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

bool CEditMap::handleInterr(SDL_Event* Event)
{
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_TS)) {
    handleChangeTS(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_BG)) {
    handleChangeTile(Event, INTRPT_CHANGE_BG);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_FG)) {
    handleChangeTile(Event, INTRPT_CHANGE_FG);
    return true;
  }
  return false;
}

void CEditMap::handleChangeTS(SDL_Event* Event)
{
  CTileset::TSControl.OnEvent(Event);

  if (CInterrupt::isFlagOff(INTRPT_CHANGE_TS) && CTileset::TSControl.wasSuccess()) {
    TileTL.bg_ID = TileTR.bg_ID = TileBL.bg_ID = TileBR.bg_ID = -1;
    TileTL.fg_ID = TileTR.fg_ID = TileBL.fg_ID = TileBR.fg_ID = -1;
    TileTL.TypeID = TileTR.TypeID = TileBL.TypeID = TileBR.TypeID = TILE_TYPE_NORMAL;
    TileTL.CollID = TileTR.CollID = TileBL.CollID = TileBR.CollID = SOLID_NONE;
  }
}

void CEditMap::handleChangeTile(SDL_Event* Event, int intrpt)
{
  CChangeTile::PickTile.OnEvent(Event);

  if (CInterrupt::isFlagOff(intrpt))
  {
    CTile* EditTile = getModTile();
    CChangeTile::PickTile.reqChange((intrpt == INTRPT_CHANGE_BG) ? EditTile->bg_ID : EditTile->fg_ID);
  }
}

void CEditMap::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
  if (handleAreaModify(sym, mod)) return;
}

void CEditMap::OnLButtonDown(int mX, int mY)
{
  const SDL_Point mouse = {mX, mY};

  CTile* EditTile = getModTile();
  bool* active;
  switch (modifyTile)
  {
    case MODIFY_TILE_TL: active = &active_TL; break;
    case MODIFY_TILE_TR: active = &active_TR; break;
    case MODIFY_TILE_BL: active = &active_BL; break;
    case MODIFY_TILE_BR: active = &active_BR; break;
    default: break;
  }

  if (handleAreaExtend(&mouse)) return;
  if (handlePlaceDomain(&mouse)) return;
  if (handleNewTile(&mouse)) return;
  if (handleGetSet(&mouse)) return;
  if (handleGetTile(&mouse)) return;
  if (handleScroll_bg(&mouse, EditTile)) return;
  if (handleScroll_fg(&mouse, EditTile)) return;
  if (handleScroll_ty(&mouse, EditTile)) return;
  // if (handleScroll_co(&mouse, EditTile)) return;
  if (handleColl(&mouse, EditTile)) return;
  if (handleTileReset(&mouse, EditTile)) return;
  if (handleOpac_ty(&mouse)) return;
  if (handleOpac_co(&mouse)) return;
  if (handleLayers(&mouse)) return;
  if (handlePlace(&mouse)) return;
  if (handleActTile(&mouse, *active)) return;
  if (handleQuadrant_lc(&mouse)) return;
}

void CEditMap::OnRButtonDown(int mX, int mY) {
  if (!CInterrupt::isNone()) return;

  const SDL_Point mouse = {mX, mY};

  if (handleAreaRemove(&mouse)) return;
  if (handleMakeDomain(&mouse)) return;
  if (handleQuadrant_rc(&mouse)) return;
}

bool CEditMap::handleAreaModify(SDL_Keycode sym, Uint16 mod) {
  if (!CInterrupt::isNone()) return false;
  bool retval = true;

  switch (sym) {
    case SDLK_d:  extendMap_R();  break;
    case SDLK_a:  extendMap_L();  break;
    case SDLK_s:  extendMap_D();  break;
    case SDLK_w:  extendMap_U();  break;
    case SDLK_l:  removeMap_R();  break;
    case SDLK_j:  removeMap_L();  break;
    case SDLK_k:  removeMap_D();  break;
    case SDLK_i:  removeMap_U();  break;
    default:      retval = false; break;
  }
  return retval;
}

bool CEditMap::handleAreaExtend(const SDL_Point* mouse) {
  using namespace mapEngine::but_quad_map;

  if (SDL_PointInRect(mouse, &buttons[LEFT])) {
    extendMap_L();
    return true;
  }
  if (SDL_PointInRect(mouse, &buttons[RIGHT])) {
    extendMap_R();
    return true;
  }
  if (SDL_PointInRect(mouse, &buttons[UP])) {
    extendMap_U();
    return true;
  }
  if (SDL_PointInRect(mouse, &buttons[DOWN])) {
    extendMap_D();
    return true;
  }
  return false;
}

bool CEditMap::handleAreaRemove(const SDL_Point* mouse)
{
  using namespace mapEngine::but_quad_map;

  if (SDL_PointInRect(mouse, &buttons[LEFT])) {
    removeMap_L();
    return true;
  }
  if (SDL_PointInRect(mouse, &buttons[RIGHT])) {
    removeMap_R();
    return true;
  }
  if (SDL_PointInRect(mouse, &buttons[UP])) {
    removeMap_U();
    return true;
  }
  if (SDL_PointInRect(mouse, &buttons[DOWN])) {
    removeMap_D();
    return true;
  }
  return false;
}

void CEditMap::extendMap_R() {
  CArea::control.OnExpandRight();
}

void CEditMap::extendMap_L() {
  CArea::control.OnExpandLeft();

  // This loop updates the position of our entities & scenery
  // to prevent unintended "movement" over the changed area
  for (int i = 0; i < CEntity::entityList.size(); i++) {
    CEntity::entityList[i].dstP.x += MAP_WIDTH * TILE_SIZE;
  }
  for (int i = 0; i < CScenery::sceneryList.size(); i++) {
    long double Z = CScenery::layerList[CScenery::sceneryList[i].layer];
    long double rel_x = CCamera::CameraControl.trueXToRel(CScenery::sceneryList[i].true_x, Z);
    long double win_x = rel_x - CCamera::CameraControl.GetX();

    CCamera::CameraControl.OnMove(MAP_WIDTH * TILE_SIZE, 0);
    rel_x = win_x + CCamera::CameraControl.GetX();
    CScenery::sceneryList[i].true_x = CCamera::CameraControl.relXToTrue(rel_x, Z);

    CCamera::CameraControl.OnMove(-MAP_WIDTH * TILE_SIZE, 0);
  }
  // Keep camera focused on same spot (relative to the area prior to expansion)
  CCamera::CameraControl.OnMove(MAP_WIDTH * TILE_SIZE, 0);
}

void CEditMap::extendMap_D() {
  CArea::control.OnExpandDown();
}

void CEditMap::extendMap_U() {
  CArea::control.OnExpandUp();

  // Update entity positions relative to new area size
  for (int i = 0; i < CEntity::entityList.size(); i++) {
    CEntity::entityList[i].dstP.y += MAP_HEIGHT * TILE_SIZE;
  }
  for (int i = 0; i < CScenery::sceneryList.size(); i++) {
    long double Z = CScenery::layerList[CScenery::sceneryList[i].layer];
    long double rel_y = CCamera::CameraControl.trueYToRel(CScenery::sceneryList[i].true_y, Z);
    long double win_y = rel_y - CCamera::CameraControl.GetY();

    CCamera::CameraControl.OnMove(0, MAP_HEIGHT * TILE_SIZE);
    rel_y = win_y + CCamera::CameraControl.GetY();
    CScenery::sceneryList[i].true_y = CCamera::CameraControl.relYToTrue(rel_y, Z);

    CCamera::CameraControl.OnMove(0, -MAP_HEIGHT * TILE_SIZE);
  }
  // Keep camera focused on same spot
  CCamera::CameraControl.OnMove(0, MAP_HEIGHT * TILE_SIZE);
}

void CEditMap::removeMap_R() {
  CArea::control.OnReduceRight();
}

void CEditMap::removeMap_L() {
  // adjustments to pre-existing objects on the map (e.g., entities)
  // are only necessary if a reduction in map area is possible
  if (CArea::control.OnReduceLeft()) {
    for (int i = 0; i < CEntity::entityList.size(); i++) {
      CEntity::entityList[i].dstP.x -= MAP_WIDTH * TILE_SIZE;
    }
    for (int i = 0; i < CScenery::sceneryList.size(); i++) {
      long double Z = CScenery::layerList[CScenery::sceneryList[i].layer];
      long double rel_x = CCamera::CameraControl.trueXToRel(CScenery::sceneryList[i].true_x, Z);
      long double win_x = rel_x - CCamera::CameraControl.GetX();

      CCamera::CameraControl.OnMove(-MAP_WIDTH * TILE_SIZE, 0);
      rel_x = win_x + CCamera::CameraControl.GetX();
      CScenery::sceneryList[i].true_x = CCamera::CameraControl.relXToTrue(rel_x, Z);

      CCamera::CameraControl.OnMove(MAP_WIDTH * TILE_SIZE, 0);
    }
    CCamera::CameraControl.OnMove(-MAP_WIDTH * TILE_SIZE, 0);
  }
}

void CEditMap::removeMap_D() {
  CArea::control.OnReduceDown();
}

void CEditMap::removeMap_U() {
  // adjustments to pre-existing objects on the map (e.g., entities)
  // are only necessary if a reduction in map area is possible
  if (CArea::control.OnReduceUp())
  {
    for (int i = 0; i < CEntity::entityList.size(); i++) {
      CEntity::entityList[i].dstP.y -= MAP_HEIGHT * TILE_SIZE;
    }
    for (int i = 0; i < CScenery::sceneryList.size(); i++) {
      long double Z = CScenery::layerList[CScenery::sceneryList[i].layer];
      long double rel_y = CCamera::CameraControl.trueYToRel(CScenery::sceneryList[i].true_y, Z);
      long double win_y = rel_y - CCamera::CameraControl.GetY();

      CCamera::CameraControl.OnMove(0, -MAP_HEIGHT * TILE_SIZE);
      rel_y = win_y + CCamera::CameraControl.GetY();
      CScenery::sceneryList[i].true_y = CCamera::CameraControl.relYToTrue(rel_y, Z);

      CCamera::CameraControl.OnMove(0, MAP_HEIGHT * TILE_SIZE);
    }
    CCamera::CameraControl.OnMove(0, -MAP_HEIGHT * TILE_SIZE);
  }
}

bool CEditMap::handleMakeDomain(const SDL_Point* mouse) {
  if (CAsset::inWorkspace(mouse))
  {
    if (rClickA == NULL)
    {
      rClickA = new SDL_Point;
      rClickA->x = mouse->x + CCamera::CameraControl.GetX();
      rClickA->y = mouse->y + CCamera::CameraControl.GetY();
    }
    else if (rClickB == NULL)
    {
      rClickB = new SDL_Point;
      rClickB->x = mouse->x + CCamera::CameraControl.GetX();
      rClickB->y = mouse->y + CCamera::CameraControl.GetY();
    }
    else
    {
      resetRClick();
    }
    return true;
  }
  return false;
}

bool CEditMap::handlePlaceDomain(const SDL_Point* mouse) {
  bool retval = false;
  if (CAsset::inWorkspace(mouse))
  {
    if (rClickA != NULL && rClickB != NULL)
    {
      retval = true;
      SDL_Rect dom = getTileDomain(rClickA, rClickB);
      SDL_Point clickPos = CCamera::CameraControl.GetCamRelPoint(*mouse);

      if (SDL_PointInRect(&clickPos, &dom))
      {
        // update the highlighted region in the map
        int tW = TILE_SIZE * (1 + (active_TR || active_BR));
        int tH = TILE_SIZE * (1 + (active_BL || active_BR));
        for (int tX = 0; tX < dom.w / tW; tX++)
        {
          for (int tY = 0; tY < dom.h / tH; tY++)
          {
            int mX = dom.x + (tX * tW);
            int mY = dom.y + (tY * tH);
            placeBlock(mX, mY);
          }
        }
      }
    }
    resetRClick();
  }
  return retval;
}

void CEditMap::resetRClick() {
  if (rClickA != NULL) {
    delete rClickA;
    rClickA = NULL;
  }
  if (rClickB != NULL) {
    delete rClickB;
    rClickB = NULL;
  }
}

bool CEditMap::handleNewTile(const SDL_Point* mouse) {
  // Place new tiles, if click is in the workspace
  if (CAsset::inWorkspace(mouse))
  {
    int mX = CCamera::CameraControl.GetX() + mouse->x;
    int mY = CCamera::CameraControl.GetY() + mouse->y;
    placeBlock(mX, mY);
    return true;
  }
  return false;
}

void CEditMap::placeBlock(const int& x, const int& y) {
  if (active_TL) CArea::control.ChangeTile(x, y, &TileTL, onTiles);
  if (active_TR) CArea::control.ChangeTile(x + TILE_SIZE, y, &TileTR, onTiles);
  if (active_BL) CArea::control.ChangeTile(x, y + TILE_SIZE, &TileBL, onTiles);
  if (active_BR) CArea::control.ChangeTile(x + TILE_SIZE, y + TILE_SIZE, &TileBR, onTiles);
}

bool CEditMap::handleGetSet(const SDL_Point* mouse) {
  // Click on "Change Tileset" button. This displays a prompt to change tilesets,
  // and the function within the loop performs a change if requested.
	using namespace mapEngine::but_tset;
  if (SDL_PointInRect(mouse, &button)) {
    CInterrupt::appendFlag(INTRPT_CHANGE_TS);
    return true;
  }
  return false;
}

bool CEditMap::handleGetTile(const SDL_Point* mouse) {
  // Click on "Change Tile" buttons. A display of all tiles is rendered,
  // and clicking a tile will update the active tile to use the clicked tile.
  using namespace mapEngine::but_t;

  if (SDL_PointInRect(mouse, &bg_button)) {
      CChangeTile::PickTile.Init(CTileset::TSControl.ts_w, CTileset::TSControl.ts_h);
      CInterrupt::appendFlag(INTRPT_CHANGE_BG);
      return true;
  }
  if (SDL_PointInRect(mouse, &fg_button)) {
      CChangeTile::PickTile.Init(CTileset::TSControl.ts_w, CTileset::TSControl.ts_h);
      CInterrupt::appendFlag(INTRPT_CHANGE_FG);
      return true;
  }
  return false;
}

bool CEditMap::handleScroll_bg(const SDL_Point* mouse, CTile* EditTile) {
  using namespace mapEngine::disp_t;

  // Check for click on arrow LEFT or RIGHT of active background tile.
  // Changes the active tile to previous or next index.
  const char arrDir = getScrollDir(&bg_pos, mouse);

  if (arrDir == 'N') return false;

  else if (arrDir == 'R') {
    if (EditTile->bg_ID < (CTileset::TSControl.ts_w * CTileset::TSControl.ts_h) - 1) EditTile->bg_ID += 1;
    else EditTile->bg_ID = 0;
    return true;
  }
  else if (arrDir == 'L') {
    if (EditTile->bg_ID > 0) EditTile->bg_ID -= 1;
    else EditTile->bg_ID = (CTileset::TSControl.ts_w * CTileset::TSControl.ts_h) - 1;
    return true;
  }
  return false;
}

bool CEditMap::handleScroll_fg(const SDL_Point* mouse, CTile* EditTile) {
  using namespace mapEngine::disp_t;

  // Click on arrow LEFT or RIGHT of active foreground tile.
  // Changes the active tile to previous or next index.

  const char arrDir = getScrollDir(&fg_pos, mouse);

  if (arrDir == 'N') return false;

  else if (arrDir == 'R') {
    if (EditTile->fg_ID < (CTileset::TSControl.ts_w * CTileset::TSControl.ts_h) - 1) EditTile->fg_ID += 1;
    else EditTile->fg_ID = 0;
    return true;
  }
  else if (arrDir == 'L') {
    if (EditTile->fg_ID > 0) EditTile->fg_ID -= 1;
    else EditTile->fg_ID = (CTileset::TSControl.ts_w * CTileset::TSControl.ts_h) - 1;
    return true;
  }
  return false;
}

bool CEditMap::handleScroll_ty(const SDL_Point* mouse, CTile* EditTile) {
  using namespace mapEngine::disp_t;

  // Click on arrow LEFT or RIGHT of active tile type.
  // Changes the active tile type to previous or next type index.

  const char arrDir = getScrollDir(&ty_pos, mouse);

  if (arrDir == 'N') return false;

  else if (arrDir == 'R') {
    if (EditTile->TypeID != TILE_TYPE_FIRE) EditTile->TypeID += 1;
    else EditTile->TypeID = 0;
    return true;
  }
  else if (arrDir == 'L') {
    if (EditTile->TypeID != 0) EditTile->TypeID -= 1;
    else EditTile->TypeID = TILE_TYPE_FIRE;
    return true;
  }
  return false;
}

// bool CEditMap::handleScroll_co(const SDL_Point* mouse, CTile* EditTile) {
//   using namespace mapEngine::disp_t;
//
//   // Click on arrow LEFT or RIGHT of active collision.
//   // Changes the active collision to previous or next collision index.
//
//   const char arrDir = getScrollDir(&co_pos, mouse);
//
//   if (arrDir == 'N') return false;
//
//   else if (arrDir == 'R') {
//     if (EditTile->CollID != SOLID_A_ML_BR) EditTile->CollID += 1;
//     else EditTile->CollID = 0;
//     return true;
//   }
//   else if (arrDir == 'L') {
//     if (EditTile->CollID != 0) EditTile->CollID -= 1;
//     else EditTile->CollID = SOLID_A_ML_BR;
//     return true;
//   }
//   return false;
// }

bool CEditMap::handleColl(const SDL_Point* mouse, CTile* EditTile) {
  if (!mouse || !EditTile) return false;
  using namespace mapEngine::disp_t;

  SDL_Rect targetR = {0, 0, co_t_size, co_t_size};
  int k = 0;
  for (int j = 0; j < coll_h; j++) {
    for (int i = 0; i < coll_w; i++) {
      targetR.x = co_pos.x + ((k % co_w) * (co_t_size + co_spac));
      targetR.y = co_pos.y + ((k / co_w) * (co_t_size + co_spac));
      if (SDL_PointInRect(mouse, &targetR)) {
        EditTile->CollID = k;
        return true;
      }
      k++;
    }
  }
  return false;
}

char CEditMap::getScrollDir(const SDL_Point* tPos, const SDL_Point* mouse) {
	using namespace mapEngine::disp_t;

  char retDir = 'N';
  if (tPos == NULL || mouse == NULL) return retDir;

  SDL_Rect arrRec;

  arrRec.x = tPos->x - (arrSpac + ARR_SZ);
  arrRec.y = tPos->y + (TILE_SIZE - ARR_SZ) / 2;
  arrRec.w = arrRec.h = ARR_SZ;
  if (SDL_PointInRect(mouse, &arrRec)) retDir = 'L';

  arrRec.x = tPos->x + TILE_SIZE + arrSpac;
  if (SDL_PointInRect(mouse, &arrRec)) retDir = 'R';

  return retDir;
}

bool CEditMap::handleTileReset(const SDL_Point* mouse, CTile* EditTile) {
  using namespace mapEngine::disp_t;

	SDL_Rect dstR;

  dstR = CAsset::getRect(bg_pos.x + rmOffset_x, bg_pos.y + rmOffset_y, rm_sz, rm_sz);
  if (SDL_PointInRect(mouse, &dstR)) {
    EditTile->bg_ID = -1;
    return true;
  }

  dstR.x = fg_pos.x + rmOffset_x;
  dstR.y = fg_pos.y + rmOffset_y;
  if (SDL_PointInRect(mouse, &dstR)) {
    EditTile->fg_ID = -1;
    return true;
  }

  dstR.x = ty_pos.x + rmOffset_x;
  dstR.y = ty_pos.y + rmOffset_y;
  if (SDL_PointInRect(mouse, &dstR)) {
    EditTile->TypeID = TILE_TYPE_NORMAL;
    return true;
  }

  dstR.x = co_pos.x + rmOffset_x;
  dstR.y = co_pos.y + rmOffset_y;
  if (SDL_PointInRect(mouse, &dstR)) {
    EditTile->CollID = SOLID_NONE;
    return true;
  }
  return false;
}

bool CEditMap::handleOpac_ty(const SDL_Point* mouse) {
  // Click on opacity bar for tile type overlay
  using namespace mapEngine::opac;

  if (SDL_PointInRect(mouse, &typeBar)) {
    double barfract = (double)(mouse->x - typeBar.x) / (double)(typeBar.w - 1);
    type_alpha = MAX_RGBA * barfract;
    SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);
    return true;
  }
  return false;
}

bool CEditMap::handleOpac_co(const SDL_Point* mouse) {
  // Click on opacity bar for tile collision overlay
  using namespace mapEngine::opac;

  if (SDL_PointInRect(mouse, &collBar)) {
    double barfract = (double)(mouse->x - collBar.x) / (double)(collBar.w - 1);
    coll_alpha = MAX_RGBA * barfract;
    SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);
    return true;
  }
  return false;
}

bool CEditMap::handleLayers(const SDL_Point* mouse) {
  // Click on View overlay buttons
  using namespace mapEngine::view_flip;

  bool* flags[] = {
    &show_bg,
		&show_fg,
		&show_ty,
		&show_co
	};

	SDL_Rect dstR = CAsset::getRect(x, y, w, h);
	for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(mouse, &dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
		dstR.y += col_h;
	}
  return false;
}

bool CEditMap::handlePlace(const SDL_Point* mouse) {
  // Click on active tile attribute switches
  using namespace mapEngine::place_flip;

  const int bits[] = {
		ENABLE_BG,
		ENABLE_FG,
		ENABLE_TYPE,
		ENABLE_COLL
	};

	SDL_Rect dstR = CAsset::getRect(x, y, w, h);
	for (int i = 0; i < sizeof(bits) / sizeof(bits[0]); i++) {
    if (SDL_PointInRect(mouse, &dstR)) {
      if (onTiles & bits[i]) onTiles &= ~bits[i];
      else onTiles |= bits[i];
      return true;
    }
		dstR.y += col_h;
	}
  return false;
}

bool CEditMap::handleActTile(const SDL_Point* mouse, bool& active) {
  using namespace mapEngine::but_act_t;

  if (!SDL_PointInRect(mouse, &button)) return false;

  active = !active;

  return true;
}

bool CEditMap::handleQuadrant_lc(const SDL_Point* mouse) {
  using namespace mapEngine::but_quad_t;

  for (int i = MODIFY_TILE_TL; i <= MODIFY_TILE_BR; i++) {
    if (SDL_PointInRect(mouse, &buttons[i])) {
      modifyTile = i;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleQuadrant_rc(const SDL_Point* mouse) {
  using namespace mapEngine::but_quad_t;

  bool* flags[] = {
    &active_TL,
    &active_TR,
    &active_BL,
    &active_BR
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(mouse, &buttons[i])) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}
