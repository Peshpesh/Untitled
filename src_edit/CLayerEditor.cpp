#include "CLayerEditor.h"

CLayerEditor CLayerEditor::Control;

namespace {
  const SDL_Rect canv           = CAsset::getWinCentRect(440, 320);
  const short subcanv_w         = canv.w / 3;
  const short b_sz              = 2;
  const SDL_Point* canvCol      = &palette::dark_cyan;

  const short title_y           = canv.y + 9;
  const short title_h           = 11;
  const SDL_Rect tbar_layer     = CAsset::getRect(canv.x,                    title_y, subcanv_w, title_h);
  const SDL_Rect tbar_option    = CAsset::getRect(tbar_layer.x + subcanv_w,  title_y, subcanv_w, title_h);
  const SDL_Rect tbar_new       = CAsset::getRect(tbar_option.x + subcanv_w, title_y, subcanv_w, title_h);
  const char* const titleLayer  = "Active Layers";
  const char* const titleOption = "Layer Options";
  const char* const titleNew    = "Make New Layer";
  const SDL_Point* tbarCol      = &palette::black;
  const SDL_Color* titletextCol = &rgb::white;
  const short z_precision       = 4;

  namespace list {
    const short layer_w           = 25;
    const short depth_w           = 109;
    const short b_h               = 11;
    const short l_x               = canv.x + (subcanv_w - (layer_w + depth_w)) / 2;
    const short l_y               = canv.y + 30;
    const short l_max             = 20;
    const SDL_Point* butCol       = &palette::silver;
    const SDL_Point* onCol        = &palette::cyan;
    const SDL_Point* hovCol       = &palette::light_cyan;
  };

  namespace options {
    const short b_w               = 120;                    // b_ for "button"
    const short b_h               = 21;
    const short f_w               = 120;                    // f_ for "float"
    const short f_h               = 11;
    const short buff_h            = 6;
    const short buff_w            = 6;
    const short d_w               = (b_w - buff_w) / 2;     // d_ for "decision"
    const short d_h               = 13;

    const short b_x               = canv.x + subcanv_w + (subcanv_w - b_w) / 2;
    const short f_x               = canv.x + subcanv_w + (subcanv_w - f_w) / 2;
    const short confirm_x         = canv.x + subcanv_w + (subcanv_w - (d_w * 2) - buff_w) / 2;
    const short cancel_x          = confirm_x + d_w + buff_w;
    const short delete_y          = canv.y + (canv.h - (((b_h + buff_h) * 2) + (f_h + buff_h) + d_h)) / 2;
    const short adjust_y          = delete_y + b_h + buff_h;
    const short f_y               = adjust_y + b_h + buff_h;
    const short d_y               = f_y + f_h + buff_h;

    const SDL_Rect delete_but     = CAsset::getRect(b_x, delete_y, b_w, b_h);
    const SDL_Rect adjust_but     = CAsset::getRect(b_x, adjust_y, b_w, b_h);
    const SDL_Rect zfield         = CAsset::getRect(f_x, f_y, f_w, f_h);
    const SDL_Rect b_confirm      = CAsset::getRect(confirm_x, d_y, d_w, d_h);
    const SDL_Rect b_cancel       = CAsset::getRect(cancel_x, d_y, d_w, d_h);

    const SDL_Point* butCol       = &palette::silver;
    const SDL_Point* onCol        = &palette::dark_green;
    const SDL_Point* offCol       = &palette::dark_gray;
    const SDL_Point* hovCol       = &palette::light_green;
    const SDL_Point* del_hovCol   = &palette::light_red;
    const SDL_Point* fCol         = &palette::white;
    const SDL_Color* ftextCol     = &rgb::black;

    const char* const del_title   = "Delete Layer";
    const char* const del_confirm = "Are You Sure?";
    const char* const adj_title   = "Adjust Depth";
    const char* const adj_info    = "Enter Z value";
    const char* const s_confirm   = "Confirm";
    const char* const s_cancel    = "Cancel";
  };

