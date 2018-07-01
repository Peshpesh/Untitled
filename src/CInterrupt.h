#ifndef _C_INTERRUPT_H_
#define _C_INTERRUPT_H_

enum interrupts {
  INTRPT_NONE       = 0,              // no interruption in normal gameplay
  INTRPT_PAUSE      = 0x00000001,     // interrupted by pause menu
  INTRPT_VIEW_MAP   = 0x00000002,     // interrupted by map viewer
  INTRPT_INVENTORY  = 0x00000004,     // interrupted by inventory interface
  INTRPT_DIALOGUE   = 0x00000008,     // interrupted by text on screen

  // INTRPT_CHANGE_TS  = 0x00000008,   // change tileset
  // INTRPT_CHANGE_EN  = 0x00000010,   // change/explore entity groups
  // INTRPT_CHANGE_SC  = 0x00000020,   // change/explore scenery groups
  // INTRPT_CHANGE_LA  = 0x00000040,   // change/make scenery layers
  // INTRPT_MODIFY_HB  = 0x00000080,   // modify primary hitbox within active entity group
  // INTRPT_GRAB_ANCH  = 0x00000100,   // click on scenery (grab) to use as anchor for placement
  // INTRPT_MAKE_ANCH  = 0x00000200,   // click on map, use point as anchor for placement
  // INTRPT_NEW        = 0x00000400,   // reset stage prompt
  // INTRPT_LOAD       = 0x00000800,   // load stage prompt
  // INTRPT_SAVE       = 0x00001000,   // save stage prompt
  // INTRPT_EXIT       = 0x00002000,   // escape program (exit)
};

class CInterrupt {

private:
  static int handle;
  static int suspend_flag;

public:
  CInterrupt();

  // turns off a bitwise flag in handle
  static void removeFlag(int flag);

  // turns on a bitwise flag in handle
  static void appendFlag(int flag);

  // assigns the suspend_flag member
  static void setSuspend(int flag);

  // turns all flags off
  static void resetFlags();

  // returns true if the flag is on in handle
  static bool isFlagOn(int flag);

  // returns true if the flag is off in handle
  static bool isFlagOff(int flag);

  // returns true if there are no interruptions
  static bool isNone();

  // returns true if a suspend_flag is on in handle
  static bool isSuspended();
};

#endif
