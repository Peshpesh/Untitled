#include "CPlanScenery.h"

SDL_Texture* CPlanScenery::img = NULL;
SDL_Texture* CPlanScenery::img_shd = NULL;

CPlanScnEdit CPlanScnEdit::control;
std::vector<CPlanScenery> CPlanScnEdit::scnList_front;
std::vector<CPlanScenery> CPlanScnEdit::scnList_back;

CPlanScenery::CPlanScenery() {
  ID     = 0;
  X      = 0;
  Y      = 0;
  Y_base = 0;
  Z      = 0;
  srcR.x = srcR.y = srcR.w = srcR.h = 0;
  has_shadow = false;
}

CPlanScnEdit::CPlanScnEdit() {
  k = 0; // working layer index

  img = NULL;
  img_shd = NULL;

  render_with_map = false;

  showScenery     = true;
  showWorkScenery = true;
  showYBase       = true;

  render_active   = false;
  has_rendered_active = false;

  group_ID = Decorations::groups::NEWYRAI;
  decor_ID = 0;
  list_page = 0;
  placePos = pvmScenery::misc::placeRelPos::TOP_LEFT;
  lock_to_grid = false;
  use_anchor   = false;
  show_anchor  = false;

  base_shadow_opacity = MAX_RGBA * 0.22;
}

bool CPlanScnEdit::OnInit() {
  group_ID = Decorations::groups::NEWYRAI;
  decor_ID = 0;
  list_page = 0;

  SDL_Texture* scenery_tex = NULL;
  SDL_Texture* shadow_tex  = NULL;
  scenery_tex = CSceneryData::loadSrcTexture(group_ID);
  shadow_tex  = CSceneryData::loadSrcShadows(group_ID);

  if (scenery_tex != NULL) {
    img = scenery_tex;
    CPlanScenery::img = scenery_tex;
  } else return false;

  if (shadow_tex != NULL) {
    img_shd = shadow_tex;
    CPlanScenery::img_shd = shadow_tex;
    SDL_SetTextureAlphaMod(img_shd, base_shadow_opacity);
  }

  scnList_front.clear();
  scnList_back.clear();
  updateSceneryButtons();
  return true;
}

void CPlanScnEdit::setOpacity(const int& opac) {
  if (opac < 0) return;
  SDL_SetTextureAlphaMod(img, (opac > MAX_RGBA) ? MAX_RGBA : opac);
  SDL_SetTextureAlphaMod(img_shd, (opac > MAX_RGBA) ? base_shadow_opacity : base_shadow_opacity * (float)(opac)/(float)(MAX_RGBA));
}

void CPlanScnEdit::resetOpacity() {
  SDL_SetTextureAlphaMod(img, MAX_RGBA);
  SDL_SetTextureAlphaMod(img_shd, base_shadow_opacity);
}

void CPlanScnEdit::addScenery(const int& X, const int& Y, const int& Z) {
  CPlanScenery tempScn;
  tempScn.ID = decor_ID;
  tempScn.X = X;
  tempScn.Y = Y;
  tempScn.Z = Z;
  tempScn.srcR = CSceneryData::getDecorDims(group_ID, decor_ID);
  tempScn.Y_base = CSceneryData::getYBase(group_ID, decor_ID, Y, tempScn.srcR.h);
  tempScn.has_shadow = CSceneryData::hasShadow(group_ID, decor_ID);
  // tempScn.img = img;


  if (render_with_map) {
    // For scenery rendered with each map layer, we must
    // place the new scenery in the correct spot based on Y_base AND Z.
    // ... Group and order first by layer, then order each layer group by Y_base.
    // Note: as i->size, Z increases. Y increases with i amongst objs with equal Z.
    int i = 0;
    while (i < scnList_back.size()) {
      // compared obj is at higher Z; place new obj at "end" of objs with equal Z
      if (Z < scnList_back[i].Z) break;
      // new obj Z exists; compared obj is at higher Y_base (in front of new obj)
      if (Z == scnList_back[i].Z && tempScn.Y_base < scnList_back[i].Y_base) break;
      i++;
    }
    scnList_back.insert(scnList_back.begin() + i, tempScn);
  } else {
    // For scenery rendered after all maps and shadows are drawn, the ordering
    // primarily depends on Y_base. On the rare instance that objects share Y_base,
    // the object with lower Z is rendered first. If Y_base and Z are shared,
    // no specific ordering is done (depends on when the objects were added).
    int i = 0;
    while (i < scnList_front.size()) {
      if (tempScn.Y_base < scnList_front[i].Y_base) break;
      if (tempScn.Y_base == scnList_front[i].Y_base && Z < scnList_front[i].Z) break;
      i++;
    }
    scnList_front.insert(scnList_front.begin() + i, tempScn);
  }
}

void CPlanScnEdit::setK(const int& k) {
  this->k = k;
}

void CPlanScnEdit::getK(int& k) {
  k = this->k;
}

void CPlanScnEdit::OnTerminate() {
  scnList_front.clear();
  scnList_back.clear();
  SDL_DestroyTexture(img);
  SDL_DestroyTexture(img_shd);
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

  if (lock_to_grid) {
    if (x_placeCell == 0) { // left-side placement
      dx = (dx / TILE_SIZE) * TILE_SIZE;
    } else if (x_placeCell == 2) { // right-side placement
      dx = (1 + (dx / TILE_SIZE)) * TILE_SIZE - 1;
    }

    if (y_placeCell == 0) { // top-side placement
      dy = (dy / TILE_SIZE) * TILE_SIZE;
    } else if (y_placeCell == 2) { // bottom-side placement
      dy = (1 + (dy / TILE_SIZE)) * TILE_SIZE - 1;
    }
  }

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
