#ifndef _CMAP_H_
#define _CMAP_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CTile.h"
#include "CSurface.h"

class CMap {
public:
	SDL_Texture* Tex_Tileset;	// Pointer to the map tileset texture

private:
	std::vector<CTile> TileList;

public:
	CMap();
	CTile* GetTile(int X, int Y);


public:
	bool OnLoad(char const* File);
	void OnLoad();

	void OnRender(int MapX, int MapY, bool bg);
	void OnRenderType(SDL_Texture* tileset, int MapX, int MapY);
	void OnRenderColl(SDL_Texture* tileset, int MapX, int MapY);
	void ViewMap(SDL_Texture* ui, int Xo, int Yo);

	void ChangeTile(int X, int Y, int tile, int fore, int type, int coll, int usetiles);

	void SaveMap(int ID, char const* areaname);
};
#endif
