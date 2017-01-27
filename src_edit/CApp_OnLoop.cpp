#include "CApp.h"

void CApp::OnLoop()
{
	int mX, mY;
	int tX = 0, tY = 0;
	SDL_GetMouseState(&mX, &mY);
	if (mX < WWIDTH && mY < WHEIGHT && mX >= 0 && mY >= 0)
	{
		mX += CCamera::CameraControl.GetX();
		mY += CCamera::CameraControl.GetY();
		mouseX = mX;
		mouseY = mY;
		tX = 32 * (mX / 32);
		tY = 32 * (mY / 32);

		if (mouseX < 0)
		{
			tX -= 32;
		}
		if (mouseY < 0)
		{
			tY -= 32;
		}
	}
	else
	{
		mX = -404404;
		mY = -404404;
		mouseX = mX;
		mouseY = mY;
	}
	// DEBUGGING
	if (Active_Mod == MODIFY_SCENE || Active_Mod == REMOVE_SCENE)
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
	return;
}
