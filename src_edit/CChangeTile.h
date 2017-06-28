#ifndef _C_CHANGETILE_H_
#define _C_CHANGETILE_H_

#include "CInterrupt.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CAsset.h"
#include "CFont.h"
#include "Define.h"

class CChangeTile : public CEvent {
public:
	static CChangeTile PickTile;

private:
	bool changeFlag;
	int pickID;

private:
	// X: x-pos on tileset being viewed (tile coordinate)
	// Y: y-pos on tileset being viewed (tile coordinate)
	// W: width of tileset (tiles)
	// H: height of tileset (tiles)
	int X, Y, W, H;
	SDL_Rect disp;				// rectangle dims: tiles rendered
	SDL_Rect frame;				// rectangle dims: display frame
	SDL_Rect dstArrL, dstArrR, dstArrU, dstArrD;
	SDL_Rect dstCancel;
	int x_Info, y_dInfo, y_tInfo;

public:
	CChangeTile();

	void Init(int W, int H);

  void OnEvent(SDL_Event* Event);

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	bool OnRender(SDL_Texture* tileset, const SDL_Point* m);

  void reqChange(int& ID);

private:
	bool RenderTileset(SDL_Texture* tileset, const SDL_Point* m);
	bool RenderInfo();
	bool RenderArrow(char dir, const SDL_Rect* dstR, const SDL_Point* m);


};

#endif
