#ifndef _C_HERO_H_
#define _C_HERO_H_

#include "CEntity.h"
// #include "CEntityMod.h"
// #include "CHUD.h"
// #include "CItem.h"

class CHero : public CEntity {
public:
	CHero();
	void Reset();

	bool OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	// Converts hex weapon code to enum
	static Uint8 ConvertBinary(const int &Weapon);

public:
	void Attack();

	bool Interact();

public:
	int Modifiers;		// integer used for storing modifiers (binary)
	int Timer_Invinc;
	int Timer_Invis;
	int Timer_Haste;
	int Timer_Flight;
	bool Underwater;
	float Air;

public:
	int MaxHealth;					// The maximum amount of HP the player can have
	int Arsenal;					// integer used for storing available weaponry (binary)
	int Weapon;						// Current weapon
	int Ammo;						// Amount of ammunition

	unsigned int Purse;				// # of amythyst

	bool Shooting;					// Has the player shot a bullet this loop?

	int Livebullets;				// # of player's live bullets in environment (prevent overflow of bullets)

	bool TryInteract;				// Is the player trying to interact with something?
};

#endif
