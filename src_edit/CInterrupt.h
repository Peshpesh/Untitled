#ifndef _C_INTERRUPT_H_
#define _C_INTERRUPT_H_

enum interrupts
{
  INTRPT_NONE       = 0,
  INTRPT_CHANGE_BG  = 0x00000001,		// intrpt via bg tile change
  INTRPT_CHANGE_FG  = 0x00000002,		// intrpt via fg tile change
  INTRPT_MAP_MODEL  = 0x00000004,   // show a simple model of the area
  INTRPT_CHANGE_TS  = 0x00000008,   // change tileset
  INTRPT_CHANGE_EN  = 0x00000010,   // change/explore entity groups
  INTRPT_CHANGE_SC  = 0x00000020,   // change/explore scenery groups
  INTRPT_CHANGE_LA  = 0x00000040,   // change/make scenery layers
  INTRPT_MODIFY_HB  = 0x00000080,   // modify primary hitbox within active entity group
  INTRPT_GRAB_ANCH  = 0x00000100,   // click on scenery (grab) to use as anchor for placement
  INTRPT_MAKE_ANCH  = 0x00000200,   // click on map, use point as anchor for placement
  INTRPT_ADD_LAYER  = 0x00000400,   // add planview map layer
  INTRPT_DEL_LAYER  = 0x00000800,   // delete planview map layer
  INTRPT_ADJ_LAYOP  = 0x00001000,   // adjust planview layer opacity
  INTRPT_NEW        = 0x00002000,   // reset stage prompt
  INTRPT_LOAD       = 0x00004000,   // load stage prompt
  INTRPT_SAVE       = 0x00008000,   // save stage prompt
  INTRPT_EXIT       = 0x00010000,   // escape program (exit)
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

  // switches/toggles a bitwise flag in handle
  static void toggleFlag(int flag);

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
