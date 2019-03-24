#ifndef _C_CAMERA_H_
#define _C_CAMERA_H_

#include <SDL.h>
#include "Define.h"

enum {
	TARGET_MODE_NORMAL = 0,		// position camera explicitly via (target's) X, Y
	TARGET_MODE_CENTER,				// camera position centered on (target's) X, Y
	TARGET_MODE_FOLLOW				// camera position loosely "follows" a target's X, Y (roughly centered)
};

// If TargetX/TargetY are not NULL, the camera will use those coordinates
// when returning X and Y via Get functions.

class CCamera {
public:
	static CCamera CameraControl;

private:
	int X;	// Camera coordinates
	int Y;	// Camera coordinates
	float* TargetX;	// Target coordinates
	float* TargetY;	// Null pointers will revert camera
	int* TargetW;
	int* TargetH;
	int X_min, X_max;			//	min/max allowable X coordinates for viewing area
	int Y_min, Y_max;			//	min/max allowable Y coordinates for viewing area
	bool uselimits;				// 	true if min/max coords are enforced
	// unsigned int follow_w;		// width of range where the target can move without updating camera X
	// unsigned int follow_h;		// height of range where the target can move without updating camera Y
	SDL_Rect follow_dom;			// rectangle (domain) containing followed object

public:
	int TargetMode;

public:
	CCamera();

public:
	void OnMove(int MoveX, int MoveY);
	void OnLoop();

public:
	int GetX();
	int GetY();
	SDL_Point GetPoint();
	void GetNormalXY(int& X, int& Y);
	SDL_Point GetWinRelPoint(const SDL_Point& absPos);
	SDL_Point GetWinRelPoint(const double& rel_x, const double& rel_y);
	SDL_Point GetCamRelPoint(const SDL_Point& winPos);
	void MakeWinRel(int& X, int& Y);

private:
	void enforceLims();
	int LimX(const int& X);
	int LimY(const int& Y);

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
	void SetTarget(float* X, float* Y, int* W, int* H);
	// bool ApplyTargetToStatic();
	void FreeTarget();
	void EnableLim();
	void DisableLim();
	void ToggleLim();
	bool isLim();
	void SetLimits(const int& X_min, const int& Y_min, const int& X_max, const int& Y_max);
	void GetLimits(int& X_min, int& Y_min, int& X_max, int& Y_max);
	void SetFollowDims(const unsigned int& w, const unsigned int& h);
	void GetFollowDims(unsigned int& w, unsigned int& h);
	SDL_Rect GetFollow();

public:	// public debug members
	// bool usedisplace;
	// void D_toggle_displace();
};
#endif
