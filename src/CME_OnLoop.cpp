#include "CMapEdit.h"

void CMapEdit::OnLoop()
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
	char Buffer[255];
	sprintf(Buffer, "X %d | Y %d [ tX %d | tY %d ]", mX, mY, tX, tY);
	SDL_SetWindowTitle(Map_Display, Buffer);

	return;
}