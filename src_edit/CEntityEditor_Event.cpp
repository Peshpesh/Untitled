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

void CEntityEditor::OnRButtonDown(int mX, int mY) {
  SDL_Point m = {mX, mY};

}
