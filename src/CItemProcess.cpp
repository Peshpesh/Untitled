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
