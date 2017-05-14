#include "CChangeTile.h"

CChangeTile::CChangeTile()
{
	X = Y = W = H = 0;
}

void CChangeTile::Init(int W, int H)
{
	X = Y = 0;
	this->W = W;
	this->H = H;
}

bool CChangeTile::RenderTileset(SDL_Renderer* renderer, SDL_Texture* tileset)
{
	int dispX, dispY, dispW, dispH;
	if (W - X < MAX_TILES)
	{
		dispW = TILE_SIZE * (W - X);
	}
	else
	{
		dispW = TILE_SIZE * MAX_TILES;
	}
	if (H - Y < MAX_TILES)
	{
		dispH = TILE_SIZE * (H - Y);
	}
	else
	{
		dispH = TILE_SIZE * MAX_TILES;
	}
	dispX = (WWIDTH - dispW) / 2;
	dispY = (WHEIGHT - dispH) / 2;

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
