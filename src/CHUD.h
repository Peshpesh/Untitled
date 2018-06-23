#ifndef _C_HUD_H_
#define _C_HUD_H_

#include "CAsset.h"
#include "CType.h"

class CHud {
  CHud();

  int* hp;
  int* maxhp;
  int* en;
  int* maxen;
  int* sp;
  int* maxsp;

public:
  static CHud control;

public:
  void assignHp(int* hp, int* maxhp);
  void assignEn(int* en, int* maxen);
  void assignSp(int* sp, int* maxsp);

public:
  void OnRender();
private:
  void drawHp();
  void drawEnergy();
  void drawEquipment();
  void drawAllyInfo();
};
#endif
