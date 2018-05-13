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

SDL_Point CCamera::GetWinRelPoint(const double& rel_x, const double& rel_y) {
	SDL_Point retval = {rel_x - GetX(), rel_y - GetY()};
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

	double half_width  = WWIDTH  / 2.0;
	double half_height = WHEIGHT / 2.0;

	// window center positions
  long double cX = CCamera::CameraControl.GetX() + half_width;
  long double cY = CCamera::CameraControl.GetY() + half_height;

	long double dX = t_pos->x - cX;
	long double dY = t_pos->y - cY;

  // relative X, Y positions
	r_pos.x = cX + (dX / Z);
	r_pos.y = cY + (dY / Z);

	return r_pos;
}

SDL_Point CCamera::ConvertToTrue(const SDL_Point* r_pos, const double& Z) {
	SDL_Point t_pos;
	if (r_pos == NULL || Z <= 0.0) return t_pos;

	// window center positions
	long double cX = CCamera::CameraControl.GetX() + (WWIDTH  / 2.0);
	long double cY = CCamera::CameraControl.GetY() + (WHEIGHT / 2.0);

	long double dX = r_pos->x - cX;
	long double dY = r_pos->y - cY;

	// true X, Y positions
	t_pos.x = cX + (dX * Z);
	t_pos.y = cY + (dY * Z);

	return t_pos;
}

double CCamera::trueXToRel(const double& true_x, const double& Z) {
	if (Z <= 0.0) return 0.0;

	double half_width = WWIDTH / 2.0;

	// window center position
  long double cX = CCamera::CameraControl.GetX() + half_width;

	// separation of true_x from center of camera
	// (no separation means that the object's relative X is at its true X)
	long double dX = true_x - cX;

  // relative X position
	return cX + (dX / Z);
}

double CCamera::trueYToRel(const double& true_y, const double& Z) {
	if (Z <= 0.0) return 0.0;

	double half_height = WHEIGHT / 2.0;

	// window center position
  long double cY = CCamera::CameraControl.GetY() + half_height;

	// separation of true_y from center of camera
	// (no separation means that the object's relative Y is at its true Y)
	long double dY = true_y - cY;

  // relative Y position
	return cY + (dY / Z);
}

double CCamera::relXToTrue(const double& rel_x, const double& Z) {
	if (Z <= 0.0) return 0.0;

	// window center position
	long double cX = CCamera::CameraControl.GetX() + (WWIDTH / 2.0);

	// separation of rel_x from center of camera
	// (no separation means that the object's relative X is at its true X)
	long double dX = rel_x - cX;

	// true X position
	return cX + (dX * Z);
}

double CCamera::relYToTrue(const double& rel_y, const double& Z) {
	// window center position
	long double cY = CCamera::CameraControl.GetY() + (WHEIGHT / 2.0);

	// separation of rel_y from center of camera
	// (no separation means that the object's relative Y is at its true Y)
	long double dY = rel_y - cY;

	// true Y position
	return cY + (dY * Z);
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
