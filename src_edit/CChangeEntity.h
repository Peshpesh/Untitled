#ifndef _C_CHANGEENTITY_H_
#define _C_CHANGEENTITY_H_

#include "CAsset.h"
#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CEntity.h"
#include "Define.h"

class CChangeEntity : public CEvent {
public:
	static CChangeEntity Control;

private:
	bool succ; // SUCC

public:
	CChangeEntity();

  void OnEvent(SDL_Event* Event);

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

	bool OnRender(const SDL_Point* m);
};

#endif
