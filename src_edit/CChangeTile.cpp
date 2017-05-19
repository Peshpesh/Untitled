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
				aX = dispX - (ARROW_SIZE + SYM_SPACING);
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	X--;
			}

			if (X < W - MAX_TILES)	// Right arrow?
			{
				aX = dispX + dispW + SYM_SPACING;
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	X++;
			}
		}

		if (H > MAX_TILES)	// Up/down arrows are worth processing
		{
			aX = dispX + (dispW / 2) - (ARROW_SIZE / 2);
			if (Y > 0) 							// Up arrow?
			{
				aY = dispY - (ARROW_SIZE + SYM_SPACING);
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	Y--;
			}

			if (Y < H - MAX_TILES)	// Down arrow?
			{
				aY = dispY + dispH + SYM_SPACING;
				if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)	Y++;
			}
		}
	}
	return retval;
}

bool CChangeTile::RenderTileset(SDL_Renderer* renderer, SDL_Texture* interface, SDL_Texture* tileset)
{
	// Render a "frame" for the tileset
	CSurface::OnDraw(renderer, interface, dispX - TILETABLE_SIZ, dispY - TILETABLE_SIZ,
		LIGHTS_X, COLOR_PURE_Y, 1, 1, dispW + (TILETABLE_SIZ*2), dispH + (TILETABLE_SIZ * 2));
	// Render the tileset (or part of it)
	CSurface::OnDraw(renderer, tileset, dispX, dispY, X * TILE_SIZE, Y * TILE_SIZE, dispW, dispH);

	// display text-based information in the table border
	int retsiz = Font::GetVSpacing(FONT_MINI);
	int xF = dispX - TILETABLE_SIZ + 1;
	int yF = dispY - TILETABLE_SIZ + 1;
	Font::Write(renderer, FONT_MINI, "Display Range:", xF, yF);
	yF += retsiz;
	xF += Font::Write(renderer, FONT_MINI, "X: ", xF, yF);
	xF += Font::Write(renderer, FONT_MINI, X, xF, yF);
	Font::Write(renderer, FONT_MINI, X + (dispW / TILE_SIZE) - 1, xF, yF);
	xF = dispX - TILETABLE_SIZ + 1;
	yF += retsiz;
	xF += Font::Write(renderer, FONT_MINI, "Y: ", xF, yF);
	xF += Font::Write(renderer, FONT_MINI, Y, xF, yF);
	Font::Write(renderer, FONT_MINI, Y + (dispH / TILE_SIZE) - 1, xF, yF);

	xF = dispX - TILETABLE_SIZ + 1;
	yF = dispY + dispW + 1;
	Font::Write(renderer, FONT_MINI, "Tileset Info:", xF, yF);
	yF += retsiz;
	xF += Font::Write(renderer, FONT_MINI, "Width: ", xF, yF);
	Font::Write(renderer, FONT_MINI, W, xF, yF);
	xF = dispX - TILETABLE_SIZ + 1;
	yF += retsiz;
	xF += Font::Write(renderer, FONT_MINI, "Height: ", xF, yF);
	Font::Write(renderer, FONT_MINI, H, xF, yF);


	int aX, aY;
	// Render clickable arrows
	aX = dispX - (ARROW_SIZE + SYM_SPACING);
	aY = dispY + (dispH / 2) - (ARROW_SIZE / 2);
	RenderArrow(renderer, interface, aX, aY, 'L');
	aX = dispX + dispW + SYM_SPACING;
	RenderArrow(renderer, interface, aX, aY, 'R');

	aX = dispX + (dispW / 2) - (ARROW_SIZE / 2);
	aY = dispY - (ARROW_SIZE + SYM_SPACING);
	RenderArrow(renderer, interface, aX, aY, 'U');
	aY = dispY + dispH + SYM_SPACING;
	RenderArrow(renderer, interface, aX, aY, 'D');

	return true;
}

bool CChangeTile::RenderArrow(SDL_Renderer* renderer, SDL_Texture* interface, const int& aX, const int& aY, char direction)
{
	bool retval = false;
	if (direction == 'L')
	{
		if (X > 0)
		{
			int mX, mY;
			SDL_GetMouseState(&mX, &mY);
			if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, L_ARRGLOW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
			else
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
		}
		else retval = CSurface::OnDraw(renderer, interface, aX, aY, L_ARRGRAY_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	}
	else if (direction == 'R')
	{
		if (X < W - MAX_TILES)
		{
			int mX, mY;
			SDL_GetMouseState(&mX, &mY);
			if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, R_ARRGLOW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
			else
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
		}
		else retval = CSurface::OnDraw(renderer, interface, aX, aY, R_ARRGRAY_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	}
	else if (direction == 'U')
	{
		if (Y > 0)
		{
			int mX, mY;
			SDL_GetMouseState(&mX, &mY);
			if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, U_ARRGLOW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
			else
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
		}
		else retval = CSurface::OnDraw(renderer, interface, aX, aY, U_ARRGRAY_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	}
	else if (direction == 'D')
	{
		if (Y < H - MAX_TILES)
		{
			int mX, mY;
			SDL_GetMouseState(&mX, &mY);
			if (mX >= aX && mX < aX + ARROW_SIZE && mY >= aY && mY < aY + ARROW_SIZE)
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, D_ARRGLOW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
			else
			{
				retval = CSurface::OnDraw(renderer, interface, aX, aY, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			}
		}
		else retval = CSurface::OnDraw(renderer, interface, aX, aY, D_ARRGRAY_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	}
	return retval;
}
