#include "CMap.h"

CMap::CMap() {
	//
}

CTile* CMap::GetTile(int X, int Y) {
	int ID = 0;
	ID = X / TILE_SIZE;
	ID += (MAP_WIDTH * (Y / TILE_SIZE));

	if (ID < 0 || ID >= TileList.size()) {
		return NULL;
	}
	return &TileList[ID];
}

void CMap::OnLoad() {
	TileList.clear();

	CTile tempTile;
	tempTile.bg_ID = -1;
	tempTile.fg_ID = -1;
	tempTile.TypeID = TILE_TYPE_NORMAL;
	tempTile.CollID = SOLID_NONE;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			TileList.push_back(tempTile);
		}
	}
}

bool CMap::OnLoad(FILE* fhandle)	{
	if (fhandle == NULL) {
		CInform::InfoControl.pushInform("---CMAP.Onload---\nmaps file is NULL");
		return false;
	}

	TileList.clear();

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			CTile tempTile;
			if (fread(&tempTile, sizeof(class CTile), 1, fhandle) != 1) {
				CInform::InfoControl.pushInform("---CMAP.NewLoad---\nfailed to load binary tile data");
				return false;
			}
			TileList.push_back(tempTile);
		}
	}
	return true;
}

bool CMap::OnSave(FILE* fhandle) {
	if (fhandle == NULL) {
		CInform::InfoControl.pushInform("---CMAP.NewSave---\nfailed to access maps handle");
		return false;
	}

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int ID = X + Y * MAP_WIDTH;
			if (fwrite(&TileList[ID], sizeof(class CTile), 1, fhandle) != 1) {
				CInform::InfoControl.pushInform("---CMAP.NewSave---\nfailed to write binary tile data");
				return false;
			}
		}
	}
	return true;
}

void CMap::OnRenderFill(int MapX, int MapY) {
	const SDL_Point* emptyCol = &palette::dark_gray;
	SDL_Rect dstmap = {MapX, MapY, MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE};
	CAsset::drawBoxFill(&dstmap, emptyCol);
}

