#include "CPlanEditor.h"

void CPlanEditor::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;
  CEvent::OnEvent(Event);
}

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

void CPlanEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (!CInterrupt::isNone()) return;

  // switch (sym) {
  //   case SDLK_d:  extendMap_R();  break;
  //   case SDLK_a:  extendMap_L();  break;
  //   case SDLK_s:  extendMap_D();  break;
  //   case SDLK_w:  extendMap_U();  break;
  //   case SDLK_l:  removeMap_R();  break;
  //   case SDLK_j:  removeMap_L();  break;
  //   case SDLK_k:  removeMap_D();  break;
  //   case SDLK_i:  removeMap_U();  break;
  //   default: break;
  // }
}

void CPlanEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CInterrupt::isFlagOn(INTRPT_ADD_LAYER)) addLayer(m);
  else if (CInterrupt::isFlagOn(INTRPT_DEL_LAYER)) deleteLayer(m);
  else if (CInterrupt::isFlagOn(INTRPT_ADJ_LAYOP)) adjustOpacity(m);
  else if (CInterrupt::isNone()) {
    if (req_rm_side) {
      handleReqRm(m);
    } else {
      if (handlePlaceDomain(m)) return;
      if (CAsset::inWorkspace(m)) {
        if (handlePlacePattern(m))     return;
        if (handlePlaceTile(m))        return;
        if (handleAdjustArea(m, true)) return;
      } else {
        if (handleTileOpts(m))    return;
        if (handlePatternOpts(m)) return;
        if (handleLayerOpts(m))   return;
        if (handleSolidOpts(m))   return;
        if (handleTypeOpts(m))    return;
        if (handlePlaceOpts(m))   return;
        if (handleVisOpts(m))     return;
        if (handleOpacOpts(m))    return;
        if (handleLayerList(m))   return;
      }
    }
  }
}

void CPlanEditor::OnRButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
  if (CInterrupt::isNone() && !req_rm_side && CAsset::inWorkspace(m)) {
    if (!pDomain_A) {
      if (handleAdjustArea(m, false)) return;
    }
    if (!pDomain_B) {
      if (handleMakeDomain(m)) return;
    } else {
      if (handlePlaceDomain(m)) return;
    }
  }
}

bool CPlanEditor::placePattern(const int& x, const int& y) {
  // place the working pattern with the top-left at (x,y)
  return placePattern(x, y, false, false);
}

bool CPlanEditor::placePattern(const int& x, const int& y, const bool& flip_x, const bool& flip_y) {
  // place the working pattern with the top-left at (x,y)
  if (!workPattern.size()) return true;
  for (int j = 0; j < pattern_h; j++) {
    int tY = y + (j * TILE_SIZE);
    for (int i = 0; i < pattern_w; i++) {
      int tX = x + (i * TILE_SIZE);
      int col = flip_x ? (pattern_w - (i+1)) : i;
      int row = flip_y ? (pattern_h - (j+1)) : j;
      int ID = col + (row * pattern_w);

      if (!placeTile(tX, tY, workPattern[ID])) return false;
    }
  }
  return true;
}

bool CPlanEditor::placeTile(const int& x, const int& y) {
  return CPlanArea::control.changeTile(x, y, k, workTile, placeflag);
}

bool CPlanEditor::placeTile(const int& x, const int& y, const CPlanTile& tile) {
  return CPlanArea::control.changeTile(x, y, k, tile, placeflag);
}

bool CPlanEditor::handlePlaceTile(const SDL_Point& m) {
  int mX = CCamera::CameraControl.GetX() + m.x;
  int mY = CCamera::CameraControl.GetY() + m.y + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
  return placeTile(mX, mY);
}

bool CPlanEditor::handlePlacePattern(const SDL_Point& m) {
  if (!workPattern.size()) return false;
  int refX = CCamera::CameraControl.GetX() + m.x;
  int refY = CCamera::CameraControl.GetY() + m.y + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
  return placePattern(refX, refY);
}

bool CPlanEditor::handleMakeDomain(const SDL_Point& m) {
  if (CAsset::inWorkspace(m)) {
    if (pDomain_A == NULL) {
      pDomain_A = new SDL_Point;
      pDomain_A->x = m.x + CCamera::CameraControl.GetX();
      pDomain_A->y = m.y + CCamera::CameraControl.GetY();
    }
    else if (pDomain_B == NULL) {
      pDomain_B = new SDL_Point;
      pDomain_B->x = m.x + CCamera::CameraControl.GetX();
      pDomain_B->y = m.y + CCamera::CameraControl.GetY();
    }
    else {
      resetDomain();
    }
    return true;
  }
  return false;
}

