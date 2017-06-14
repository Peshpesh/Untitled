#include "CEditMap.h"

bool CEditMap::OnEvent(SDL_Point* mouse)
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

bool CEditMap::handleInterr(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleNewTile(SDL_Point* mouse)
{
  // Place new tiles, if click is in the workspace
  if (mouse->x < WWIDTH && mouse->y < WHEIGHT)
  {
    int mX = CCamera::CameraControl.GetX() + mouse->x;
    int mY = CCamera::CameraControl.GetY() + mouse->y;
    if (active_TL) CArea::AreaControl.ChangeTile(mX, mY, &TileTL, onTiles);
    if (active_TR) CArea::AreaControl.ChangeTile(mX + TILE_SIZE, mY, &TileTR, onTiles);
    if (active_BL) CArea::AreaControl.ChangeTile(mX, mY + TILE_SIZE, &TileBL, onTiles);
    if (active_BR) CArea::AreaControl.ChangeTile(mX + TILE_SIZE, mY + TILE_SIZE, &TileBR, onTiles);

    return true;
  }
  return false;
}

bool CEditMap::handleGetSet(SDL_Point* mouse)
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

bool CEditMap::handleGetTile(SDL_Point* mouse)
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

bool CEditMap::handleScroll_bg(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleScroll_fg(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleScroll_ty(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleScroll_co(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleRemove_bg(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleRemove_fg(SDL_Point* mouse, CTile* EditTile)
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

bool CEditMap::handleOpac_ty(SDL_Point* mouse)
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

bool CEditMap::handleOpac_co(SDL_Point* mouse)
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

bool CEditMap::handleLayers(SDL_Point* mouse)
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

bool CEditMap::handlePlace(SDL_Point* mouse)
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

bool CEditMap::handleActTile(SDL_Point* mouse, bool& active)
{
  using namespace but_act_t;

  if (mouse->x < x || mouse->x >= x + w || mouse->y < y || mouse->y >= y + h)
  {
    return false;
  }

  active = !active;

  return true;
}

bool CEditMap::handleQuadrant(SDL_Point* mouse)
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
