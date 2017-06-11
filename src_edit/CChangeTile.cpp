#include "CChangeTile.h"

CChangeTile CChangeTile::PickTile;

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
	// process clicks on the tileset. Return value of true (done processing events)
	if (mX >= dispX && mX < dispX + dispW && mY >= dispY && mY < dispY + dispH)
	{
		int xrel = mX - dispX;
		int yrel = mY - dispY;
		int xtile = X + (xrel / TILE_SIZE);
		int ytile = Y + (yrel / TILE_SIZE);
		ID = (ytile * W) + xtile;
		retval = true;
	}

	// process clicks on cancel button. Return value of true (done processing events)
	if (!retval)
	{
		int cX = dispX + dispW + ((TILETABLE_SIZ - CANCEL_SZ) / 2);
		int cY = dispY - TILETABLE_SIZ + ((TILETABLE_SIZ - CANCEL_SZ) / 2);
		if (mX >= cX && mX < cX + CANCEL_SZ && mY >= cY && mY < cY + CANCEL_SZ) retval = true;
	}

	// Maybe an arrow was clicked?
	if (!retval)
	{
		int aX, aY;
		if (W > MAX_TILES)	// Left/right arrows are worth processing
		{
			aY = dispY + (dispH / 2) - (ARR_SZ / 2);
			if (X > 0) 							// Left arrow?
			{
				aX = dispX - (ARR_SZ + SYM_SPACING);
				if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
				{
					X--;
					return retval;
				}
			}
			if (X < W - MAX_TILES)	// Right arrow?
			{
				aX = dispX + dispW + SYM_SPACING;
				if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
				{
					X++;
					return retval;
				}
			}
		}
		if (H > MAX_TILES)	// Up/down arrows are worth processing
		{
			aX = dispX + (dispW / 2) - (ARR_SZ / 2);
			if (Y > 0) 							// Up arrow?
			{
				aY = dispY - (ARR_SZ + SYM_SPACING);
				if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
				{
					Y--;
					return retval;
				}
			}
			if (Y < H - MAX_TILES)	// Down arrow?
			{
				aY = dispY + dispH + SYM_SPACING;
				if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
				{
					Y++;
					return retval;
				}
			}
		}
	}
	return retval;
}

bool CChangeTile::RenderTileset(SDL_Texture* interface, SDL_Texture* tileset, const int& mX, const int& mY)
{
	// Render a "frame" for the tileset
	CSurface::OnDraw(interface, dispX - TILETABLE_SIZ, dispY - TILETABLE_SIZ,
		LIGHTS_X, COLOR_PURE_Y, 1, 1, dispW + (TILETABLE_SIZ * 2), dispH + (TILETABLE_SIZ * 2));
	// Render the tileset (or part of it)
	CSurface::OnDraw(tileset, dispX, dispY, X * TILE_SIZE, Y * TILE_SIZE, dispW, dispH);
	if (mX >= dispX && mX < dispX + dispW && mY >= dispY && mY < dispY + dispH)
	{
		int hX = dispX + TILE_SIZE * ((mX - dispX) / TILE_SIZE);
		int hY = dispY + TILE_SIZE * ((mY - dispY) / TILE_SIZE);
		CSurface::OnDraw(interface, hX, hY, TILE_HILIGHT_X, TILE_HILIGHT_Y, TILE_SIZE, TILE_SIZE);
	}

	// display text-based information in the table border
	int retsiz = Font::GetVSpacing(FONT_MINI);
	int xF = dispX - TILETABLE_SIZ + 1;
	int yF = dispY - TILETABLE_SIZ + 1;
	Font::Write(FONT_MINI, "Display Range:", xF, yF);
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "X: ", xF, yF);
	xF += Font::Write(FONT_MINI, X, xF, yF);
	Font::Write(FONT_MINI, X + (dispW / TILE_SIZE) - 1, xF, yF);
	xF = dispX - TILETABLE_SIZ + 1;
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "Y: ", xF, yF);
	xF += Font::Write(FONT_MINI, Y, xF, yF);
	Font::Write(FONT_MINI, Y + (dispH / TILE_SIZE) - 1, xF, yF);

	xF = dispX - TILETABLE_SIZ + 1;
	yF = dispY + dispW + 1;
	Font::Write(FONT_MINI, "Tileset Info:", xF, yF);
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "Width: ", xF, yF);
	Font::Write(FONT_MINI, W, xF, yF);
	xF = dispX - TILETABLE_SIZ + 1;
	yF += retsiz;
	xF += Font::Write(FONT_MINI, "Height: ", xF, yF);
	Font::Write(FONT_MINI, H, xF, yF);

	// Render clickable arrows
	int aX, aY;
	aX = dispX - (ARR_SZ + SYM_SPACING);
	aY = dispY + (dispH / 2) - (ARR_SZ / 2);
	RenderArrow(interface, aX, aY, 'L', mX, mY);
	aX = dispX + dispW + SYM_SPACING;
	RenderArrow(interface, aX, aY, 'R', mX, mY);
	aX = dispX + (dispW / 2) - (ARR_SZ / 2);
	aY = dispY - (ARR_SZ + SYM_SPACING);
	RenderArrow(interface, aX, aY, 'U', mX, mY);
	aY = dispY + dispH + SYM_SPACING;
	RenderArrow(interface, aX, aY, 'D', mX, mY);

	// Render cancel button
	int cX = dispX + dispW + ((TILETABLE_SIZ - CANCEL_SZ) / 2);
	int cY = dispY - TILETABLE_SIZ + ((TILETABLE_SIZ - CANCEL_SZ) / 2);
	CSurface::OnDraw(interface, cX, cY, CANCEL_X, CANCEL_Y, CANCEL_SZ, CANCEL_SZ);

	return true;
}

