#include "CPlanEditor.h"

bool CPlanEditor::OnRender(const SDL_Point& m) {
  if (!CAsset::drawAppFrame()) return false;

  bool interr = !(CInterrupt::isNone());

  if (!drawTileOpts(interr ? NULL : &m))  return false;
  if (!drawLayerOpts(interr ? NULL : &m)) return false;
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
    CPlanArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), k, visflag);
  }
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
        // CInterrupt::isFlagOn(INTRPT_CHANGE_TS) ? on_col :
        SDL_PointInRect(m, &add_button) ? hov_col : btn_col)) return false;

    if (!CAsset::drawStrBox(&del_button, stroke_sz,
        // CInterrupt::isFlagOn(INTRPT_CHANGE_BG) ? on_col :
        SDL_PointInRect(m, &del_button) ? hov_col : btn_col)) return false;
  } else {
    if (!CAsset::drawStrBox(&add_button, stroke_sz, btn_col)) return false;
    if (!CAsset::drawStrBox(&del_button, stroke_sz, btn_col)) return false;
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
  return true;
}

bool CPlanEditor::drawDelLayer(const SDL_Point& m) {
  return true;
}
