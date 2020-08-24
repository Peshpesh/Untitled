#include "CPlanEditor.h"

bool CPlanEditor::OnRender(const SDL_Point& m) {
  if (!CAsset::drawAppFrame()) return false;

  bool interr = !(CInterrupt::isNone());

  if (!drawTileOutline(interr ? NULL : &m)) return false;
  if (!drawTileOpts(interr ? NULL : &m))    return false;
  if (!drawLayerOpts(interr ? NULL : &m))   return false;
  if (!drawVisOpts())   return false;
  if (!drawPlaceOpts()) return false;
  if (!drawSolidOpts()) return false;
  if (!drawTypeOpts())  return false;
  if (!drawInterr(m))   return false;
  return true;
}

void CPlanEditor::RenderMap() {
  // render the area's layers in order from bottom to top
  for (int k = 0; k < CPlanArea::control.LayerList.size(); k++) {
    if (k == this->k) {
      CPlanArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(),
                                  k, visflag, active_opacity);
    } else {
      CPlanArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(),
                                  k, pvm_visflags::MAP, (k > this->k) ? over_opacity : under_opacity);
    }
  }
  CTileset::TSControl.maxTileAlpha();
}

bool CPlanEditor::drawTileOutline(const SDL_Point* m) {
  if (!m || !CAsset::inWorkspace(m)) return true;

  SDL_Point map_pos = CCamera::CameraControl.GetCamRelPoint(*m);
  int tX = -CCamera::CameraControl.GetX() + (TILE_SIZE * (map_pos.x / TILE_SIZE));
  int tY = -CCamera::CameraControl.GetY() + (TILE_SIZE * (map_pos.y / TILE_SIZE));
  if (map_pos.x < 0) tX -= TILE_SIZE;
  if (map_pos.y < 0) tY -= TILE_SIZE;

  SDL_Rect dstR = {tX, tY, TILE_SIZE, TILE_SIZE};

  return CAsset::drawBox(&dstR, pvmEditor::outline_col, pvmEditor::outline_sz);
}

bool CPlanEditor::drawTileOpts(const SDL_Point* m) {
  using namespace pvmEditor;
  using namespace tileOpts;

  if (m) {
    if (!CAsset::drawStrBox(&ts_button, stroke_sz,
        CInterrupt::isFlagOn(INTRPT_CHANGE_TS) ? on_col :
        SDL_PointInRect(m, &ts_button) ? hov_col : btn_col)) return false;

    if (!CAsset::drawStrBox(&tile_button, stroke_sz,
        CInterrupt::isFlagOn(INTRPT_CHANGE_BG) ? on_col :
        SDL_PointInRect(m, &tile_button) ? hov_col : btn_col)) return false;
  } else {
    if (!CAsset::drawStrBox(&ts_button, stroke_sz,
        CInterrupt::isFlagOn(INTRPT_CHANGE_TS) ? on_col : btn_col)) return false;

    if (!CAsset::drawStrBox(&tile_button, stroke_sz,
        CInterrupt::isFlagOn(INTRPT_CHANGE_BG) ? on_col : btn_col)) return false;
  }
  Font::NewCenterWrite(ts_title, &ts_button, title_fcol);
  Font::NewCenterWrite(tile_title, &tile_button, title_fcol);
  return true;
}

bool CPlanEditor::drawLayerOpts(const SDL_Point* m) {
  using namespace pvmEditor;
  using namespace layerOpts;

  if (m) {
    if (!CAsset::drawStrBox(&add_button, stroke_sz,
        SDL_PointInRect(m, &add_button) ? hov_col : btn_col)) return false;

    const SDL_Point* col =  (CPlanArea::control.LayerList.size() == 1) ? nul_col
                            : (SDL_PointInRect(m, &del_button) ? hov_col : btn_col);
    if (!CAsset::drawStrBox(&del_button, stroke_sz, col)) return false;
  } else {
    if (!CAsset::drawStrBox(&add_button, stroke_sz, btn_col)) return false;

    const SDL_Point* col = (CPlanArea::control.LayerList.size() > 1) ? btn_col : nul_col;
    if (!CAsset::drawStrBox(&del_button, stroke_sz, col)) return false;
  }
  Font::NewCenterWrite(add_str, &add_button, btn_fcol);
  Font::NewCenterWrite(del_str, &del_button, btn_fcol);
  return true;
}

bool CPlanEditor::drawVisOpts() {
  using namespace pvmEditor;
  using namespace visOpts;

  Font::NewCenterWrite(title, &title_r, btn_fcol);
  for (int i = 0; i < nOpts; i++) {
    bool is_active = visflag & opts[i];
    if (!CAsset::drawStrBox(&buttons[i], stroke_sz, is_active ? on_col : off_col)) return false;
    Font::NewCenterWrite(labels[i], &buttons[i], btn_fcol);
  }
  return true;
}

bool CPlanEditor::drawPlaceOpts() {
  using namespace pvmEditor;
  using namespace placeOpts;

  Font::NewCenterWrite(title, &title_r, btn_fcol);
  for (int i = 0; i < nOpts; i++) {
    bool is_active = placeflag & opts[i];
    if (!CAsset::drawStrBox(&buttons[i], stroke_sz, is_active ? on_col : off_col)) return false;
    Font::NewCenterWrite(labels[i], &buttons[i], btn_fcol);
  }
  return true;
}