bool CChangeTile::RenderArrow(SDL_Texture* interface, const int& aX, const int& aY, char direction, const int& mX, const int& mY)
{
	bool retval = false;
	if (direction == 'L')
	{
		if (X > 0)
		{
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				retval = CSurface::OnDraw(interface, aX, aY, L_ARR_GL_X, L_ARR_Y, ARR_SZ, ARR_SZ);
			}
			else
			{
				retval = CSurface::OnDraw(interface, aX, aY, L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
			}
		}
		else retval = CSurface::OnDraw(interface, aX, aY, L_ARR_GR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	}
	else if (direction == 'R')
	{
		if (X < W - MAX_TILES)
		{
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				retval = CSurface::OnDraw(interface, aX, aY, R_ARR_GL_X, R_ARR_Y, ARR_SZ, ARR_SZ);
			}
			else
			{
				retval = CSurface::OnDraw(interface, aX, aY, R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);
			}
		}
		else retval = CSurface::OnDraw(interface, aX, aY, R_ARR_GR_X, R_ARR_Y, ARR_SZ, ARR_SZ);
	}
	else if (direction == 'U')
	{
		if (Y > 0)
		{
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				retval = CSurface::OnDraw(interface, aX, aY, U_ARR_GL_X, U_ARR_Y, ARR_SZ, ARR_SZ);
			}
			else
			{
				retval = CSurface::OnDraw(interface, aX, aY, U_ARR_X, U_ARR_Y, ARR_SZ, ARR_SZ);
			}
		}
		else retval = CSurface::OnDraw(interface, aX, aY, U_ARR_GR_X, U_ARR_Y, ARR_SZ, ARR_SZ);
	}
	else if (direction == 'D')
	{
		if (Y < H - MAX_TILES)
		{
			if (mX >= aX && mX < aX + ARR_SZ && mY >= aY && mY < aY + ARR_SZ)
			{
				retval = CSurface::OnDraw(interface, aX, aY, D_ARR_GL_X, D_ARR_Y, ARR_SZ, ARR_SZ);
			}
			else
			{
				retval = CSurface::OnDraw(interface, aX, aY, D_ARR_X, D_ARR_Y, ARR_SZ, ARR_SZ);
			}
		}
		else retval = CSurface::OnDraw(interface, aX, aY, D_ARR_GR_X, D_ARR_Y, ARR_SZ, ARR_SZ);
	}
	return retval;
}
