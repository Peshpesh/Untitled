#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() {
	X = Y = 0;
	X_min = X_max = Y_min = Y_max = 0;
	follow_w = 60;
	follow_h = 50;
	TargetX = TargetY = NULL;
	TargetW = TargetH = NULL;
	TargetMode = TARGET_MODE_NORMAL;
	uselimits = false;

	// usedisplace = true;
}

void CCamera::OnMove(int MoveX, int MoveY) {
	X += MoveX;
	Y += MoveY;
}

int CCamera::GetX() {
	if (TargetX != NULL) {
		// int x_disp = (usedisplace && TargetW) ? *TargetW / 2 : 0;
		int x_disp = TargetW ? *TargetW / 2 : 0;
		if (TargetMode == TARGET_MODE_FOLLOW) {
			int current_X = *TargetX + x_disp - (WWIDTH / 2) - (*TargetX + x_disp < WWIDTH / 2);
			if (current_X < X - (follow_w / 2)) X -= (X - (follow_w / 2)) - current_X;
			else if (current_X > X + (follow_w / 2)) X += current_X - (X + follow_w / 2);
			return LimX(X);
		} else if (TargetMode == TARGET_MODE_CENTER) {
			return LimX(*TargetX + x_disp - (WWIDTH / 2) - (*TargetX + x_disp < WWIDTH / 2));
		}
		return LimX(*TargetX + x_disp);
	}
	return LimX(X);
}

int CCamera::GetY() {
	if (TargetY != NULL) {
		// int y_disp = (usedisplace && TargetH) ? *TargetH / 2 : 0;
		int y_disp = TargetH ? *TargetH / 2 : 0;
		if (TargetMode == TARGET_MODE_FOLLOW) {
			int current_Y = *TargetY + y_disp - (WHEIGHT / 2) - (*TargetY + y_disp < WHEIGHT / 2);
			if (current_Y < Y - (follow_h / 2)) Y -= (Y - (follow_h / 2)) - current_Y;
			else if (current_Y > Y + (follow_h / 2)) Y += current_Y - (Y + follow_h / 2);
			return LimY(Y);
		} else if (TargetMode == TARGET_MODE_CENTER) {
			return LimY(*TargetY + y_disp - (WHEIGHT / 2) - (*TargetY + y_disp < WHEIGHT / 2));
		}
		return LimY(*TargetY + y_disp);
	}
	return LimY(Y);
}

int CCamera::LimX(const int& X) {
	if (!uselimits) return X;

	if (X < X_min) return X_min;
	if (X + WWIDTH > X_max + 1) return X_max + 1 - WWIDTH;

	return X;
}

int CCamera::LimY(const int& Y) {
	if (!uselimits) return Y;

	if (Y < Y_min) return Y_min;
	if (Y + WHEIGHT > Y_max + 1) return Y_max + 1 - WHEIGHT;

	return Y;
}

SDL_Point CCamera::GetPoint() {
	SDL_Point retval = {GetX(), GetY()};
	return retval;
}

SDL_Point CCamera::GetWinRelPoint(const SDL_Point& absPos) {
	SDL_Point retval = {absPos.x - GetX(), absPos.y - GetY()};
	return retval;
}

SDL_Point CCamera::GetWinRelPoint(const double& rel_x, const double& rel_y) {
	SDL_Point retval = {rel_x - GetX(), rel_y - GetY()};
	return retval;
}

SDL_Point CCamera::GetCamRelPoint(const SDL_Point& winPos) {
	SDL_Point retval = {winPos.x + GetX(), winPos.y + GetY()};
	return retval;
}

void CCamera::MakeWinRel(int& X, int& Y) {
	X -= GetX();
	Y -= GetY();
}

SDL_Point CCamera::ConvertToRel(const SDL_Point& t_pos, const double& Z) {
	SDL_Point r_pos;
	if (Z <= 0.0) return r_pos;

	double half_width  = WWIDTH  / 2.0;
	double half_height = WHEIGHT / 2.0;

	// window center positions
  long double cX = GetX() + half_width;
  long double cY = GetY() + half_height;

	long double dX = t_pos.x - cX;
	long double dY = t_pos.y - cY;

  // relative X, Y positions
	r_pos.x = cX + (dX / Z);
	r_pos.y = cY + (dY / Z);

	return r_pos;
}

SDL_Point CCamera::ConvertToTrue(const SDL_Point& r_pos, const double& Z) {
	SDL_Point t_pos;
	if (Z <= 0.0) return t_pos;

	// window center positions
	long double cX = GetX() + (WWIDTH  / 2.0);
	long double cY = GetY() + (WHEIGHT / 2.0);

	long double dX = r_pos.x - cX;
	long double dY = r_pos.y - cY;

	// true X, Y positions
	t_pos.x = cX + (dX * Z);
	t_pos.y = cY + (dY * Z);

	return t_pos;
}

double CCamera::trueXToRel(const double& true_x, const double& Z) {
	if (Z <= 0.0) return 0.0;

	double half_width = WWIDTH  / 2.0;

	// window center position
  long double cX = GetX() + half_width;

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
  long double cY = GetY() + half_height;

	// separation of true_y from center of camera
	// (no separation means that the object's relative Y is at its true Y)
	long double dY = true_y - cY;

  // relative Y position
	return cY + (dY / Z);
}

double CCamera::relXToTrue(const double& rel_x, const double& Z) {
	if (Z <= 0.0) return 0.0;

	// window center position
	long double cX = GetX() + (WWIDTH  / 2.0);

	// separation of rel_x from center of camera
	// (no separation means that the object's relative X is at its true X)
	long double dX = rel_x - cX;

	// true X position
	return cX + (dX * Z);
}

double CCamera::relYToTrue(const double& rel_y, const double& Z) {
	// window center position
	long double cY = GetY() + (WHEIGHT / 2.0);

	// separation of rel_y from center of camera
	// (no separation means that the object's relative Y is at its true Y)
	long double dY = rel_y - cY;

	// true Y position
	return cY + (dY * Z);
}

void CCamera::SetPos(int X, int Y) {
	this->X = X;
	this->Y = Y;
}

void CCamera::SetTarget(float* X, float* Y) {
	TargetX = X;
	TargetY = Y;
	TargetW = TargetH = NULL;
}

void CCamera::SetTarget(float* X, float* Y, int* W, int* H) {
	TargetX = X;
	TargetY = Y;
	TargetW = W;
	TargetH = H;
}

void CCamera::EnableLim() {
	uselimits = true;
}
void CCamera::DisableLim() {
	uselimits = false;
}

void CCamera::SetLimits(const int& X_min, const int& Y_min, const int& X_max, const int& Y_max) {
	this->X_min = X_min;
	this->Y_min = Y_min;
	this->X_max = X_max;
	this->Y_max = Y_max;
}

//////////////////////////////////////
//////////////////////////////////////

// void CCamera::D_toggle_displace() {
// 	usedisplace = !usedisplace;
// }
