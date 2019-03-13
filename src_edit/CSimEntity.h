#ifndef _C_SIMENTITY_H_
#define _C_SIMENTITY_H_

#include "CArea.h"
#include "CEntity.h"

namespace Entityflags {
	enum {
		NONE		= 0,
		GRAVITY = 0x00000001,	// Entity subject to gravity
		GHOST		= 0x00000002,	// Entity can translate thru walls
		HOLLOW	= 0x00000004,	// Entity allows other entities to translate thru it (collisions ON)
	};
};

class CSimEntity {

public:
	SDL_Texture* sprtSrc;
	float	X;	// sprite x-position
	float	Y;  // sprite y-position
	SDL_Rect spriteR;	// sprite position & size on texture
	SDL_Rect hitboxR;	// X and Y are offset values relative to sprite
	bool	move_left;
	bool	move_right;

public:
	int 	Flags;
	bool	Dead;		// is Entity dead

protected:
	float	SpeedX; // pixels / idealframe
	float	SpeedY; // pixels / idealframe
	float	AccelX; // pixels / idealframe^2
	float	AccelY; // pixels / idealframe^2
	short jump_timer;
	short jump_timer_init;
	short jump_timer_max;
	bool Jumper;
	bool Grounded;

public:
	float	MaxSpeedX; // pixels / idealframe
	float	MaxSpeedY; // pixels / idealframe
	float	MaxAccelX; // pixels / idealframe^2
	float	MaxAccelY; // pixels / idealframe^2

public:
	CSimEntity();

public:
	void OnLoad();

	void OnLoop();

	bool OnRender();
	void OnRenderHitbox();

	void OnCleanup();

protected:
	void OnMove(float MoveX, float MoveY);
	void stopMove();

public:
	bool Jump();
	void JumpRelease();

protected:
	void Translate(double NewX, double NewY);
	int getVertDeflect(const double& NewX, const double& NewY);
	int CollGround(const int& collID, const int& X_offset, const int& Y_offset);
	bool CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb);
	bool CollTile(const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br);
	bool CollTile_top(const int& collID, const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br);
	bool CollTile_bot(const int& collID, const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br);
};

#endif
