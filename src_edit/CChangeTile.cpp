#include "CChangeTile.h"

CChangeTile CChangeTile::PickTile;

namespace {
	const unsigned short Max_Tiles = 8;
	const unsigned short Frame_Size = 24;
	const unsigned short hilightSize = 2;
	const SDL_Point* frameCol = &palette::gray;
	const SDL_Point* hilightCol = &palette::white;
	const SDL_Color* arrFill = &rgb::blue;
	const SDL_Color* arrDisable = &rgb::gray;
	const SDL_Color* arrHover = &rgb::light_cyan;
	const SDL_Color* arrStr = &rgb::black;
}

CChangeTile::CChangeTile()
{
	changeFlag = false;
	pickID = 0;
	X = Y = W = H = 0;
	disp.x = disp.y = disp.w = disp.h = 0;
	frame.x = frame.y = frame.w = frame.h = 0;
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
	int cX = disp.x + disp.w + ((Frame_Size - CANCEL_SZ) / 2);
	int cY = disp.y - Frame_Size + ((Frame_Size - CANCEL_SZ) / 2);
	if (mX >= cX && mX < cX + CANCEL_SZ && mY >= cY && mY < cY + CANCEL_SZ)
	{
		CInterrupt::removeFlag(INTRPT_CHANGE_BG);
		CInterrupt::removeFlag(INTRPT_CHANGE_FG);
		return;
	}

	// Maybe an arrow was clicked?
	int aX, aY;
	if (W > Max_Tiles)	// Left/right arrows are worth processing
	{
		aY = disp.y + (disp.h / 2) - (ARR_SZ / 2);
		if (X > 0) 							// Left arrow?
		{
			aX = disp.x - (ARR_SZ + SYM_SPACING);
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				X--;
				return;
			}
		}
		if (X < W - Max_Tiles)	// Right arrow?
		{
			aX = disp.x + disp.w + SYM_SPACING;
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				X++;
				return;
			}
		}
	}
	if (H > Max_Tiles)	// Up/down arrows are worth processing
	{
		aX = disp.x + (disp.w / 2) - (ARR_SZ / 2);
		if (Y > 0) 							// Up arrow?
		{
			aY = disp.y - (ARR_SZ + SYM_SPACING);
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				Y--;
				return;
			}
		}
		if (Y < H - Max_Tiles)	// Down arrow?
		{
			aY = disp.y + disp.h + SYM_SPACING;
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				Y++;
				return;
			}
		}
	}
}

bool CChangeTile::RenderTileset(SDL_Texture* interface, SDL_Texture* tileset, const SDL_Point* m)
{
	// Render a "frame" for the tileset
	CAsset::drawBoxFill(&frame, frameCol);
	{
		// Render the tileset (or part of it)
		SDL_Rect srcR = CAsset::getRect(X * TILE_SIZE, Y * TILE_SIZE, disp.w, disp.h);
		CSurface::OnDraw(tileset, &srcR, &disp);
	}

	if (SDL_PointInRect(m, &disp))
	{
		int hX = disp.x + TILE_SIZE * ((m->x - disp.x) / TILE_SIZE);
		int hY = disp.y + TILE_SIZE * ((m->y - disp.y) / TILE_SIZE);
		SDL_Rect hilight = CAsset::getRect(hX, hY, TILE_SIZE, TILE_SIZE);
		CAsset::drawBox(&hilight, hilightCol, hilightSize);
	}

	// display text-based information in the table border
	int retsiz = Font::GetVSpacing(FONT_MINI);
	int xF = disp.x - Frame_Size + 1;
	int yF = disp.y - Frame_Size + 1;
	Font::Write(FONT_MINI, "Display Range:", xF, yF);
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "X: ", xF, yF);
	xF += Font::Write(FONT_MINI, X, xF, yF);
	Font::Write(FONT_MINI, X + (disp.w / TILE_SIZE) - 1, xF, yF);
	xF = disp.x - Frame_Size + 1;
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "Y: ", xF, yF);
	xF += Font::Write(FONT_MINI, Y, xF, yF);
	Font::Write(FONT_MINI, Y + (disp.h / TILE_SIZE) - 1, xF, yF);

	xF = disp.x - Frame_Size + 1;
	yF = disp.y + disp.w + 1;
	Font::Write(FONT_MINI, "Tileset Info:", xF, yF);
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "Width: ", xF, yF);
	Font::Write(FONT_MINI, W, xF, yF);
	xF = disp.x - Frame_Size + 1;
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "Height: ", xF, yF);
	Font::Write(FONT_MINI, H, xF, yF);

	// Render clickable arrows
	int aX, aY;
	aX = disp.x - (ARR_SZ + SYM_SPACING);
	aY = disp.y + (disp.h / 2) - (ARR_SZ / 2);
	RenderArrow(interface, aX, aY, 'L', m);
	aX = disp.x + disp.w + SYM_SPACING;
	RenderArrow(interface, aX, aY, 'R', m);
	aX = disp.x + (disp.w / 2) - (ARR_SZ / 2);
	aY = disp.y - (ARR_SZ + SYM_SPACING);
	RenderArrow(interface, aX, aY, 'U', m);
	aY = disp.y + disp.h + SYM_SPACING;
	RenderArrow(interface, aX, aY, 'D', m);

	// Render cancel button
	int cX = disp.x + disp.w + ((Frame_Size - CANCEL_SZ) / 2);
	int cY = disp.y - Frame_Size + ((Frame_Size - CANCEL_SZ) / 2);
	CSurface::OnDraw(interface, cX, cY, CANCEL_X, CANCEL_Y, CANCEL_SZ, CANCEL_SZ);

	return true;
}

bool CChangeTile::RenderArrow(SDL_Texture* interface, const int& aX, const int& aY, char direction, const SDL_Point* m)
{
	SDL_Rect dstR = CAsset::getRect(aX, aY, ARR_SZ, ARR_SZ);
	bool hover = SDL_PointInRect(m, &dstR);
	bool enable = false;

	if (direction == 'L') enable = (X > 0);
	if (direction == 'R') enable = (X < W - Max_Tiles);
	if (direction == 'U') enable = (Y > 0);
	if (direction == 'D') enable = (Y < H - Max_Tiles);

	const SDL_Color* arrCol = enable ? (hover ? arrHover : arrFill) : arrDisable;

	return CAsset::drawStrArrow(&dstR, direction, arrCol, arrStr);
}

void CChangeTile::reqChange(int& ID)
{
	if (changeFlag)
	{
		ID = pickID;
		changeFlag = false;
	}
}
