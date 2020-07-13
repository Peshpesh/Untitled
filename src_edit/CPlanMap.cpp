#include "CPlanMap.h"

CPlanMap::CPlanMap() {
	//
}

CPlanTile* CPlanMap::GetTile(int X, int Y) {
	int ID = 0;
	ID = X / TILE_SIZE;
	ID += (MAP_WIDTH * (Y / TILE_SIZE));

	if (ID < 0 || ID >= TileList.size()) {
		return NULL;
	}
	return &TileList[ID];
}

void CPlanMap::OnLoad() {
	TileList.clear();

	CPlanTile tempTile;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			TileList.push_back(tempTile);
		}
	}
}

bool CPlanMap::OnLoad(FILE* fhandle)	{
	if (fhandle == NULL) {
		CInform::InfoControl.pushInform("---CPlanMap.Onload---\nmaps file is NULL");
		return false;
	}

	TileList.clear();

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			CPlanTile tempTile;
			if (fread(&tempTile, sizeof(struct CPlanTile), 1, fhandle) != 1) {
				CInform::InfoControl.pushInform("---CPlanMap.OnLoad---\nfailed to load tile data");
				return false;
			}
			TileList.push_back(tempTile);
		}
	}
	return true;
}

bool CPlanMap::OnSave(FILE* fhandle) {
	if (fhandle == NULL) {
		CInform::InfoControl.pushInform("---CPlanMap.OnSave---\nfailed to access maps handle");
		return false;
	}

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int ID = X + Y * MAP_WIDTH;
			if (fwrite(&TileList[ID], sizeof(struct CPlanTile), 1, fhandle) != 1) {
				CInform::InfoControl.pushInform("---CPlanMap.OnSave---\nfailed to write tile data");
				return false;
			}
		}
	}
	return true;
}

void CPlanMap::OnRender(int MapX, int MapY) {
	if (CTileset::TSControl.tileset == NULL) return;

	int tset_w = CTileset::TSControl.ts_w; // tiles
	int tset_h = CTileset::TSControl.ts_h; // tiles

	// Render surface tiles, row by row
	int ID = 0;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int TilesetX = 0, TilesetY = 0;
			if (TileList[ID].ID >= 0) {
				TilesetX = (TileList[ID].ID % tset_w) * TILE_SIZE;	// X on src texture
				TilesetY = (TileList[ID].ID / tset_w) * TILE_SIZE;	// Y on src texture
			} else {
				ID++;
				continue;
			}
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			CSurface::OnDraw(CTileset::TSControl.tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CPlanMap::OnRenderFill(int MapX, int MapY) {
	if (CTileset::TSControl.grid_tileset == NULL) return;

	int tset_w = CTileset::TSControl.grid_w; // tiles
	int tset_h = CTileset::TSControl.grid_h; // tiles
	int TilesetX = 0, TilesetY = 0;

	// Render grid fill
	int ID = 0;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			CSurface::OnDraw(CTileset::TSControl.grid_tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CPlanMap::OnRenderType(int MapX, int MapY) {
	// if (CTileset::TSControl.grid_tileset == NULL) return;
	//
	// int tset_w = CTileset::TSControl.grid_w; // tiles
	// int tset_h = CTileset::TSControl.grid_h; // tiles
	// int TilesetX = 0, TilesetY = 0;
	//
	// // Render grid fill
	// int ID = 0;
	// for (int Y = 0; Y < MAP_HEIGHT; Y++) {
	// 	for (int X = 0; X < MAP_WIDTH; X++) {
	// 		int tX = MapX + (X * TILE_SIZE);
	// 		int tY = MapY + (Y * TILE_SIZE);
	// 		CSurface::OnDraw(CTileset::TSControl.grid_tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
	// 		ID++;
	// 	}
	// }


	// if (tileset == NULL) return;
	//
	// int PixWidth;
	// int PixHeight;
	//
	// SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);
	//
	// int tset_w = PixWidth / TILE_SIZE; // tiles
	// int tset_h = PixHeight / TILE_SIZE; // tiles
	//
	// int ID = 0;
	//
	// for (int Y = 0; Y < MAP_HEIGHT; Y++) {
	// 	for (int X = 0; X < MAP_WIDTH; X++) {
	// 		if (TileList[ID].type != TILE_TYPE_NORMAL) {
	// 			int tX = MapX + (X * TILE_SIZE);
	// 			int tY = MapY + (Y * TILE_SIZE);
	// 			int TilesetX = (TileList[ID].type % tset_w) * TILE_SIZE;
	// 			int TilesetY = (TileList[ID].type / tset_w) * TILE_SIZE;
	// 			CSurface::OnDraw(tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
	// 		}
	// 		ID++;
	// 	}
	// }
}

void CPlanMap::OnRenderSolid(int MapX, int MapY) {
	// Render mask for solid tiles
	int ID = 0;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].solid) {
				int tX = MapX + (X * TILE_SIZE);
				int tY = MapY + (Y * TILE_SIZE);
				const SDL_Rect tmp_o = {tX++, tY++, TILE_SIZE, TILE_SIZE};
				const SDL_Rect tmp_i = {tX, tY, TILE_SIZE - 2, TILE_SIZE - 2};
				CAsset::drawBox(&tmp_o, &palette::white);
				CAsset::drawBox(&tmp_i, &palette::black);
			}
			ID++;
		}
	}
}

void CPlanMap::changeTile(const int& X, const int& Y, const CPlanTile& tile, const int& useTiles) {
	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
	if (useTiles & ENABLE_BG) 	TileList[ID].ID 		= tile.ID;
	if (useTiles & ENABLE_TYPE)	TileList[ID].type 	= tile.type;
	if (useTiles & ENABLE_COLL)	TileList[ID].solid 	= tile.solid;
}
