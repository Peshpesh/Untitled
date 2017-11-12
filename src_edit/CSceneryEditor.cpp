#include "CSceneryEditor.h"

CSceneryEditor CSceneryEditor::control;

CSceneryEditor::CSceneryEditor() {
  layer = 0;

  showScenery     = true;
  showWorkScenery = true;
  layer_alpha     = MAX_RGBA;
  other_alpha     = MAX_RGBA;
  render_active   = false;
  has_rendered_active = false;

  group_ID = Decorations::groups::GLOBAL;
  decor_ID = Decorations::global::NOTHING;
  placePos = sceneryEngine::misc::placeRelPos::TOP_LEFT;
  snap_scenery = false;
}

bool CSceneryEditor::OnInit() {
  if (!CScenery::OnInit()) return false;

  updateSceneryButtons();

  return true;
}

void CSceneryEditor::updateSceneryButtons() {
  using namespace sceneryEngine::misc::sceneryButtons;

  sceneryButtons.clear();
  for (int i = 0; i < CSceneryData::getNumDecor(group_ID); i++)
  {
    // add buttons
    CButton button(list_x, list_y + (i * button_h), button_w, button_h);
    button.defCol = offCol;
    button.onCol  = onCol;
    button.hovCol = hovCol;
    sceneryButtons.push_back(button);
  }
}

void CSceneryEditor::getPosDisplace(int& dx, int& dy, const SDL_Point* m, const SDL_Rect& dstR) {
  using namespace sceneryEngine::misc::placeRelPos;

  int x_placeCell = placePos % numpos_x;
  int y_placeCell = placePos / numpos_x;
  if (y_placeCell >= numpos_y) return;

  if (snap_scenery) {
    // SDL_Point map_m = CCamera::CameraControl.GetCamRelPoint(m);
    // dx += (x_placeCell * TILE_SIZE / 2) - (x_placeCell + 1 == numpos_x) - (map_m.x % TILE_SIZE);
    // dy += (y_placeCell * TILE_SIZE / 2) - (y_placeCell + 1 == numpos_y) - (map_m.y % TILE_SIZE);
  }
  dx += -(((x_placeCell * dstR.w) / 2) - (x_placeCell + 1 == numpos_x));
  dy += -(((y_placeCell * dstR.h) / 2) - (y_placeCell + 1 == numpos_y));
}

void CSceneryEditor::setOpacity(const unsigned short& A) {
  for (int i = 0; i < CScenery::texList.size(); i++) {
    SDL_SetTextureAlphaMod(CScenery::texList[i].img, A);
  }
}

void CSceneryEditor::OnTerminate() {
  //
}
