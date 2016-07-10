#ifndef _CPLAYER_H_
#define _CPLAYER_H_

#include "CEntity.h"
#include "CEntityMod.h"
#include "CHUD.h"
#include "CItem.h"

	enum // Modifier flags
	{
		MODE_NONE = 0,					// No abilities

		MODE_INVINCIBLE = 0x00000001,	// Invincibility
		MODE_INVISIBLE = 0x00000002,	// Invisibility
		MODE_HASTE = 0x00000004,		// Increased speed
		MODE_FLIGHT = 0x00000008,		// Ability to fly
		MODE_AQUALUNG = 0x00000010,		// Infinite breath underwater

		MODE_POISON = 0x00000020,		// Poisoned
		MODE_SLOW = 0x00000040,			// Decreased speed
	};

	enum // List of arms
	{
		UNARMED = 0,
		ARM_TEST = 0x00000001,
		ARM_TEST_A = 0x00000002,
		ARM_TEST_B = 0x00000004,
		ARM_TEST_C = 0x00000008,
		ARM_TEST_D = 0x00000010,
		ARM_TEST_E = 0x00000020,
	};

class CPlayer : public CEntity
{
public:
	CPlayer();
	void Reset();

	bool OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames);

	void OnLoop();

	void OnRender(SDL_Renderer* Surf_Dest);

	void OnCleanup();

	void OnAnimate();

	bool OnCollision(CEntity* Entity);

	// Converts hex weapon code to enum
	static Uint8 ConvertBinary(const int &Weapon);

public:
	void OnShoot(SDL_Renderer* renderer);

	bool Interact();

// private:
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
