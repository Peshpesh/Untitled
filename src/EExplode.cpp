#include "EExplode.h"

CExplode::CExplode()
{
  MaxSpeedX = 0.0f;
	MaxSpeedY = 0.0f;
	Flags = ENTITY_FLAG_HOLLOW;

  // timers are in number of FRAMES at the desired FPS.
  ExplodeTime = 1.0f * CFPS::FPSControl.GetTargetFPS();
}

bool CExplode::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CExplode::OnLoop()
{
  if (ExplodeTime > 0.0f)
  {
    ExplodeTime -= CFPS::FPSControl.GetSpeedFactor();
    if (!(ExplodeTime > 0.0f))
    {
      Dead = true;
    }
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

bool CExplode::OnCollision(CEntity* Entity)
{
	return true;
}
