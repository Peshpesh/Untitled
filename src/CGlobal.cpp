#include "CGlobal.h"

CGlobal CGlobal::control;

CGlobinfo::CGlobinfo() {
  lastloaded = 'A';
  N_load = 0;
  N_save = 0;
  N_death = 0;
  N_fin_easy = 0;
  N_fin_norm = 0;
  N_fin_hard = 0;
  N_fin_brut = 0;
  uptime = 0;
  playtime = 0;
}

CGlobal::CGlobal() {
  //
}

void CGlobal::push_data(const CGlobinfo& data) {
  this->data = data;
}

CGlobinfo CGlobal::pull_data() {
  return data;
}

void CGlobal::changeLastLoad(const char& slot) {
  if (slot == 'A' || slot == 'B' || slot == 'C') data.lastloaded = slot;
}

void CGlobal::incrLoad() {
  data.N_load++;
}

void CGlobal::incrSave() {
  data.N_save++;
}

void CGlobal::incrDeath() {
  data.N_death++;
}

void CGlobal::incrFinEasy() {
  data.N_fin_easy++;
}

void CGlobal::incrFinNorm() {
  data.N_fin_norm++;
}

void CGlobal::incrFinHard() {
  data.N_fin_hard++;
}

void CGlobal::incrFinBrut() {
  data.N_fin_brut++;
}

void CGlobal::incrPlaytime(unsigned long addtime) {
  data.playtime += addtime;
}

unsigned long CGlobal::getNumLoad() {
  return data.N_load;
}

unsigned long CGlobal::getNumSave() {
  return data.N_save;
}

unsigned long CGlobal::getNumDeath() {
  return data.N_death;
}

unsigned long CGlobal::getNumFin() {
  return getNumFinEasy() + getNumFinNorm() + getNumFinHard() + getNumFinBrut();
}

unsigned long CGlobal::getNumFinEasy() {
  return data.N_fin_easy;
}

unsigned long CGlobal::getNumFinNorm() {
  return data.N_fin_norm;
}

unsigned long CGlobal::getNumFinHard() {
  return data.N_fin_hard;
}

unsigned long CGlobal::getNumFinBrut() {
  return data.N_fin_brut;
}

unsigned long long CGlobal::getUptime() {
  return data.uptime + SDL_GetTicks();
}

unsigned long long CGlobal::getPlaytime() {
  return data.playtime;
}
