#include "CInventory.h"

CInventory CInventory::control;

CInventory::CInventory() {
  muns = 0;
  pos = 0;
  itemsrc = NULL;
}

bool CInventory::init() {
  if ((itemsrc = CSurface::OnLoad("../res/item.png")) == NULL) {
    return false;
  } return true;
}

void CInventory::reinit() {
  muns = 0;
  pos = 0;
  equipment.clear();
  items.clear();

  // DEBUGGING
  addItem(items::JOURNAL);
  addItem(items::WARMGLOVES);
}

void CInventory::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CInventory::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  Gamecon action = CControls::handler.getAction(sym, mod);

  // lol
  short eq_rows = 1 + ((equipment.size() - 1) / invinterface::row_items);
  short it_rows = 1 + ((items.size() - 1) / invinterface::row_items);
  short eq_resid = equipment.size() % invinterface::row_items;
  short it_resid = items.size() % invinterface::row_items;
  short row = (pos < equipment.size()) ?
              1 + (pos / invinterface::row_items) :
              eq_rows + 1 + ((pos - equipment.size()) / invinterface::row_items);

  // LOL
  switch (action) {
    case CON_LEFT: {
      if (pos < equipment.size()) {
        if (pos % invinterface::row_items == 0) {
          pos += (row == eq_rows) ? eq_resid - 1 : invinterface::row_items - 1;
        } else {
          pos--;
        }
      } else {
        if ((pos - equipment.size()) % invinterface::row_items == 0) {
          pos += (row == eq_rows + it_rows) ? it_resid - 1 : invinterface::row_items - 1;
        } else {
          pos--;
        }
      }
      break;
    }
    case CON_RIGHT: {
      if (pos < equipment.size()) {
        if ((pos + 1) % invinterface::row_items == 0) {
          pos -= (invinterface::row_items - 1);
        } else if (pos == equipment.size() - 1) {
          pos -= (eq_resid - 1);
        } else {
          pos++;
        }
      } else {
        short adj_pos = pos - equipment.size();
        if ((adj_pos + 1) % invinterface::row_items == 0) {
          pos -= (invinterface::row_items - 1);
        } else if (adj_pos == items.size() - 1) {
          pos -= (it_resid - 1);
        } else {
          pos++;
        }
      }
      break;
    } // LMFAOOOOOOOOOO WLAWLAOW ALKWLAW AOLWAW
    case CON_DOWN: {
      if (pos < equipment.size()) {
        if (row == eq_rows) {
          pos += eq_resid ? eq_resid : invinterface::row_items;
          if (pos > equipment.size() + items.size()) pos = pos % invinterface::row_items;
        } else {
          if (pos + invinterface::row_items < equipment.size()) {
            pos += invinterface::row_items;
          } else {
            if (equipment.size() + (pos % invinterface::row_items) > equipment.size() + items.size()) {
              pos = pos % invinterface::row_items;
            } else {
              pos = equipment.size() + (pos % invinterface::row_items);
            }
          }
        }
      } else {
        short adj_pos = pos - equipment.size();
        if (row == eq_rows + it_rows) {
          if (adj_pos % invinterface::row_items >= equipment.size()) {
            pos = equipment.size() + (adj_pos % invinterface::row_items);
          } else {
            pos = adj_pos % invinterface::row_items;
          }
        } else {
          if (adj_pos + invinterface::row_items < items.size()) {
            pos += invinterface::row_items;
          } else {
            if (adj_pos % invinterface::row_items >= equipment.size()) {
              pos = equipment.size() + (adj_pos % invinterface::row_items);
            } else {
              pos = adj_pos % invinterface::row_items;
            }
          }
        }
      }
      break;
    }
    case CON_UP: {
      if (pos < equipment.size()) {
        if (pos >= invinterface::row_items) {
          pos -= invinterface::row_items;
        } else {
          if (pos >= items.size()) {
            if (pos + (invinterface::row_items * (eq_rows - 1)) >= equipment.size()) {
              pos = pos + (invinterface::row_items * (eq_rows - 1)) - invinterface::row_items;
            } else {
              pos = pos + (invinterface::row_items * (eq_rows - 1));
            }
          } else {
            if (pos + (invinterface::row_items * (it_rows - 1)) >= items.size()) {
              pos = pos + (invinterface::row_items * (it_rows - 1)) - invinterface::row_items;
            } else {
              pos = pos + (invinterface::row_items * (it_rows - 1));
            }
          }
        }
      } else {
        short adj_pos = pos - equipment.size();
        if (adj_pos >= invinterface::row_items) {
          pos -= invinterface::row_items;
        } else {
          if (adj_pos >= equipment.size()) {
            if (adj_pos + (invinterface::row_items * (it_rows - 1)) >= items.size()) {
              pos = adj_pos + (invinterface::row_items * (it_rows - 1)) - invinterface::row_items;
            } else {
              pos = adj_pos + (invinterface::row_items * (it_rows - 1));
            }
          } else {
            if (adj_pos + (invinterface::row_items * (eq_rows - 1)) >= equipment.size()) {
              pos = adj_pos + (invinterface::row_items * (eq_rows - 1)) - invinterface::row_items;
            } else {
              pos = adj_pos + (invinterface::row_items * (eq_rows - 1));
            }
          }
        }
      }
      break;
    }
    // case CON_ATTACK: {
    //   switch (pos) {
    //     case RESUME:     		unpause(); break;
    //     case AUDIO_MENU:    menu_kind = ADJUST_AUDIO; pos = 0; break;
    //     case VIDEO_MENU: 		menu_kind = ADJUST_VIDEO; pos = 0; break;
    //     case QUIT_MENU:    	menu_kind = QUIT_GAME; pos = 0; break;
    //     default: break;
    //   } break;
    // }
    // case CON_PAUSE: unpause(); break;
    default: break;
  }
}

bool CInventory::OnRender() {
  if (!drawFrame())     return false;
  if (!drawEquipment()) return false;
  if (!drawItems())     return false;
  if (!drawCursor())    return false;
  drawInfo();
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
    if (!CSurface::OnDraw(itemsrc, equipment[i].spr, dest)) return false;
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
    if (!CSurface::OnDraw(itemsrc, items[i].spr, dest)) return false;
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

void CInventory::drawInfo() {
  using namespace invinterface;
  std::string name, about;
  if (pos < equipment.size()) {
    fetchInfo(equipment[pos].ID, name, about);
  } else {
    fetchInfo(items[pos - equipment.size()].ID, name, about);
  }
  CType::NewCenterWrite(name.c_str(), title_r, f_col);
  CType::NewCenterWrite(about.c_str(), about_r, f_col);
}

short CInventory::canAddItem(const short& ID) {
  // using namespace items::adderrors;
  // for (int i = 0; i < equipment.size(); i++) {
  //   if (ID == equipment[i].ID) {
  //     if (equipment[i].maxnum == 1) return ONLYONE;
  //     if (equipment[i].num == equipment[i].maxnum) return TOOMANY;
  //     return 0;
  //   }
  // }
  //
  // for (int i = 0; i < items.size(); i++) {
  //   if (ID == items[i].ID) {
  //     if (items[i].num == items[i].maxnum) return TOOMANY;
  //   }
  // }
  // if (items.size() == items::max_items) return NOSPACE;
  //
  // return 0;
}

void CInventory::addItem(const short& ID) {
  CItem newitem = fetchItem(ID);
  if (newitem.equip) {
    equipment.push_back(newitem);
  } else {
    items.push_back(newitem);
  }
}

void CInventory::Cleanup() {
  SDL_DestroyTexture(itemsrc);
}
