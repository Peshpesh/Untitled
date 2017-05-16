#ifndef _CCHANGETILE_H_
#define _CCHANGETILE_H_

#include "CSurface.h"
#include "Font.h"
#include "Define.h"

class CChangeTile {
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

	bool RenderTileset(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Texture* tileset);

private:
	bool RenderArrow(SDL_Renderer* renderer, SDL_Texture* interface, const int& aX, const int& aY, char direction);

};

#endif
