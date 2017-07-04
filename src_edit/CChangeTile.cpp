#include "CChangeTile.h"

CChangeTile CChangeTile::PickTile;

namespace
{
	const unsigned short Max_Tiles = 8;
	const unsigned short Frame_Size = 24;
	const unsigned short hilightSize = 2;
	const SDL_Point* frameCol = &palette::gray;
	const SDL_Point* hilightCol = &palette::white;
	const SDL_Color* arrFill = &rgb::blue;
	const SDL_Color* arrDisable = &rgb::gray;
	const SDL_Color* arrHover = &rgb::light_cyan;
	const SDL_Color* arrStr = &rgb::black;
	const std::string dispHeader = "Display Range: ";
	const std::string tileHeader = "Tileset Info: ";
}

CChangeTile::CChangeTile()
{
	changeFlag = false;
	pickID = 0;
	X = Y = W = H = 0;
	disp.x = disp.y = disp.w = disp.h = 0;
	frame.x = frame.y = frame.w = frame.h = 0;

	dstArrL.x = 0;
	dstArrR.x = 0;
	dstArrU.y = 0;
	dstArrD.y = 0;

	dstArrL.y = dstArrR.y = (WHEIGHT - ARR_SZ) / 2;
	dstArrU.x = dstArrD.x = (WWIDTH - ARR_SZ) / 2;

	dstArrL.w = dstArrL.h = ARR_SZ;
	dstArrR.w = dstArrR.h = ARR_SZ;
	dstArrU.w = dstArrU.h = ARR_SZ;
	dstArrD.w = dstArrD.h = ARR_SZ;

	dstCancel.x = dstCancel.y = 0;
	dstCancel.w = dstCancel.h = CANCEL_SZ;

	x_Info = y_dInfo = y_tInfo = 0;
}

void CChangeTile::Init(int W, int H)
{
	X = Y = 0;
	this->W = W;
	this->H = H;

	if (W < Max_Tiles) 	disp.w = TILE_SIZE * W;
	else								disp.w = TILE_SIZE * Max_Tiles;
	if (H < Max_Tiles)	disp.h = TILE_SIZE * H;
	else								disp.h = TILE_SIZE * Max_Tiles;

	disp.x = (WWIDTH - disp.w) / 2;
	disp.y = (WHEIGHT - disp.h) / 2;

	frame.x = disp.x - Frame_Size;
	frame.y = disp.y - Frame_Size;
	frame.w = disp.w + (Frame_Size * 2);
	frame.h = disp.h + (Frame_Size * 2);

	dstArrL.x = frame.x + ((Frame_Size - ARR_SZ) / 2) + ((Frame_Size - ARR_SZ) % 2);
	dstArrU.y = frame.y + ((Frame_Size - ARR_SZ) / 2) + ((Frame_Size - ARR_SZ) % 2);
	dstArrR.x = disp.x + disp.w + ((Frame_Size - ARR_SZ) / 2);
	dstArrD.y = disp.y + disp.h + ((Frame_Size - ARR_SZ) / 2);

	dstCancel.x = disp.x + disp.w + ((Frame_Size - CANCEL_SZ) / 2);
	dstCancel.y = frame.y + ((Frame_Size - CANCEL_SZ) / 2);

	x_Info = frame.x + 1;
	y_dInfo = frame.y + 1;
	y_tInfo = disp.y + disp.w + 1;
}

void CChangeTile::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CChangeTile::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
	if (sym == SDLK_ESCAPE)
	{
		CInterrupt::removeFlag(INTRPT_CHANGE_BG);
		CInterrupt::removeFlag(INTRPT_CHANGE_FG);
		return;
	}

	if (W > Max_Tiles)
	{
		if (sym == SDLK_RIGHT && X < W - Max_Tiles) 	X++;
		else if (sym == SDLK_LEFT && X > 0) 					X--;
	}
	if (H > Max_Tiles)
	{
		if (sym == SDLK_DOWN && Y < H - Max_Tiles) 		Y++;
		else if (sym == SDLK_UP && Y > 0) 						Y--;
	}
}

