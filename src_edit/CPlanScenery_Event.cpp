#include "CPlanScenery.h"

void CPlanScnEdit::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool CPlanScnEdit::handleInterr(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_SC)) {
    CChangeScenery::Control.OnEvent(Event);
    if (CInterrupt::isFlagOff(INTRPT_CHANGE_SC)) {
      short tmp_group = group_ID;
      CChangeScenery::Control.handleChanges(tmp_group, decor_ID);
      changeGroup(tmp_group);
    }
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_GRAB_ANCH | INTRPT_MAKE_ANCH)) {
    CAnchorScenery::Control.OnEvent(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_ADJ_PVSCN)) {
    if (target == NULL) {
      // ...
    }
  }
  return false;
}

void CPlanScnEdit::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (CInterrupt::isFlagOn(INTRPT_ADJ_PVSCN)) {
    if (sym == SDLK_ESCAPE || sym == SDLK_RETURN) {
      if (target != NULL) {
        delete target;
        target = NULL;
      }
      target_scn = NULL;
      CInterrupt::removeFlag(INTRPT_ADJ_PVSCN);
    } else if (target == NULL) {
      switch (sym) {
        case SDLK_LEFT:   target_scn->X--; break;
        case SDLK_RIGHT:  target_scn->X++; break;
        case SDLK_UP:     target_scn->Y--; target_scn->Y_base--; break;
        case SDLK_DOWN:   target_scn->Y++; target_scn->Y_base++; break;
        default: break;
      }
    }
  }
}

void CPlanScnEdit::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CInterrupt::isFlagOn(INTRPT_ADJ_PVSCN)) {
    // if we're here, then that must mean a
    // target dropdown menu is open or a move is underway
    if (target != NULL) handleTargetMenu(&m);
    else {
      // left-click during a move will stop the move
      target_scn = NULL;
      CInterrupt::removeFlag(INTRPT_ADJ_PVSCN);
    }
  } else {
    // if (target_scn != NULL && CAsset::inWorkspace(&m)) target_scn = NULL;

    if (handleChScenery(&m)) return;
    // if (handleChLayer(&m)) return;
    if (handleBriefChange(&m)) return;
    // if (handleLayerMeter(&m)) return;
    // if (handleOtherMeter(&m)) return;
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
}

void CPlanScnEdit::OnRButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CInterrupt::isFlagOn(INTRPT_ADJ_PVSCN)) {
    delete target;
    target = NULL;
    target_scn = NULL;
    CInterrupt::removeFlag(INTRPT_ADJ_PVSCN);
  }
  if (handleTargetScenery(&m)) return;
}

bool CPlanScnEdit::handleAddScenery(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;
  // click in workspace attempts to add scenery data

  if (CPlanArea::control.LayerList.size() == 0) {
    CInform::InfoControl.pushInform("Cannot add scenery--\nNo Layers exist");
    return false;
  }

  SDL_Rect srcR = CSceneryData::getDecorDims(group_ID, decor_ID);
  int X = use_anchor ? CAnchorScenery::Control.getRelX() : m->x;
  int Y = use_anchor ? CAnchorScenery::Control.getRelY() : m->y;
  int Z = CPlanArea::control.getZ(k);

  // correct for camera offset
  X += CCamera::CameraControl.GetX();
  Y += CCamera::CameraControl.GetY();

  getPosDisplace(X, Y, srcR);

  // correct for depth
  Y += Z * TILE_SIZE;

  addScenery(X, Y, Z);
  return true;
}

bool CPlanScnEdit::handleTargetScenery(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;

  for (int i = scnList_front.size() - 1; i >= 0; i--) {
    if (scnList_front[i].Z == CPlanArea::control.getZ(k)) {
      SDL_Rect dstR;
      dstR.x = scnList_front[i].X;
      dstR.y = scnList_front[i].Y - (scnList_front[i].Z * TILE_SIZE);
      dstR.w = scnList_front[i].srcR.w;
      dstR.h = scnList_front[i].srcR.h;
      CCamera::CameraControl.MakeWinRel(dstR.x, dstR.y);
      if (SDL_PointInRect(m, &dstR)) {
        target = new SDL_Point;
        target->x = m->x;
        target->y = m->y;
        target_scn = &scnList_front[i];
        CInterrupt::appendFlag(INTRPT_ADJ_PVSCN);
        return true;
      }
    }
  }

  for (int i = scnList_back.size() - 1; i >= 0; i--) {
    if (scnList_back[i].Z == CPlanArea::control.getZ(k)) {
      SDL_Rect dstR;
      dstR.x = scnList_back[i].X;
      dstR.y = scnList_back[i].Y - (scnList_back[i].Z * TILE_SIZE);
      dstR.w = scnList_back[i].srcR.w;
      dstR.h = scnList_back[i].srcR.h;
      CCamera::CameraControl.MakeWinRel(dstR.x, dstR.y);
      if (SDL_PointInRect(m, &dstR)) {
        target = new SDL_Point;
        target->x = m->x;
        target->y = m->y;
        target_scn = &scnList_back[i];
        CInterrupt::appendFlag(INTRPT_ADJ_PVSCN);
        return true;
      }
    }
  }
  return false;
}