bool CPlanEditor::handlePlaceDomain(const SDL_Point& m) {
  if (!pDomain_A) return false;
  else if (!pDomain_B) {
    // effectively, a "cancel"
    resetDomain();
    return false;
  }

  bool retval = false;
  SDL_Point m_rel = CCamera::CameraControl.GetCamRelPoint(m);
  SDL_Rect d = CAsset::getTileRect(pDomain_A, pDomain_B);

  if (CAsset::inWorkspace(m)) {
    retval = true;
    if (workPattern.size()) {
      bool flip_x = (pDomain_A->x > pDomain_B->x);
      bool flip_y = (pDomain_A->y > pDomain_B->y);
      int tW = d.w / TILE_SIZE;
      int tH = d.h / TILE_SIZE;

      if (tW % pattern_w) tW += pattern_w - (tW % pattern_w);
      if (tH % pattern_h) tH += pattern_h - (tH % pattern_h);
      if (flip_x) d.x -= (tW * TILE_SIZE) - d.w;
      if (flip_y) d.y -= (tH * TILE_SIZE) - d.h;
      d.w = tW * TILE_SIZE;
      d.h = tH * TILE_SIZE;

      if (SDL_PointInRect(&m_rel, &d)) {
        // fill domain with patterns
        for (int pY = 0; pY < tH / pattern_h; pY++) {
          int Y = d.y + (pY * pattern_h * TILE_SIZE) + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
          for (int pX = 0; pX < tW / pattern_w; pX++) {
            int X = d.x + (pX * pattern_w * TILE_SIZE);
            placePattern(X, Y, flip_x, flip_y);
          }
        }
      }
    } else if (SDL_PointInRect(&m_rel, &d)) {
      // fill domain with tiles (no pattern)
      for (int tY = 0; tY < d.h / TILE_SIZE; tY++) {
        int Y = d.y + (tY * TILE_SIZE) + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
        for (int tX = 0; tX < d.w / TILE_SIZE; tX++) {
          int X = d.x + (tX * TILE_SIZE);
          placeTile(X, Y);
        }
      }
    }
    resetDomain();
  }
  return retval;
}

void CPlanEditor::resetDomain() {
  if (pDomain_A != NULL) {
    delete pDomain_A;
    pDomain_A = NULL;
  }
  if (pDomain_B != NULL) {
    delete pDomain_B;
    pDomain_B = NULL;
  }
}

bool CPlanEditor::handleAdjustArea(const SDL_Point& m, bool extend) {
  int W = 0;
  int H = 0;
  CPlanArea::control.GetDims(W, H);
  int px_W = W * MAP_WIDTH * TILE_SIZE;
  int px_H = H * MAP_HEIGHT * TILE_SIZE;

  int mX = CCamera::CameraControl.GetX() + m.x;
  int mY = CCamera::CameraControl.GetY() + m.y + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
  if (mX >= 0 && mX < px_W) {
    if (mY < 0 && mY >= -TILE_SIZE) {
      if (extend) extendMap_U();
      else if (H > 1) {
        if (CPlanArea::control.isUpEmpty()) removeMap_U();
        else {
          req_rm_side   = new char;
          *req_rm_side  = 'U';
        }
      }
      return true;
    } else if (mY >= px_H && mY < px_H + TILE_SIZE) {
      if (extend) extendMap_D();
      else if (H > 1) {
        if (CPlanArea::control.isDownEmpty()) removeMap_D();
        else {
          req_rm_side   = new char;
          *req_rm_side  = 'D';
        }
      }
      return true;
    }
  }

  if (mY >= 0 && mY < px_H) {
    if (mX < 0 && mX >= -TILE_SIZE) {
      if (extend) extendMap_L();
      else if (W > 1) {
        if (CPlanArea::control.isLeftEmpty()) removeMap_L();
        else {
          req_rm_side   = new char;
          *req_rm_side  = 'L';
        }
      }
      return true;
    } else if (mX >= px_W && mX < px_W + TILE_SIZE) {
      if (extend) extendMap_R();
      else if (W > 1) {
        if (CPlanArea::control.isRightEmpty()) removeMap_R();
        else {
          req_rm_side   = new char;
          *req_rm_side  = 'R';
        }
      }
      return true;
    }
  }
  return false;
}

