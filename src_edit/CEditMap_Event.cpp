#include "CEditMap.h"

using namespace map_editor;

bool CEditMap::OnEvent(SDL_Point* mouse)
{
  if (handleInterr(mouse)) return true;
  if (handleNewTile(mouse)) return true;
  if (handleGetSet(mouse)) return true;
  if (handleGetTile(mouse)) return true;
  if (handleScroll_bg(mouse)) return true;
  if (handleScroll_fg(mouse)) return true;
  if (handleScroll_ty(mouse)) return true;
  if (handleScroll_co(mouse)) return true;
  if (handleRemove_bg(mouse)) return true;
  if (handleRemove_fg(mouse)) return true;
  if (handleOpac_ty(mouse)) return true;
  if (handleOpac_co(mouse)) return true;
  if (handleLayers(mouse)) return true;
  if (handlePlace(mouse)) return true;

	return false;
}

bool CEditMap::handleInterr(SDL_Point* mouse)
{
  // Event is passed to intrpting prompts, if there are any
	if (intrpt & ~INTRPT_NONE)
	{
		if (intrpt & INTRPT_CH_BTILE)
		{
			if (CChangeTile::PickTile.OnLClick(mouse->x, mouse->y, active_bg)) intrpt = INTRPT_NONE;
		}
		if (intrpt & INTRPT_CH_FTILE)
		{
			if (CChangeTile::PickTile.OnLClick(mouse->x, mouse->y, active_fg)) intrpt = INTRPT_NONE;
		}
		return true;
	}
  return false;
}

bool CEditMap::handleNewTile(SDL_Point* mouse)
{
  // Place new tile, if click is in the workspace
  if (mouse->x < WWIDTH && mouse->y < WHEIGHT)
  {
    int mX = CCamera::CameraControl.GetX() + mouse->x;
    int mY = CCamera::CameraControl.GetY() + mouse->y;
    CArea::AreaControl.ChangeTile(mX, mY,	no_bg ? -1 : active_bg, no_fg ? -1 : active_fg, active_type, active_coll, onTiles);
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
			// 	active_bg = 0;
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
      intrpt = INTRPT_CH_BTILE;
      return true;
    }
  }
  if (mouse->x >= fg_x && mouse->x < fg_x + fg_w)
  {
    if (mouse->y >= fg_y && mouse->y < fg_y + fg_h)
    {
      CChangeTile::PickTile.Init(tset_w, tset_h);
      intrpt = INTRPT_CH_FTILE;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_bg(SDL_Point* mouse)
{
  // Click on arrow LEFT or RIGHT of active background tile.
  // Changes the active tile to previous or next index.
  using namespace disp_t;
  if (mouse->y >= bg_y && mouse->y < bg_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= bg_x - TILE_SIZE && mouse->x < bg_x)
    {
        if (active_bg != 0) active_bg -= 1;
        else active_bg = (tset_w * tset_h) - 1;
        return true;
    }
    // Right Arrow
    if (mouse->x >= bg_x + TILE_SIZE && mouse->x < bg_x + (TILE_SIZE * 2))
    {
        if (active_bg != (tset_w * tset_h) - 1) active_bg += 1;
        else active_bg = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_fg(SDL_Point* mouse)
{
  // Click on arrow LEFT or RIGHT of active foreground tile.
  // Changes the active tile to previous or next index.
  using namespace disp_t;
  if (mouse->y >= fg_y && mouse->y < fg_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= fg_x - TILE_SIZE && mouse->x < fg_x)
    {
        if (active_fg != 0) active_fg -= 1;
        else active_fg = (tset_w * tset_h) - 1;
        return true;
    }
    // Right Arrow
    if (mouse->x >= fg_x + TILE_SIZE && mouse->x < fg_x + (TILE_SIZE * 2))
    {
        if (active_fg != (tset_w * tset_h) - 1) active_fg += 1;
        else active_fg = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_ty(SDL_Point* mouse)
{
  // Click on arrow LEFT or RIGHT of active tile type.
  // Changes the active tile type to previous or next type index.
  using namespace disp_t;
  if (mouse->y >= ty_y && mouse->y < ty_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= ty_x - TILE_SIZE && mouse->x < ty_x)
    {
        if (active_type != 0) active_type -= 1;
        else active_type = TILE_TYPE_FIRE;
        return true;
    }
    // Right Arrow
    if (mouse->x >= ty_x + TILE_SIZE && mouse->x < ty_x + (TILE_SIZE * 2))
    {
        if (active_type != TILE_TYPE_FIRE) active_type += 1;
        else active_type = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleScroll_co(SDL_Point* mouse)
{
  // Click on arrow LEFT or RIGHT of active collision.
  // Changes the active collision to previous or next collision index.
  using namespace disp_t;
  if (mouse->y >= co_y && mouse->y < co_y + TILE_SIZE)
  {
    // Left Arrow
    if (mouse->x >= co_x - TILE_SIZE && mouse->x < co_x)
    {
        if (active_coll != 0) active_coll -= 1;
        else active_coll = SOLID_A_ML_BR;
        return true;
    }
    // Right Arrow
    if (mouse->x >= co_x + TILE_SIZE && mouse->x < co_x + (TILE_SIZE * 2))
    {
        if (active_coll != SOLID_A_ML_BR) active_coll += 1;
        else active_coll = 0;
        return true;
    }
  }
  return false;
}

bool CEditMap::handleRemove_bg(SDL_Point* mouse)
{
  // Click on background activity switch.
  // Turn the background tile on/off.
  using namespace rm_flip;
  if (mouse->y >= bg_y && mouse->y < bg_y + SWITCH_SIZE)
  {
    if (mouse->x >= bg_x && mouse->x < bg_x + SWITCH_SIZE)
    {
      if (!no_bg) no_bg = true;
      else no_bg = false;
      return true;
    }
  }
  return false;
}

bool CEditMap::handleRemove_fg(SDL_Point* mouse)
{
  // Click on foreground activity switch.
  // Turn the foreground tile on/off.
  using namespace rm_flip;
  if (mouse->y >= fg_y && mouse->y < fg_y + SWITCH_SIZE)
  {
    if (mouse->x >= fg_x && mouse->x < fg_x + SWITCH_SIZE)
    {
      if (no_fg) no_fg = false;
      else no_fg = true;
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
      if (onTiles & ENABLE_BTILE) onTiles ^= ENABLE_BTILE;
      else onTiles |= ENABLE_BTILE;
      return true;
    }
    Yi = Yf + SYM_SPACING;
    Yf = Yi + SWITCH_SIZE;
    if (mouse->y >= Yi && mouse->y < Yf)
    {
      if (onTiles & ENABLE_FTILE) onTiles ^= ENABLE_FTILE;
      else onTiles |= ENABLE_FTILE;
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
