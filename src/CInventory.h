#ifndef _C_INVENTORY_H_
#define _C_INVENTORY_H_

#include "CEvent.h"
#include "CControls.h"
#include "CInterrupt.h"
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
  namespace adderrors {
    enum {
      ONLYONE = 1,
      TOOMANY = 2,
      NOSPACE = 3,
    };
  }
}

namespace invinterface {
  extern const short row_items;
  extern const short buff_sp;
  extern const short canv_w;
  extern const short canv_h;
  extern const short menu_w;
  extern const short str_w;
  extern const SDL_Rect canvas_r;
  extern const SDL_Rect equip_r;
  extern const SDL_Rect items_r;
  extern const SDL_Rect title_r;
  extern const SDL_Rect about_r;
  extern const SDL_Color* f_col;
  extern const SDL_Point* c_col;
  extern const SDL_Point* s_col;
  extern const SDL_Color* cursor_col;
  extern const short cursor_w;
  namespace optmenu {
    extern const SDL_Rect menu_r;
    extern const SDL_Rect opts_r;
    extern const SDL_Point* c_col;
    extern const SDL_Color* f_inactive;
    extern const SDL_Color* f_col;
    extern const SDL_Color* f_hov;
    extern const short str_w;
    extern const SDL_Point* s_col;
    extern const short num_options;
    extern const short opts_h;
    extern const char* const opt_list[];
    enum decision {
      USE_ITEM,
      DROP_ITEM,
      CANCEL,
    };
  }
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
  SDL_Texture* itemsrc;
  std::vector<CItem> equipment;
  std::vector<CItem> items;
  short muns;
  short pos;
  bool menuactive;
  short menupos;

public:
  bool init();
  void reinit();

public:
  void OnEvent(SDL_Event* Event);
private:
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void handleNav(const Gamecon& action);
  void handleMenu(const Gamecon& action);

public:
  bool OnRender();
private:
  bool drawFrame();
  bool drawEquipment();
  bool drawItems();
  bool drawCursor(const SDL_Rect& dest);
  void drawInfo();
  bool drawMenu();

public:
  short canAddItem(const short& ID);
  void addItem(const short& ID);

private:
  CItem fetchItem(const short& ID);
  void fetchInfo(const short& ID, std::string& name, std::string& about);

public:
  void Cleanup();
};

#endif
