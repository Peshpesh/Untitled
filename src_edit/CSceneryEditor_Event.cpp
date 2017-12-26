#include "CSceneryEditor.h"

void CSceneryEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool CSceneryEditor::handleInterr(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_SC)) {
    CChangeScenery::Control.OnEvent(Event);
    if (CInterrupt::isFlagOff(INTRPT_CHANGE_SC)) {
      CChangeScenery::Control.handleChanges(group_ID, decor_ID);
      updateSceneryButtons();
    }
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_LA)) {
    CLayerEditor::Control.OnEvent(Event);
    if (CInterrupt::isFlagOff(INTRPT_CHANGE_LA)) {
      layer = CLayerEditor::Control.getRecentLayer();
    }
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_GRAB_ANCH | INTRPT_MAKE_ANCH)) {
    CAnchorScenery::Control.OnEvent(Event);
    return true;
  }
  return false;
}

void CSceneryEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CSceneryEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleChScenery(&m)) return;
  if (handleChLayer(&m)) return;
  if (handleBriefChange(&m)) return;
  if (handleLayerMeter(&m)) return;
  if (handleOtherMeter(&m)) return;
  if (handleSwitchView(&m)) return;
  if (handleSwitchPlace(&m)) return;
  if (handleSceneryList(&m)) return;
  if (handlePlaceRelPos(&m)) return;
  if (handleGrabAnchor(&m)) return;
  if (handleMakeAnchor(&m)) return;
  if (handleAdvAnchor(&m)) return;
  if (handleArchDisplace(&m)) return;
  if (handleAddScenery(&m)) return;
}

void CSceneryEditor::OnRButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleRemoveScenery(&m)) return;
}

bool CSceneryEditor::handleAddScenery(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;
  // click in workspace attempts to add scenery data

  if (CScenery::layerList.size() == 0) {
    CInform::InfoControl.pushInform("Cannot add scenery--\nNo Layers exist");
    return false;
  }

  SDL_Rect srcR = CSceneryData::getDecorDims(group_ID, decor_ID);

  if (use_anchor) {
    double X = CAnchorScenery::Control.getRelX();
    double Y = CAnchorScenery::Control.getRelY();
    getPosDisplace(X, Y, srcR);
    if (!CScenery::addScenery(group_ID, decor_ID, X, Y, layer)) {
      // error
      CInform::InfoControl.pushInform("Error\ncould not add scenery");
    }
  } else {
    int X = m->x;
    int Y = m->y;
    getPosDisplace(X, Y, srcR);

    const SDL_Point dstP = {X, Y};
    if (!CScenery::addScenery(group_ID, decor_ID, &dstP, layer)) {
      // error
      CInform::InfoControl.pushInform("Error\ncould not add scenery");
    }
  }

  return true;
}

bool CSceneryEditor::handleRemoveScenery(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;
  // click in workspace attempts to remove scenery data

  if (CScenery::layerList.size() == 0) return false;
  if (CScenery::sceneryList.size() == 0) return false;

  for (int i = CScenery::sceneryList.size() - 1; i >= 0; i--) {
    if (layer == CScenery::sceneryList[i].layer) {
      double true_x = CScenery::sceneryList[i].true_x;
      double true_y = CScenery::sceneryList[i].true_y;
      double z = CScenery::layerList[layer];
      double rel_x = CCamera::CameraControl.trueXToRel(true_x, z);
      double rel_y = CCamera::CameraControl.trueYToRel(true_y, z);
      int w = CScenery::sceneryList[i].srcR.w;
      int h = CScenery::sceneryList[i].srcR.h;
      SDL_Point w_pos = CCamera::CameraControl.GetWinRelPoint(rel_x, rel_y);
      SDL_Rect w_rec = CAsset::getRect(w_pos.x, w_pos.y, w, h);
      if (SDL_PointInRect(m, &w_rec)) {
        CScenery::sceneryList.erase(CScenery::sceneryList.begin() + i);
        break;
      }
    }
  }
  return true;
}

bool CSceneryEditor::handleChScenery(const SDL_Point* m) {
  using namespace sceneryEngine::buttons::chScenery;

  if (SDL_PointInRect(m, &button.dstR)) {
    CChangeScenery::Control.OnInit(group_ID, decor_ID);
    CInterrupt::appendFlag(INTRPT_CHANGE_SC);
    return true;
  }
  return false;
}

