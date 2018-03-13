#ifndef _C_GAMEDATA_H_
#define _C_GAMEDATA_H_

// This is similar to the CGameinfo class,
// except this contains the data specific to
// progress (etc.) in a game file.

struct CHeroData {
  short health;
  short max_health;
  CHeroData();
};

struct CLevelAData {
  bool adventure_ready;
  CLevelAData();
};

struct CLevelBData {
  bool defeat_mother;
  bool own_medikit_used;
  CLevelBData();
};

struct CMiscData {
  CMiscData();
};

class CGamedata {
  CGamedata();

public:
  static CGamedata control;
  CHeroData data_hero;
  CLevelAData data_levelA;
  CLevelBData data_levelB;
  // CMiscData data_misc;
  void reset();
};

#endif
