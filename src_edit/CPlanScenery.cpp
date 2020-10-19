#include "CPlanScenery.h"

CPlanScnEdit CPlanScnEdit::control;
std::vector<CPlanScenery> CPlanScnEdit::scnList;

CPlanScnEdit::CPlanScnEdit() {
  k = 0; // working layer index

  img = NULL;

  showScenery     = true;
  showWorkScenery = true;

  render_active   = false;
  has_rendered_active = false;

  group_ID = Decorations::groups::GLOBAL;
  decor_ID = Decorations::global::NOTHING;
  list_page = 0;
  placePos = pvmScenery::misc::placeRelPos::TOP_LEFT;
  use_anchor = false;
  show_anchor = false;
}

void CPlanScnEdit::OnInit() {
  group_ID = Decorations::groups::GLOBAL;
  decor_ID = Decorations::global::NOTHING;
  list_page = 0;

  SDL_Texture* scenery_tex = NULL;
  scenery_tex = CSceneryData::loadSrcTexture(group_ID);

  if (scenery_tex != NULL) img = scenery_tex;

  scnList.clear();
  updateSceneryButtons();
}

void CPlanScnEdit::setK(const int& k) {
  this->k = k;
}

void CPlanScnEdit::getK(int& k) {
  k = this->k;
}

void CPlanScnEdit::OnTerminate() {
  scnList.clear();
  SDL_DestroyTexture(img);
}

//////////////////////////////////////////
//////////////////////////////////////////
//////////////////////////////////////////


void CPlanScnEdit::updateSceneryButtons() {
  using namespace pvmScenery::misc::sceneryButtons;

  sceneryButtons.clear();
  list_page = 0;

  for (int i = 0; i < CSceneryData::getNumDecor(group_ID); i++) {
    // add buttons
    CButton button(list_x, list_y + ((i % max_buttons) * button_h), button_w, button_h);
    button.defCol = offCol;
    button.onCol  = onCol;
    button.hovCol = hovCol;
    sceneryButtons.push_back(button);
  }
}

void CPlanScnEdit::getPosDisplace(int& dx, int& dy, const SDL_Rect& dstR) {
  using namespace pvmScenery::misc::placeRelPos;

  int x_placeCell = placePos % numpos_x;
  int y_placeCell = placePos / numpos_x;
  if (y_placeCell >= numpos_y) return;

  dx += -(((x_placeCell * dstR.w) / 2) - (x_placeCell + 1 == numpos_x));
  dy += -(((y_placeCell * dstR.h) / 2) - (y_placeCell + 1 == numpos_y));
}

void CPlanScnEdit::getPosDisplace(double& dx, double& dy, const SDL_Rect& dstR) {
  using namespace pvmScenery::misc::placeRelPos;

  int x_placeCell = placePos % numpos_x;
  int y_placeCell = placePos / numpos_x;
  if (y_placeCell >= numpos_y) return;

  dx += -(((x_placeCell * dstR.w) / 2.0) - (x_placeCell + 1 == numpos_x));
  dy += -(((y_placeCell * dstR.h) / 2.0) - (y_placeCell + 1 == numpos_y));
}