void CPlanScnEdit::handleTargetMenu(const SDL_Point* m) {
  using namespace pvmScenery::dropmenu;

  enum {
    TARGET_MOVE = 0,
    TARGET_DEL
  };

  for (int j = 0; j < nopts; j++) {
    SDL_Rect b = {target->x, target->y + button_h*j, button_w, button_h};
    if (SDL_PointInRect(m, &b)) {
      switch (j) {
        case TARGET_MOVE: {
          // close the menu but keep the interrupt active
          delete target;
          target = NULL;
          return;
          break;
        }
        case TARGET_DEL: {
          delete target;
          target = NULL;
          CInterrupt::removeFlag(INTRPT_ADJ_PVSCN);
          // find and delete the targeted scenery
          for (int i = scnList_front.size() - 1; i >= 0; i--) {
            if (target_scn == &scnList_front[i]) {
              target_scn = NULL;
              scnList_front.erase(scnList_front.begin() + i);
              return;
            }
          }
          for (int i = scnList_back.size() - 1; i >= 0; i--) {
            if (target_scn == &scnList_back[i]) {
              target_scn = NULL;
              scnList_back.erase(scnList_back.begin() + i);
              return;
            }
          }
          break;
        }
        default: break;
      }
    }
  }
  delete target;
  target = NULL;
  target_scn = NULL;
  CInterrupt::removeFlag(INTRPT_ADJ_PVSCN);
}

bool CPlanScnEdit::handleChScenery(const SDL_Point* m) {
  using namespace pvmScenery::buttons::chScenery;

  if (SDL_PointInRect(m, &button.dstR)) {
    CChangeScenery::Control.OnInit(group_ID, decor_ID, img);
    CInterrupt::appendFlag(INTRPT_CHANGE_SC);
    return true;
  }
  return false;
}

// bool CPlanScnEdit::handleChLayer(const SDL_Point* m) {
//   using namespace pvmScenery::buttons::chLayer;
//
//   if (SDL_PointInRect(m, &button.dstR)) {
//     CLayerEditor::Control.OnInit(layer);
//     CInterrupt::appendFlag(INTRPT_CHANGE_LA);
//     return true;
//   }
//   return false;
// }

bool CPlanScnEdit::handleBriefChange(const SDL_Point* m) {
  using namespace pvmScenery::misc::layerBrief;
  if (CPlanArea::control.LayerList.size() <= 1) return false;

  if (SDL_PointInRect(m, &l_button)) {
    if (k == 0) k = CPlanArea::control.LayerList.size() - 1;
    else k--;
    return true;
  }
  if (SDL_PointInRect(m, &r_button)) {
    if (++k >= CPlanArea::control.LayerList.size()) k = 0;
    return true;
  }
  return false;
}

// bool CPlanScnEdit::handleLayerMeter(const SDL_Point* m) {
//   using namespace pvmScenery::meters::opacLayer;
//
//   if (SDL_PointInRect(m, &meter.dstR)) {
//     double fract = 0.0;
//     if (meter.clickPos(m, fract)) layer_alpha = fract * MAX_RGBA;
//     return true;
//   }
//   return false;
// }
//
// bool CPlanScnEdit::handleOtherMeter(const SDL_Point* m) {
//   using namespace pvmScenery::meters::opacOther;
//
//   if (SDL_PointInRect(m, &meter.dstR)) {
//     double fract = 0.0;
//     if (meter.clickPos(m, fract)) other_alpha = fract * MAX_RGBA;
//     return true;
//   }
//   return false;
// }

bool CPlanScnEdit::handleSwitchView(const SDL_Point* m) {
  using namespace pvmScenery::switches::view;

  bool* flags[] = {
    &showYBase,
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

bool CPlanScnEdit::handleSwitchPlace(const SDL_Point* m) {
  using namespace pvmScenery::switches::place;

  bool* flags[] = {
    &render_with_map,
    &lock_to_grid,
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

bool CPlanScnEdit::handleSceneryList(const SDL_Point* m) {
  using namespace pvmScenery::misc::sceneryButtons;

  int i = list_page * max_buttons;
  while (i < sceneryButtons.size() && i < (list_page + 1) * max_buttons) {
    if (SDL_PointInRect(m, &sceneryButtons[i].dstR)) {
      decor_ID = i;
      return true;
    } i++;
  }

  if (sceneryButtons.size() > max_buttons) {
    // true if "previous" button is valid
    bool prev_option = list_page;

    // true if "next" button is valid
    bool next_option = (sceneryButtons.size() - (list_page * max_buttons)) > max_buttons;

    if (prev_option && SDL_PointInRect(m, &prev_pg)) {
      list_page--;
      return true;
    } else if (next_option && SDL_PointInRect(m, &next_pg)) {
      list_page++;
      return true;
    }
  }
  return false;
}

bool CPlanScnEdit::handlePlaceRelPos(const SDL_Point* m) {
  using namespace pvmScenery::buttons::placeRelPos;
  using namespace pvmScenery::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      placePos = i;
      return true;
    }
  }
  return false;
}

bool CPlanScnEdit::handleGrabAnchor(const SDL_Point* m) {
  using namespace pvmScenery::anchor;

  if (SDL_PointInRect(m, &grab_anch.dstR)) {
    CAnchorScenery::Control.OnInit(k);
    CInterrupt::appendFlag(INTRPT_GRAB_ANCH);
    return true;
  }
  return false;
}

bool CPlanScnEdit::handleMakeAnchor(const SDL_Point* m) {
  using namespace pvmScenery::anchor;

  if (SDL_PointInRect(m, &make_anch.dstR)) {
    CAnchorScenery::Control.OnInit(k);
    CInterrupt::appendFlag(INTRPT_MAKE_ANCH);
    return true;
  }
  return false;
}

bool CPlanScnEdit::handleAdvAnchor(const SDL_Point* m) {
  using namespace pvmScenery::anchor;

  if (SDL_PointInRect(m, &adv_anch.dstR)) {
    CAnchorScenery::Control.advanceAnchor();
    return true;
  }
  return false;
}

bool CPlanScnEdit::handleArchDisplace(const SDL_Point* m) {
  using namespace pvmScenery::anchor::disp;

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
