#ifndef _C_MAP_H_
#define _C_MAP_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CAsset.h"
#include "CTile.h"
#include "CTileset.h"
#include "CSurface.h"
#include "CInform.h"

class CMap {
	std::vector<CTile> TileList;

public:
	CMap();
	CTile* GetTile(int X, int Y);

public:
	void OnLoad();
	bool OnLoad(FILE* fhandle);
	bool OnSave(FILE* fhandle);

	void OnRenderFill(int MapX, int MapY);
	void OnRender(int MapX, int MapY, bool bg);
	void OnRenderType(SDL_Texture* tileset, int MapX, int MapY);
	void OnRenderColl(SDL_Texture* tileset, int MapX, int MapY);

	void ChangeTile(int X, int Y, CTile* NewTile, int useTiles);
	// void ViewMap(SDL_Texture* ui, int Xo, int Yo);
	// bool OnLoad(char const* File);
	// bool SaveMap(int ID, char const* areaname);
};
#endif
