#include "CInventory.h"

CInventory CInventory::control;

CInventory::CInventory() {
  muns = 0;
  pos = 0;
}

void CInventory::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CInventory::OnKeyDown(SDL_Keycode sym, Uint16 mod) {

}

bool CInventory::OnRender() {
  // const short canv_w = 400;
  // const short canv_h = 100 + 150 + 120;
  // const short str_w = 2;
  // const SDL_Rect equip_r = {(WWIDTH - canv_w) / 2, (WHEIGHT - canv_h) / 2, canv_w, 100};
  // const SDL_Rect items_r = {(WWIDTH - canv_w) / 2, equip_r.y + equip_r.h, canv_w, 150};
  // const SDL_Rect title_r = {(WWIDTH - canv_w) / 2, items_r.y + items_r.h, canv_w, 36};
  // const SDL_Rect about_r = {(WWIDTH - canv_w) / 2, items_r.y + items_r.h, canv_w, 120};
  // const SDL_Color* f_col = &rgb::green;
  // const SDL_Point* c_col = &palette::black;
  // const SDL_Point* s_col = &palette::light_green;
  if (!drawFrame())     return false;
  if (!drawEquipment()) return false;
  if (!drawItems())     return false;
  if (!drawCursor())    return false;
  if (!drawInfo())      return false;
  return true;
}

bool CInventory::drawFrame() {
  using namespace invinterface;
  if (!CAsset::drawStrBox(canvas_r, str_w, c_col, s_col)) return false;
  if (!CAsset::drawStrBox(about_r, str_w, c_col, s_col)) return false;
  return true;
}

bool CInventory::drawEquipment() {
  using namespace invinterface;
  int init_x = equip_r.x + (equip_r.w - (ITEM_SIZE * row_items) - (buff_sp * (row_items - 1))) / 2;
  int init_y = equip_r.y + (equip_r.h - (ITEM_SIZE * 2) - buff_sp) / 2;
  SDL_Rect dest = {init_x, init_y, ITEM_SIZE, ITEM_SIZE};

  for (int i = 0; i < equipment.size(); i++) {
    // render equipment icon
    // if (!CSurface::OnDraw(...texture..., equipment[i].spr, dest)) return false;
    if (((i + 1) % row_items == 0)) {
      dest.x = init_x;
      dest.y += buff_sp + ITEM_SIZE;
    } else {
      dest.x += buff_sp + ITEM_SIZE;
    }
  }
  return true;
}

bool CInventory::drawItems() {
  using namespace invinterface;
  int init_x = items_r.x + (items_r.w - (ITEM_SIZE * row_items) - (buff_sp * (row_items - 1))) / 2;
  int init_y = items_r.y + (items_r.h - (ITEM_SIZE * 2) - buff_sp) / 2;
  SDL_Rect dest = {init_x, init_y, ITEM_SIZE, ITEM_SIZE};

  for (int i = 0; i < items.size(); i++) {
    // render item icon
    // if (!CSurface::OnDraw(...texture..., items[i].spr, dest)) return false;
    if (((i + 1) % row_items == 0)) {
      dest.x = init_x;
      dest.y += buff_sp + ITEM_SIZE;
    } else {
      dest.x += buff_sp + ITEM_SIZE;
    }
  }
  return true;
}

bool CInventory::drawCursor() {
  using namespace invinterface;
  return true;
}

bool CInventory::drawInfo() {
  using namespace invinterface;
  return true;
}
