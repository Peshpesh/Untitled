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
  target_scn = NULL;

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

void CPlanScnEdit::changeGroup(const int& new_group) {
  if (new_group < 0 || new_group == group_ID) return;

  // attempt to load the new scenery group
  SDL_Texture* tmp_tex;
  SDL_Texture* tmp_shd;
  tmp_tex = CSceneryData::loadSrcTexture(new_group);
  tmp_shd = CSceneryData::loadSrcShadows(new_group);

  if (tmp_tex != NULL) {
    // empty the vector of current scenery
    scnList_back.clear();
    scnList_front.clear();

    // replace the old scenery texture with the new one
    group_ID = new_group;
    SDL_DestroyTexture(img);
    SDL_DestroyTexture(img_shd);
    img     = tmp_tex;
    img_shd = tmp_shd;
  }

  updateSceneryButtons();
}


bool CPlanScnEdit::OnLoad(const char* fname) {
  using namespace pvmScenery::io;

  std::string filePath = path + fname + ext;
  FILE* FileHandle = fopen(filePath.c_str(), "rb");

  if (FileHandle == NULL)  {
    CInform::InfoControl.pushInform("---CPlanScnEdit---\nfailed to open load file");
    return false;
  }

  scnList_back.clear();
  scnList_front.clear();

  int N_back, N_front;
  short group;

  fread(&group,   sizeof(short), 1, FileHandle);
  fread(&N_back,  sizeof(int),   1, FileHandle);
  fread(&N_front, sizeof(int),   1, FileHandle);

  changeGroup(group);

  for (int i = 0; i < N_back + N_front; i++) {
    CPlanScenery tempScn;
    fread(&tempScn.ID, sizeof(int),   1, FileHandle);
    fread(&tempScn.X,  sizeof(int),   1, FileHandle);
    fread(&tempScn.Y,  sizeof(int),   1, FileHandle);
    fread(&tempScn.Z,  sizeof(short), 1, FileHandle);
    tempScn.srcR = CSceneryData::getDecorDims(group, tempScn.ID);
    tempScn.Y_base = CSceneryData::getYBase(group, tempScn.ID, tempScn.Y, tempScn.srcR.h);
    tempScn.has_shadow = CSceneryData::hasShadow(group, tempScn.ID);

    if (i < N_back) scnList_back.push_back(tempScn);
    else scnList_front.push_back(tempScn);
  }

  fclose(FileHandle);
  return true;
}

bool CPlanScnEdit::OnSave(const char* fname) {
  using namespace pvmScenery::io;

  std::string filePath = path + fname + ext;
  FILE* FileHandle = fopen(filePath.c_str(), "wb");

  if (FileHandle == NULL) {
    CInform::InfoControl.pushInform("---CPlanScnEdit---\nfailed to open save file");
    return false;
  }

  const int N_back  = scnList_back.size();
  const int N_front = scnList_front.size();

  fwrite(&group_ID, sizeof(short), 1, FileHandle);
  fwrite(&N_back,   sizeof(int),   1, FileHandle);
  fwrite(&N_front,  sizeof(int),   1, FileHandle);

  for (int i = 0; i < N_back; i++) {
    fwrite(&scnList_back[i].ID, sizeof(int),   1, FileHandle);
    fwrite(&scnList_back[i].X,  sizeof(int),   1, FileHandle);
    fwrite(&scnList_back[i].Y,  sizeof(int),   1, FileHandle);
    fwrite(&scnList_back[i].Z,  sizeof(short), 1, FileHandle);
  }

  for (int i = 0; i < N_front; i++) {
    fwrite(&scnList_front[i].ID, sizeof(int),   1, FileHandle);
    fwrite(&scnList_front[i].X,  sizeof(int),   1, FileHandle);
    fwrite(&scnList_front[i].Y,  sizeof(int),   1, FileHandle);
    fwrite(&scnList_front[i].Z,  sizeof(short), 1, FileHandle);
  }

  fclose(FileHandle);
  return true;
}

void CPlanScnEdit::pushLayersUp(const short& z) {
  // this function pushes all existing scenery "up" by increasing their
  // Z, generally a response to a new layer being added below
  // all existing layers
  // Note: in the case where scenery is being pushed up, Z is negative
  for (int i = 0; i < scnList_back.size(); i++) {
    scnList_back[i].Z -= z;
  }
  for (int i = 0; i < scnList_front.size(); i++) {
    scnList_front[i].Z -= z;
  }
}

void CPlanScnEdit::deleteLayer(const short& z) {
  // Remove all scenery at depth z
  for (int i = scnList_back.size() - 1; i >= 0; i--) {
    if (scnList_back[i].Z == z) scnList_back.erase(scnList_back.begin() + i);
  }
  for (int i = scnList_front.size() - 1; i >= 0; i--) {
    if (scnList_front[i].Z == z) scnList_front.erase(scnList_front.begin() + i);
  }
}
