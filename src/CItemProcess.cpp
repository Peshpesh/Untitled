#include "CItemProcess.h"

CPlayer* CItemProcess::Player;

CItemProcess::CItemProcess()
{
  Player = NULL;
}

bool CItemProcess::OnInit(CPlayer* player)
{
  if (player == NULL)
    return false;

  Player = player;
  return true;
}

bool CItemProcess::OnLoop(const int& itemID)
{
  bool retval = false;
  switch(itemID)
  {
    case HPUP:    retval = UseHPUP();     break;
    case HPDW:    retval = UseHPDW();     break;
    case BOMB:    retval = UseBOMB();     break;
    case CHARM:   retval = UseCHARM();    break;
    case KEY:     retval = UseKEY();      break;
    default:      break;
  }
  return retval;
}

bool CItemProcess::UseHPUP()
{
  bool retval = true;
  if (Player->Health < Player->MaxHealth)
  {
    Player->Health += 5;
    if (Player->Health > Player->MaxHealth)
      Player->Health = Player->MaxHealth;
  }
  else
  {
    retval = false;
  }
  return retval;
}

bool CItemProcess::UseHPDW()
{
  bool retval = true;
  if (Player->Health > 0)
  {
    Player->Health -= 5;
    if (Player->Health < 0)
    {
      Player->Health = 0;
    }
  }
  else
  {
    retval = false;
  }
  return retval;
}

bool CItemProcess::UseBOMB()
{
  CEntity::EntityList.push_back(new CBomb());
  int ID = CEntity::EntityList.size() - 1;
  CEntity::EntityList[ID]->X = Player->X;
  CEntity::EntityList[ID]->Y = Player->Y;
  int ex_Xo = CEntityInfo::EntityInfoList[3].Xo;
  int ex_Yo = CEntityInfo::EntityInfoList[3].Yo;
  int ex_W = CEntityInfo::EntityInfoList[3].W;
  int ex_H = CEntityInfo::EntityInfoList[3].H;

  CEntity::EntityList[ID]->OnLoad(Tex_Entity, ex_Xo, ex_Yo, ex_W, ex_H, 2);
  bool retval = true;
  return retval;
}

bool CItemProcess::UseCHARM()
{
  bool retval = false;
  return retval;
}

bool CItemProcess::UseKEY()
{
  bool retval = false;
  return retval;
}
