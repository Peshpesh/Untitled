#include "CEntityEditor.h"

void CEntityEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool CEntityEditor::handleInterr(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_EN)) {
    CChangeEntity::Control.OnEvent(Event);
    if (CInterrupt::isFlagOff(INTRPT_CHANGE_EN)) {
      CChangeEntity::Control.handleChanges(group_ID, entity_ID);
      updateEntityButtons();
    }
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_MODIFY_HB)) {
    CHitboxEditor::Control.OnEvent(Event);
    return true;
  }
  return false;
}

void CEntityEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CEntityEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleChEntity(&m)) return;
  if (handleEditHitbox(&m)) return;
  if (handleEntityMeter(&m)) return;
  if (handleHitboxMeter(&m)) return;
  if (handleBriefChange(&m)) return;
  if (handleSwitchView(&m)) return;
  if (handleSwitchPlace(&m)) return;
  if (handleEntityList(&m)) return;
  if (handlePlaceRelPos(&m)) return;
  if (handleAddEntity(&m)) return;
}

bool CEntityEditor::handleAddEntity(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;
  // click in workspace attempts to add entity data

  SDL_Rect srcR = CEntityData::getEntityDims(group_ID, entity_ID);
  SDL_Rect hitR = CEntityData::getHitboxDims(group_ID, entity_ID);

  if (!*planview) {
    int X = (*planview || place_hitbox) ? m->x - hitR.x : m->x;
    int Y = (*planview || place_hitbox) ? m->y - hitR.y : m->y;
    getPosDisplace(X, Y, m, place_hitbox ? hitR : srcR);

    // correct for camera offset
    X += CCamera::CameraControl.GetX();
    Y += CCamera::CameraControl.GetY();

    const SDL_Point dstP = {X, Y};
    CEntity newEntity(group_ID, entity_ID, &dstP);
    CEntity::entityList.push_back(newEntity);
  } else {
    int X = m->x - hitR.x;
    int Y = m->y - hitR.y;
    short Z = CPlanArea::control.getZ(*k);
    getPosDisplace(X, Y, m, hitR);

    // correct for depth
    Y += Z * TILE_SIZE;

    // correct for camera offset
    X += CCamera::CameraControl.GetX();
    Y += CCamera::CameraControl.GetY();

    CPlanEntity newEntity(group_ID, entity_ID, X, Y, Z);

    if (render_with_map) {
      // For objects rendered with each map layer, we must
      // place the new object in the correct spot based on Y_base AND Z.
      // ... Group and order first by layer, then order each layer group by Y_base.
      // Note: as i->size, Z increases. Y increases with i amongst objs with equal Z.
      int i = 0;
      while (i < CEntity::entList_back.size()) {
        short cmp_Z    = CEntity::entList_back[i].Z;
        int cmp_Y_base = CEntity::entList_back[i].Y_base;
        // compared obj is at higher Z; place new obj at "end" of objs with equal Z
        if (Z < cmp_Z) break;
        // new obj Z exists; compared obj is at higher Y_base (in front of new obj)
        if (Z == cmp_Z && newEntity.Y_base < cmp_Y_base) break;
        i++;
      }
      CEntity::entList_back.insert(CEntity::entList_back.begin() + i, newEntity);
    } else {
      // For objects rendered after all maps and shadows are drawn, the ordering
      // primarily depends on Y_base. On the rare instance that objects share Y_base,
      // the object with lower Z is rendered first. If Y_base and Z are shared,
      // no specific ordering is done (depends on when the objects were added).
      int i = 0;
      while (i < CEntity::entList_front.size()) {
        short cmp_Z    = CEntity::entList_front[i].Z;
        int cmp_Y_base = CEntity::entList_front[i].Y_base;
        if (newEntity.Y_base < cmp_Y_base) break;
        if (newEntity.Y_base == cmp_Y_base && Z < cmp_Z) break;
        i++;
      }
      CEntity::entList_front.insert(CEntity::entList_front.begin() + i, newEntity);
    }
  }

  CEntity::CheckCollide();
  return true;
}

bool CEntityEditor::handleChEntity(const SDL_Point* m) {
  using namespace entityEngine::buttons::chEntity;

  if (SDL_PointInRect(m, &button.dstR)) {
    CChangeEntity::Control.OnInit(group_ID, entity_ID);
    CInterrupt::appendFlag(INTRPT_CHANGE_EN);
    return true;
  }
  return false;
}

