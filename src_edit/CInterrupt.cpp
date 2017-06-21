#include "CInterrupt.h"

int CInterrupt::handle = INTRPT_NONE;

CInterrupt::CInterrupt()
{
  //
}

void CInterrupt::removeFlag(int flag)
{
  handle &= ~flag;
}

void CInterrupt::appendFlag(int flag)
{
  handle |= flag;
}

bool CInterrupt::isFlagOn(int flag)
{
  return (handle & flag);
}

bool CInterrupt::isFlagOff(int flag)
{
  return (handle & ~flag);
}

bool CInterrupt::isNone()
{
  return !isFlagOff(INTRPT_NONE);
}
