#include "CGamedata.h"

CGamedata CGamedata::control;

CHeroData::CHeroData() {
  reset();
}

CYraiData::CYraiData() {
  reset();
}

CRhighidData::CRhighidData() {
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
  data_yrai.reset();
  data_rhighid.reset();
}

void CHeroData::reset() {
  health = 7;
  max_health = 7;
  X = 200;
  Y = 500;
}

void CYraiData::reset() {
  adventure_ready = false;
}

void CRhighidData::reset() {
  defeat_mother = false;
  own_medikit_used = false;
}

void CMiscData::reset() {
  //
}
