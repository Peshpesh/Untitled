#include "CGameinfo.h"

std::vector<CGameinfo*> CGameinfo::infolist;

CGameinfo::CGameinfo() {
  reset();
}

CGameinfo::CGameinfo(Difficulty diff) {
  reset(diff);
}

void CGameinfo::reset() {
  diff = NORMAL;
  N_load = 0;
  N_save = 0;
  N_death = 0;
  time = 0;
}

void CGameinfo::reset(Difficulty diff) {
  this->diff = diff;
  N_load = 0;
  N_save = 0;
  N_death = 0;
  time = 0;
}
