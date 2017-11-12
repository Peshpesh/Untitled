#include "CSceneryEditor.h"

bool CSceneryEditor::OnRender(const SDL_Point* m) {
  bool no_intrpt = CInterrupt::isNone();

  if (no_intrpt) {
    if (!drawWorkingScenery(m)) return false;
  }
  if (!CAsset::drawAppFrame()) return false;
  if (!drawChScenery(m, no_intrpt)) return false;
  if (!drawChLayer(m, no_intrpt)) return false;
  if (!drawLayerBrief(m, no_intrpt)) return false;
  if (!drawSceneryList(m, no_intrpt)) return false;
  if (!drawPlaceRelPos(m, no_intrpt)) return false;
  if (!drawOpacLayer()) return false;
  if (!drawOpacOther()) return false;
  if (!drawSwitchView()) return false;
  if (!drawSwitchPlace()) return false;
  if (!no_intrpt) {
    if (!drawIntrpt(m)) return false;
  }
  return true;
}

bool CSceneryEditor::drawBackground(int& N) {
  if (!showScenery) return true;

  // Draw background scenery
  setOpacity(other_alpha);

  while (N > 0) {
    if (CScenery::layerList[CScenery::sceneryList[N-1].layer] < 1.0) break;
    N--;

    if (!has_rendered_active) {
      if (!render_active && CScenery::sceneryList[N].layer == layer) {
        setOpacity(layer_alpha);
        render_active = true;
      }
      else if (render_active && CScenery::sceneryList[N].layer != layer) {
        setOpacity(other_alpha);
        render_active = false;
        has_rendered_active = true;
      }
    }
    if (!CScenery::sceneryList[N].OnRender()) return false;
  }
  return true;
}

bool CSceneryEditor::drawForeground(int& N) {
  // Draw foreground scenery
  if (showScenery) {
    while (N > 0) {
      if (CScenery::layerList[CScenery::sceneryList[N-1].layer] > 1.0) break;
      N--;

      if (!has_rendered_active) {
        if (!render_active && CScenery::sceneryList[N].layer == layer) {
          setOpacity(layer_alpha);
          render_active = true;
        }
        else if (render_active && CScenery::sceneryList[N].layer != layer) {
          setOpacity(other_alpha);
          render_active = false;
          has_rendered_active = true;
        }
      }
      if (!CScenery::sceneryList[N].OnRender()) return false;
    }
  }

  setOpacity(layer_alpha);
  render_active = false;
  has_rendered_active = false;

  return true;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

bool CSceneryEditor::drawWorkingScenery(const SDL_Point* m) {
  if (!showWorkScenery) return true;

  SDL_Rect srcR = CSceneryData::getDecorDims(group_ID, decor_ID);

  int X = m->x;
  int Y = m->y;

  getPosDisplace(X, Y, m, srcR);
  SDL_Rect dstR = {X, Y, srcR.w, srcR.h};

  return CSurface::OnDraw(CScenery::fetchTexture(group_ID), &srcR, &dstR);
}

bool CSceneryEditor::drawChScenery(const SDL_Point* m, const bool& hov) {
  using namespace sceneryEngine::buttons::chScenery;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CHANGE_SC))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CSceneryEditor::drawChLayer(const SDL_Point* m, const bool& hov) {
  using namespace sceneryEngine::buttons::chLayer;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CHANGE_LA))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

bool CSceneryEditor::drawLayerBrief(const SDL_Point* m, const bool& hov) {
  using namespace sceneryEngine::misc::layerBrief;

  std::string vals[] = {
    Font::intToStr(CScenery::layerList.size()),
    Font::intToStr(layer),
    Font::doubleToStr(CScenery::getLayerZ(layer), CLayerEditor::Control.getZPrecision())
  };

  Font::FontControl.SetFont(FONT_MINI);
  for (int i = 0; i < num_fields; i++) {
    CAsset::drawBoxFill(&fields[i], fieldCol);
    vals[i] = labels[i] + vals[i];
    Font::NewCenterWrite(vals[i].c_str(), &fields[i]);
  }

  CAsset::drawBoxFill(&l_button, SDL_PointInRect(m, &l_button) ? hovCol : butCol);
  CAsset::drawBoxFill(&r_button, SDL_PointInRect(m, &r_button) ? hovCol : butCol);
  Font::NewCenterWrite("$L", &l_button);
  Font::NewCenterWrite("$R", &r_button);

  return true;
}

bool CSceneryEditor::drawSceneryList(const SDL_Point* m, const bool& hov) {
  Font::FontControl.SetFont(FONT_MINI);
  std::string name;
  for (int i = 0; i < sceneryButtons.size(); i++) {
    if (!sceneryButtons[i].OnRender(m, (hov && i != decor_ID), (i == decor_ID))) return false;
    name = CSceneryData::getDecorName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &sceneryButtons[i].dstR);
  }
  return true;
}

bool CSceneryEditor::drawPlaceRelPos(const SDL_Point* m, const bool& hov) {
  using namespace sceneryEngine::buttons::placeRelPos;
  using namespace sceneryEngine::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    buttons[i].OnRender(m, hov, (placePos == i));
  }
  return true;
}

bool CSceneryEditor::drawOpacLayer() {
  using namespace sceneryEngine::meters::opacLayer;
  return meter.OnRender((double)(layer_alpha) / MAX_RGBA, label);
}

bool CSceneryEditor::drawOpacOther() {
  using namespace sceneryEngine::meters::opacOther;
  return meter.OnRender((double)(other_alpha) / MAX_RGBA, label);
}

bool CSceneryEditor::drawSwitchView() {
  using namespace sceneryEngine::switches;
  using namespace sceneryEngine::switches::view;

  const bool flags[] = {
    showScenery,
    showWorkScenery
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (!buttons[i].OnRender(flags[i])) return false;

    const SDL_Point tPos = {buttons[i].dstR.x + lab_x_offset, buttons[i].dstR.y + lab_y_offset};
    Font::Write(FONT_MINI, labels[i], &tPos);
  }
  return true;
}

bool CSceneryEditor::drawSwitchPlace() {
  using namespace sceneryEngine::switches;
  using namespace sceneryEngine::switches::place;

  const bool flags[] = {
    snap_scenery
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (!buttons[i].OnRender(flags[i])) return false;

    const SDL_Point tPos = {buttons[i].dstR.x + lab_x_offset, buttons[i].dstR.y + lab_y_offset};
    Font::Write(FONT_MINI, labels[i], &tPos);
  }
  return true;
}

bool CSceneryEditor::drawIntrpt(const SDL_Point* m) {
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_SC)) {
    if (!CChangeScenery::Control.OnRender(m)) return false;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_LA)) {
    if (!CLayerEditor::Control.OnRender(m)) return false;
  }
  return true;
}