  namespace newLayer {
    const short b_w               = 120;                    // b_ for "button"
    const short b_h               = 21;
    const short f_w               = 120;                    // f_ for "float"
    const short f_h               = 11;
    const short buff_h            = 6;
    const short buff_w            = 6;
    const short d_w               = (b_w - buff_w) / 2;     // d_ for "decision"
    const short d_h               = 13;

    const short b_x               = canv.x + (subcanv_w * 2) + (subcanv_w - b_w) / 2;
    const short f_x               = canv.x + (subcanv_w * 2) + (subcanv_w - f_w) / 2;
    const short confirm_x         = canv.x + (subcanv_w * 2) + (subcanv_w - (d_w * 2) - buff_w) / 2;
    const short cancel_x          = confirm_x + d_w + buff_w;
    const short b_y               = canv.y + (canv.h - (b_h + f_h + buff_h)) / 2;
    const short f_y               = b_y + b_h + buff_h;
    const short d_y               = f_y + f_h + buff_h;

    const SDL_Rect newbut         = CAsset::getRect(b_x, b_y, b_w, b_h);
    const SDL_Rect zfield         = CAsset::getRect(f_x, f_y, f_w, f_h);
    const SDL_Rect b_confirm      = CAsset::getRect(confirm_x, d_y, d_w, d_h);
    const SDL_Rect b_cancel       = CAsset::getRect(cancel_x, d_y, d_w, d_h);

    const SDL_Point* butCol       = &palette::silver;
    const SDL_Point* onCol        = &palette::dark_green;
    const SDL_Point* hovCol       = &palette::light_green;
    const SDL_Point* fCol         = &palette::white;
    const SDL_Color* ftextCol     = &rgb::black;

    const char* const title       = "Create Layer";
    const char* const info        = "Enter Z value";
    const char* const s_confirm   = "Create";
    const char* const s_cancel    = "Cancel";
  };
}

CLayerEditor::CLayerEditor() {
  OnInit(0);
}

void CLayerEditor::OnInit(const short& layer) {
  delLayer  = false;
  adjLayer  = false;
  makeLayer = false;
  z_string  = "";
  list_pg   = 0;
  q_layer   = layer;
  resetLists();
}

void CLayerEditor::resetLists() {
  using namespace list;
  if (!layerList.empty()) layerList.clear();
  if (!depthList.empty()) depthList.clear();

  for (int i = 0; i < CScenery::layerList.size(); i++) {
    layerList.push_back(CAsset::getRect(l_x, l_y + (i * b_h), layer_w, b_h));
    depthList.push_back(CAsset::getRect(l_x + layer_w, l_y + (i * b_h), depth_w, b_h));
  }
}

void CLayerEditor::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CLayerEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleChangeLayer(&m)) return;
  if (handleDeleteLayer(&m)) return;
  if (handleAdjustLayer(&m)) return;
  if (handleNewLayer(&m)) return;
}

void CLayerEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (makeLayer || adjLayer) enterZval(sym);
  else if (delLayer) handleDeleteLayer(sym);
  else {
    switch (sym) {
      case SDLK_RETURN: terminate(); break;
      case SDLK_ESCAPE: terminate(); break;
      default: break;
    }
  }
}

bool CLayerEditor::handleChangeLayer(const SDL_Point* m) {
  using namespace list;
  for (int i = list_pg * l_max; i < (layerList.size() <= l_max ? layerList.size() : l_max * (list_pg + 1)); i++) {
    if (SDL_PointInRect(m, &layerList[i]) || SDL_PointInRect(m, &depthList[i])) {
      q_layer = i;
      return true;
    }
  }
  return false;
}

bool CLayerEditor::handleDeleteLayer(const SDL_Point* m) {
  using namespace options;

  if (delLayer) {
    if (SDL_PointInRect(m, &b_confirm)) {
      deleteLayer();
      return true;
    }
    if (SDL_PointInRect(m, &b_cancel)) {
      delLayer = false;
      return true;
    }
  }
  else if (!(makeLayer || adjLayer) && CScenery::layerList.size() > 0) {
    return delLayer = SDL_PointInRect(m, &delete_but);
  }
  return false;
}

