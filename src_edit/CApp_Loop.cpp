#include "CApp.h"

void CApp::OnLoop()
{
	int mX, mY;
	int tX = 0, tY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouse.x = mouseX;
	mouse.y = mouseY;
	if (mouseX < WWIDTH && mouseY < WHEIGHT && mouseX >= 0 && mouseY >= 0)
	{
		mX = mouseX + CCamera::CameraControl.GetX();
		mY = mouseY + CCamera::CameraControl.GetY();
		tX = TILE_SIZE * (mX / TILE_SIZE);
		tY = TILE_SIZE * (mY / TILE_SIZE);

		if (mX < 0)
		{
			tX -= TILE_SIZE;
		}
		if (mY < 0)
		{
			tY -= TILE_SIZE;
		}
	}
	else
	{
		mX = -404404;
		mY = -404404;
	}
	// DEBUGGING
	if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
	{
		double trueX, trueY;
		double rX = mX;
		double rY = mY;
		CSceneryEdit::ScnControl.ConvertToTrue(rX, rY, CSceneryEdit::ScnControl.Z, trueX, trueY);
		if (rX < 0) rX = -rX;
		if (trueX < 0) trueX = -trueX;

		char Buffer[255];
		sprintf(Buffer, "X %d | Y %d [ tX %d | tY %d ]", mX, mY, (int)(trueX), (int)(trueY));
		SDL_SetWindowTitle(Map_Display, Buffer);
	}
	else
	{
		char Buffer[255];
		sprintf(Buffer, "X %d | Y %d [ tX %d | tY %d ]", mX, mY, tX, tY);
		SDL_SetWindowTitle(Map_Display, Buffer);
	}

	if (SDL_GetWindowFlags(Map_Display) & SDL_WINDOW_MINIMIZED)
	{
		SDL_RestoreWindow(Map_Display);
	}
	CFPS::FPSControl.OnLoop();
	return;
}
