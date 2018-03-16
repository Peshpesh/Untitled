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
	// SDL_Texture* Tex_Tileset;	// Pointer to the map tileset texture

private:
	std::vector<CTile> TileList;

public:
	CMap();
	CTile* GetTile(int X, int Y);


public:
	bool OnLoad(char const* File);
	void OnLoad();

	void OnRender(SDL_Renderer* renderer, int MapX, int MapY, bool bg);

	void ViewMap(SDL_Renderer* renderer, SDL_Texture* ui, int Xo, int Yo);

	void ChangeTile(int X, int Y, int tile, int fore, int type, int coll);

};
#endif
