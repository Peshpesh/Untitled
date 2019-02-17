#include "CSimulate.h"

bool CSimulate::OnRender(const SDL_Point* m) {
  bool intrpt = !(CInterrupt::isNone());
  if (!CAsset::drawAppFrame()) return false;

  if (intrpt && !drawIntrpt(m)) return false;
  return true;
}

bool CSimulate::drawIntrpt(const SDL_Point* m) {
  return true;
}
