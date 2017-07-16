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
  placePos  = entityEngine::misc::placeRelPos::TOP_LEFT;
}

bool CEntityEditor::OnInit() {
  if (!CEntity::OnInit()) return false;

  using namespace entityEngine::misc::entityButtons;
  for (int i = 0; i < CEntityData::getNumEntities(Entities::groups::GLOBAL); i++)
  {
    // add buttons
    CButton button(list_x, list_y + (i * button_h), button_w, button_h);
    button.defCol = offCol;
    button.onCol  = onCol;
    button.hovCol = hovCol;
    entityButtons.push_back(button);
  }
  return true;
}

void CEntityEditor::OnTerminate() {
  CEntity::entityList.clear();

  for (int i = 0; i < CEntity::textureList.size(); i++) {
    SDL_DestroyTexture(CEntity::textureList[i].img);
  } CEntity::textureList.clear();
}
