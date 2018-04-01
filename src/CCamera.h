#ifndef _C_CAMERA_H_
#define _C_CAMERA_H_

#include <SDL.h>
#include "Define.h"

enum {
	TARGET_MODE_NORMAL = 0,
	TARGET_MODE_CENTER
};

class CCamera {
public:
	static CCamera CameraControl;

private:
	int X;	// Camera coordinates
	int Y;	// Camera coordinates
	float* TargetX;	// Target coordinates
	float* TargetY;	// Null pointers will revert camera

public:
	int TargetMode;

public:
	CCamera();

public:
	void OnMove(int MoveX, int MoveY);

public:
	int GetX();
	int GetY();
	SDL_Point GetPoint();
	SDL_Point GetWinRelPoint(const SDL_Point& absPos);
	SDL_Point GetWinRelPoint(const double& rel_x, const double& rel_y);
	SDL_Point GetCamRelPoint(const SDL_Point& winPos);
	void MakeWinRel(int& X, int& Y);

public:
	// 2.5D projection functions
	SDL_Point ConvertToRel(const SDL_Point& t_pos, const double& Z);
	SDL_Point ConvertToTrue(const SDL_Point& r_pos, const double& Z);
	double trueXToRel(const double& true_x, const double& Z);
	double trueYToRel(const double& true_y, const double& Z);
	double relXToTrue(const double& rel_x, const double& Z);
	double relYToTrue(const double& rel_y, const double& Z);

public:
	void SetPos(int X, int Y);
	void SetTarget(float* X, float* Y);
};
#endif
