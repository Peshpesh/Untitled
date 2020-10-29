#include "CPlanScenery.h"

void CPlanScenery::OnRender() {
  SDL_Point pos; // rendering position
  pos.x = X;
  pos.y = Y - (Z * TILE_SIZE);
  pos = CCamera::CameraControl.GetWinRelPoint(pos);
  CSurface::OnDraw(img, &srcR, &pos);
}

void CPlanScenery::OnRenderShadow() {
  if (!has_shadow) return;

  SDL_Point pos; // rendering position
  pos.x = X;
  pos.y = Y - (Z * TILE_SIZE);
  pos = CCamera::CameraControl.GetWinRelPoint(pos);
  CSurface::OnDraw(img_shd, &srcR, &pos);
}

bool CPlanScnEdit::OnRender(const SDL_Point& m) {
  Font::FontControl.SetFont(FONT_MINI);
  if (CInterrupt::isNone()) {
    if (!drawWorkingScenery(m)) return false;
  }

  OnRenderYBase();

  if (!OnRenderSettings(&m)) return false;
  return true;
}

void CPlanScnEdit::OnRenderYBase() {
  using namespace pvmScenery::ybase;
  SDL_Point pos; // rendering position
  SDL_Rect lin;  // base-line
  lin.h = 1;
  if (showYBase) {
    for (int i = 0; i < scnList_back.size(); i++) {
      pos.x = scnList_back[i].X + (scnList_back[i].srcR.w / 2);
      pos.y = scnList_back[i].Y_base - (scnList_back[i].Z * TILE_SIZE);
      pos = CCamera::CameraControl.GetWinRelPoint(pos);
      Font::NewCenterWrite(FONT_MINI, "X", &pos, back_col);
      lin.x = pos.x - (scnList_back[i].srcR.w / 2);
      lin.y = pos.y;
      lin.w = scnList_back[i].srcR.w;
      CAsset::drawBoxFill(&lin, back_col_pt);
    }
    for (int i = 0; i < scnList_front.size(); i++) {
      pos.x = scnList_front[i].X + (scnList_front[i].srcR.w / 2);
      pos.y = scnList_front[i].Y_base - (scnList_front[i].Z * TILE_SIZE);
      pos = CCamera::CameraControl.GetWinRelPoint(pos);
      Font::NewCenterWrite(FONT_MINI, "X", &pos, front_col);
      lin.x = pos.x - (scnList_front[i].srcR.w / 2);
      lin.y = pos.y;
      lin.w = scnList_front[i].srcR.w;
      CAsset::drawBoxFill(&lin, front_col_pt);
    }
  }
}

bool CPlanScnEdit::OnRenderSettings(const SDL_Point* m) {
  Font::FontControl.SetFont(FONT_MINI);
  bool no_intrpt = CInterrupt::isNone();

  if (!drawAnchor(no_intrpt ? m : NULL)) return false;
  if (!drawAnchDisplace(no_intrpt ? m : NULL)) return false;

  if (!CAsset::drawAppFrame()) return false;

  if (!drawChScenery(no_intrpt ? m : NULL, no_intrpt)) return false;
  // if (!drawChLayer(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawLayerBrief(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawSceneryList(no_intrpt ? m : NULL, no_intrpt)) return false;
  if (!drawPlaceRelPos(no_intrpt ? m : NULL, no_intrpt)) return false;
  // if (!drawOpacLayer()) return false;
  // if (!drawOpacOther()) return false;
  if (!drawSwitchView()) return false;
  if (!drawSwitchPlace()) return false;

  if (!no_intrpt) {
    if (!drawIntrpt(m)) return false;
  }
  return true;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

bool CPlanScnEdit::drawWorkingScenery(const SDL_Point& m) {
  using namespace pvmScenery::ybase;
  if (!showWorkScenery) return true;

  SDL_Rect srcR = CSceneryData::getDecorDims(group_ID, decor_ID);

  int X = m.x;
  int Y = m.y;

  if (lock_to_grid) {
    // correct for camera offset
    X += CCamera::CameraControl.GetX();
    Y += CCamera::CameraControl.GetY();
  }

  getPosDisplace(X, Y, srcR);

  if (lock_to_grid) {
    // return to window-relative
    X -= CCamera::CameraControl.GetX();
    Y -= CCamera::CameraControl.GetY();
  }

  SDL_Rect dstR = {X, Y, srcR.w, srcR.h};

  if (!CSurface::OnDraw(img, &srcR, &dstR)) return false;

  if (showYBase) {
    int Y_base = CSceneryData::getYBase(group_ID, decor_ID, Y, srcR.h);
    SDL_Point pos; // rendering position
    pos.x = X + (srcR.w / 2);
    pos.y = Y_base;
    Font::NewCenterWrite(FONT_MINI, "X", &pos, work_col);
  }

  return true;
}

bool CPlanScnEdit::drawChScenery(const SDL_Point* m, const bool& hov) {
  using namespace pvmScenery::buttons::chScenery;

  if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CHANGE_SC))) {
    return false;
  }
  Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
  return true;
}

