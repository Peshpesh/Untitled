#include "EBomb.h"

CBomb::CBomb()
{
  MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;

  // timers are in number of FRAMES at the desired FPS.
  FuseTime = 3.0f * CFPS::FPSControl.GetTargetFPS();
  ExplodeTime = 1.0f * CFPS::FPSControl.GetTargetFPS();
}

bool CBomb::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CBomb::OnLoop()
{
  if (FuseTime > 0.0f)
  {
    FuseTime -= CFPS::GetSpeedFactor;
    if (!(FuseTime > 0.0f))
    {
      
    }
  }
  else if (ExplodeTime > 0.0f)
  {
    ExplodeTime -= CFPS::GetSpeedFactor;
  }
  else
  {
    Dead = true;
  }

	CEntity::OnLoop();
}

void CBomb::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CBomb::OnCleanup()
{
	CEntity::OnCleanup();
}

void CBomb::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CBomb::OnCollision(CEntity* Entity)
{
	return true;
}