void CPlanEditor::handleReqRm(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace adjArea;

  if (SDL_PointInRect(&m, &yes_btn)) {
    switch (*req_rm_side) {
      case 'R': removeMap_R(); break;
      case 'L': removeMap_L(); break;
      case 'U': removeMap_U(); break;
      case 'D': removeMap_D(); break;
      default: break;
    }
    delete req_rm_side;
    req_rm_side = NULL;
  } else if (SDL_PointInRect(&m, &no_btn)) {
    delete req_rm_side;
    req_rm_side = NULL;
  }
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
  // Click on "Clear Tile" button.
  if (SDL_PointInRect(&m, &clear_button)) {
    workTile.ID = -1;
    return true;
  }

  return false;
}


bool CPlanEditor::handlePatternOpts(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace patternOpts;

  // Click on Use/Free Pattern button.
  if (workPattern.size()) {
    if (SDL_PointInRect(&m, &button)) {
      // free pattern
      pattern_w = pattern_h = 0;
      workPattern.clear();
      return true;
    }
  } else if (pDomain_A && pDomain_B && SDL_PointInRect(&m, &button)) {
    SDL_Rect box = CAsset::getTileRect(pDomain_A, pDomain_B);
    int tW = box.w / TILE_SIZE;
    int tH = box.h / TILE_SIZE;
    if (tW <= MAX_PATTERN_W && tH <= MAX_PATTERN_H) {
      // get pattern for use
      for (int Y = 0; Y < tH; Y++) {
        for (int X = 0; X < tW; X++) {
          int mX = box.x + (X * TILE_SIZE);
          int mY = box.y + (Y * TILE_SIZE) + (CPlanArea::control.LayerList[k].Z * TILE_SIZE);
          CPlanTile* tmp = CPlanArea::control.GetTile(mX, mY, k);
          workPattern.push_back(*tmp);
        }
      }
      pattern_w = tW;
      pattern_h = tH;
      resetDomain();
    }
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

bool CPlanEditor::handleLayerList(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace basicLayer;

  if (SDL_PointInRect(&m, &module_r)) {
    SDL_Rect layer_rec = k_r;
    layer_rec.w += z_r.w;
    short n_lists = 1;
    for (int i = 0; i < CPlanArea::control.LayerList.size(); i++) {
      if (i > 0 && i % items_per_list == 0) {
        if (n_lists < max_num_lists) {
          layer_rec.x += layer_rec.w + spac_w;
          layer_rec.y = k_r.y;
          n_lists++;
        } else break;
      }
      int ID = CPlanArea::control.LayerList.size() - 1 - i;
      layer_rec.y += layer_rec.h;

      if (SDL_PointInRect(&m, &layer_rec)) {
        k = ID;
      }
    }
    return true;
  }
  return false;
}

void CPlanEditor::extendMap_R() {
  CPlanArea::control.expandRight();
}

void CPlanEditor::extendMap_L() {
  CPlanArea::control.expandLeft();
  // Keep camera focused on same spot (relative to the area prior to expansion)
  CCamera::CameraControl.OnMove(MAP_WIDTH * TILE_SIZE, 0);
}

void CPlanEditor::extendMap_D() {
  CPlanArea::control.expandDown();
}

void CPlanEditor::extendMap_U() {
  CPlanArea::control.expandUp();
  // Keep camera focused on same spot
  CCamera::CameraControl.OnMove(0, MAP_HEIGHT * TILE_SIZE);
}

void CPlanEditor::removeMap_R() {
  CPlanArea::control.reduceRight();
}

void CPlanEditor::removeMap_L() {
  if (CPlanArea::control.reduceLeft()) {
    CCamera::CameraControl.OnMove(-MAP_WIDTH * TILE_SIZE, 0);
  }
}

void CPlanEditor::removeMap_D() {
  CPlanArea::control.reduceDown();
}

void CPlanEditor::removeMap_U() {
  if (CPlanArea::control.reduceUp()) {
    CCamera::CameraControl.OnMove(0, -MAP_HEIGHT * TILE_SIZE);
  }
}

//=======================//
// Interruption handling //
//=======================//

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
