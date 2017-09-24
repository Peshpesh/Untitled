#include "CLayerEditor.h"

CLayerEditor CLayerEditor::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(600, 440);
  const short b_sz              = 2;
  const SDL_Point* canvCol      = &palette::dark_violet;
  const short layer_w           = 25;
  const short depth_w           = 109;
  const short but_h             = 11;
  const short list_x            = canv.x + (canv.w - (layer_w + depth_w)) / 2;
  const short list_y            = canv.y + 30;
  const SDL_Point* butCol       = &palette::silver;
  const SDL_Point* onCol        = &palette::dark_green;
  const SDL_Point* hovCol       = &palette::light_cyan;
  const short z_precision       = 4;
}

CLayerEditor::CLayerEditor() {
  OnInit();
}

void CLayerEditor::OnInit() {
  makeLayer = false;
  z_string  = "";
  resetLists();
}

void CLayerEditor::resetLists() {
  if (!layerList.empty()) layerList.clear();
  if (!depthList.empty()) depthList.clear();

  for (int i = 0; i < CScenery::layerList.size(); i++) {
    layerList.push_back(CAsset::getRect(list_x, list_y + (i * but_h), layer_w, but_h));
    depthList.push_back(CAsset::getRect(list_x + layer_w, list_y + (i * but_h), depth_w, but_h));
  }
}

void CLayerEditor::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CLayerEditor::OnLButtonDown(int mX, int mY) {

}

void CLayerEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (makeLayer) enterZval(sym);
  else {
    switch (sym) {
      case SDLK_RETURN: terminate(); break;
      case SDLK_ESCAPE: terminate(); break;
      default: break;
    }
  }
}

void CLayerEditor::enterZval(SDL_Keycode sym) {
  switch (sym) {
    case SDLK_0:	        addToZ('0');	      break;
    case SDLK_1:	        addToZ('1');	      break;
    case SDLK_2:	        addToZ('2');	      break;
    case SDLK_3:	        addToZ('3');	      break;
    case SDLK_4:	        addToZ('4');	      break;
    case SDLK_5:	        addToZ('5');	      break;
    case SDLK_6:	        addToZ('6');	      break;
    case SDLK_7:	        addToZ('7');	      break;
    case SDLK_8:	        addToZ('8');	      break;
    case SDLK_9:	        addToZ('9');	      break;
    case SDLK_PERIOD:     addToZ('.');        break;
    case SDLK_BACKSPACE:  delFromZ();         break;
    case SDLK_RETURN:     newLayer();         break;
    case SDLK_ESCAPE:     makeLayer = false;  break;
    default:              break;
  }
}

void CLayerEditor::addToZ(const char& sym) {
  // don't add a zero if the string is empty
  if (z_string.empty() && sym == '0') return;

  // if the requested add is a period,
  // it can only be added if no other periods are in the string.
  // Also, if the period is added when the string is empty, a leading
  // zero must be added.
  if (sym == '.') {
    if (z_string.empty()) z_string.push_back('0');
    else {
      for (int i = 0; i < z_string.size(); i++) {
        if (z_string[i] == sym) return;
      }
    }
  }
  // if the requested add is anything other than a period,
  // it cannot be added to the string if there are already 4 digits on either
  // side of the floating point (z_precision = 4).
  else {
    bool fract = false;
    short fract_i = 0;
    for (int i = 0; i < z_string.size(); i++) {
      if (z_string[i] == '.') {
        fract = true;
        fract_i = i;
        break;
      }
    }
    if (!fract && z_string.size() >= z_precision) return;
    if (z_string.size() - fract_i  > z_precision) return;
  }
  // if the program flow makes it to this point in this function,
  // then we are able to push back the requested symbol.
  z_string.push_back(sym);
}

void CLayerEditor::delFromZ() {
  if (z_string == "0.") z_string.clear();
  else if (z_string.size() > 0) z_string.erase(z_string.end() - 1);
}

void CLayerEditor::newLayer() {
  if (z_string.empty()) return;

  int i = 0;
  while (true) {
    if (z_string[i] != '0' && z_string[i] != '.') break;
    if (z_string.size() <= ++i) return;
  }
  // make new layer
}

bool CLayerEditor::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  if (!drawCanvas())    return false;
  if (!drawList(m))     return false;
  if (!drawOptions(m))  return false;

  return true;
}

bool CLayerEditor::drawCanvas() {
  Font::FontControl.SetFont(FONT_MINI);
  if (!CAsset::drawStrBox(&canv, b_sz, canvCol)) return false;
  return true;
}

bool CLayerEditor::drawList(const SDL_Point* m) {
  std::string N;
  std::string Z;
  for (int i = 0; i < layerList.size(); i++) {
    if (!CAsset::drawStrBox(&layerList[i], b_sz, butCol)) return false;
    if (!CAsset::drawStrBox(&depthList[i], b_sz, butCol)) return false;
    N = Font::intToStr(i);
    Z = Font::doubleToStr(CScenery::layerList[i], z_precision);
    Font::NewCenterWrite(N.c_str(), &layerList[i]);
    Font::NewCenterWrite(Z.c_str(), &depthList[i]);
  }
  return true;
}

bool CLayerEditor::drawOptions(const SDL_Point* m) {
  return true;
}

void CLayerEditor::terminate() {
  CInterrupt::removeFlag(INTRPT_CHANGE_LA);
  layerList.clear();
  depthList.clear();
}
