#include "EBomb.h"

CBomb::CBomb()
{
  MaxSpeedX = 0.0f;
	MaxSpeedY = 9.0f;
	Flags = ENTITY_FLAG_HOLLOW | ENTITY_FLAG_GRAVITY;

  // timers are in number of FRAMES at the desired FPS.
  FuseTime = 3.0f * CFPS::FPSControl.GetTargetFPS();
  // ExplodeTime = 1.0f * CFPS::FPSControl.GetTargetFPS();
}

bool CBomb::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CBomb::OnLoop()
{
  if (FuseTime > 0.0f)
  {
    FuseTime -= CFPS::FPSControl.GetSpeedFactor();
    if (!(FuseTime > 0.0f))
    {
      Dead = true;
      // Add explosion entity?
      CEntity::EntityList.push_back(new CExplode());
      int ID = CEntity::EntityList.size() - 1;
      CEntity::EntityList[ID]->X = this->X;
      CEntity::EntityList[ID]->Y = this->Y;
      // int ex_Xo = CEntityInfo::EntityInfoList[4].Xo;
      // int ex_Yo = CEntityInfo::EntityInfoList[4].Yo;
      // int ex_W = CEntityInfo::EntityInfoList[4].W;
      // int ex_H = CEntityInfo::EntityInfoList[4].H;
      int ex_Xo = CEntityInfo::Com_EntityInfo[EXPLODE].Xo;
      int ex_Yo = CEntityInfo::Com_EntityInfo[EXPLODE].Yo;
      int ex_W = CEntityInfo::Com_EntityInfo[EXPLODE].W;
      int ex_H = CEntityInfo::Com_EntityInfo[EXPLODE].H;

      CEntity::EntityList[ID]->OnLoad(Tex_Entity, ex_Xo, ex_Yo, ex_W, ex_H, 2);
    }
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
