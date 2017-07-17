#include "CChangeEntity.h"

CChangeEntity CChangeEntity::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(300, 200);
  // const SDL_Rect fnameBox       = {225,210,190,11};
  // const SDL_Rect titleBox       = {225,193,190,16};
  // const SDL_Rect infoBox        = {225,222,190,40};
  // const SDL_Rect okButton       = {255,270,60,13};
  // const SDL_Rect cancelButton   = {325,270,60,13};
  // const SDL_Point* canvCol      = &palette::black;
  // const SDL_Point* fnameBoxCol  = &palette::white;
  // const SDL_Point* optCol       = &palette::black;
  // const SDL_Point* optHovCol    = &palette::light_indigo;
  // const SDL_Point* bCol         = &palette::white;
  // const SDL_Color* textCol      = &rgb::white;
  // const SDL_Color* fnameCol     = &rgb::dark_red;
  // const short bstrsiz = 2;
  // const short cstrsiz = 3;
}

CChangeEntity::CChangeEntity() {
  succ = false;
}

void CChangeEntity::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CChangeEntity::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: break;
    case SDLK_ESCAPE: break;
    default: break;
  }
}

void CChangeEntity::OnLButtonDown(int mX, int mY) {
  //
}

bool CChangeEntity::OnRender(const SDL_Point* m) {
  return true;
}