void CMap::OnRender(int MapX, int MapY, bool bg) {
	if (CTileset::TSControl.tileset == NULL) return;

	int tset_w = CTileset::TSControl.ts_w; // tiles
	int tset_h = CTileset::TSControl.ts_h; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int TilesetX = 0, TilesetY = 0;
			if (bg && TileList[ID].bg_ID >= 0) {
				TilesetX = (TileList[ID].bg_ID % tset_w) * TILE_SIZE;
				TilesetY = (TileList[ID].bg_ID / tset_w) * TILE_SIZE;
			}
			else if (!bg && TileList[ID].fg_ID >= 0) {
				TilesetX = (TileList[ID].fg_ID % tset_w) * TILE_SIZE;
				TilesetY = (TileList[ID].fg_ID / tset_w) * TILE_SIZE;
			}
			else {
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

void CMap::OnRenderType(SDL_Texture* tileset, int MapX, int MapY) {
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			if (TileList[ID].TypeID != TILE_TYPE_NORMAL) {
				int tX = MapX + (X * TILE_SIZE);
				int tY = MapY + (Y * TILE_SIZE);
				int TilesetX = (TileList[ID].TypeID % tset_w) * TILE_SIZE;
				int TilesetY = (TileList[ID].TypeID / tset_w) * TILE_SIZE;
				CSurface::OnDraw(tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			}
			ID++;
		}
	}
}

void CMap::OnRenderColl(SDL_Texture* tileset, int MapX, int MapY) {
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
		for (int X = 0; X < MAP_WIDTH; X++) {
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			int TilesetX = ((TileList[ID].CollID) % tset_w) * TILE_SIZE;
			int TilesetY = ((TileList[ID].CollID) / tset_w) * TILE_SIZE;
			CSurface::OnDraw(tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::ChangeTile(int X, int Y, CTile* NewTile, int useTiles) {
	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
	if (useTiles & ENABLE_BG) 	TileList[ID].bg_ID = NewTile->bg_ID;
	if (useTiles & ENABLE_FG) 	TileList[ID].fg_ID = NewTile->fg_ID;
	if (useTiles & ENABLE_TYPE)	TileList[ID].TypeID = NewTile->TypeID;
	if (useTiles & ENABLE_COLL)	TileList[ID].CollID = NewTile->CollID;
}

// bool CMap::OnLoad(char const* File) {
// 	FILE* FileHandle = fopen(File, "r");
//
// 	if (FileHandle == NULL) {
// 		CInform::InfoControl.pushInform("---CMAP.Onload---\nfailed to open map file");
// 		return false;
// 	}
//
// 	TileList.clear();
//
// 	for (int Y = 0; Y < MAP_HEIGHT; Y++)
// 	{
// 		for (int X = 0; X < MAP_WIDTH; X++)
// 		{
// 			CTile tempTile;
// 			fscanf(FileHandle, "%d:%d:%d:%d ", &tempTile.bg_ID, &tempTile.fg_ID, &tempTile.TypeID, &tempTile.CollID);
// 			TileList.push_back(tempTile);
// 		}
// 		fscanf(FileHandle, "\n");
// 	}
// 	fclose(FileHandle);
// 	return true;
// }

// bool CMap::SaveMap(int ID, char const* areaname) {
// 	int TensDigit = ID / 10;
// 	int OnesDigit = ID % 10;
// 	int zeroASCII = 48;
//
// 	// Add 48, as 48 is the ASCII decimal code for zero ('0')
// 	char ID_ASCII[] = { (char)(TensDigit + zeroASCII), (char)(OnesDigit + zeroASCII), '\0'};
//
// 	char pre[] = "../data/maps/";
// 	char ext[] = ".map";
// 	char* filename = new char[std::strlen(areaname) + std::strlen(pre) + std::strlen(ext) + std::strlen(ID_ASCII) + 1];
// 	std::strcpy(filename, pre);
// 	std::strcat(filename, areaname);
// 	std::strcat(filename, ID_ASCII);
// 	std::strcat(filename, ext);
//
// 	FILE* FileHandle = fopen(filename, "w");
// 	if (FileHandle == NULL) {
// 		delete filename;
// 		return false;
// 	}
//
// 	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
// 		for (int X = 0; X < MAP_WIDTH; X++) {
// 			int ID = X + Y * MAP_WIDTH;
// 			fprintf(FileHandle, "%d:%d:%d:%d ", TileList[ID].bg_ID, TileList[ID].fg_ID, TileList[ID].TypeID, TileList[ID].CollID);
// 		}
// 		fprintf(FileHandle, "\n");
// 	}
// 	fclose(FileHandle);
// 	delete filename;
// 	return true;
// }

// void CMap::ViewMap(SDL_Texture* ui, int Xo, int Yo) {
// 	if (ui == NULL)	return;
//
// 	int VTileSize = 2; // Pixels
// 	int ID = 0;
//
// 	for (int Y = 0; Y < MAP_HEIGHT; Y++) {
// 		for (int X = 0; X < MAP_WIDTH; X++) {
// 			int VTileY = 350; // 350 px is where the 2 x 2 tiles start for the editor.
// 			switch (TileList[ID].TypeID) {
// 					case TILE_TYPE_NORMAL: VTileY += VTileSize * 3; break;
// 					case TILE_TYPE_WATER: VTileY += VTileSize * 2; break;
// 					case TILE_TYPE_ICE: VTileY += VTileSize * 4; break;
// 					case TILE_TYPE_FIRE: VTileY += VTileSize * 4; break;
// 					default: break;
// 			}
// 			CSurface::OnDraw(ui, Xo + X * VTileSize, Yo + Y * VTileSize, 0, VTileY, VTileSize, VTileSize);
// 			ID++;
// 		}
// 	}
// }
