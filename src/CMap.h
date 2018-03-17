#ifndef _C_MAP_H_
#define _C_MAP_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CTile.h"
#include "CSurface.h"

struct CMap_Tileset {
	SDL_Texture* img;
	int w;
	int h;
};

class CMap {
private:
	std::vector<CTile> TileList;

public:
	static CMap_Tileset Tileset;

	CMap();
	CTile* GetTile(int X, int Y);

public:
	bool Load(FILE* fhandle);

	void OnRender(int MapX, int MapY, bool bg);
};
#endif
