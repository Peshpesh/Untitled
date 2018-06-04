#ifndef _C_HUD_H_
#define _C_HUD_H_

#include "CPlayer.h"
#include "Font.h"

class CHUD
{
public:
	static CHUD HUDControl;
	SDL_Texture* Tex_HUD;

public:
	CHUD();

	bool	OnInit(SDL_Renderer* renderer);

	void	OnLoop(int HP, int MaxHP, int Purse);

	void	OnRender(SDL_Renderer* renderer, const int &HP, const int &Max_HP, const int &Purse, const int &Weapon, const int &Arsenal);

	Uint8	HealthBar(const int &HP, const int &MaxHP);
};
#endif
