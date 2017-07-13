#ifndef _C_INTERRUPT_H_
#define _C_INTERRUPT_H_

enum interrupts
{
  INTRPT_NONE       = 0,
  INTRPT_CHANGE_BG  = 0x00000001,		// intrpt via bg tile change
  INTRPT_CHANGE_FG  = 0x00000002,		// intrpt via fg tile change
  INTRPT_MAP_MODEL  = 0x00000004,
  INTRPT_CHANGE_TS  = 0x00000008,
  INTRPT_NEW        = 0x00000010,
  INTRPT_LOAD       = 0x00000020,
  INTRPT_SAVE       = 0x00000040,
  INTRPT_CH_ENTITY  = 0x00000080,
  INTRPT_CH_ENTGRP  = 0x00000100,
};

class CInterrupt {

private:
  static int handle;

public:
  CInterrupt();

  // turns off a bitwise flag in handle
  static void removeFlag(int flag);

  // turns on a bitwise flag in handle
  static void appendFlag(int flag);

  // turns all flags off
  static void resetFlags();

  // returns true if the flag is on in handle
  static bool isFlagOn(int flag);

  // returns true if the flag is off in handle
  static bool isFlagOff(int flag);

  // returns true if there are no interruptions
  static bool isNone();

};

#endif
