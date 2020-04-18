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
			if (fread(&tempTile, sizeof(class CPlanTile), 1, fhandle) != 1) {
				CInform::InfoControl.pushInform("---CPlanMap.NewLoad---\nfailed to load binary tile data");
				return false;
			}
			TileList.push_back(tempTile);
		}
	}
	return true;
}

bool CPlanMap::OnSave(FILE* fhandle) {
	if (fhandle == NULL) {
		CInform::InfoControl.pushInform("---CPlanMap.NewSave---\nfailed to access maps handle");
		return false;
	}

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int ID = X + Y * MAP_WIDTH;
			if (fwrite(&TileList[ID], sizeof(class CPlanTile), 1, fhandle) != 1) {
				CInform::InfoControl.pushInform("---CPlanMap.NewSave---\nfailed to write binary tile data");
				return false;
			}
		}
	}
	return true;
}

void CPlanMap::OnRenderFill(int MapX, int MapY) {
	const SDL_Point* emptyCol = &palette::dark_gray;
	SDL_Rect dstmap = {MapX, MapY, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE};
	CAsset::drawBoxFill(&dstmap, emptyCol);
}

void CPlanMap::OnRender(int MapX, int MapY) {
	if (CTileset::TSControl.tileset == NULL) return;

	int tset_w = CTileset::TSControl.ts_w; // tiles
	int tset_h = CTileset::TSControl.ts_h; // tiles

	// Render surface tiles, row by row.
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

void CPlanMap::OnRenderType(SDL_Texture* tileset, int MapX, int MapY) {
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].type != TILE_TYPE_NORMAL) {
				int tX = MapX + (X * TILE_SIZE);
				int tY = MapY + (Y * TILE_SIZE);
				int TilesetX = (TileList[ID].type % tset_w) * TILE_SIZE;
				int TilesetY = (TileList[ID].type / tset_w) * TILE_SIZE;
				CSurface::OnDraw(tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			}
			ID++;
		}
	}
}

void CPlanMap::OnRenderColl(SDL_Texture* tileset, int MapX, int MapY) {
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;
	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].solid) {
				int tX = MapX + (X * TILE_SIZE);
				int tY = MapY + (Y * TILE_SIZE);
				const SDL_Rect tmp = {tX, tY, TILE_SIZE, TILE_SIZE};
				CAsset::drawBox(&tmp, &palette::red);
			}
			ID++;
		}
	}
}

void CPlanMap::ChangeTile(int X, int Y, CPlanTile* NewTile, int useTiles) {
	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
	if (useTiles & ENABLE_BG) 	TileList[ID].ID 		= NewTile->ID;
	if (useTiles & ENABLE_TYPE)	TileList[ID].type 	= NewTile->type;
	if (useTiles & ENABLE_COLL)	TileList[ID].solid 	= NewTile->solid;
}
