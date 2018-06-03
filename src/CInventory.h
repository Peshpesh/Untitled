#ifndef _C_INVENTORY_H_
#define _C_INVENTORY_H_

#include "CEvent.h"
#include "CAsset.h"
#include "CType.h"
#include "Define.h"
#include <string>
#include <vector>

namespace items {
  extern const short max_items;
  enum {
    MISSING = 0,
    JOURNAL,
    PEWPEW,
    MEDIKIT,
    WARMGLOVES,
    ROOMKEY_RUINS,
    TRANQUIL_STONE,
  };
}

namespace invinterface {
  extern const short row_items;
  extern const short buff_sp;
  extern const short canv_w;
  extern const short canv_h;
  extern const short str_w;
  extern const SDL_Rect canvas_r;
  extern const SDL_Rect equip_r;
  extern const SDL_Rect items_r;
  extern const SDL_Rect title_r;
  extern const SDL_Rect about_r;
  extern const SDL_Color* f_col;
  extern const SDL_Point* c_col;
  extern const SDL_Point* s_col;
}

struct CItem {
  short ID;
  bool equip;
  unsigned short num;
  unsigned short maxnum;
  SDL_Rect spr;
};

class CInventory : public CEvent {
  CInventory();
public:
  static CInventory control;
  std::vector<CItem> equipment;
  std::vector<CItem> items;
  short muns;
  short pos;

public:
  void OnEvent(SDL_Event* Event);
private:
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);

public:
  bool OnRender();
private:
  bool drawFrame();
  bool drawEquipment();
  bool drawItems();
  bool drawCursor();
  bool drawInfo();

public:
  CItem fetchItem(const short& ID);
private:
  void fetchInfo(const short& ID, std::string& name, std::string& about);
};

#endif
