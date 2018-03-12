#include "CGamedata.h"

CGamedata CGamedata::control;

CLevelAData::CLevelAData() {
  adventure_ready = false;
}

CLevelBData::CLevelBData() {
  defeat_mother = false;
  own_medikit_used = false;
}

CGamedata::CGamedata() {
  //
}

void CGamedata::reset() {
  data_levelA.adventure_ready = false;
  data_levelB.defeat_mother = false;
  data_levelB.own_medikit_used = false;
}
