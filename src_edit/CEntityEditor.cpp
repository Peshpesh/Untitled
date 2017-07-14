#include "CEntityEditor.h"

CEntityEditor CEntityEditor::Control;

CEntityEditor::CEntityEditor()
{
  showEntity = true;
  showHitbox = true;
  showWorkEntity = true;
  showWorkHitbox = true;
  entity_alpha = MAX_RGBA;
  hitbox_alpha = MAX_RGBA;

  group_ID  = Entities::groups::GLOBAL;
  entity_ID = Entities::global::PLAYER;
}

bool CEntityEditor::OnInit() {
  if (!CEntity::OnInit()) return false;

  using namespace entityEngine::misc::entityButtons;
  for (int i = 0; i < CEntityData::getNumEntities(Entities::groups::GLOBAL); i++)
  {
    // add buttons
  }

  return true;
}

void CEntityEditor::OnTerminate() {
  CEntity::entityList.clear();

  for (int i = 0; i < CEntity::textureList.size(); i++) {
    SDL_DestroyTexture(CEntity::textureList[i].img);
  } CEntity::textureList.clear();

}
