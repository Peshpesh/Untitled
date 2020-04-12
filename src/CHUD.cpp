#include "CHUD.h"

CHud CHud::control;

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
  hp = maxhp = NULL;
  en = maxen = NULL;
  sp = maxsp = NULL;
}

void CHud::assignHp(int* hp, int* maxhp) {
  this->hp    = hp;
  this->maxhp = maxhp;
}

void CHud::assignEn(int* en, int* maxen) {
  this->en    = en;
  this->maxen = maxen;
}

void CHud::assignSp(int* sp, int* maxsp) {
  this->sp    = sp;
  this->maxsp = maxsp;
}

void CHud::OnRender() {
  drawHp();
  drawEnergy();
  drawEquipment();
  drawAllyInfo();
}

void CHud::drawHp() {
  using namespace hud;
  if (hp == NULL || maxhp == NULL) return;

  double hp_frac = (double)(*hp) / *maxhp;
  SDL_Rect hp_fill = {hp_bar.x, hp_bar.y, hp_bar.w * hp_frac, hp_bar.h};
  if (!CAsset::drawBoxFill(hp_bar, *no_col)) return;
  if (!CAsset::drawBoxFill(hp_fill, *hp_col)) return;

  std::string s_hp = CUtil::intToStr(*hp) + "$L" + CUtil::intToStr(*maxhp);
  CType::Write(FONT_MINI, s_hp.c_str(), p_s_hp, hp_col);
}

void CHud::drawEnergy() {
  using namespace hud;
  if (en == NULL || maxen == NULL) return;

  double en_frac = (double)(*en) / *maxen;
  SDL_Rect en_fill = {en_bar.x, en_bar.y, en_bar.w * en_frac, en_bar.h};
  if (!CAsset::drawBoxFill(en_bar, *no_col)) return;
  if (!CAsset::drawBoxFill(en_fill, *en_col)) return;

  std::string s_en = CUtil::intToStr(*en) + "$L" + CUtil::intToStr(*maxen);
  CType::Write(FONT_MINI, s_en.c_str(), p_s_en, en_col);
}

void CHud::drawEquipment() {
  using namespace hud;
  if (!CAsset::drawBoxFill(c_equip, *no_col)) return;
}

void CHud::drawAllyInfo() {
  using namespace hud;
  if (!CAsset::drawBoxFill(ally, *no_col)) return;
}
