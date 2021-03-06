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

  int X = place_hitbox ? m->x - hitR.x : m->x;
  int Y = place_hitbox ? m->y - hitR.y : m->y;

  getPosDisplace(X, Y, m, place_hitbox ? hitR : srcR);
  const SDL_Point dstP = {X, Y};
  CEntity newEntity(group_ID, entity_ID, &dstP);
  CEntity::entityList.push_back(newEntity);
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
  return false;
}

bool CEntityEditor::handleHitboxMeter(const SDL_Point* m) {
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
  for (int i = 0; i < entityButtons.size(); i++) {
    if (SDL_PointInRect(m, &entityButtons[i].dstR)) {
      entity_ID = i;
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
  return false;
}
