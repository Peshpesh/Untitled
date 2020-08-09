#include "CPlanEditor.h"

void CPlanEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

void CPlanEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CInterrupt::isFlagOn(INTRPT_ADD_LAYER)) addLayer(m);
  else if (CInterrupt::isFlagOn(INTRPT_DEL_LAYER)) deleteLayer(m);
  else {
    if (CAsset::inWorkspace(m)) {
      if (handlePlaceTile(m)) return;
    } else {
      if (handleTileOpts(m))  return;
      if (handleLayerOpts(m))  return;
      if (handleSolidOpts(m)) return;
      if (handleTypeOpts(m))  return;
      if (handlePlaceOpts(m)) return;
      if (handleVisOpts(m))   return;
    }
  }
}

bool CPlanEditor::handlePlaceTile(const SDL_Point& m) {
  if (CAsset::inWorkspace(m)) {
    int mX = CCamera::CameraControl.GetX() + m.x;
    int mY = CCamera::CameraControl.GetY() + m.y + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
    placeTile(mX, mY);
    return true;
  }
  return false;
}

void CPlanEditor::placeTile(const int& x, const int &y) {
  CPlanArea::control.changeTile(x, y, k, workTile, placeflag);
}

bool CPlanEditor::handleTileOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace tileOpts;

  // Click on "Change Tileset" button. This displays a prompt to change tilesets,
  // and the function within the loop performs a change if requested.
  if (SDL_PointInRect(&m, &ts_button)) {
    CInterrupt::appendFlag(INTRPT_CHANGE_TS);
    return true;
  }
  // Click on "Change Tile" button. A display of all tiles is rendered,
  // and clicking a tile will update the active tile to use the clicked tile.
  if (SDL_PointInRect(&m, &tile_button)) {
    CChangeTile::PickTile.Init(CTileset::TSControl.ts_w, CTileset::TSControl.ts_h);
    CInterrupt::appendFlag(INTRPT_CHANGE_BG);
    return true;
  }
  return false;
}

bool CPlanEditor::handleLayerOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace layerOpts;

  // Click on "Create Layer" button. This displays options to add a new layer
  // and includes info on existing layers.
  if (SDL_PointInRect(&m, &add_button)) {
    CInterrupt::appendFlag(INTRPT_ADD_LAYER);
    return true;
  }
  // Click on "Delete Layer" button. This lists the available layers to delete
  // (if any) and asks for confirmation.
  if (SDL_PointInRect(&m, &del_button)) {
    CInterrupt::appendFlag(INTRPT_DEL_LAYER);
    return true;
  }
  return false;
}

bool CPlanEditor::handleVisOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace visOpts;

  for (int i = 0; i < nOpts; i++) {
    if (SDL_PointInRect(&m, &buttons[i])) {
      visflag ^= opts[i]; // toggle flag (on -> off, off -> on)
      return true;
    }
  }
  return false;
}

bool CPlanEditor::handlePlaceOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace placeOpts;

  for (int i = 0; i < nOpts; i++) {
    if (SDL_PointInRect(&m, &buttons[i])) {
      placeflag ^= opts[i]; // toggle flag (on -> off, off -> on)
      return true;
    }
  }
  return false;
}

bool CPlanEditor::handleSolidOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace solidOpts;

  if (SDL_PointInRect(&m, &button)) {
    workTile.solid = !(workTile.solid);
    return true;
  }
  return false;
}

bool CPlanEditor::handleTypeOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace typeOpts;

  SDL_Rect targetR = {0, 0, type_sz, type_sz};
  int k = 0;
  for (int j = 0; j < CTileset::TSControl.type_h; j++) {
    for (int i = 0; i < CTileset::TSControl.type_w; i++) {
      targetR.x = pos.x + ((k % cols) * (type_sz + spac));
      targetR.y = pos.y + ((k / cols) * (type_sz + spac));
      if (SDL_PointInRect(&m, &targetR)) {
        workTile.type = k;
        return true;
      }
      k++;
    }
  }
  return false;
}

void CPlanEditor::extendMap_R() {

}

void CPlanEditor::extendMap_L() {

}

void CPlanEditor::extendMap_D() {

}

void CPlanEditor::extendMap_U() {

}

void CPlanEditor::removeMap_R() {

}

void CPlanEditor::removeMap_L() {

}

void CPlanEditor::removeMap_D() {

}

void CPlanEditor::removeMap_U() {

}

//=======================//
// Interruption handling //
//=======================//

bool CPlanEditor::handleInterr(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_BG)) {
    changeTile(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_CHANGE_TS)) {
    changeTileset(Event);
    return true;
  }
  return false;
}

void CPlanEditor::changeTileset(SDL_Event* Event) {
  CTileset::TSControl.OnEvent(Event);

  if (CInterrupt::isFlagOff(INTRPT_CHANGE_TS) && CTileset::TSControl.wasSuccess()) {
    workTile.ID = -1;
  }
}

void CPlanEditor::changeTile(SDL_Event* Event) {
  CChangeTile::PickTile.OnEvent(Event);

  if (CInterrupt::isFlagOff(INTRPT_CHANGE_BG)) {
    CChangeTile::PickTile.reqChange(workTile.ID);
  }
}

void CPlanEditor::addLayer(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace layerOpts::addOpts;

  // check adjustment to k
  SDL_Rect mins_btn = CAsset::getRect(k_field.x - incr_size, k_field.y, incr_size, incr_size);
  SDL_Rect plus_btn = CAsset::getRect(k_field.x + k_field.w, k_field.y, incr_size, incr_size);

  if (SDL_PointInRect(&m, &mins_btn)) {
    if (new_k != 0) new_k--;
    return;
  }
  if (SDL_PointInRect(&m, &plus_btn)) {
    if (new_k != CPlanArea::control.LayerList.size()) new_k++;
    return;
  }
  // check adjustment to z
  mins_btn.y = z_field.y;
  plus_btn.y = z_field.y;
  if (SDL_PointInRect(&m, &mins_btn)) {
    new_z--; return;
  }
  if (SDL_PointInRect(&m, &plus_btn)) {
    new_z++; return;
  }

  if (SDL_PointInRect(&m, &conf_btn)) {
    CPlanArea::control.addLayer(new_k, new_z);
    CInterrupt::removeFlag(INTRPT_ADD_LAYER);
    k = new_k;
    new_k = new_z = 0;
    return;
  }
  if (SDL_PointInRect(&m, &canc_btn)) {
    CInterrupt::removeFlag(INTRPT_ADD_LAYER);
    new_k = new_z = 0;
    return;
  }
}

void CPlanEditor::deleteLayer(const SDL_Point& m) {
  CInterrupt::removeFlag(INTRPT_DEL_LAYER);
}
