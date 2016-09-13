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
    case ITEM_HPUP:    retval = UseHPUP();     break;
    case ITEM_HPDW:    retval = UseHPDW();     break;
    case ITEM_BOMB:    retval = UseBOMB();     break;
    case ITEM_CHARM:   retval = UseCHARM();    break;
    case ITEM_KEY:     retval = UseKEY();      break;
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
  int ex_Xo = CEntityInfo::Com_EntityInfo[BOMB].Xo;
  int ex_Yo = CEntityInfo::Com_EntityInfo[BOMB].Yo;
  int ex_W = CEntityInfo::Com_EntityInfo[BOMB].W;
  int ex_H = CEntityInfo::Com_EntityInfo[BOMB].H;
  CEntity::EntityList[ID]->OnLoad(CEntityRes::Com_Texture, ex_Xo, ex_Yo, ex_W, ex_H, 2);
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
