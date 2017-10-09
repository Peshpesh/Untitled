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

SDL_Point CCamera::GetCamRelPoint(const SDL_Point* winPos)
{
	SDL_Point retval = {winPos->x + GetX(), winPos->y + GetY()};
	return retval;
}

void CCamera::MakeWinRel(int& X, int& Y)
{
	X -= GetX();
	Y -= GetY();
}

SDL_Point CCamera::ConvertToRel(const SDL_Point* t_pos, const double& Z) {
	SDL_Point r_pos;
	if (t_pos == NULL || Z <= 0.0) return r_pos;

	// window center positions
  double cX = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
  double cY = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);

  // relative X, Y positions
  r_pos.x = (t_pos->x - (cX * (1 - Z))) / Z;
  r_pos.y = (t_pos->y - (cY * (1 - Z))) / Z;

	return r_pos;
}

SDL_Point CCamera::ConvertToTrue(const SDL_Point* r_pos, const double& Z) {
	SDL_Point t_pos;
	if (r_pos == NULL || Z <= 0.0) return t_pos;

	// window center positions
  double cX = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
  double cY = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);

	// true X, Y positions
  t_pos.x = (cX * (1 - Z)) + (r_pos->x * Z);
  t_pos.y = (cY * (1 - Z)) + (r_pos->y * Z);

	return t_pos;
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
