#include "CEditMap.h"

bool CEditMap::OnLClick(const SDL_Point* mouse)
{
  CTile* EditTile;
  bool* active;
  switch (modifyTile)
  {
    case MODIFY_TILE_TL: EditTile = &TileTL; active = &active_TL; break;
    case MODIFY_TILE_TR: EditTile = &TileTR; active = &active_TR; break;
    case MODIFY_TILE_BL: EditTile = &TileBL; active = &active_BL; break;
    case MODIFY_TILE_BR: EditTile = &TileBR; active = &active_BR; break;
    default: break;
  }

  if (handleInterr(mouse, EditTile)) return true;
  if (handleNewRegion(mouse)) return true;
  if (handleNewTile(mouse)) return true;
  if (handleGetSet(mouse)) return true;
  if (handleGetTile(mouse)) return true;
  if (handleScroll_bg(mouse, EditTile)) return true;
  if (handleScroll_fg(mouse, EditTile)) return true;
  if (handleScroll_ty(mouse, EditTile)) return true;
  if (handleScroll_co(mouse, EditTile)) return true;
  if (handleRemove_bg(mouse, EditTile)) return true;
  if (handleRemove_fg(mouse, EditTile)) return true;
  if (handleOpac_ty(mouse)) return true;
  if (handleOpac_co(mouse)) return true;
  if (handleLayers(mouse)) return true;
  if (handlePlace(mouse)) return true;
  if (handleActTile(mouse, *active)) return true;
  if (handleQuadrant(mouse)) return true;

	return false;
}

bool CEditMap::OnRClick(const SDL_Point* mouse)
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

bool CEditMap::handleNewRegion(const SDL_Point* mouse)
{
  bool retval = false;
  if (rClickA != NULL && rClickB != NULL)
  {
    retval = true;
<<<<<<< HEAD
    SDL_Rect dom = getTileDomain(rClickA, rClickB);
    if (SDL_PointInRect(mouse, &dom))
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
          placeQuadrant(mX, mY);
        }
      }
    }
  }
=======

    SDL_Rect newRegion = CAsset::getTileRect(rClickA, rClickB);
    newRegion.x -= CCamera::CameraControl.GetX();
    newRegion.y -= CCamera::CameraControl.GetY();
    if (SDL_PointInRect(mouse, &newRegion))
    {
      SDL_Delay(5000);
    }
  }

>>>>>>> 41a9e5df10b7910d657057d586cde90cd8e94fc4
  resetRClick();
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

bool CEditMap::handleInterr(const SDL_Point* mouse, CTile* EditTile)
{
  // Event is passed to intrpting prompts, if there are any
	if (intrpt & ~INTRPT_NONE)
	{
		if (intrpt & INTRPT_CHANGE_BG)
		{
      if (CChangeTile::PickTile.OnLClick(mouse->x, mouse->y, EditTile->bg_ID)) intrpt = INTRPT_NONE;
		}
		if (intrpt & INTRPT_CHANGE_FG)
		{
      if (CChangeTile::PickTile.OnLClick(mouse->x, mouse->y, EditTile->fg_ID)) intrpt = INTRPT_NONE;
		}
		return true;
	}
  return false;
}

bool CEditMap::handleNewTile(const SDL_Point* mouse)
{
  // Place new tiles, if click is in the workspace
  if (mouse->x < WWIDTH && mouse->y < WHEIGHT)
  {
    int mX = CCamera::CameraControl.GetX() + mouse->x;
    int mY = CCamera::CameraControl.GetY() + mouse->y;
    placeQuadrant(mX, mY);
    return true;
  }
  return false;
}

<<<<<<< HEAD
void CEditMap::placeQuadrant(const int& x, const int& y)
{
  if (active_TL) CArea::AreaControl.ChangeTile(x, y, &TileTL, onTiles);
  if (active_TR) CArea::AreaControl.ChangeTile(x + TILE_SIZE, y, &TileTR, onTiles);
  if (active_BL) CArea::AreaControl.ChangeTile(x, y + TILE_SIZE, &TileBL, onTiles);
  if (active_BR) CArea::AreaControl.ChangeTile(x + TILE_SIZE, y + TILE_SIZE, &TileBR, onTiles);
}

=======
>>>>>>> 41a9e5df10b7910d657057d586cde90cd8e94fc4
bool CEditMap::handleGetSet(const SDL_Point* mouse)
{
  // Click on "Change Tileset" button. This displays a prompt to change tilesets,
  // and the function within the loop performs a change if requested.
	using namespace but_tset;
	if (mouse->x >= x && mouse->x < x + w)
	{
		if (mouse->y >= y && mouse->y < y + h)
		{
			// if ((Main_Tileset = CUI::UIControl.OnChange(Map_Interface, Tileset_Path)) != NULL)
			// {
			// 	CArea::AreaControl.ChangeSet(Main_Tileset);
			// 	TileTL.bg_ID = 0;
			// 	QueryTileset();
			return true;
			// }
		}
	}
  return false;
}

bool CEditMap::handleGetTile(const SDL_Point* mouse)
{
  // Click on "Change Tile" buttons. A display of all tiles is rendered,
  // and clicking a tile will update the active tile to use the clicked tile.
  using namespace but_t;
  if (mouse->x >= bg_x && mouse->x < bg_x + bg_w)
  {
    if (mouse->y >= bg_y && mouse->y < bg_y + bg_h)
    {
      CChangeTile::PickTile.Init(tset_w, tset_h);
      intrpt = INTRPT_CHANGE_BG;
      return true;
    }
  }
  if (mouse->x >= fg_x && mouse->x < fg_x + fg_w)
  {
    if (mouse->y >= fg_y && mouse->y < fg_y + fg_h)
    {
      CChangeTile::PickTile.Init(tset_w, tset_h);
      intrpt = INTRPT_CHANGE_FG;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_bg(const SDL_Point* mouse, CTile* EditTile)
{
  // Click on arrow LEFT or RIGHT of active background tile.
  // Changes the active tile to previous or next index.
  using namespace disp_t;
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
  using namespace disp_t;
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
  using namespace disp_t;
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
  using namespace disp_t;
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
  using namespace but_rm;
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
  using namespace but_rm;
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
  using namespace opac;
  if (mouse->y >= ty_y && mouse->y < ty_y + h)
  {
    if (mouse->x >= x && mouse->x < x + w)
    {
      double barfract = (double)(mouse->x - x) / (double)(w - 1);
      type_alpha = MAX_RGBA * barfract;
      SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);
      return true;
    }
  }
  return false;
}

bool CEditMap::handleOpac_co(const SDL_Point* mouse)
{
  // Click on opacity bar for tile collision overlay
  using namespace opac;
  if (mouse->y >= co_y && mouse->y < co_y + h)
  {
    if (mouse->x >= x && mouse->x < x + w)
    {
      double barfract = (double)(mouse->x - x) / (double)(w - 1);
      coll_alpha = MAX_RGBA * barfract;
      SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);
      return true;
    }
  }
  return false;
}

bool CEditMap::handleLayers(const SDL_Point* mouse)
{
  // Click on View overlay buttons
  using namespace view_flip;
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
  using namespace place_flip;
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
  using namespace but_act_t;

  if (mouse->x < x || mouse->x >= x + w || mouse->y < y || mouse->y >= y + h)
  {
    return false;
  }

  active = !active;

  return true;
}

bool CEditMap::handleQuadrant(const SDL_Point* mouse)
{
  using namespace but_quad_t;

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
