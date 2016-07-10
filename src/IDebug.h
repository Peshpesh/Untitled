#ifndef _IDEBUG_H_
#define _IDEBUG_H_

#include "CItem.h"

class IHPUP : public CItem
{
public:
	IHPUP();

	void OnRender(SDL_Renderer* renderer, SDL_Texture* texture,
		const int& xO, const int& yO, const int& tW, const int& tH);
};

class IHPDW : public CItem
{
public:
	IHPDW();

	void OnRender(SDL_Renderer* renderer, SDL_Texture* texture,
		const int& xO, const int& yO, const int& tW, const int& tH);
};

#endif