bool CPlanEditor::drawSolidOpts() {
  using namespace pvmEditor;
  using namespace solidOpts;

  if (!CAsset::drawStrBox(&button, stroke_sz, workTile.solid ? on_col : off_col)) return false;
  // label[false] = label[0] = "Solid Off"
  // label[true]  = label[1] = "Solid On"
  Font::NewCenterWrite(labels[workTile.solid], &button, btn_fcol);

  return true;
}

bool CPlanEditor::drawTypeOpts() {
  using namespace pvmEditor;
  using namespace typeOpts;

  CTileset::TSControl.maxTypeAlpha();
  SDL_Rect dstR = {0, 0, type_sz, type_sz};
  int k = 0;
  for (int j = 0; j < CTileset::TSControl.type_h; j++) {
    for (int i = 0; i < CTileset::TSControl.type_w; i++) {
      int tX = i * TILE_SIZE;
      int tY = j * TILE_SIZE;
      SDL_Rect srcR = CAsset::getRect(tX, tY, TILE_SIZE, TILE_SIZE);
      dstR.x = pos.x + ((k % cols) * (type_sz + spac));
      dstR.y = pos.y + ((k / cols) * (type_sz + spac));
      CSurface::OnDraw(CTileset::TSControl.type_tileset, &srcR, &dstR);
      if (k == workTile.type) {
        CAsset::drawBox(&dstR, hl_col);
      }
      k++;
    }
  }
  CTileset::TSControl.refreshTypeAlpha();
  return true;
}


bool CPlanEditor::drawInterr(const SDL_Point& m) {
	if (!CInterrupt::isNone()) {
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_BG)) {
			if (!CChangeTile::PickTile.OnRender(&m)) return false;
			// CChangeTile::PickTile.hilightID(TileTL.bg_ID, TileTR.bg_ID, TileBL.bg_ID, TileBR.bg_ID);
		}
		if (CInterrupt::isFlagOn(INTRPT_CHANGE_TS)) {
			if (!CTileset::TSControl.OnRender(&m)) return false;
		}
    if (CInterrupt::isFlagOn(INTRPT_ADD_LAYER)) {
      if (!drawAddLayer(m)) return false;
    }
    if (CInterrupt::isFlagOn(INTRPT_DEL_LAYER)) {
      if (!drawDelLayer(m)) return false;
    }
	}
	return true;
}

