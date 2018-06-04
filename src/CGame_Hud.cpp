#include "CGame.h"

CHud::CHud() {
  //
}

bool CHud::OnRender() {
  double hp_frac = (double)(CGame::control.Hero.Health) / CGame::control.Hero.MaxHealth;
  SDL_Rect test = {10, 10, 100 * hp_frac, 20};
  return CAsset::drawBoxFill(test, &palette::red);
}
