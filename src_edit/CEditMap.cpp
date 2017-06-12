#include "CEditMap.h"

CEditMap CEditMap::MapEditor;

CEditMap::CEditMap()
{
  Main_Tileset = NULL;    // The actual tileset in use
  Type_Tileset = NULL;    // Tileset showing tile type
  Coll_Tileset = NULL;    // Tileset showing collision type

	no_bg = false;
	no_fg = true;
	show_fg = show_ty = show_co = true;
	type_alpha = 85;
	coll_alpha = 125;
	type_w = type_h = tset_w = tset_h = 0;

  onTiles = ENABLE_BG | ENABLE_FG | ENABLE_TYPE | ENABLE_COLL;
  intrpt = 0;

  ActiveTileTL.bg_ID = ActiveTileTL.fg_ID = 0;
  ActiveTileTR.bg_ID = ActiveTileTR.fg_ID = 0;
  ActiveTileBL.bg_ID = ActiveTileBL.fg_ID = 0;
  ActiveTileBR.bg_ID = ActiveTileBR.fg_ID = 0;
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
