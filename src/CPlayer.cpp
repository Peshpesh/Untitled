#include "CPlayer.h"
#include "EBullet.h"

CPlayer::CPlayer()
{
	Type = ENTITY_TYPE_PLAYER;
	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;
	Modifiers = MODE_NONE;
	Arsenal = 0x00000001;
	MaxHealth = 12;
	Health = 3;
	MaxSpeedX = 7.0;
	MaxSpeedY = 12.0;
	Timer_Invinc = Timer_Invis =
		Timer_Haste = Timer_Flight = 0;
	Weapon = ARM_TEST;
	Underwater = false;
	Air = 100.0;
	Shooting = TryInteract = false;
	Livebullets = 0;
	Purse = 0;
	Ammo = 0;
	Col_X = 8;
	Col_Width = 16;
	Col_Height = 31;

}

void CPlayer::Reset()
{
	Type = ENTITY_TYPE_PLAYER;
	Flags = ENTITY_FLAG_GRAVITY | ENTITY_FLAG_HOLLOW;
	Modifiers = MODE_NONE;
	Arsenal = 0x00000001;
	MaxHealth = 12;
	Health = 3;
	MaxSpeedX = 7.0;
	MaxSpeedY = 12.0;
	Timer_Invinc = Timer_Invis =
		Timer_Haste = Timer_Flight = 0;
	Weapon = ARM_TEST;
	Underwater = false;
	Air = 100.0;
	Shooting = TryInteract = false;
	Livebullets = 0;
	Purse = 0;
	Ammo = 0;

	MoveLeft = MoveRight = false;
	SpeedX = SpeedY = AccelX = AccelY = 0.0f;
	MaxAccelX = 0.5f;
	MaxAccelY = 0.75f;
	Jumper = false;
	Dead = false;
	Engaged = false;
	Wet = false;
	Icy = false;

	Damage = 0;
}

bool CPlayer::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CPlayer::OnLoop()
{
	if (Dead)
	{
		//
	}
	if (Modifiers & MODE_INVINCIBLE)
	{
		if (Timer_Invinc == 0)  // If the timer hits 0, turn invincibility off
		{
			Modifiers ^= MODE_INVINCIBLE;
		}
		else
		if (Timer_Invinc > 0)	// If the timer is not at 0 yet, run it down 1 frame
		{
			Timer_Invinc--;
		}
	}
	if (!Engaged)	CEntity::OnLoop();
}

void CPlayer::OnRender(SDL_Renderer* renderer)
{
	// if (CEntityMod::EntityControl.Arm_Texture == NULL) return;
	if (CEntityRes::Arm_Texture == NULL) return;
	CEntity::OnRender(renderer);

	// Draw the weapon
	if (Weapon != UNARMED)
	CSurface::OnDraw(renderer, CEntityRes::Arm_Texture, X - CCamera::CameraControl.GetX(),
		Y - CCamera::CameraControl.GetY(), (ConvertBinary(Weapon) - 1) * Width, CurrentFrameRow * Height, Width, Height);

	if (!Dead) CHUD::HUDControl.OnRender(renderer, Health, MaxHealth, Purse, Weapon, Arsenal);
}

void CPlayer::OnCleanup()
{
	CEntity::OnCleanup();
}

void CPlayer::OnAnimate()
{
	if (CurrentFrameCol == 0 && Weapon != UNARMED)
	{
		CurrentFrameCol = 4;			// Column 4 starts the armed frames
	}
	if (SpeedX != 0)
	{
		Anim_Control.MaxFrames = 4;		// For mainchar
		if (Anim_Control.GetCurrentFrame() == 0) Anim_Control.SetCurrentFrame(1);
	}
	else
	{
		Anim_Control.MaxFrames = 0;
	}
	CEntity::OnAnimate();
}

bool CPlayer::OnCollision(CEntity* Entity)
{
	// If the player is not invincible and the collision causes damage...
	if (!(Modifiers & MODE_INVINCIBLE) && Entity->Flags & ENTITY_FLAG_DAMAGE && Entity->Type == ENTITY_TYPE_GENERIC)
	{
		Health -= Entity->Damage;		// Deal the appropriate amt of dmg
		if (Health <= 0)
		{
			Dead = true;	// if you run out of health, you're dead
			++CGameData::GameControl.Global.deathcount;
		}
		else                            // Otherwise, you get a grace period of invincibility
		{
			Modifiers = Modifiers | MODE_INVINCIBLE;		// Player is now invincible
			Timer_Invinc = CFPS::FPSControl.GetFPS() * 2;   // FPS * # of seconds invincible
			// This gives us the # of invincibility frames
			// for the current FPS
		}
	}
	else if (Entity->Type == ENTITY_TYPE_ITEM && Entity->Health != 0)
	{
		Health += Entity->Health;
		if (Health > MaxHealth) Health = MaxHealth;
	}
	else if (Entity->Type == ENTITY_TYPE_COIN && Entity->Health != 0)
	{
		Purse += Entity->Health;
		if (Purse > 99) Purse = 99;
	}
	else if (TryInteract)
	{
		if (Entity->Type == ENTITY_TYPE_NPC && !Engaged)
		{
			Engaged = Entity->Engaged = true;
		}
		TryInteract = false;
	//	else TryInteract = false;
	}
	return true;
}

void CPlayer::OnShoot()
{
	switch (Weapon)
	{
	case ARM_TEST:
		if (CurrentFrameRow == 0)
		{
			CEntity::EntityList.push_back(new CArm_Test(false));
			CEntity::EntityList[CEntity::EntityList.size() - 1]->X = this->X - 33.0;
			CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = this->Y;
		}
		else
		{
			CEntity::EntityList.push_back(new CArm_Test(true));
			CEntity::EntityList[CEntity::EntityList.size() - 1]->X = this->X + 33.0;
			CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = this->Y;
		}
		CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityRes::Bul_Texture,
			0, 0, 32, 32, 1);
		break;
	default: break;
	}
}

bool CPlayer::Interact()
{
	// If the player can jump (i.e., they're on the ground)
	if (Jumper)
	{
		TryInteract = true;
		return true;	// They can interact
	}
	return false;
}

// Converts hex weapon code to enum
Uint8 CPlayer::ConvertBinary(const int &Weapon)
{
	Uint8 i;

	switch (Weapon)
	{
	case ARM_TEST:		i = 1; break;
	case ARM_TEST_A:	i = 2; break;
	case ARM_TEST_B:	i = 3; break;
	case ARM_TEST_C:	i = 4; break;
	case ARM_TEST_D:	i = 5; break;
	case ARM_TEST_E:	i = 6; break;
	default:			break;
	}
	return i;
}
