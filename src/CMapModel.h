#ifndef _C_MAPMODEL_H_
#define _C_MAPMODEL_H_

#include "CEvent.h"
#include "CControls.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CType.h"
#include "CArea.h"
#include "CLocation.h"

namespace mapmodel {
  extern const short mod_t_sz;        // Model tile size (px)
  extern const short b_sz;            // canvas border thickness (px)
  extern const SDL_Point* b_col;      // canvas border color
  extern const SDL_Point* canv_col;   // canvas color
  extern const SDL_Point* hero_col;   // hero location indicator color
  extern const SDL_Color* f_col;      // title color
  extern const short title_h;         // title box height
  // extern const short font; // typefont?
}

class CMapModel : public CEvent {
  CMapModel();
  int aW;
  int aH;
  int mW;
  int mH;
  SDL_Rect visCanvas;
  SDL_Rect visFrame;
  SDL_Rect visTitle;

public:
  static CMapModel control;

  void OnInit();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  bool OnRender();
  bool OnRender(const float& hero_x, const float& hero_y);

private:
  bool renderVisWindow();
  bool renderTitle();
  bool renderArea();
  bool renderMap(CMap* map, const int& x_rel, const int& y_rel);
  bool renderPosition(const float& x, const float& y);

private:
  bool drawVisTile(const int& x_rel, const int& y_rel, const int& bg_ID, const int& fg_ID);
};

#endif
