#include "CPlanEditor.h"

void CPlanEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

void CPlanEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CInterrupt::isFlagOn(INTRPT_ADD_LAYER)) addLayer(m);
  else if (CInterrupt::isFlagOn(INTRPT_DEL_LAYER)) deleteLayer(m);
  else if (CInterrupt::isFlagOn(INTRPT_ADJ_LAYOP)) adjustOpacity(m);
  else {
    if (CAsset::inWorkspace(m)) {
      if (handlePlaceTile(m)) return;
    } else {
      if (handleTileOpts(m))  return;
      if (handleLayerOpts(m)) return;
      if (handleSolidOpts(m)) return;
      if (handleTypeOpts(m))  return;
      if (handlePlaceOpts(m)) return;
      if (handleVisOpts(m))   return;
      if (handleOpacOpts(m))  return;
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
  if (CPlanArea::control.LayerList.size() > 1 && SDL_PointInRect(&m, &del_button)) {
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

bool CPlanEditor::handleOpacOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace opacOpts;

  short* opac[] = {
    &active_opacity,
    &over_opacity,
    &under_opacity
  };

  for (int i = 0; i < nMeters; i++) {
    if (SDL_PointInRect(&m, &meters[i])) {
      SDL_Rect meter_fill = meters[i];
      meter_fill.x += stroke_sz;
      meter_fill.w -= stroke_sz * 2;
      if (m.x < meter_fill.x) *opac[i] = 0;
      else if (m.x > meter_fill.x + meter_fill.w) *opac[i] = MAX_RGBA;
      else {
        float new_opac = float(m.x - meter_fill.x) * MAX_RGBA / meter_fill.w;
        if (new_opac < 0) new_opac = 0;
        if (new_opac > MAX_RGBA) new_opac = MAX_RGBA;
        *opac[i] = new_opac;
      }
      return true;
    }
  }
  // Click on "Specify..." button. This displays options to manually adjust
  // layer opacities.
  if (SDL_PointInRect(&m, &more_button)) {
    CInterrupt::appendFlag(INTRPT_ADJ_LAYOP);
    for (int i = 0; i < CPlanArea::control.LayerList.size(); i++) {
      temp_opac.push_back(CPlanArea::control.LayerList[i].opacity);
      temp_force.push_back(CPlanArea::control.LayerList[i].force_opacity);
    }
    return true;
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
    if (sel_k != 0) sel_k--;
    return;
  }
  if (SDL_PointInRect(&m, &plus_btn)) {
    if (sel_k != CPlanArea::control.LayerList.size()) sel_k++;
    return;
  }
  // check adjustment to z
  mins_btn.y = z_field.y;
  plus_btn.y = z_field.y;
  if (SDL_PointInRect(&m, &mins_btn)) {
    sel_z--; return;
  }
  if (SDL_PointInRect(&m, &plus_btn)) {
    sel_z++; return;
  }

  if (SDL_PointInRect(&m, &conf_btn)) {
    CPlanArea::control.addLayer(sel_k, sel_z);
    CInterrupt::removeFlag(INTRPT_ADD_LAYER);
    k = sel_k;
    sel_k = sel_z = 0;
    return;
  }
  if (SDL_PointInRect(&m, &canc_btn)) {
    CInterrupt::removeFlag(INTRPT_ADD_LAYER);
    sel_k = sel_z = 0;
    return;
  }
}

void CPlanEditor::deleteLayer(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace layerOpts::delOpts;

  SDL_Rect list_r = CAsset::getRect(list_x, list_y + list_item_h,
                                    list_item_w,
                                    list_item_h * CPlanArea::control.LayerList.size());
  if (SDL_PointInRect(&m, &list_r)) {
    SDL_Rect list_item_r = CAsset::getRect(list_x, list_y, list_item_w, list_item_h);
    for (int i = CPlanArea::control.LayerList.size() - 1; i >= 0; i--) {
      list_item_r.y += list_item_r.h;
      if (SDL_PointInRect(&m, &list_item_r)) {
        sel_k = i;
        break;
      }
    }
    return;
  }

  if (SDL_PointInRect(&m, &conf_btn)) {
    CPlanArea::control.delLayer(sel_k);
    CInterrupt::removeFlag(INTRPT_DEL_LAYER);
    if (k >= CPlanArea::control.LayerList.size()) k = CPlanArea::control.LayerList.size() - 1;
    sel_k = sel_z = 0;
    return;
  }
  if (SDL_PointInRect(&m, &canc_btn)) {
    CInterrupt::removeFlag(INTRPT_DEL_LAYER);
    sel_k = sel_z = 0;
    return;
  }
}

void CPlanEditor::adjustOpacity(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace opacOpts::adjOpts;

  SDL_Rect meter_rec  = meter_r;
  SDL_Rect off_opac_r = CAsset::getRect(meter_rec.x, meter_rec.y, stroke_sz, meter_rec.h);
  meter_rec.x += stroke_sz;
  meter_rec.w -= stroke_sz * 2;
  SDL_Rect on_opac_r  = CAsset::getRect(meter_rec.x + meter_rec.w, meter_rec.y, stroke_sz, meter_rec.h);
  SDL_Rect force_rec = force_r;

  for (int i = CPlanArea::control.LayerList.size() - 1; i >= 0; i--) {
    meter_rec.y   += meter_rec.h + spac_h;
    off_opac_r.y  += off_opac_r.h + spac_h;
    on_opac_r.y   += on_opac_r.h + spac_h;
    force_rec.y   += force_rec.h + spac_h;

    if (SDL_PointInRect(&m, &force_rec)) {
      CPlanArea::control.LayerList[i].force_opacity = !CPlanArea::control.LayerList[i].force_opacity;
      return;
    }
    if (SDL_PointInRect(&m, &meter_rec)) {
      float new_opac = float(m.x - meter_rec.x) * MAX_RGBA / meter_rec.w;
      if (new_opac < 0) new_opac = 0;
      if (new_opac > MAX_RGBA) new_opac = MAX_RGBA;
      CPlanArea::control.LayerList[i].opacity = new_opac;
      return;
    }
    if (SDL_PointInRect(&m, &off_opac_r)) {
      CPlanArea::control.LayerList[i].opacity = 0;
      return;
    }
    if (SDL_PointInRect(&m, &on_opac_r)) {
      CPlanArea::control.LayerList[i].opacity = MAX_RGBA;
      return;
    }
  }

  if (SDL_PointInRect(&m, &conf_btn)) {
    temp_opac.clear();
    temp_force.clear();
    CInterrupt::removeFlag(INTRPT_ADJ_LAYOP);
    return;
  }
  if (SDL_PointInRect(&m, &canc_btn)) {
    for (int i = 0; i < CPlanArea::control.LayerList.size(); i++) {
      CPlanArea::control.LayerList[i].opacity = temp_opac[i];
      CPlanArea::control.LayerList[i].force_opacity = temp_force[i];
    }
    temp_opac.clear();
    temp_force.clear();
    CInterrupt::removeFlag(INTRPT_ADJ_LAYOP);
    return;
  }
}
