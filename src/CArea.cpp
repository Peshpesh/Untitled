#include "CArea.h"

CArea CArea::control;

CArea::CArea() {
	OnInit();
}

void CArea::OnInit() {
	MapList.clear();
	AreaHeight = AreaWidth = 1;
	tileset_ID = -1;	 // will want to change this to some tileset used on title screen
	location_ID = -1;

	CMap tempMap;
	// tempMap.OnLoad();

	MapList.push_back(tempMap);
}

bool CArea::Load(const int& location_ID) {
	std::string abbrname = CLocation::getAbbrname(location_ID);
	if (abbrname.empty()) return false;

	// try to load area/maps
  std::string fpath = "../data/maps/";
  std::string ext = ".area";
  std::string fname = fpath + std::string(abbrname) + ext;

	FILE* FileHandle = fopen(fname.c_str(), "rb");
	if (FileHandle == NULL) {
		// ERROR: failed to open .area file
		return false;
	}

	MapList.clear();
	this->location_ID = location_ID;

	// Grab the ID of the tileset for the area
	short setID;
	fread(&setID, sizeof(short), 1, FileHandle);
	if (setID != tileset_ID) {
		// load new tileset
		if (!ChangeTileset(setID)) {
			// ERROR: failed to change tileset image
		}
	}

	// Grab AreaWidth & AreaHeight
	fread(&AreaWidth, sizeof(int), 1, FileHandle);
	fread(&AreaHeight, sizeof(int), 1, FileHandle);

	for (int X = 0; X < AreaWidth; X++) {
		for (int Y = 0; Y < AreaHeight; Y++) {
			CMap tempMap;
			if (tempMap.Load(FileHandle) == false) {
				fclose(FileHandle);
				return false;
			}
			MapList.push_back(tempMap);
		}
	}
	fclose(FileHandle);
	return true;
}

bool CArea::ChangeTileset(const short& fID) {
	using namespace Tileset;

	if (fID < 0 || fID >= num) {
		// invalid tileset ID
		return false;
	}

	SDL_Texture* try_surf = NULL;
	std::string filepath = path + name[fID] + extension;

	if ((try_surf = CSurface::OnLoad(filepath.c_str())) != 0) {
		SDL_DestroyTexture(CMap::Tileset.img);
		CMap::Tileset.img = try_surf;
		CAsset::queryTileDims(CMap::Tileset.img, CMap::Tileset.w, CMap::Tileset.h);
		tileset_ID = fID;
	}
	else {
		// ERROR: failed to load tileset image
		return false;
	}
	return true;
}

void CArea::GetDims(int& mW, int& mH) {
	mW = AreaWidth;
	mH = AreaHeight;
}

CMap* CArea::GetMap(int X, int Y) {
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int ID = X / MapWidth;
	ID += ((Y / MapHeight) * AreaWidth);

	if (ID < 0 || ID >= MapList.size()) return NULL;

	return &MapList[ID];
}

CTile* CArea::GetTile(int X, int Y) {
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	CMap* Map = GetMap(X, Y);

	if (Map == NULL) return NULL;

	X = X % MapWidth;
	Y = Y % MapHeight;
	return Map->GetTile(X, Y);
}

// void CArea::OnLoop() {
// 	if (CTransition::control.activated) {
//
// 	}
// }

void CArea::OnRender(int CameraX, int CameraY, bool bg) {
	int MapWidth = MAP_WIDTH * TILE_SIZE; // pixels
	int MapHeight = MAP_HEIGHT * TILE_SIZE; // pixels

	int FirstID = -CameraX / MapWidth;
	FirstID = FirstID + ((-CameraY / MapHeight) * AreaWidth);

	int maxMaps = 4;
	int loopMax = (maxMaps <= MapList.size()) ? maxMaps : MapList.size();

	for (int i = 0; i < loopMax; i++)
	{
		int ID = FirstID + ((i / 2) * AreaWidth) + (i % 2);
		if (ID < 0 || ID >= MapList.size()) continue;

		int X = ((ID % AreaWidth) * MapWidth) + CameraX;
		int Y = ((ID / AreaWidth) * MapHeight) + CameraY;

		MapList[ID].OnRender(X, Y, bg);
	}
}

void CArea::ShowAreaMap() {

}

// void CArea::ChangeTile(int X, int Y, CTile* NewTile, int useTiles) {
// 	if (X < 0 || Y < 0 || X >= (AreaWidth * MAP_WIDTH * TILE_SIZE) || Y >= (AreaHeight * MAP_HEIGHT * TILE_SIZE))
// 		return;
//
// 	int mapWidth = MAP_WIDTH * TILE_SIZE;
// 	int mapHeight = MAP_HEIGHT * TILE_SIZE;
// 	int ID = (X / mapWidth) + (Y / mapHeight) * AreaWidth;
// 	MapList[ID].ChangeTile(X % mapWidth, Y % mapHeight, NewTile, useTiles);
// }

void CArea::OnCleanup() {
	MapList.clear();
}
