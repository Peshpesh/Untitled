#include "CEntityEditor.h"

void CEntityEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool CEntityEditor::handleInterr(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_CH_ENTITY)) {
    //
  }
  else if (CInterrupt::isFlagOn(INTRPT_CH_ENTGRP)) {
    //
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

  if (handleAddEntity(&m)) return;
  if (handleChEntity(&m)) return;
  if (handleChGroup(&m)) return;
  if (handleEntityMeter(&m)) return;
  if (handleHitboxMeter(&m)) return;
  if (handleSwitchView(&m)) return;
  if (handleEntityList(&m)) return;
}

bool CEntityEditor::handleAddEntity(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;

  // click in workspace attempts to add entity data
  CEntity newEntity(group_ID, entity_ID, m);
  CEntity::entityList.push_back(newEntity);

  return true;
}

bool CEntityEditor::handleChEntity(const SDL_Point* m) {
  using namespace entityEngine::buttons::chEntity;

  if (SDL_PointInRect(m, &button.dstR)) {
    CInterrupt::appendFlag(INTRPT_CH_ENTITY);
    return true;
  }
  return false;
}

bool CEntityEditor::handleChGroup(const SDL_Point* m) {
  using namespace entityEngine::buttons::chGroup;

  if (SDL_PointInRect(m, &button.dstR)) {
    CInterrupt::appendFlag(INTRPT_CH_ENTGRP);
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

bool CEntityEditor::handleEntityList(const SDL_Point* m) {

  for (int i = 0; i < entityButtons.size(); i++) {
    if (SDL_PointInRect(m, &entityButtons[i].dstR)) {
      entity_ID = i;
      return true;
    }
  }

  return false;
}

void CEntityEditor::OnRButtonDown(int mX, int mY) {
  SDL_Point m = {mX, mY};

}