bool CSceneryEditor::handleChLayer(const SDL_Point* m) {
  using namespace sceneryEngine::buttons::chLayer;

  if (SDL_PointInRect(m, &button.dstR)) {
    CLayerEditor::Control.OnInit(layer);
    CInterrupt::appendFlag(INTRPT_CHANGE_LA);
    return true;
  }
  return false;
}

bool CSceneryEditor::handleBriefChange(const SDL_Point* m) {
  using namespace sceneryEngine::misc::layerBrief;
  if (CScenery::layerList.size() == 0) return false;

  if (SDL_PointInRect(m, &l_button)) {
    if (layer == 0) layer = CScenery::layerList.size() - 1;
    else layer--;
    return true;
  }
  if (SDL_PointInRect(m, &r_button)) {
    if (++layer >= CScenery::layerList.size()) layer = 0;
    return true;
  }
  return false;
}

bool CSceneryEditor::handleLayerMeter(const SDL_Point* m) {
  using namespace sceneryEngine::meters::opacLayer;

  if (SDL_PointInRect(m, &meter.dstR)) {
    double fract = 0.0;
    if (meter.clickPos(m, fract)) layer_alpha = fract * MAX_RGBA;
    return true;
  }
  return false;
}

bool CSceneryEditor::handleOtherMeter(const SDL_Point* m) {
  using namespace sceneryEngine::meters::opacOther;

  if (SDL_PointInRect(m, &meter.dstR)) {
    double fract = 0.0;
    if (meter.clickPos(m, fract)) other_alpha = fract * MAX_RGBA;
    return true;
  }
  return false;
}

bool CSceneryEditor::handleSwitchView(const SDL_Point* m) {
  using namespace sceneryEngine::switches::view;

  bool* flags[] = {
    &showScenery,
    &showWorkScenery
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handleSwitchPlace(const SDL_Point* m) {
  using namespace sceneryEngine::switches::place;

  bool* flags[] = {
    &use_anchor,
    &show_anchor
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handleSceneryList(const SDL_Point* m) {
  for (int i = 0; i < sceneryButtons.size(); i++) {
    if (SDL_PointInRect(m, &sceneryButtons[i].dstR)) {
      decor_ID = i;
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handlePlaceRelPos(const SDL_Point* m) {
  using namespace sceneryEngine::buttons::placeRelPos;
  using namespace sceneryEngine::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      placePos = i;
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handleGrabAnchor(const SDL_Point* m) {
  using namespace sceneryEngine::anchor;

  if (!CScenery::sceneryList.empty() && SDL_PointInRect(m, &grab_anch.dstR)) {
    CAnchorScenery::Control.OnInit(layer);
    CInterrupt::appendFlag(INTRPT_GRAB_ANCH);
    return true;
  }
  return false;
}

bool CSceneryEditor::handleMakeAnchor(const SDL_Point* m) {
  using namespace sceneryEngine::anchor;

  if (!CScenery::layerList.empty() && SDL_PointInRect(m, &make_anch.dstR)) {
    CAnchorScenery::Control.OnInit(layer);
    CInterrupt::appendFlag(INTRPT_MAKE_ANCH);
    return true;
  }
  return false;
}

bool CSceneryEditor::handleAdvAnchor(const SDL_Point* m) {
  using namespace sceneryEngine::anchor;

  if (SDL_PointInRect(m, &adv_anch.dstR)) {
    CAnchorScenery::Control.advanceAnchor();
    return true;
  }
  return false;
}

bool CSceneryEditor::handleArchDisplace(const SDL_Point* m) {
  using namespace sceneryEngine::anchor::disp;

  // Buttons are oriented left-to-right, top-to-bottom in order.
  for (int i = X_MINUS; i <= Y_PLUS; i++) {
    if (SDL_PointInRect(m, &lr_buttons[i])) {
      switch (i) {
        case X_MINUS: CAnchorScenery::Control.disp_x--; break;
        case X_PLUS:  CAnchorScenery::Control.disp_x++; break;
        case Y_MINUS: CAnchorScenery::Control.disp_y--; break;
        case Y_PLUS:  CAnchorScenery::Control.disp_y++; break;
        default: break;
      }
      return true;
    }
  }
  return false;
}
