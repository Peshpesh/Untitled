#ifndef _C_GAMEDATA_H_
#define _C_GAMEDATA_H_

// This is similar to the CGameinfo class,
// except this contains the data specific to
// progress (etc.) in a game file.

struct CLevelAData {
  bool adventure_ready;
  CLevelAData();
};

struct CLevelBData {
  bool defeat_mother;
  bool own_medikit_used;
  CLevelBData();
};

class CGamedata {
  CGamedata();

public:
  static CGamedata control;
  CLevelAData data_levelA;
  CLevelBData data_levelB;
  void reset();
};

#endif
