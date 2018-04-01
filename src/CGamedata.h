#ifndef _C_GAMEDATA_H_
#define _C_GAMEDATA_H_

// This is similar to the CGameinfo class,
// except this contains the data specific to
// progress (etc.) in a game file.

struct CHeroData {
  short health;
  short max_health;
  int X;
  int Y;
  CHeroData();
  void reset();
};

struct CLevelAData {
  bool adventure_ready;
  CLevelAData();
  void reset();
};

struct CLevelBData {
  bool defeat_mother;
  bool own_medikit_used;
  CLevelBData();
  void reset();
};

struct CMiscData {
  CMiscData();
  void reset();
};

class CGamedata {
  CGamedata();

public:
  static CGamedata control;
  CHeroData data_hero;
  CLevelAData data_levelA;
  CLevelBData data_levelB;
  // CMiscData data_misc;
  void resetAll();
};

#endif
