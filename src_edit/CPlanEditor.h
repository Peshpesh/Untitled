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
  int placeflag; // bitwise flag for tiles to place
  CPlanTile workTile;
  int Z;

public:
  static CPlanEditor control;

  bool OnInit();

  void OnTerminate();

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point& mouse);

  void RenderMap();

private:
  void OnLButtonDown(int mX, int mY);
  bool handlePlaceTile(const SDL_Point& m);
  void placeTile(const int& x, const int& y);

  bool handleTileOpts(const SDL_Point& m);
  bool handleVisOpts(const SDL_Point& m);
  bool handlePlaceOpts(const SDL_Point& m);
  bool handleSolidOpts(const SDL_Point& m);
  bool handleTypeOpts(const SDL_Point& m);

  bool handleInterr(SDL_Event* Event);
  void changeTileset(SDL_Event* Event);
  void changeTile(SDL_Event* Event);

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
  bool drawTileOpts(const SDL_Point* m);
  bool drawVisOpts();
  bool drawPlaceOpts();
  bool drawSolidOpts();
  bool drawTypeOpts();
  bool drawInterr(const SDL_Point& m);
};

namespace pvmEditor {
  extern const short stroke_sz;
  extern const SDL_Point* btn_col;
  extern const SDL_Point* hov_col;
  extern const SDL_Point* on_col;
  extern const SDL_Point* off_col;
  extern const SDL_Color* btn_fcol;
  namespace tileOpts {
    extern const SDL_Rect ts_button;
    extern const SDL_Rect tile_button;
    extern const SDL_Color* title_fcol;
    extern const char* const ts_title;
    extern const char* const tile_title;
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
} // planview map editor namespaces //

#endif
