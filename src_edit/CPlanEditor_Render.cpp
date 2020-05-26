#include "CPlanEditor.h"

bool CPlanEditor::OnRender(const SDL_Point& m) {
  // if (!RenderWkspc(mouse)) return false;
  if (!CAsset::drawAppFrame()) return false;
  // if (!RenderSidebar(mouse)) return false;
  // if (!RenderBottom(mouse)) return false;

  if (!drawVisOpts()) return false;
  if (!drawPlaceOpts()) return false;
  if (!drawSolidOpts()) return false;
  if (!drawTypeOpts()) return false;
  return true;
}

void CPlanEditor::RenderMap() {
  // render the area's layers in order from bottom to top
  for (int k = 0; k < CPlanArea::control.LayerList.size(); k++) {
    CPlanArea::control.OnRender(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), k, visflag);
  }
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
        CAsset::drawBox(&dstR, &palette::red);
      }
      k++;
    }
  }
  CTileset::TSControl.refreshTypeAlpha();
  return true;
}
