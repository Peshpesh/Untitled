#ifndef _C_GAMEINFO_H_
#define _C_GAMEINFO_H_

// This class contains the data that "describes" a
// given game file. It is meant to be a brief
// representation of the general info in a game---
// it does not contain specific data (e.g., progress in
// the story), which goes in the CGamedata class.

#include <vector>

enum Difficulty {
  EASY    = 0,
  NORMAL  = 1,
  HARD    = 2,
  BRUTAL  = 3,
};

class CGameinfo {
public:
  static std::vector<CGameinfo*> infolist;
  CGameinfo();
  CGameinfo(Difficulty diff);
  void reset();
  void reset(Difficulty diff);

public:
  Difficulty diff;
  unsigned int N_load;
  unsigned int N_save;
  unsigned int N_death;
  unsigned long long time;
  // more ...
};

#endif
