#ifndef _C_GAME_H_
#define _C_GAME_H_

#include "CEvent.h"
#include "CGameIO.h"

class CGame : public CEvent {
  CGame();

public:
  static CGame control;

  // bool init(const short& slot); // initialize game in the passed file slot

  // bool OnCleanup(); // clear game-dependent information
};

#endif
