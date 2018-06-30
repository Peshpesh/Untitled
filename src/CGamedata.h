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

struct CYraiData {
  bool adventure_ready;
  CYraiData();
  void reset();
};

struct CRhighidData {
  bool defeat_mother;
  bool own_medikit_used;
  CRhighidData();
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
  CYraiData data_yrai;
  CRhighidData data_rhighid;
  // CMiscData data_misc;
  void resetAll();
};
#endif
