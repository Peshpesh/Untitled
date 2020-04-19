#ifndef _C_MODULE_H_
#define _C_MODULE_H_

#include "CSimulate.h"
#include "CAsset.h"
#include "CFont.h"
#include "CInterrupt.h"

enum {
  MODIFY_MAP = 0,
  MODIFY_NPC,
  MODIFY_SCENE,
  MODIFY_SIM,
  MODIFY_OPTIONS,
};

class CModule {
  CModule();
public:
  static CModule control;
  int active_mod;

  void renderSwitch(const SDL_Point& m);
  bool handleSwitch(const SDL_Point& m);
};

#endif
