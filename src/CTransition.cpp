#include "CTransition.h"

CTransition CTransition::control;

namespace {
  const short reset_time = 250;  // milliseconds
  const short delay_time = 300;  // milliseconds
}

CTransition::CTransition() {
  activated = false;
  fadeout_timer = fadein_timer = delay_timer = last_time = 0;
  locationID = location::DEFAULT;
  X = Y = 0;
  mode = APP_MODE_TITLE;
  color = rgb::black;
}

void CTransition::setColor(const SDL_Color& color) {
  this->color = color;
}

void CTransition::reqTrans(const int& loc, const int &X, const int &Y) {
  if (loc < 0 || loc >= location::num) return;

  fadeout_timer = fadein_timer = reset_time;
  delay_timer = delay_time;
  last_time = SDL_GetTicks();

  locationID = loc;
  this->X = X;
  this->Y = Y;
}

void CTransition::reqReset() {
  fadeout_timer = fadein_timer = reset_time;
  delay_timer = delay_time;
  last_time = SDL_GetTicks();
  locationID = location::DEFAULT;
  X = Y = 0;
}

void CTransition::reqMode(const app_module& mode) {
  if (!CMode::isFlagOn(mode)) {
    this->mode = mode;
    switch_mode = true;
  }
}

bool CTransition::isActive() {
  return (fadeout_timer || fadein_timer || delay_timer);
}

app_module CTransition::getMode() {
  return mode;
}

void CTransition::OnLoop() {
  if (fadeout_timer) {
    fadeout_timer -= (SDL_GetTicks() - last_time);
    last_time = SDL_GetTicks();
    if (fadeout_timer <= 0) {
      fadeout_timer = 0;
      activated = true;
      if (switch_mode) changeMode();
    }
  } else if (delay_timer) {
    if (!activated) {
      delay_timer -= (SDL_GetTicks() - last_time);
      if (delay_timer < 0) delay_timer = 0;
    } last_time = SDL_GetTicks();
  } else if (fadein_timer) {
    fadein_timer -= (SDL_GetTicks() - last_time);
    if (fadein_timer < 0) fadein_timer = 0;
    last_time = SDL_GetTicks();
  }
}

bool CTransition::OnRender() {
  if (fadeout_timer) {
    return wipeout();
  } else if (delay_timer) {
    return blank();
  } else if (fadein_timer) {
    return wipein();
  }
  return true;
}

bool CTransition::wipeout() {
  // left-to-right wipe (TO color)
  int w = ((float)(WWIDTH * (reset_time - fadeout_timer)) / reset_time);
  SDL_Rect fill = {0, 0, w, WHEIGHT};
  return CAsset::drawBoxFill(fill, color);
}

bool CTransition::blank() {
  // blank screen between fades
  SDL_Rect fill = {0, 0, WWIDTH, WHEIGHT};
  return CAsset::drawBoxFill(fill, color);
}

bool CTransition::wipein() {
  // left-to-right wipe (FROM color)
  int w = ((float)(WWIDTH * fadein_timer) / reset_time);
  SDL_Rect fill = {WWIDTH - w, 0, w, WHEIGHT};
  return CAsset::drawBoxFill(fill, color);
}

void CTransition::changeMode() {
  CMode::changeFlag(mode);
  switch_mode = false;
}