void CLayerEditor::handleDeleteLayer(SDL_Keycode sym) {
  if (CScenery::layerList.size() > 0) {
    switch (sym) {
      case SDLK_RETURN: deleteLayer();
      case SDLK_ESCAPE: delLayer = false;
      default:          break;
    }
  }
}

bool CLayerEditor::handleAdjustLayer(const SDL_Point* m) {
  using namespace options;

  if (adjLayer) {
    if (SDL_PointInRect(m, &b_confirm)) {
      adjustLayer();
      return true;
    }
    if (SDL_PointInRect(m, &b_cancel)) {
      resetNewLayer();
      return true;
    }
  }
  else if (!(makeLayer || delLayer) && CScenery::layerList.size() > 0) {
    return adjLayer = SDL_PointInRect(m, &adjust_but);
  }
  return false;
}

bool CLayerEditor::handleNewLayer(const SDL_Point* m) {
  using namespace newLayer;
  if (makeLayer) {
    if (SDL_PointInRect(m, &b_confirm)) {
      makeNewLayer();
      return true;
    }
    if (SDL_PointInRect(m, &b_cancel)) {
      resetNewLayer();
      return true;
    }
  }
  else if (!(delLayer || adjLayer)) {
    return makeLayer = SDL_PointInRect(m, &newbut);
  }
  return false;
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
    case SDLK_ESCAPE:     resetNewLayer();    break;
    case SDLK_RETURN:     makeLayer ? makeNewLayer() : adjustLayer(); break;
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

void CLayerEditor::deleteLayer() {
  delLayer = false;
  CScenery::removeLayerIndex(q_layer);
  resetLists();
  if (q_layer >= layerList.size()) q_layer = layerList.size() - 1;
}

void CLayerEditor::adjustLayer() {
  q_layer = CScenery::adjustLayerDepth(q_layer, CAsset::strToDouble(z_string));
  if (q_layer < 0) {
    // ERROR
    CInform::InfoControl.pushInform("Error in depth adjustment");
    q_layer = 0;
  }
  resetLists();
  resetNewLayer();
}

void CLayerEditor::makeNewLayer() {
  if (z_string.empty()) {
    makeLayer = false;
    return;
  }

  // Ensure that the string represents a non-zero value
  // If any character in the string is not a '0' or floating point,
  // the string is valid for making a new layer
  int i = 0;
  while (true) {
    if (z_string[i] != '0' && z_string[i] != '.') break;
    if (z_string.size() <= ++i) {     // invalid string
      resetNewLayer();
      return;
    }
  }

  // make new layer
  q_layer = CScenery::addLayer(CAsset::strToDouble(z_string));
  if (q_layer < 0) {
    // ERROR
    CInform::InfoControl.pushInform("Error in creating layer");
    q_layer = 0;
  }
  resetLists();
  resetNewLayer();
}

void CLayerEditor::resetNewLayer() {
  z_string.clear();
  makeLayer = adjLayer = false;
}

bool CLayerEditor::OnRender(const SDL_Point* m) {
  if (m == NULL) return false;

  Font::FontControl.SetFont(FONT_MINI);

  if (!drawCanvas())    return false;
  if (!drawTitle())     return false;
  if (!drawList(m))     return false;
  if (!drawNewLayer(m)) return false;
  if (!drawOptions(m))  return false;

  return true;
}

bool CLayerEditor::drawCanvas() {
  if (!CAsset::drawStrBox(&canv, b_sz, canvCol)) return false;
  return true;
}

bool CLayerEditor::drawTitle() {
  using namespace list;
  if (!CAsset::drawBoxFill(&tbar_layer, tbarCol))   return false;
  if (!CAsset::drawBoxFill(&tbar_new, tbarCol))     return false;
  if (!CAsset::drawBoxFill(&tbar_option, tbarCol))  return false;

  Font::NewCenterWrite(titleLayer, &tbar_layer, titletextCol);
  Font::NewCenterWrite(titleNew, &tbar_new, titletextCol);
  Font::NewCenterWrite(titleOption, &tbar_option, titletextCol);

  return true;
}

bool CLayerEditor::drawList(const SDL_Point* m) {
  using namespace list;

  std::string N;
  std::string Z;

  for (int i = list_pg * l_max; i < (layerList.size() <= l_max ? layerList.size() : l_max * (list_pg + 1)); i++) {
    const SDL_Point* col = (i == q_layer) ? onCol : (
                            (SDL_PointInRect(m, &depthList[i]) || SDL_PointInRect(m, &layerList[i])) ?
                            hovCol : butCol);

    if (!CAsset::drawStrBox(&layerList[i], b_sz, col)) return false;
    if (!CAsset::drawStrBox(&depthList[i], b_sz, col)) return false;
    N = Font::intToStr(i);
    Z = Font::doubleToStr(CScenery::layerList[i], z_precision);
    Font::NewCenterWrite(N.c_str(), &layerList[i]);
    Font::NewCenterWrite(Z.c_str(), &depthList[i]);
  }
  return true;
}

bool CLayerEditor::drawNewLayer(const SDL_Point* m) {
  using namespace newLayer;

  const SDL_Point* col = makeLayer ? onCol : (SDL_PointInRect(m, &newbut) ? hovCol : butCol);

  if (!CAsset::drawStrBox(&newbut, b_sz, col)) return false;
  Font::NewCenterWrite(makeLayer ? info : title, &newbut);

  if (makeLayer) {
    if (!CAsset::drawBoxFill(&zfield, fCol)) return false;
    if (!CAsset::drawStrBox(&b_confirm, b_sz, SDL_PointInRect(m, &b_confirm) ? hovCol : butCol)) return false;
    if (!CAsset::drawStrBox(&b_cancel, b_sz, SDL_PointInRect(m, &b_cancel) ? hovCol : butCol)) return false;

    Font::FontControl.setDynamic();
    Font::NewCenterWrite(z_string.c_str(), &zfield, ftextCol);
    Font::NewCenterWrite(s_confirm, &b_confirm);
    Font::NewCenterWrite(s_cancel, &b_cancel);
  }
  return true;
}

bool CLayerEditor::drawOptions(const SDL_Point* m) {
  using namespace options;
  const SDL_Point* col;

  bool anyLayers = CScenery::layerList.size();

  col = adjLayer ? onCol : (
        (makeLayer || !anyLayers) ? offCol : (
        !delLayer && SDL_PointInRect(m, &adjust_but) ? hovCol : butCol));
  if (!CAsset::drawStrBox(&adjust_but, b_sz, col)) return false;

  col = delLayer ? onCol : (
        (adjLayer || makeLayer || !anyLayers) ? offCol : (
        SDL_PointInRect(m, &delete_but) ? del_hovCol : butCol));
  if (!CAsset::drawStrBox(&delete_but, b_sz, col)) return false;

  Font::NewCenterWrite(del_title, &delete_but);
  Font::NewCenterWrite(!delLayer ? (adjLayer ? adj_info : adj_title) : del_confirm, &adjust_but);

  if (adjLayer || delLayer) {
    if (adjLayer) {
      if (!CAsset::drawBoxFill(&zfield, fCol)) return false;
      Font::FontControl.setDynamic();
      Font::NewCenterWrite(z_string.c_str(), &zfield, ftextCol);
    }
    if (!CAsset::drawStrBox(&b_confirm, b_sz, SDL_PointInRect(m, &b_confirm) ? hovCol : butCol)) return false;
    if (!CAsset::drawStrBox(&b_cancel, b_sz, SDL_PointInRect(m, &b_cancel) ? hovCol : butCol)) return false;

    Font::NewCenterWrite(s_confirm, &b_confirm);
    Font::NewCenterWrite(s_cancel, &b_cancel);
  }
  return true;
}

void CLayerEditor::terminate() {
  CInterrupt::removeFlag(INTRPT_CHANGE_LA);
  layerList.clear();
  depthList.clear();
}

unsigned short CLayerEditor::getRecentLayer() {
  return (q_layer < 0) ? 0 : q_layer;
}

unsigned short CLayerEditor::getZPrecision() {
  return (z_precision < 0) ? 0 : z_precision;
}
