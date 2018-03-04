#include "CGameinfo.h"

std::vector<CGameinfo*> CGameinfo::infolist;

CGameinfo::CGameinfo() {
  diff = NORMAL;
  N_load = 0;
  N_save = 0;
  N_death = 0;
  time = 758723028;
}
