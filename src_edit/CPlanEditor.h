#ifndef _C_PLANEDITOR_H_
#define _C_PLANEDITOR_H_

#include "CPlanArea.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
#include "CEntity.h"
#include "CScenery.h"
#include "CCamera.h"
#include "CChangeTile.h"
#include "CTileset.h"
#include "CInterrupt.h"
#include "CInform.h"
#include "CError.h"
#include "Define.h"

class CPlanEditor : public CEvent {
  CPlanEditor();

  short visflag;    // bitwise flag for rendering map & its attributes
  int placeflag;    // bitwise flag for tiles to place
  CPlanTile workTile;
  int k;
  int sel_k;
  int sel_z;
  short active_opacity; // standard opacity of active layer
  short over_opacity;   // standard opacity of layers above active layer
  short under_opacity;  // standard opacity of layers below active layer
  std::vector<short> temp_opac; // vector for temporarily storing old layer opacities
  std::vector<bool> temp_force; // for temporarily storing old force-opacity flags

public:
  static CPlanEditor control;

  bool OnInit();

  void getK(int& k);

  void OnTerminate();

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point& mouse);

  void RenderMap();

private:
  void OnLButtonDown(int mX, int mY);
  bool handlePlaceTile(const SDL_Point& m);
  void placeTile(const int& x, const int& y);

  bool handleTileOpts(const SDL_Point& m);
  bool handleLayerOpts(const SDL_Point& m);
  bool handleVisOpts(const SDL_Point& m);
  bool handlePlaceOpts(const SDL_Point& m);
  bool handleSolidOpts(const SDL_Point& m);
  bool handleTypeOpts(const SDL_Point& m);
  bool handleOpacOpts(const SDL_Point& m);

  bool handleInterr(SDL_Event* Event);
  void changeTileset(SDL_Event* Event);
  void changeTile(SDL_Event* Event);
  void addLayer(const SDL_Point& m);
  void deleteLayer(const SDL_Point& m);
  void adjustOpacity(const SDL_Point& m);

private:
  void extendMap_R();
  void extendMap_L();
  void extendMap_D();
  void extendMap_U();
  void removeMap_R();
  void removeMap_L();
  void removeMap_D();
  void removeMap_U();

private:
  bool drawTileOutline(const SDL_Point* m);
  bool drawTileOpts(const SDL_Point* m);
  bool drawLayerOpts(const SDL_Point* m);
  bool drawVisOpts();
  bool drawPlaceOpts();
  bool drawSolidOpts();
  bool drawTypeOpts();
  bool drawOpacOpts(const SDL_Point* m);

  bool drawInterr(const SDL_Point& m);
  bool drawAddLayer(const SDL_Point& m);
  bool drawDelLayer(const SDL_Point& m);
  bool drawAdjustOpacity(const SDL_Point& m);
};

