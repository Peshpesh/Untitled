#ifndef _C_CHANGETILE_H_
#define _C_CHANGETILE_H_

#include "CSurface.h"
#include "CFont.h"
#include "Define.h"

// Change-tile interface definitions
#define MAX_TILES 8

class CChangeTile {
public:
	static CChangeTile PickTile;

private:
	// X: x-pos on tileset being viewed (tile coordinate)
	// Y: y-pos on tileset being viewed (tile coordinate)
	// W: width of tileset (tiles)
	// H: height of tileset (tiles)
	int X, Y, W, H;
	int dispX, dispY, dispW, dispH;

public:
	CChangeTile();

	void Init(int W, int H);

	bool OnLClick(int mX, int mY, int& ID);

	bool RenderTileset(SDL_Texture* interface, SDL_Texture* tileset, const int& mX, const int& mY);

private:
	bool RenderArrow(SDL_Texture* interface, const int& aX, const int& aY, char direction, const int& mX, const int& mY);

};

#endif
