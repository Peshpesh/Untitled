#include "EExplode.h"

CExplode::CExplode()
{
  MaxSpeedX = 0.0f;
	MaxSpeedY = 0.0f;
	Flags = ENTITY_FLAG_HOLLOW;

  // timers are in number of FRAMES at the desired FPS.
  ExplodeTime = 1.0f * CFPS::FPSControl.GetTargetFPS();
}

bool CExplode::OnLoad(SDL_Texture* entityset, SDL_Renderer* renderer, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, renderer, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CExplode::OnLoop()
{
  if (FuseTime > 0.0f)
  {
    FuseTime -= CFPS::FPSControl.GetSpeedFactor();
    if (!(FuseTime > 0.0f))
    {

    }
  }
  else if (ExplodeTime > 0.0f)
  {
    ExplodeTime -= CFPS::FPSControl.GetSpeedFactor();
  }
  else
  {
    Dead = true;
  }

	CEntity::OnLoop();
}

void CExplode::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CExplode::OnCleanup()
{
	CEntity::OnCleanup();
}

void CExplode::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CBomb::OnCollision(CEntity* Entity)
{
	return true;
}
