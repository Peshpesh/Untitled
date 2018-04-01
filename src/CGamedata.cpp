#include "CGamedata.h"

CGamedata CGamedata::control;

CHeroData::CHeroData() {
  reset();
}

CLevelAData::CLevelAData() {
  reset();
}

CLevelBData::CLevelBData() {
  reset();
}

CMiscData::CMiscData() {
  reset();
}

CGamedata::CGamedata() {
  //
}

void CGamedata::resetAll() {
  data_hero.reset();
  data_levelA.reset();
  data_levelB.reset();
}

void CHeroData::reset() {
  health = 7;
  max_health = 7;
  X = 100;
  Y = 100;
}

void CLevelAData::reset() {
  adventure_ready = false;
}

void CLevelBData::reset() {
  defeat_mother = false;
  own_medikit_used = false;
}

void CMiscData::reset() {
  //
}
