#include "CMap.h"

CMap_Tileset CMap::Tileset;

CMap::CMap() {
	//
}

CTile* CMap::GetTile(int X, int Y) {
	int ID = 0;
	ID = X / TILE_SIZE;
	ID += (MAP_WIDTH * (Y / TILE_SIZE));

	if (ID < 0 || ID >= TileList.size())
	{
		return NULL;
	}
	return &TileList[ID];
}

bool CMap::Load(FILE* fhandle) {
	if (fhandle == NULL) {
		// CInform::InfoControl.pushInform("---CMAP.Onload---\nmaps file is NULL");
		return false;
	}

	TileList.clear();

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			CTile tempTile;
			if (fread(&tempTile, sizeof(class CTile), 1, fhandle) != 1) {
				// CInform::InfoControl.pushInform("---CMAP.NewLoad---\nfailed to load binary tile data");
				return false;
			}
			TileList.push_back(tempTile);
		}
	}
	return true;
}

void CMap::OnRender(int MapX, int MapY, bool bg)
{
	// if (CTileset::TSControl.tileset == NULL) return;
	//
	// int tset_w = CTileset::TSControl.ts_w; // tiles
	// int tset_h = CTileset::TSControl.ts_h; // tiles

	if (Tileset.img == NULL) return;
	int tset_w = Tileset.w; // tiles
	int tset_h = Tileset.h; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int TilesetX = 0, TilesetY = 0;
			if (bg && TileList[ID].bg_ID >= 0)
			{
				TilesetX = (TileList[ID].bg_ID % Tileset.w) * TILE_SIZE;
				TilesetY = (TileList[ID].bg_ID / Tileset.w) * TILE_SIZE;
			}
			else if (!bg && TileList[ID].fg_ID >= 0)
			{
				TilesetX = (TileList[ID].fg_ID % Tileset.w) * TILE_SIZE;
				TilesetY = (TileList[ID].fg_ID / Tileset.w) * TILE_SIZE;
			}
			else
			{
				ID++;
				continue;
			}
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			CSurface::OnDraw(Tileset.img, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

// void CMap::ChangeTile(int X, int Y, int tile, int fore, int type, int coll)
// {
// 	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
// 	TileList[ID].TileID = tile;
// 	TileList[ID].ForeID = fore;
// 	TileList[ID].TypeID = type;
// 	TileList[ID].CollID = coll;
// }
