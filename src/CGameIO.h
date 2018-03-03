#ifndef _C_GAMEIO_H_
#define _C_GAMEIO_H_

#include <stdio.h>
#include "CGlobal.h"

enum Difficulty {
  EASY    = 0,
  NORMAL  = 1,
  HARD    = 2,
  BRUTAL  = 3,
};

// This class should handle files describing each game's status/progress.
// Namely, this should be able to output/load game data.
// It should include things like:
//    - player status (HP, equip, special charge)
//    - area and save location
//    - inventory & funds
//    - history of noteworthy events
//    - story progress
//    - any permanent settings, like difficulty
// Note that this class should NOT have to be accessed BY objects like
// entities or stages. This class should use information associated with
// these objects to create save files, and then be able to read in data from
// such a file to reconstruct these objects at a later time.
// For example, imagine a building in Stage A could render as damaged or new
// DEPENDING on the player's progress in the story. The game loop will have to
// figure out whether the building is damaged or new when Stage A loads, and it
// should NOT have to consult THIS CLASS to figure that out. Instead, that info
// should be stored somewhere in a stage or progress class, which is updated during
// gameplay or when a game is loaded.
// This is mainly to prevent complicated and circular dependencies.

struct CGameinfo {
  CGameinfo();
private:
  // CPlayer hero;
  // CInventory inv;
  Difficulty diff;
  unsigned int N_load;
  unsigned int N_save;
  unsigned int N_death;
  unsigned long long time;
  // more ...
};

class CGameIO {
  CGameIO();

public:
  static CGameIO control;

  bool loadGlobal();

  void saveGlobal();
};

#endif
