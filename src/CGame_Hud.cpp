#include "CGame.h"

namespace hud {
  const short x = 24;
  const short y_bf = 8;
  const SDL_Rect c_equip  = {x, y_bf, 24, 24};
  const SDL_Rect hp_bar   = {x, c_equip.y + c_equip.h + y_bf, 100, 8};
  const SDL_Rect en_bar   = {x, hp_bar.y + hp_bar.h, 100, 8};
  const SDL_Point p_s_hp  = {hp_bar.x + hp_bar.w, hp_bar.y};
  const SDL_Point p_s_en  = {en_bar.x + en_bar.w, en_bar.y};
  const SDL_Rect ally     = {x, en_bar.y + en_bar.h + y_bf, 24, 24};
  const SDL_Color* hp_col = &rgb::red;
  const SDL_Color* en_col = &rgb::cyan;
  const SDL_Color* sp_col = &rgb::green;
  const SDL_Color* no_col = &rgb::dark_gray;
}

CHud::CHud() {
  //
}

bool CHud::OnRender() {
  if (!drawHp()) return false;
  if (!drawEnergy()) return false;
  if (!drawEquipment()) return false;
  if (!drawAllyInfo()) return false;
  return true;
}

bool CHud::drawHp() {
  using namespace hud;

  double hp_frac = (double)(CGame::control.Hero.Health) / CGame::control.Hero.MaxHealth;
  SDL_Rect hp_fill = {hp_bar.x, hp_bar.y, hp_bar.w * hp_frac, hp_bar.h};
  if (!CAsset::drawBoxFill(hp_bar, *no_col)) return false;
  if (!CAsset::drawBoxFill(hp_fill, *hp_col)) return false;

  std::string s_hp = CAsset::intToStr(CGame::control.Hero.Health) + "$L" + CAsset::intToStr(CGame::control.Hero.MaxHealth);
  CType::Write(FONT_MINI, s_hp.c_str(), p_s_hp, hp_col);

  return true;
}

bool CHud::drawEnergy() {
  using namespace hud;

  double en_frac = 0.9; //(double)(CGame::control.Hero.Health) / CGame::control.Hero.MaxHealth;

  SDL_Rect en_fill = {en_bar.x, en_bar.y, en_bar.w * en_frac, en_bar.h};
  if (!CAsset::drawBoxFill(en_bar, *no_col)) return false;
  if (!CAsset::drawBoxFill(en_fill, *en_col)) return false;

  std::string s_en = CAsset::intToStr(0) + "$L" + CAsset::intToStr(0);
  CType::Write(FONT_MINI, s_en.c_str(), p_s_en, en_col);

  return true;
}

bool CHud::drawEquipment() {
  using namespace hud;
  if (!CAsset::drawBoxFill(c_equip, *no_col)) return false;
  return true;
}

bool CHud::drawAllyInfo() {
  using namespace hud;
  if (!CAsset::drawBoxFill(ally, *no_col)) return false;
  return true;
}
