#ifndef _C_PLANMAP_H_
#define _C_PLANMAP_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CAsset.h"
#include "CTile.h"
#include "CTileset.h"
#include "CSurface.h"
#include "CInform.h"

class CPlanMap {
	std::vector<CPlanTile> TileList;

public:
	CPlanMap();
	CPlanTile* GetTile(int X, int Y);

public:
	void OnLoad();
	bool OnLoad(FILE* fhandle);
	bool OnSave(FILE* fhandle);

	void OnRenderFill(int MapX, int MapY);
	void OnRender(int MapX, int MapY);
	void OnRenderType(SDL_Texture* tileset, int MapX, int MapY);
	void OnRenderColl(SDL_Texture* tileset, int MapX, int MapY);

	void ChangeTile(int X, int Y, CPlanTile* NewTile, int useTiles);
};
#endif
