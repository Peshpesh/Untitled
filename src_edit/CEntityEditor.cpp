#include "CEntityEditor.h"

CEntityEditor CEntityEditor::Control;

CEntityEditor::CEntityEditor()
{
  showEntity = true;
  showHitbox = true;
  entity_alpha = MAX_RGBA;
  hitbox_alpha = MAX_RGBA / 4;

  group_ID  = Entities::groups::GLOBAL;
  entity_ID = Entities::global::PLAYER;
}

bool CEntityEditor::OnInit() {
  if (!CEntity::OnInit()) return false;

  return true;
}

void CEntityEditor::OnTerminate() {
  CEntity::entityList.clear();

  for (int i = 0; i < CEntity::textureList.size(); i++) {
    SDL_DestroyTexture(CEntity::textureList[i].img);
  } CEntity::textureList.clear();

}
