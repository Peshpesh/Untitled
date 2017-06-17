#include "CEditMap.h"

CEditMap CEditMap::MapEditor;
// SDL_Point* CEditMap::shadowColor = NULL;

CEditMap::CEditMap()
{
  Main_Tileset = NULL;    // The actual tileset in use
  Type_Tileset = NULL;    // Tileset showing tile type
  Coll_Tileset = NULL;    // Tileset showing collision type

  TileTL.bg_ID = TileTL.fg_ID = -1;
  TileTR.bg_ID = TileTR.fg_ID = -1;
  TileBL.bg_ID = TileBL.fg_ID = -1;
  TileBR.bg_ID = TileBR.fg_ID = -1;

  active_TL = true;
  active_TR = false;
  active_BL = false;
  active_BR = false;

  modifyTile = MODIFY_TILE_TL;
  shadowColor = &color::light_blue;
  shadow_w = 2;

  rClickA = NULL;
  rClickB = NULL;
  flexAreaColor = &color::yellow;
  fixAreaColor = &color::red;
  hoverAreaColor = &color::light_red;
  rc_area_w = 1;

	show_fg = show_ty = show_co = true;
	type_alpha = 85;
	coll_alpha = 125;
	type_w = type_h = tset_w = tset_h = 0;

  onTiles = ENABLE_BG | ENABLE_FG | ENABLE_TYPE | ENABLE_COLL;

  intrpt = 0;
}

bool CEditMap::OnInit()
{
  if ((Main_Tileset = CSurface::OnLoad("../res/tile/default.png")) == NULL)
  {
    return false;
  }

  int PixWidth, PixHeight;
  SDL_QueryTexture(Main_Tileset, NULL, NULL, &PixWidth, &PixHeight);
  tset_w = PixWidth / TILE_SIZE;
  tset_h = PixHeight / TILE_SIZE;

  if ((Type_Tileset = CSurface::OnLoad("../res_edit/types.png")) == NULL)
  {
    return false;
  }

  SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);
  SDL_QueryTexture(Type_Tileset, NULL, NULL, &PixWidth, &PixHeight);
  type_w = PixWidth / TILE_SIZE;
  type_h = PixHeight / TILE_SIZE;

  if ((Coll_Tileset = CSurface::OnLoad("../res_edit/slopes.png")) == NULL)
  {
    return false;
  }

  SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);
  SDL_QueryTexture(Coll_Tileset, NULL, NULL, &PixWidth, &PixHeight);
  coll_w = PixWidth / TILE_SIZE;
  coll_h = PixHeight / TILE_SIZE;

  if (CArea::AreaControl.OnLoad(Main_Tileset) == false)
		return false;

  return true;
}

SDL_Rect CEditMap::getTileDomain(const SDL_Point* A, const SDL_Point* B)
{
  // First, this takes in points A and B ("A" being the initial point,
  // "B" being the terminal) and fetches the smallest box that contains both
  // points AND has width and height that are multiples of TILE_SIZE.
  // At this point, the box contains all tiles that "collide" with a box
  // drawn from points A to B.
  // Finally, the box is expanded (if necessary) to encapsulate not only the
  // aforementioned tiles, but ALSO TILES THAT WOULD BE PLACED if we tried to
  // issue a placement (left-click) on every tile in the box. This makes it so
  // the domain also contains active tiles that are not oriented top-left in
  // the 2 x 2 block settings.

  SDL_Rect domain;

  if (A == NULL || B == NULL) return domain;

  domain = CAsset::getTileRect(A, B);

  if (active_TR || active_BR)
  {
    int tW = domain.w / TILE_SIZE;
    domain.w += TILE_SIZE * (tW % 2);
    if (B->x < A->x) domain.x -= TILE_SIZE * (tW % 2);
  }

  if (active_BL || active_BR)
  {
    int tH = domain.h / TILE_SIZE;
    domain.h += TILE_SIZE * (tH % 2);
    if (B->y < A->y) domain.y -= TILE_SIZE * (tH % 2);
  }

  return domain;
}

void CEditMap::OnTerminate()
{
  SDL_DestroyTexture(Main_Tileset);
  SDL_DestroyTexture(Type_Tileset);
  SDL_DestroyTexture(Coll_Tileset);
}
