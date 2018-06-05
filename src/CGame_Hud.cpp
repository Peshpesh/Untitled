#include "CGame.h"

namespace hud {
  const SDL_Color* hp_col = &rgb::red;
  const SDL_Color* sh_col = &rgb::cyan;
  const SDL_Color* sp_col = &rgb::green;
  const SDL_Color* em_col = &rgb::dark_gray;
  const SDL_Rect hp_bar = {32, 32, 100, 10};
  const SDL_Rect sh_bar = {32, 42, 100, 10};
}

CHud::CHud() {
  //
}

bool CHud::OnRender() {
  using namespace hud;
  double hp_frac = (double)(CGame::control.Hero.Health) / CGame::control.Hero.MaxHealth;

  SDL_Rect hp_fill = {hp_bar.x, hp_bar.y, hp_bar.w * hp_frac, hp_bar.h};
  if (!CAsset::drawBoxFill(hp_bar, *em_col)) return false;
  if (!CAsset::drawBoxFill(hp_fill, *hp_col)) return false;

  double sh_frac = 0.9; //(double)(CGame::control.Hero.Health) / CGame::control.Hero.MaxHealth;

  SDL_Rect sh_fill = {sh_bar.x, sh_bar.y, sh_bar.w * sh_frac, sh_bar.h};
  if (!CAsset::drawBoxFill(sh_bar, *em_col)) return false;
  if (!CAsset::drawBoxFill(sh_fill, *sh_col)) return false;
  return true;
}
