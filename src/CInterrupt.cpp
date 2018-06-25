#include "CInterrupt.h"

int CInterrupt::handle = INTRPT_NONE;
int CInterrupt::suspend_flag = INTRPT_PAUSE | INTRPT_VIEW_MAP | INTRPT_INVENTORY;

CInterrupt::CInterrupt() {
  //
}

void CInterrupt::removeFlag(int flag) {
  handle &= ~flag;
}

void CInterrupt::appendFlag(int flag) {
  handle |= flag;
}

void CInterrupt::setSuspend(int flag) {
  suspend_flag = flag;
}

void CInterrupt::resetFlags() {
  handle = INTRPT_NONE;
}

bool CInterrupt::isFlagOn(int flag) {
  return (handle & flag);
}

bool CInterrupt::isFlagOff(int flag) {
  return !(handle & flag);
}

bool CInterrupt::isNone() {
  return (handle == INTRPT_NONE);
}

bool CInterrupt::isSuspended() {
  return isFlagOn(suspend_flag);
}
