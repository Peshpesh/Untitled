#include "CSceneryEditor.h"

bool CSceneryEditor::OnRender(const SDL_Point* m) {
  Font::FontControl.SetFont(FONT_MINI);
  bool no_intrpt = CInterrupt::isNone();

  if (no_intrpt) {
    if (!drawWorkingScenery(m)) return false;
  }
  if (!CAsset::drawAppFrame()) return false;
  if (!drawChScenery(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawChLayer(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawLayerBrief(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawSceneryList(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawPlaceRelPos(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawOpacLayer()) return false;
  if (!drawOpacOther()) return false;
  if (!drawSwitchView()) return false;
  if (!drawSwitchPlace()) return false;
  if (!drawAnchor(no_intrpt ? m : NULL)) return false;
  if (!drawAnchDisplace(no_intrpt ? m : NULL)) return false;
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

  getPosDisplace(X, Y, srcR);
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

  if (m) {
    CAsset::drawBoxFill(&l_button, SDL_PointInRect(m, &l_button) ? hovCol : butCol);
    CAsset::drawBoxFill(&r_button, SDL_PointInRect(m, &r_button) ? hovCol : butCol);
  } else {
    CAsset::drawBoxFill(&l_button, butCol);
    CAsset::drawBoxFill(&r_button, butCol);
  }
  Font::NewCenterWrite("$L", &l_button);
  Font::NewCenterWrite("$R", &r_button);

  return true;
}

bool CSceneryEditor::drawSceneryList(const SDL_Point* m, const bool& hov) {
  using namespace sceneryEngine::misc::sceneryButtons;
  std::string name;

  int i = list_page * max_buttons;
  while (i < sceneryButtons.size() && i < (list_page + 1) * max_buttons) {
    if (!sceneryButtons[i].OnRender(m, (hov && i != decor_ID), (i == decor_ID))) return false;
    name = CSceneryData::getDecorName(group_ID, i);
    Font::NewCenterWrite(name.c_str(), &sceneryButtons[i].dstR);
    i++;
  }

  if (sceneryButtons.size() > max_buttons) {
    bool prev_option = list_page; // true if "previous" button is valid
    bool next_option = false;     // true if "next" button is valid

    // how many buttons on this page?
    int butts_on_page = sceneryButtons.size() - (list_page * max_buttons);
    if (butts_on_page > max_buttons) {
      butts_on_page = max_buttons;
      next_option = true;
    }

    int pg_y = list_y + (butts_on_page * button_h);
    SDL_Rect prev_pg = CAsset::getRect(list_x, pg_y, pg_button_w, pg_button_h);
    SDL_Rect curr_pg = CAsset::getRect(list_x + pg_button_w, pg_y, pg_button_w, pg_button_h);
    SDL_Rect next_pg = CAsset::getRect(list_x + pg_button_w + pg_button_w, pg_y, pg_button_w, pg_button_h);
    CAsset::drawBoxFill(&prev_pg, prev_option ? (SDL_PointInRect(m, &prev_pg) ? hovCol : onCol) : offCol);
    CAsset::drawBoxFill(&curr_pg, offCol);
    CAsset::drawBoxFill(&next_pg, next_option ? (SDL_PointInRect(m, &next_pg) ? hovCol : onCol) : offCol);
    std::string page_str = Font::intToStr(list_page);
    Font::NewCenterWrite(page_str.c_str(), &curr_pg);
    Font::NewCenterWrite("$L$L", &prev_pg);
    Font::NewCenterWrite("$R$R", &next_pg);
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
    use_anchor,
    show_anchor
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (!buttons[i].OnRender(flags[i])) return false;

    const SDL_Point tPos = {buttons[i].dstR.x + lab_x_offset, buttons[i].dstR.y + lab_y_offset};
    Font::Write(FONT_MINI, labels[i], &tPos);
  }
  return true;
}

bool CSceneryEditor::drawAnchor(const SDL_Point* m) {
  using namespace sceneryEngine::anchor;

  if (show_anchor) {
    if (!CAnchorScenery::Control.OnRender()) return false;
  }

  if (!grab_anch.OnRender(m, true, CInterrupt::isFlagOn(INTRPT_GRAB_ANCH))) return false;
  Font::NewCenterWrite(label_grab, &grab_anch.dstR);
  if (!make_anch.OnRender(m, true, CInterrupt::isFlagOn(INTRPT_MAKE_ANCH))) return false;
  Font::NewCenterWrite(label_make, &make_anch.dstR);
  if (!adv_anch.OnRender(m, true)) return false;
  Font::NewCenterWrite(label_adv, &adv_anch.dstR);

  return true;
}

bool CSceneryEditor::drawAnchDisplace(const SDL_Point* m) {
  using namespace sceneryEngine::anchor::disp;

  bool hov[] = {
    m ? SDL_PointInRect(m, &lr_buttons[0]) : false,
    m ? SDL_PointInRect(m, &lr_buttons[1]) : false,
    m ? SDL_PointInRect(m, &lr_buttons[2]) : false,
    m ? SDL_PointInRect(m, &lr_buttons[3]) : false,
  };

  if (!CAsset::drawBoxFill(&field_h_disp, fieldCol)) return false;
  if (!CAsset::drawBoxFill(&field_v_disp, fieldCol)) return false;

  for (int i = 0; i < sizeof(hov) / sizeof(hov[0]); i++) {
    if (!CAsset::drawBoxFill(&lr_buttons[i], hov[i] ? hovCol : butCol)) return false;
    Font::NewCenterWrite((i % 2) ? "$R" : "$L", &lr_buttons[i]);
  }

  std::string field;
  field = label_h_disp + Font::intToStr(CAnchorScenery::Control.disp_x);
  Font::NewCenterWrite(field.c_str(), &field_h_disp);
  field = label_v_disp + Font::intToStr(CAnchorScenery::Control.disp_y);
  Font::NewCenterWrite(field.c_str(), &field_v_disp);

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
