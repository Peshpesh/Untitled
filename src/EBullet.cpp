#include "EBullet.h"

CArm_Test::CArm_Test(bool right)
{
	MaxSpeedX = 20;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_FRIEND | ENTITY_FLAG_HOLLOW | ENTITY_FLAG_BULLET;
	Damage = 1;
	Level = 1;

	this->X = 0.0f;
	this->Y = 0.0f;

	Width = 0;
	Height = 0;

	Dir_Right = right;
	Used = false;
	Life_Time = 15;

	SpeedX = 1;
	SpeedY = 0;
}

bool CArm_Test::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CArm_Test::OnLoop()
{
	if (Used)
	{
		OnDeath(true);
		return;
	}
	if (Life_Time == 0)
	{
		OnDeath(false);
		return;
	}
	
	if (Dir_Right)
		MoveRight = true;
	else
		MoveLeft = true;

	if (MoveLeft)
	{
		AccelX = -20.0;
	}
	else if (MoveRight)
	{
		AccelX = 20.0;
	}

	SpeedX += AccelX * CFPS::FPSControl.GetSpeedFactor();
	SpeedY += AccelY * CFPS::FPSControl.GetSpeedFactor();

	// Make sure we're not overstepping our boundaries,
	// so to speak...
	if (SpeedX > MaxSpeedX) SpeedX = MaxSpeedX;
	if (SpeedX < -MaxSpeedX) SpeedX = -MaxSpeedX;
	if (SpeedY > MaxSpeedY) SpeedY = MaxSpeedY;
	if (SpeedY < -MaxSpeedY) SpeedY = -MaxSpeedY;

	CEntity::OnAnimate();
	if (!CEntity::OnMove(SpeedX, SpeedY))
		Dead = true;

	--Life_Time;
}

void CArm_Test::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CArm_Test::OnCleanup()
{
	CEntity::OnCleanup();
}

void CArm_Test::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CArm_Test::OnCollision(CEntity* Entity)
{
	if (Entity->Health > 0 && Entity->Type == ENTITY_TYPE_GENERIC && !Used)
	{
		Entity->Health -= Damage;						// Deal the appropriate amt of dmg
//		if (Entity->Health <= 0) Entity->Dead = true;	// if you run out of health, you're dead
		Used = true;
	}
	return true;
}

void CArm_Test::OnDeath(bool hit)
{
	Dead = true;
}
