#ifndef _C_FPS_H_
#define _C_FPS_H_

#include <SDL.h>

class CFPS
{
public:
	static CFPS FPSControl;

private:
	int		OldTime;
	int		LastTime;

	float	SpeedFactor;
	float TargetFPS;

	int		NumFrames;
	int		Frames;

public:
	CFPS();

	void	OnLoop();

public:
	int		GetFPS();

	float	GetSpeedFactor();

	float GetTargetFPS();
};
#endif
