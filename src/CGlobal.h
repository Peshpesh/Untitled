#ifndef _C_GLOBAL_H_
#define _C_GLOBAL_H_

#include <SDL.h>

struct CGlobinfo {
  CGlobinfo();
  char lastloaded;
  unsigned long N_load;
  unsigned long N_save;
  unsigned long N_death;
  unsigned long N_fin_easy;
  unsigned long N_fin_norm;
  unsigned long N_fin_hard;
  unsigned long N_fin_brut;
  unsigned long long uptime;
  unsigned long long playtime;
  // more ...
};

class CGlobal {
  CGlobal();

public:
  static CGlobal control;

private:
  // external objects should not be able to interact directly
  // with the global data structure.
  CGlobinfo data;

public:
  // exchange global data members with inquiring objects here...
  void push_data(const CGlobinfo& data);
  CGlobinfo pull_data();
public:
  void changeLastLoad(const char& slot);
  void incrLoad();
  void incrSave();
  void incrDeath();
  void incrFinEasy();
  void incrFinNorm();
  void incrFinHard();
  void incrFinBrut();
  void incrPlaytime(unsigned long addtime);
public:
  unsigned long getNumLoad();
  unsigned long getNumSave();
  unsigned long getNumDeath();
  unsigned long getNumFin();
  unsigned long getNumFinEasy();
  unsigned long getNumFinNorm();
  unsigned long getNumFinHard();
  unsigned long getNumFinBrut();
  unsigned long long getUptime();
  unsigned long long getPlaytime();
};

#endif
