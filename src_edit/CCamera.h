#ifndef _CCAMERA_H_
#define _CCAMERA_H_

#include <SDL.h>
#include "Define.h"

enum
{
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

public:
	void SetPos(int X, int Y);
	void SetTarget(float* X, float* Y);
};
#endif
