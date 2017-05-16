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

	if (mX >= dispX && mX < dispX + dispW && mY >= dispY && mY < dispY + dispH)
	{
		int xrel = mX - dispX;
		int yrel = mY - dispY;
		int xtile = X + (xrel / TILE_SIZE);
		int ytile = Y + (yrel / TILE_SIZE);
		ID = (ytile * W) + xtile;
		retval = true;
	}
	else
	{
		// Maybe an arrow was clicked?
		int aX, aY;
		if (W > MAX_TILES)	// Left/right arrows are worth processing
		{
			aY = dispY + (dispH / 2) - (ARROW_SIZE / 2);
			if (X > 0) 							// Left arrow?
			{
				aX = dispX - (MENU_BORDER_SIZ + ARROW_SIZE + SYM_SPACING);
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	X--;
			}

			if (X < W - MAX_TILES)	// Right arrow?
			{
				aX = dispX + dispW + MENU_BORDER_SIZ + SYM_SPACING;
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	X++;
			}
		}

		if (H > MAX_TILES)	// Up/down arrows are worth processing
		{
			aX = dispX + (dispW / 2) - (ARROW_SIZE / 2);
			if (Y > 0) 							// Up arrow?
			{
				aY = dispY - (MENU_BORDER_SIZ + ARROW_SIZE + SYM_SPACING);
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	Y--;
			}

			if (Y < H - MAX_TILES)	// Down arrow?
			{
				aY = dispY + dispH + MENU_BORDER_SIZ + SYM_SPACING;
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	Y++;
			}
		}
	}
	return retval;
}

bool CChangeTile::RenderTileset(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Texture* tileset)
{
	int aX, aY;
	// Render a "frame" for the tileset
	CSurface::OnDraw(renderer, interface, dispX - MENU_BORDER_SIZ, dispY - MENU_BORDER_SIZ,
		LIGHTS_X, COLOR_PURE_Y, 1, 1, dispW + (MENU_BORDER_SIZ*2), dispH + (MENU_BORDER_SIZ*2));
	// Render the tileset (or part of it)
	CSurface::OnDraw(renderer, tileset, dispX, dispY, X * TILE_SIZE, Y * TILE_SIZE, dispW, dispH);

	// Render clickable arrows
	aX = dispX - (MENU_BORDER_SIZ + ARROW_SIZE + SYM_SPACING);
	aY = dispY + (dispH / 2) - (ARROW_SIZE / 2);
	CSurface::OnDraw(renderer, interface, aX, aY, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	aX = dispX + dispW + MENU_BORDER_SIZ + SYM_SPACING;
	CSurface::OnDraw(renderer, interface, aX, aY, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	aX = dispX + (dispW / 2) - (ARROW_SIZE / 2);
	aY = dispY - (MENU_BORDER_SIZ + ARROW_SIZE + SYM_SPACING);
	CSurface::OnDraw(renderer, interface, aX, aY, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	aY = dispY + dispH + MENU_BORDER_SIZ + SYM_SPACING;
	CSurface::OnDraw(renderer, interface, aX, aY, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	return true;
}