bool CEntityEditor::handleEditHitbox(const SDL_Point* m) {
  using namespace entityEngine::buttons::editHitbox;

  if (SDL_PointInRect(m, &button.dstR)) {
    if (!CHitboxEditor::Control.OnInit(group_ID, entity_ID)) {
      // problem
      CInform::InfoControl.pushInform("---error---\nhitbox editor init failed");
    }
    else {
      CInterrupt::appendFlag(INTRPT_MODIFY_HB);
    }
    return true;
  }
  return false;
}

bool CEntityEditor::handleEntityMeter(const SDL_Point* m) {
  using namespace entityEngine::meters::opacEntity;

  if (!*planview) {
    if (SDL_PointInRect(m, &meter.dstR)) {
      double fract = 0.0;
      if (meter.clickPos(m, fract)) {
        entity_alpha = fract * MAX_RGBA;
        for (int i = 0; i < CEntity::textureList.size(); i++) {
          SDL_SetTextureAlphaMod(CEntity::textureList[i].img, entity_alpha);
        }
      }
      return true;
    }
  }
  return false;
}

bool CEntityEditor::handleHitboxMeter(const SDL_Point* m) {
  if (*planview) return false;
  using namespace entityEngine::meters::opacHitbox;

  if (SDL_PointInRect(m, &meter.dstR)) {
    double fract = 0.0;
    if (meter.clickPos(m, fract)) {
      hitbox_alpha = fract * MAX_RGBA;
    }
    return true;
  }
  return false;
}

bool CEntityEditor::handleBriefChange(const SDL_Point* m) {
  using namespace entityEngine::misc::layerBrief;
  if (!*planview) return false;
  if (CPlanArea::control.LayerList.size() <= 1) return false;

  if (SDL_PointInRect(m, &l_button)) {
    if (*k == 0) *k = CPlanArea::control.LayerList.size() - 1;
    else (*k)--;
    return true;
  }
  if (SDL_PointInRect(m, &r_button)) {
    if (++(*k) >= CPlanArea::control.LayerList.size()) *k = 0;
    return true;
  }
  return false;
}

bool CEntityEditor::handleSwitchView(const SDL_Point* m) {
  using namespace entityEngine::switches::view;

  bool* flags[] = {
    &showEntity,
    &showHitbox,
    &showWorkEntity,
    &showWorkHitbox
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}

bool CEntityEditor::handleSwitchPlace(const SDL_Point* m) {
  if (*planview) return false;
  using namespace entityEngine::switches::place;

  bool* flags[] = {
    &place_hitbox,
    &snap_tile
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}

bool CEntityEditor::handleEntityList(const SDL_Point* m) {
  using namespace entityEngine::misc::entityButtons;

  int i = list_page * max_buttons;
  while (i < entityButtons.size() && i < (list_page + 1) * max_buttons) {
    if (SDL_PointInRect(m, &entityButtons[i].dstR)) {
      entity_ID = i;
      return true;
    } i++;
  }

  if (entityButtons.size() > max_buttons) {
    // true if "previous" button is valid
    bool prev_option = list_page;

    // true if "next" button is valid
    bool next_option = (entityButtons.size() - (list_page * max_buttons)) > max_buttons;

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

bool CEntityEditor::handlePlaceRelPos(const SDL_Point* m) {
  using namespace entityEngine::buttons::placeRelPos;
  using namespace entityEngine::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      placePos = i;
      return true;
    }
  }
  return false;
}

void CEntityEditor::OnRButtonDown(int mX, int mY) {
  SDL_Point m = {mX, mY};
  if (handleRmEntity(&m)) return;
}

bool CEntityEditor::handleRmEntity(const SDL_Point* m) {
  if (!*planview) {
    const SDL_Point mAbs = CCamera::CameraControl.GetCamRelPoint(*m);
    for (int i = CEntity::entityList.size() - 1; i >= 0; i--) {
      const SDL_Rect dstR = { CEntity::entityList[i].dstP.x,
                              CEntity::entityList[i].dstP.y,
                              CEntity::entityList[i].srcR.w,
                              CEntity::entityList[i].srcR.h  };
      if (SDL_PointInRect(&mAbs, &dstR)) {
        CEntity::entityList.erase(CEntity::entityList.begin() + i);
        CEntity::CheckCollide();
        return true;
      }
    }
  }
  return false;
}
