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
  place_hitbox  = false;
  snap_tile     = false;
}

bool CEntityEditor::OnInit() {
  if (!CEntity::OnInit()) return false;
  if (!CEntityData::init()) return false;

  updateEntityButtons();

  return true;
}


void CEntityEditor::getPosDisplace(int& dx, int& dy, const SDL_Point* m, const SDL_Rect& entR) {
  using namespace entityEngine::misc::placeRelPos;

  int x_placeCell = placePos % numpos_x;
  int y_placeCell = placePos / numpos_x;
  if (y_placeCell >= numpos_y) return;

  if (snap_tile) {
    SDL_Point map_m = CCamera::CameraControl.GetCamRelPoint(m);
    dx += (x_placeCell * TILE_SIZE / 2) - (x_placeCell + 1 == numpos_x) - (map_m.x % TILE_SIZE);
    dy += (y_placeCell * TILE_SIZE / 2) - (y_placeCell + 1 == numpos_y) - (map_m.y % TILE_SIZE);
  }

  dx += -(((x_placeCell * entR.w) / 2) - (x_placeCell + 1 == numpos_x));
  dy += -(((y_placeCell * entR.h) / 2) - (y_placeCell + 1 == numpos_y));
}

void CEntityEditor::updateEntityButtons() {
  using namespace entityEngine::misc::entityButtons;

  entityButtons.clear();
  for (int i = 0; i < CEntityData::getNumEntities(group_ID); i++)
  {
    // add buttons
    CButton button(list_x, list_y + (i * button_h), button_w, button_h);
    button.defCol = offCol;
    button.onCol  = onCol;
    button.hovCol = hovCol;
    entityButtons.push_back(button);
  }
}

void CEntityEditor::OnTerminate() {
  CEntity::entityList.clear();

  for (int i = 0; i < CEntity::textureList.size(); i++) {
    SDL_DestroyTexture(CEntity::textureList[i].img);
  } CEntity::textureList.clear();
}
