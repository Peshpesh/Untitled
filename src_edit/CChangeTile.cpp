#include "CChangeTile.h"

CChangeTile::CChangeTile()
{
	X = Y = W = H = 0;
	dispX = dispY = dispW = dispH = 0;
}

void CChangeTile::Init(int W, int H)
{
	X = Y = 0;
	this->W = W;
	this->H = H;

	if (W < MAX_TILES) 	dispW = TILE_SIZE * W;
	else								dispW = TILE_SIZE * MAX_TILES;
	if (H < MAX_TILES)	dispH = TILE_SIZE * H;
	else								dispH = TILE_SIZE * MAX_TILES;

	dispX = (WWIDTH - dispW) / 2;
	dispY = (WHEIGHT - dispH) / 2;
}

bool CChangeTile::OnLClick(int mX, int mY, int& ID)
{
	bool retval = false;
	if (mX < dispX || mX >= dispX + dispW || mY < dispY || mY >= dispY + dispH)
	{

	}
	else
	{
		int xrel = mX - dispX;
		int yrel = mY - dispY;
		int xtile = X + (xrel / TILE_SIZE);
		int ytile = Y + (yrel / TILE_SIZE);
		ID = (ytile * W) + xtile;
		retval = true;
	}
	return retval;
}

bool CChangeTile::RenderTileset(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Texture* tileset)
{
	CSurface::OnDraw(renderer, interface, dispX - MENU_BORDER_SIZ, dispY - MENU_BORDER_SIZ,
		LIGHTS_X, COLOR_PURE_Y, 1, 1, dispW + (MENU_BORDER_SIZ*2), dispH + (MENU_BORDER_SIZ*2));
	CSurface::OnDraw(renderer, tileset, dispX, dispY, X, Y, dispW, dispH);

	return true;
}

// void CChangeTile::OnLButtonDown(int mX, int mY)
// {
//
// }
//
// int CChangeTile::GetID()
// {
// 	int TileID;
//
// 	// Get X,Y relative to tileset display
// 	X -= (WWIDTH - W) / 2;
// 	Y -= (WHEIGHT - W) / 2;
//
// 	TileID = X / TILE_SIZE;
// 	TileID += (Y / TILE_SIZE) * W / TILE_SIZE;
//
// 	return TileID;
// }
