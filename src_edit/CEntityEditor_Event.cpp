#include "CEntityEditor.h"

void CEntityEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool CEntityEditor::handleInterr(SDL_Event* Event) {
  return false;
}

void CEntityEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CEntityEditor::OnLButtonDown(int mX, int mY) {
  SDL_Point m = {mX, mY};

  // click in workspace attempts to add/subtract entity data
  if (CAsset::inWorkspace(&m)) {
    CEntity newEntity(group_ID, entity_ID, &m);
    CEntity::entityList.push_back(newEntity);
  }
}

void CEntityEditor::OnRButtonDown(int mX, int mY) {
  SDL_Point m = {mX, mY};

}