namespace pvmEditor {
  extern const short stroke_sz;
  extern const SDL_Point* btn_col;
  extern const SDL_Point* hov_col;
  extern const SDL_Point* nul_col;
  extern const SDL_Point* on_col;
  extern const SDL_Point* off_col;
  extern const SDL_Color* btn_fcol;
  extern const short outline_sz;
  extern const SDL_Point* outline_col;
  namespace tileOpts {
    extern const SDL_Rect ts_button;
    extern const SDL_Rect tile_button;
    extern const SDL_Color* title_fcol;
    extern const char* const ts_title;
    extern const char* const tile_title;
  }
  namespace layerOpts {
    extern const SDL_Rect add_button;
    extern const SDL_Rect del_button;
    // extern const SDL_Rect sel_button;
    // extern const SDL_Rect edt_button;
    extern const char* const add_str;
    extern const char* const del_str;
    namespace addOpts {
      extern const SDL_Rect window;
      extern const SDL_Rect list_header;
      extern const SDL_Rect work_header;
      extern const SDL_Rect k_header;
      extern const SDL_Rect z_header;
      extern const SDL_Rect k_field;
      extern const SDL_Rect z_field;
      extern const short incr_size;
      extern const char* const list_title;
      extern const char* const info;
      extern const char* const new_k_title;
      extern const char* const new_z_title;
      extern const char* const conf_title;
      extern const char* const canc_title;
      extern const short list_x;
      extern const short list_y;
      extern const short k_w; // width of k-index column
      extern const short z_w; // width of depth (z) column
      extern const short list_item_w;
      extern const short list_item_h;
      extern const SDL_Rect k_title_r;
      extern const SDL_Rect z_title_r;
      extern const SDL_Rect conf_btn;
      extern const SDL_Rect canc_btn;
      extern const SDL_Point* window_col;
      extern const SDL_Point* border_col;
      extern const SDL_Point* field_col;
      extern const SDL_Point* item_col_A;
      extern const SDL_Point* item_col_B;
      extern const SDL_Point* active_col;
      extern const SDL_Point* new_col;
      extern const SDL_Color* title_fcol;
    }
    namespace delOpts {
      extern const SDL_Rect window;
      extern const SDL_Rect list_header;
      extern const short k_w; // width of k-index column
      extern const short z_w; // width of depth (z) column
      extern const short list_x;
      extern const short list_y;
      extern const short list_item_w;
      extern const short list_item_h;
      extern const SDL_Rect k_title_r;
      extern const SDL_Rect z_title_r;
      extern const SDL_Rect conf_btn;
      extern const SDL_Rect canc_btn;
      extern const char* const info;
      extern const char* const conf_title;
      extern const char* const canc_title;
      extern const SDL_Point* window_col;
      extern const SDL_Point* border_col;
      extern const SDL_Point* item_col_A;
      extern const SDL_Point* item_col_B;
      extern const SDL_Point* active_col;
      extern const SDL_Color* title_fcol;  // title/info text color
    }
  }
  namespace visOpts {
    extern const short nOpts;
    extern const short opts[];
    extern const short w;
    extern const short h;
    extern const short opt_h;
    extern const short x;
    extern const short y;
    extern const SDL_Rect title_r;
    extern const SDL_Rect buttons[];
    extern const SDL_Color* title_fcol;
    extern const char* const title;
    extern const char* const labels[];
  }
  namespace placeOpts {
    extern const short nOpts;
    extern const short opts[];
    extern const short w;
    extern const short h;
    extern const short opt_h;
    extern const short x;
    extern const short y;
    extern const SDL_Rect title_r;
    extern const SDL_Rect buttons[];
    extern const SDL_Color* title_fcol;
    extern const char* const title;
    extern const char* const labels[];
  }
  namespace solidOpts {
    extern const short w;
    extern const short h;
    extern const short x;
    extern const short y;
    extern const SDL_Rect button;
    extern const char* const labels[];
  }
  namespace typeOpts {
    extern const short type_sz;
    extern const short cols;
    extern const short spac;
    // extern const short x;
    // extern const short y;
    extern const SDL_Point pos;
    extern const SDL_Point* hl_col;
  }
  namespace opacOpts {
    extern const short nMeters;
    extern const SDL_Rect r_titles[];
    extern const SDL_Rect meters[];
    extern const char* const titles[];
    extern const SDL_Rect more_button;
    extern const char* const more_title;
    namespace adjOpts {
      extern const SDL_Rect window;
      extern const SDL_Rect header;
      extern const short spac_h;
      extern const SDL_Rect k_r;
      extern const SDL_Rect z_r;
      extern const SDL_Rect meter_r;
      extern const SDL_Rect force_r;
      extern const SDL_Rect conf_btn;
      extern const SDL_Rect canc_btn;
      extern const char* const info;
      extern const char* const k_title;
      extern const char* const z_title;
      extern const char* const meter_title;
      extern const char* const force_title;
      extern const char* const conf_title;
      extern const char* const canc_title;
      extern const SDL_Point* window_col;
      extern const SDL_Point* border_col;
      extern const SDL_Point* item_col_A;
      extern const SDL_Point* item_col_B;
      extern const SDL_Color* title_fcol;
    }
  }
} // planview map editor namespaces //

#endif
