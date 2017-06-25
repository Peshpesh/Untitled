#include "CEditMap.h"

void CEditMap::OnEvent(SDL_Event* Event)
{
  if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

bool CEditMap::handleInterr(SDL_Event* Event)
{
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_TS))
  {
    handleChangeTS(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_BG))
  {
    handleChangeTile(Event, INTRPT_CHANGE_BG);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_FG))
  {
    handleChangeTile(Event, INTRPT_CHANGE_FG);
    return true;
  }
  return false;
}

void CEditMap::handleChangeTS(SDL_Event* Event)
{
  CTileset::PickTS.OnEvent(Event);
  if (CTileset::PickTS.reqChange())    // try to change tileset
  {
    SDL_Texture* tmpset = CTileset::PickTS.changeTileset();
    if (tmpset != NULL)
    {
      SDL_DestroyTexture(Tileset);
      Tileset = tmpset;
      queryTileDims(Tileset, tset_w, tset_h);
      CArea::AreaControl.OnLoad(Tileset);
      TileTL.reset(); TileTR.reset(); TileBL.reset(); TileBR.reset();
    }
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

CTile* CEditMap::getModTile()
{
  CTile* EditTile;
  switch (modifyTile)
  {
    case MODIFY_TILE_TL: EditTile = &TileTL; break;
    case MODIFY_TILE_TR: EditTile = &TileTR; break;
    case MODIFY_TILE_BL: EditTile = &TileBL; break;
    case MODIFY_TILE_BR: EditTile = &TileBR; break;
    default: break;
  }
  return EditTile;
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

  if (handlePlaceDomain(&mouse)) return;
  if (handleNewTile(&mouse)) return;
  if (handleGetSet(&mouse)) return;
  if (handleGetTile(&mouse)) return;
  if (handleScroll_bg(&mouse, EditTile)) return;
  if (handleScroll_fg(&mouse, EditTile)) return;
  if (handleScroll_ty(&mouse, EditTile)) return;
  if (handleScroll_co(&mouse, EditTile)) return;
  if (handleRemove_bg(&mouse, EditTile)) return;
  if (handleRemove_fg(&mouse, EditTile)) return;
  if (handleOpac_ty(&mouse)) return;
  if (handleOpac_co(&mouse)) return;
  if (handleLayers(&mouse)) return;
  if (handlePlace(&mouse)) return;
  if (handleActTile(&mouse, *active)) return;
  if (handleQuadrant_lc(&mouse)) return;
}

void CEditMap::OnRButtonDown(int mX, int mY)
{
  if (!CInterrupt::isNone()) return;

  const SDL_Point mouse = {mX, mY};

  if (handleMakeDomain(&mouse)) return;
  if (handleQuadrant_rc(&mouse)) return;
}

bool CEditMap::handleAreaModify(SDL_Keycode sym, Uint16 mod)
{
  if (!CInterrupt::isNone()) return false;

  switch (sym)
  {
  case SDLK_d:
    CArea::AreaControl.OnExpandRight(); break;
  case SDLK_a:
    CArea::AreaControl.OnExpandLeft();
    CCamera::CameraControl.OnMove(MAP_WIDTH*TILE_SIZE, 0);  // Keeps the area from jerking around
    for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
    {
      if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
      CEntityEdit::NPCControl.EntityList[i].X += MAP_WIDTH*TILE_SIZE;
    }	// This loop updates the position of our entities
    // to prevent unwanted repositioning over the changed area
    break;
  case SDLK_s:
    CArea::AreaControl.OnExpandDown(); break;
  case SDLK_w:
    CArea::AreaControl.OnExpandUp();
    CCamera::CameraControl.OnMove(0, MAP_HEIGHT*TILE_SIZE);
    for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
    {
      if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
      CEntityEdit::NPCControl.EntityList[i].Y += MAP_HEIGHT*TILE_SIZE;
    }
    break;

  case SDLK_l:
    CArea::AreaControl.OnReduceRight(); break;
  case SDLK_j:
    if (CArea::AreaControl.OnReduceLeft())
    {
      CCamera::CameraControl.OnMove(-MAP_WIDTH*TILE_SIZE, 0);
      for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
      {
        if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
        CEntityEdit::NPCControl.EntityList[i].X -= MAP_WIDTH*TILE_SIZE;
      }
    }
    break;
  case SDLK_k:
    CArea::AreaControl.OnReduceDown(); break;
  case SDLK_i:
    if (CArea::AreaControl.OnReduceUp())
    {
      CCamera::CameraControl.OnMove(0, -MAP_HEIGHT*TILE_SIZE);
      for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
      {
        if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
        CEntityEdit::NPCControl.EntityList[i].Y -= MAP_WIDTH*TILE_SIZE;
      }
    }
    break;

  default:
    break;
  }

  return true;
}

bool CEditMap::handleMakeDomain(const SDL_Point* mouse)
{
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

bool CEditMap::handlePlaceDomain(const SDL_Point* mouse)
{
  bool retval = false;
  if (CAsset::inWorkspace(mouse))
  {
    if (rClickA != NULL && rClickB != NULL)
    {
      retval = true;
      SDL_Rect dom = getTileDomain(rClickA, rClickB);
      SDL_Point clickPos = CCamera::CameraControl.GetCamRelPoint(mouse);

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

void CEditMap::resetRClick()
{
  if (rClickA != NULL)
  {
    delete rClickA;
    rClickA = NULL;
  }
  if (rClickB != NULL)
  {
    delete rClickB;
    rClickB = NULL;
  }
}

bool CEditMap::handleNewTile(const SDL_Point* mouse)
{
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

void CEditMap::placeBlock(const int& x, const int& y)
{
  if (active_TL) CArea::AreaControl.ChangeTile(x, y, &TileTL, onTiles);
  if (active_TR) CArea::AreaControl.ChangeTile(x + TILE_SIZE, y, &TileTR, onTiles);
  if (active_BL) CArea::AreaControl.ChangeTile(x, y + TILE_SIZE, &TileBL, onTiles);
  if (active_BR) CArea::AreaControl.ChangeTile(x + TILE_SIZE, y + TILE_SIZE, &TileBR, onTiles);
}

bool CEditMap::handleGetSet(const SDL_Point* mouse)
{
  // Click on "Change Tileset" button. This displays a prompt to change tilesets,
  // and the function within the loop performs a change if requested.
	using namespace mapEngine::but_tset;
  if (SDL_PointInRect(mouse, &button))
  {
    CInterrupt::appendFlag(INTRPT_CHANGE_TS);
    return true;
  }
  return false;
}

bool CEditMap::handleGetTile(const SDL_Point* mouse)
{
  // Click on "Change Tile" buttons. A display of all tiles is rendered,
  // and clicking a tile will update the active tile to use the clicked tile.
  using namespace mapEngine::but_t;

  if (SDL_PointInRect(mouse, &bg_button))
  {
      CChangeTile::PickTile.Init(tset_w, tset_h);
      CInterrupt::appendFlag(INTRPT_CHANGE_BG);
      return true;
  }
  if (SDL_PointInRect(mouse, &fg_button))
  {
      CChangeTile::PickTile.Init(tset_w, tset_h);
      CInterrupt::appendFlag(INTRPT_CHANGE_FG);
      return true;
  }
  return false;
}

bool CEditMap::handleScroll_bg(const SDL_Point* mouse, CTile* EditTile)
{
  // Click on arrow LEFT or RIGHT of active background tile.
  // Changes the active tile to previous or next index.
  using namespace mapEngine::disp_t;
  if (mouse->y >= bg_y && mouse->y < bg_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= bg_x - TILE_SIZE && mouse->x < bg_x)
    {
        if (EditTile->bg_ID > 0) EditTile->bg_ID -= 1;
        else EditTile->bg_ID = (tset_w * tset_h) - 1;
        return true;
    }
    // Right Arrow
    if (mouse->x >= bg_x + TILE_SIZE && mouse->x < bg_x + (TILE_SIZE * 2))
    {
        if (EditTile->bg_ID < (tset_w * tset_h) - 1) EditTile->bg_ID += 1;
        else EditTile->bg_ID = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_fg(const SDL_Point* mouse, CTile* EditTile)
{
  // Click on arrow LEFT or RIGHT of active foreground tile.
  // Changes the active tile to previous or next index.
  using namespace mapEngine::disp_t;
  if (mouse->y >= fg_y && mouse->y < fg_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= fg_x - TILE_SIZE && mouse->x < fg_x)
    {
        if (EditTile->fg_ID > 0) EditTile->fg_ID -= 1;
        else EditTile->fg_ID = (tset_w * tset_h) - 1;
        return true;
    }
    // Right Arrow
    if (mouse->x >= fg_x + TILE_SIZE && mouse->x < fg_x + (TILE_SIZE * 2))
    {
        if (EditTile->fg_ID < (tset_w * tset_h) - 1) EditTile->fg_ID += 1;
        else EditTile->fg_ID = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_ty(const SDL_Point* mouse, CTile* EditTile)
{
  // Click on arrow LEFT or RIGHT of active tile type.
  // Changes the active tile type to previous or next type index.
  using namespace mapEngine::disp_t;
  if (mouse->y >= ty_y && mouse->y < ty_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= ty_x - TILE_SIZE && mouse->x < ty_x)
    {
        if (EditTile->TypeID != 0) EditTile->TypeID -= 1;
        else EditTile->TypeID = TILE_TYPE_FIRE;
        return true;
    }
    // Right Arrow
    if (mouse->x >= ty_x + TILE_SIZE && mouse->x < ty_x + (TILE_SIZE * 2))
    {
        if (EditTile->TypeID != TILE_TYPE_FIRE) EditTile->TypeID += 1;
        else EditTile->TypeID = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_co(const SDL_Point* mouse, CTile* EditTile)
{
  // Click on arrow LEFT or RIGHT of active collision.
  // Changes the active collision to previous or next collision index.
  using namespace mapEngine::disp_t;
  if (mouse->y >= co_y && mouse->y < co_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= co_x - TILE_SIZE && mouse->x < co_x)
    {
        if (EditTile->CollID != 0) EditTile->CollID -= 1;
        else EditTile->CollID = SOLID_A_ML_BR;
        return true;
    }
    // Right Arrow
    if (mouse->x >= co_x + TILE_SIZE && mouse->x < co_x + (TILE_SIZE * 2))
    {
        if (EditTile->CollID != SOLID_A_ML_BR) EditTile->CollID += 1;
        else EditTile->CollID = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleRemove_bg(const SDL_Point* mouse, CTile* EditTile)
{
  // Turn the background tile off.
  using namespace mapEngine::but_rm;
  if (mouse->y >= bg_y && mouse->y < bg_y + SWITCH_SIZE)
  {
    if (mouse->x >= bg_x && mouse->x < bg_x + SWITCH_SIZE)
    {
      EditTile->bg_ID = -1;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleRemove_fg(const SDL_Point* mouse, CTile* EditTile)
{
  // Turn the foreground tile off.
  using namespace mapEngine::but_rm;
  if (mouse->y >= fg_y && mouse->y < fg_y + SWITCH_SIZE)
  {
    if (mouse->x >= fg_x && mouse->x < fg_x + SWITCH_SIZE)
    {
      EditTile->fg_ID = -1;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleOpac_ty(const SDL_Point* mouse)
{
  // Click on opacity bar for tile type overlay
  using namespace mapEngine::opac;

  if (SDL_PointInRect(mouse, &typeBar))
  {
    double barfract = (double)(mouse->x - typeBar.x) / (double)(typeBar.w - 1);
    type_alpha = MAX_RGBA * barfract;
    SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);
    return true;
  }
  return false;
}

bool CEditMap::handleOpac_co(const SDL_Point* mouse)
{
  // Click on opacity bar for tile collision overlay
  using namespace mapEngine::opac;

  if (SDL_PointInRect(mouse, &collBar))
  {
    double barfract = (double)(mouse->x - collBar.x) / (double)(collBar.w - 1);
    coll_alpha = MAX_RGBA * barfract;
    SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);
    return true;
  }
  return false;
}

bool CEditMap::handleLayers(const SDL_Point* mouse)
{
  // Click on View overlay buttons
  using namespace mapEngine::view_flip;
  if (mouse->x >= x && mouse->x < x + SWITCH_SIZE)
  {
    int Yi = y;
    int Yf = y + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (show_fg) show_fg = false;
      else show_fg = true;
      return true;
    }
    Yi = Yf + SYM_SPACING;
    Yf = Yi + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (show_ty) show_ty = false;
      else show_ty = true;
      return true;
    }
    Yi = Yf + SYM_SPACING;
    Yf = Yi + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (show_co) show_co = false;
      else show_co = true;
      return true;
    }
  }
  return false;
}

bool CEditMap::handlePlace(const SDL_Point* mouse)
{
  // Click on active tile attribute switches
  using namespace mapEngine::place_flip;
  if (mouse->x >= x && mouse->x < x + SWITCH_SIZE)
  {
    int Yi = y;
    int Yf = y + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (onTiles & ENABLE_BG) onTiles ^= ENABLE_BG;
      else onTiles |= ENABLE_BG;
      return true;
    }
    Yi = Yf + SYM_SPACING;
    Yf = Yi + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (onTiles & ENABLE_FG) onTiles ^= ENABLE_FG;
      else onTiles |= ENABLE_FG;
      return true;
    }
    Yi = Yf + SYM_SPACING;
    Yf = Yi + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (onTiles & ENABLE_TYPE) onTiles ^= ENABLE_TYPE;
      else onTiles |= ENABLE_TYPE;
      return true;
    }
    Yi = Yf + SYM_SPACING;
    Yf = Yi + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (onTiles & ENABLE_COLL) onTiles ^= ENABLE_COLL;
      else onTiles |= ENABLE_COLL;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleActTile(const SDL_Point* mouse, bool& active)
{
  using namespace mapEngine::but_act_t;

  if (!SDL_PointInRect(mouse, &button)) return false;

  active = !active;

  return true;
}

bool CEditMap::handleQuadrant_lc(const SDL_Point* mouse)
{
  using namespace mapEngine::but_quad_t;

  if (mouse->x < left_x || mouse->x >= right_x + w || mouse->y < top_y || mouse->y >= bottom_y + h)
  {
    return false;
  }

  if (mouse->y < top_y + h)
  {
    if (mouse->x < left_x + w)
    {
      // top left
      modifyTile = MODIFY_TILE_TL;
    }
    else
    {
      // top right
      modifyTile = MODIFY_TILE_TR;
    }
  }
  else
  {
    if (mouse->x < left_x + w)
    {
      // bottom left
      modifyTile = MODIFY_TILE_BL;
    }
    else
    {
      // bottom right
      modifyTile = MODIFY_TILE_BR;
    }
  }
  return true;
}

bool CEditMap::handleQuadrant_rc(const SDL_Point* mouse)
{
  using namespace mapEngine::but_quad_t;

  if (mouse->x < left_x || mouse->x >= right_x + w || mouse->y < top_y || mouse->y >= bottom_y + h)
  {
    return false;
  }

  if (mouse->y < top_y + h)
  {
    if (mouse->x < left_x + w)
    {
      // top left
      active_TL = !active_TL;
    }
    else
    {
      // top right
      active_TR = !active_TR;
    }
  }
  else
  {
    if (mouse->x < left_x + w)
    {
      // bottom left
      active_BL = !active_BL;
    }
    else
    {
      // bottom right
      active_BR = !active_BR;
    }
  }
  return true;
}
