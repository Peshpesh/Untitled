#include "CGamedata.h"

CGamedata CGamedata::control;

CHeroData::CHeroData() {
  health = 7;
  max_health = 7;
}

CLevelAData::CLevelAData() {
  adventure_ready = false;
}

CLevelBData::CLevelBData() {
  defeat_mother = false;
  own_medikit_used = false;
}

CMiscData::CMiscData() {
  //
}

CGamedata::CGamedata() {
  //
}

void CGamedata::reset() {
  data_hero.health = 7;
  data_hero.max_health = 7;
  data_levelA.adventure_ready = false;
  data_levelB.defeat_mother = false;
  data_levelB.own_medikit_used = false;
}
