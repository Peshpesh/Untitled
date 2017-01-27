#ifndef _C_CHANGETILE_H_
#define _C_CHANGETILE_H_

#include "CSurface.h"
#include "CEvent.h"
#include "Define.h"

class CChangeTile : public CEvent {
public:
	static CChangeTile	UIControl;

private:
	bool Running;
	int X;
	int Y;
	int W, H;

public:
	CChangeTile();

	int OnExecute(SDL_Renderer* renderer, SDL_Texture* tileset);

	void OnEvent(SDL_Event* Event);

	int GetID();

	void OnLButtonDown(int mX, int mY);
};

#endif