void CChangeTile::OnLButtonDown(int mX, int mY)
{
	SDL_Point m = {mX, mY};
	// process clicks on the tileset.
	if (SDL_PointInRect(&m, &disp))
	{
		int xrel = m.x - disp.x;
		int yrel = m.y - disp.y;
		int xtile = X + (xrel / TILE_SIZE);
		int ytile = Y + (yrel / TILE_SIZE);
		pickID = (ytile * W) + xtile;
		changeFlag = true;
		CInterrupt::removeFlag(INTRPT_CHANGE_BG);
		CInterrupt::removeFlag(INTRPT_CHANGE_FG);
		return;
	}

	// process clicks on cancel button.
	if (SDL_PointInRect(&m, &dstCancel))
	{
		CInterrupt::removeFlag(INTRPT_CHANGE_BG);
		CInterrupt::removeFlag(INTRPT_CHANGE_FG);
		return;
	}

	// Maybe an arrow was clicked?
	if (W > Max_Tiles)	// Left/right arrows are worth processing
	{
		if (X > 0 && SDL_PointInRect(&m, &dstArrL))	// Left arrow?
		{
			X--; return;
		}
		if (X < W - Max_Tiles && SDL_PointInRect(&m, &dstArrR))	// Right arrow?
		{
			X++; return;
		}
	}
	if (H > Max_Tiles)	// Up/down arrows are worth processing
	{
		if (Y > 0 && SDL_PointInRect(&m, &dstArrU)) // Up arrow?
		{
			Y--; return;
		}
		if (Y < H - Max_Tiles && SDL_PointInRect(&m, &dstArrD))	// Down arrow?
		{
			Y++; return;
		}
	}
}

bool CChangeTile::OnRender(SDL_Texture* tileset, const SDL_Point* m)
{
	// Render the field of tiles & tileset information
	if (!RenderTileset(tileset, m)) return false;
	if (!RenderInfo()) return false;

	// Render clickable arrows
	if (!RenderArrow('L', &dstArrL, m)) return false;
	if (!RenderArrow('R', &dstArrR, m)) return false;
	if (!RenderArrow('U', &dstArrU, m)) return false;
	if (!RenderArrow('D', &dstArrD, m)) return false;

	// Render cancel button
	if (!CAsset::drawCancel(&dstCancel)) return false;

	return true;
}

bool CChangeTile::RenderTileset(SDL_Texture* tileset, const SDL_Point* m)
{
	if (tileset == NULL) return false;

	// Render a "frame" for the tileset
	CAsset::drawBoxFill(&frame, frameCol);
	{
		// Render the tileset (or part of it)
		SDL_Rect srcR = CAsset::getRect(X * TILE_SIZE, Y * TILE_SIZE, disp.w, disp.h);
		if (!CSurface::OnDraw(tileset, &srcR, &disp)) return false;
	}

	// outline tile hovered by cursor
	if (SDL_PointInRect(m, &disp))
	{
		int hX = disp.x + TILE_SIZE * ((m->x - disp.x) / TILE_SIZE);
		int hY = disp.y + TILE_SIZE * ((m->y - disp.y) / TILE_SIZE);
		SDL_Rect hilight = CAsset::getRect(hX, hY, TILE_SIZE, TILE_SIZE);
		if (!CAsset::drawBox(&hilight, hilightCol, hilightSize)) return false;
	}

	return true;
}

bool CChangeTile::RenderInfo()
{
	// display text-based information in the table border
	const int Xf = X + (disp.w / TILE_SIZE) - 1;
	const int Yf = Y + (disp.h / TILE_SIZE) - 1;
	std::string dispLabX = "X: " + Font::intToStr(X) + "-" + Font::intToStr(Xf);
	std::string dispLabY = "Y: " + Font::intToStr(Y) + "-" + Font::intToStr(Yf);
	std::string tileLabW = "Width: " + Font::intToStr(W);
	std::string tileLabH = "Height: " + Font::intToStr(H);

	SDL_Point dstPos = {x_Info, y_dInfo};

	std::string dispInfo = dispHeader + "\n" + dispLabX + "\n" + dispLabY;
	Font::Write(FONT_MINI, dispInfo.c_str(), &dstPos);

	dstPos.y = y_tInfo;

	std::string tileInfo = tileHeader + "\n" + tileLabW + "\n" + tileLabH;
	Font::Write(FONT_MINI, tileInfo.c_str(), &dstPos);

	return true;
}

bool CChangeTile::RenderArrow(char dir, const SDL_Rect* dstR, const SDL_Point* m)
{
	bool hover = SDL_PointInRect(m, dstR);	// true if cursor is hovering arrow
	bool enable = false;	// true if the arrow is responsive to events

	if (dir == 'L') enable = (X > 0);
	if (dir == 'R') enable = (X < W - Max_Tiles);
	if (dir == 'U') enable = (Y > 0);
	if (dir == 'D') enable = (Y < H - Max_Tiles);

	const SDL_Color* arrCol = enable ? (hover ? arrHover : arrFill) : arrDisable;

	return CAsset::drawStrArrow(dstR, dir, arrCol, arrStr);
}

void CChangeTile::reqChange(short& ID)
{
	if (changeFlag)
	{
		ID = pickID;
		changeFlag = false;
	}
}