// bool CPlanScnEdit::drawChLayer(const SDL_Point* m, const bool& hov) {
//   using namespace pvmScenery::buttons::chLayer;
//
//   if (!button.OnRender(m, hov, CInterrupt::isFlagOn(INTRPT_CHANGE_LA))) {
//     return false;
//   }
//   Font::NewCenterWrite(FONT_MINI, label, &button.dstR);
//   return true;
// }

bool CPlanScnEdit::drawLayerBrief(const SDL_Point* m, const bool& hov) {
  using namespace pvmScenery::misc::layerBrief;

  std::string vals[] = {
    Font::intToStr(CPlanArea::control.LayerList.size()),
    Font::intToStr(k),
    Font::intToStr(CPlanArea::control.LayerList[k].Z)
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

bool CPlanScnEdit::drawSceneryList(const SDL_Point* m, const bool& hov) {
  using namespace pvmScenery::misc::sceneryButtons;
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

    // how many buttons remain?
    int butts_remain = sceneryButtons.size() - (list_page * max_buttons);
    if (butts_remain > max_buttons) {
      next_option = true;
    }
    CAsset::drawBoxFill(&prev_pg, prev_option ? (m && SDL_PointInRect(m, &prev_pg) ? hovCol : onCol) : offCol);
    CAsset::drawBoxFill(&curr_pg, offCol);
    CAsset::drawBoxFill(&next_pg, next_option ? (m && SDL_PointInRect(m, &next_pg) ? hovCol : onCol) : offCol);
    std::string page_str = Font::intToStr(list_page);
    Font::NewCenterWrite(page_str.c_str(), &curr_pg);
    Font::NewCenterWrite("$L$L", &prev_pg);
    Font::NewCenterWrite("$R$R", &next_pg);
  }
  return true;
}

bool CPlanScnEdit::drawPlaceRelPos(const SDL_Point* m, const bool& hov) {
  using namespace pvmScenery::buttons::placeRelPos;
  using namespace pvmScenery::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    buttons[i].OnRender(m, hov, (placePos == i));
  }
  return true;
}

// bool CPlanScnEdit::drawOpacLayer() {
//   using namespace pvmScenery::meters::opacLayer;
//   return meter.OnRender((double)(layer_alpha) / MAX_RGBA, label);
// }
//
// bool CPlanScnEdit::drawOpacOther() {
//   using namespace pvmScenery::meters::opacOther;
//   return meter.OnRender((double)(other_alpha) / MAX_RGBA, label);
// }

bool CPlanScnEdit::drawSwitchView() {
  using namespace pvmScenery::switches;
  using namespace pvmScenery::switches::view;

  const bool flags[] = {
    showYBase,
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

bool CPlanScnEdit::drawSwitchPlace() {
  using namespace pvmScenery::switches;
  using namespace pvmScenery::switches::place;

  const bool flags[] = {
    render_with_map,
    lock_to_grid,
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

bool CPlanScnEdit::drawAnchor(const SDL_Point* m) {
  using namespace pvmScenery::anchor;

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

bool CPlanScnEdit::drawAnchDisplace(const SDL_Point* m) {
  using namespace pvmScenery::anchor::disp;

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

bool CPlanScnEdit::drawIntrpt(const SDL_Point* m) {
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_SC)) {
    if (!CChangeScenery::Control.OnRender(m)) return false;
  }
  // if (CInterrupt::isFlagOn(INTRPT_CHANGE_LA)) {
  //   if (!CLayerEditor::Control.OnRender(m)) return false;
  // }
  return true;
}
