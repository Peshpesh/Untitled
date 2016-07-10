#ifndef _CME_CHTILE_H_
#define _CME_CHTILE_H_

#include "CSurface.h"
#include "CEvent.h"
#include "Define.h"

class CME_ChTile : public CEvent {
public:
	static CME_ChTile	UIControl;

private:
	bool Running;
	int X;
	int Y;
	int W, H;

public:
	CME_ChTile();

	int OnExecute(SDL_Renderer* renderer, SDL_Texture* tileset);

	void OnEvent(SDL_Event* Event);

	int GetID();

	void OnLButtonDown(int mX, int mY);
};

#endif