bool CPlanEditor::drawAddLayer(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace layerOpts::addOpts;
  // draw window
  if (!CAsset::drawStrBox(&window, stroke_sz, window_col, border_col)) return false;

  // draw titles and info
  Font::NewCenterWrite(list_title, &list_header, title_fcol);
  Font::NewCenterWrite(info, &work_header, title_fcol);
  Font::NewCenterWrite(new_k_title, &k_header, title_fcol);
  Font::NewCenterWrite(new_z_title, &z_header, title_fcol);
  SDL_Rect k_rec = k_title_r;
  SDL_Rect z_rec = z_title_r;
  Font::NewCenterWrite("K", &k_rec, title_fcol);
  Font::NewCenterWrite("Z", &z_rec, title_fcol);

  // draw new layer k field
  SDL_Rect mins_btn = CAsset::getRect(k_field.x - incr_size, k_field.y, incr_size, incr_size);
  SDL_Rect plus_btn = CAsset::getRect(k_field.x + k_field.w, k_field.y, incr_size, incr_size);
  std::string k_str = Font::intToStr(sel_k);
  if (!CAsset::drawBoxFill(&k_field, field_col)) return false;
  if (!CAsset::drawBoxFill(&mins_btn, SDL_PointInRect(&m, &mins_btn) ? active_col : item_col_B)) return false;
  if (!CAsset::drawBoxFill(&plus_btn, SDL_PointInRect(&m, &plus_btn) ? active_col : item_col_B)) return false;
  Font::NewCenterWrite(k_str.c_str(), &k_field, btn_fcol);
  Font::NewCenterWrite("$D", &mins_btn, btn_fcol);
  Font::NewCenterWrite("$U", &plus_btn, btn_fcol);

  // draw new layer z field
  mins_btn.y = z_field.y;
  plus_btn.y = z_field.y;
  std::string z_str = Font::intToStr(sel_z);
  if (!CAsset::drawBoxFill(&z_field, field_col)) return false;
  if (!CAsset::drawBoxFill(&mins_btn, SDL_PointInRect(&m, &mins_btn) ? active_col : item_col_B)) return false;
  if (!CAsset::drawBoxFill(&plus_btn, SDL_PointInRect(&m, &plus_btn) ? active_col : item_col_B)) return false;
  Font::NewCenterWrite(z_str.c_str(), &z_field, btn_fcol);
  Font::NewCenterWrite("$D", &mins_btn, btn_fcol);
  Font::NewCenterWrite("$U", &plus_btn, btn_fcol);

  // draw layer list preview
  if (sel_k == CPlanArea::control.LayerList.size()) {
    // the only case in which the new layer's k-index
    // is NOT shared with an existing layer is if it is
    // the highest value possible.
    k_rec.y += k_rec.h;
    z_rec.y += z_rec.h;

    if (!CAsset::drawBoxFill(&k_rec, new_col)) return false;
    if (!CAsset::drawBoxFill(&z_rec, new_col)) return false;

    std::string k_index = Font::intToStr(sel_k);
    std::string depth   = Font::intToStr(sel_z);

    Font::NewCenterWrite(k_index.c_str(), &k_rec, btn_fcol);
    Font::NewCenterWrite(depth.c_str(), &z_rec, btn_fcol);
  }

  bool alt_col = false;
  for (int i = CPlanArea::control.LayerList.size() - 1; i >= 0; i--) {
    k_rec.y += k_rec.h;
    z_rec.y += z_rec.h;

    const SDL_Point* col = (i == k) ? active_col : (alt_col ? item_col_B : item_col_A);
    if (!CAsset::drawBoxFill(&k_rec, col)) return false;
    if (!CAsset::drawBoxFill(&z_rec, col)) return false;

    std::string k_index = Font::intToStr(i + (int)(i >= sel_k));
    std::string depth   = Font::intToStr(CPlanArea::control.LayerList[i].Z);

    Font::NewCenterWrite(k_index.c_str(), &k_rec, btn_fcol);
    Font::NewCenterWrite(depth.c_str(), &z_rec, btn_fcol);

    if (i == sel_k) {
      // if an old layer shares the new layer's k-index,
      // then that layer and all layers above it are "pushed up"
      // by one.
      k_rec.y += k_rec.h;
      z_rec.y += z_rec.h;

      if (!CAsset::drawBoxFill(&k_rec, new_col)) return false;
      if (!CAsset::drawBoxFill(&z_rec, new_col)) return false;

      std::string k_index = Font::intToStr(sel_k);
      std::string depth   = Font::intToStr(sel_z);

      Font::NewCenterWrite(k_index.c_str(), &k_rec, btn_fcol);
      Font::NewCenterWrite(depth.c_str(), &z_rec, btn_fcol);
    }

    alt_col = !alt_col;
  }

  // draw create & cancel buttons
  if (!CAsset::drawStrBox(&conf_btn, stroke_sz,
    SDL_PointInRect(&m, &conf_btn) ? active_col : window_col, border_col)) return false;
  if (!CAsset::drawStrBox(&canc_btn, stroke_sz,
    SDL_PointInRect(&m, &canc_btn) ? active_col : window_col, border_col)) return false;

  Font::NewCenterWrite(conf_title, &conf_btn, SDL_PointInRect(&m, &conf_btn) ? btn_fcol : title_fcol);
  Font::NewCenterWrite(canc_title, &canc_btn, SDL_PointInRect(&m, &canc_btn) ? btn_fcol : title_fcol);

  return true;
}

bool CPlanEditor::drawDelLayer(const SDL_Point& m) {
  using namespace pvmEditor;
  using namespace layerOpts::delOpts;

  // draw window
  if (!CAsset::drawStrBox(&window, stroke_sz, window_col, border_col)) return false;

  // draw titles and info
  Font::NewCenterWrite(info, &list_header, title_fcol);
  SDL_Rect k_rec = k_title_r;
  SDL_Rect z_rec = z_title_r;
  Font::NewCenterWrite("K", &k_rec, title_fcol);
  Font::NewCenterWrite("Z", &z_rec, title_fcol);

  // draw layer list
  bool alt_col = false;
  for (int i = CPlanArea::control.LayerList.size() - 1; i >= 0; i--) {
    k_rec.y += k_rec.h;
    z_rec.y += z_rec.h;

    const SDL_Point* col = (i == sel_k) ? active_col : (alt_col ? item_col_B : item_col_A);
    if (!CAsset::drawBoxFill(&k_rec, col)) return false;
    if (!CAsset::drawBoxFill(&z_rec, col)) return false;

    std::string k_index = Font::intToStr(i);
    std::string depth   = Font::intToStr(CPlanArea::control.LayerList[i].Z);

    Font::NewCenterWrite(k_index.c_str(), &k_rec, btn_fcol);
    Font::NewCenterWrite(depth.c_str(), &z_rec, btn_fcol);

    alt_col = !alt_col;
  }

  // draw create & cancel buttons
  if (!CAsset::drawStrBox(&conf_btn, stroke_sz,
    SDL_PointInRect(&m, &conf_btn) ? active_col : window_col, border_col)) return false;
  if (!CAsset::drawStrBox(&canc_btn, stroke_sz,
    SDL_PointInRect(&m, &canc_btn) ? active_col : window_col, border_col)) return false;

  Font::NewCenterWrite(conf_title, &conf_btn, SDL_PointInRect(&m, &conf_btn) ? btn_fcol : title_fcol);
  Font::NewCenterWrite(canc_title, &canc_btn, SDL_PointInRect(&m, &canc_btn) ? btn_fcol : title_fcol);

  return true;
}
