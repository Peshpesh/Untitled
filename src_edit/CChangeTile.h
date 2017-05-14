#ifndef _CCHANGETILE_H_
#define _CCHANGETILE_H_

#include "CSurface.h"
#include "Font.h"
#include "Define.h"

class CChangeTile {
private:
	int X, Y, W, H;

public:
	CChangeTile();

	void Init(int W, int H);

	bool RenderTileset(SDL_Renderer* renderer, SDL_Texture* tileset);

};

#endif
