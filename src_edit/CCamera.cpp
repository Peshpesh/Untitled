#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera()
{
	X = Y = 0;
	TargetX = TargetY = NULL;
	TargetMode = TARGET_MODE_NORMAL;
}

void CCamera::OnMove(int MoveX, int MoveY)
{
	X += MoveX;
	Y += MoveY;
}

int CCamera::GetX()
{
	if (TargetX != NULL)
	{
		if (TargetMode == TARGET_MODE_CENTER)
		{
			if (*TargetX < WWIDTH / 2) return *TargetX - (WWIDTH / 2) - 1;
			return *TargetX - (WWIDTH / 2);
		}
		return *TargetX;
	}
	return X;
}

int CCamera::GetY()
{
	if (TargetY != NULL)
	{
		if (TargetMode == TARGET_MODE_CENTER)
		{
			if (*TargetY < WHEIGHT / 2) return *TargetY - (WHEIGHT / 2) - 1;
			return *TargetY - (WHEIGHT / 2);
		}
		return *TargetY;
	}
	return Y;
}

SDL_Point CCamera::GetPoint()
{
	SDL_Point retval = {GetX(), GetY()};
	return retval;
}

SDL_Point CCamera::GetWinRelPoint(const SDL_Point* absPos)
{
	SDL_Point retval = {absPos->x - GetX(), absPos->y - GetY()};
	return retval;
}

void CCamera::MakeWinRel(int& X, int& Y)
{
	X -= GetX();
	Y -= GetY();
}

void CCamera::SetPos(int X, int Y)
{
	this->X = X;
	this->Y = Y;
}

void CCamera::SetTarget(float* X, float* Y)
{
	TargetX = X;
	TargetY = Y;
}
