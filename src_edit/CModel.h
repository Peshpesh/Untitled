#ifndef _C_MODEL_H_
#define _C_MODEL_H_

#include "CEntity.h"
#include "CScenery.h"
#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CArea.h"
#include "CStage.h"
// #include "CFileIO.h"

namespace model {
  extern const short info_sz;
  extern const short mod_t_sz;        // Model tile size (px)
  extern const short b_sz;            // canvas border thickness (px)
  extern const SDL_Point* b_col;      // canvas border color
  extern const SDL_Point* canv_col;   // canvas color
}

class CModel : public CEvent {
  CModel();

  int aW;
  int aH;
  int mW;
  int mH;
  SDL_Rect infoCanvas;
  SDL_Rect visCanvas;
  SDL_Rect typeCanvas;
  SDL_Rect collCanvas;
  SDL_Rect infoFrame;
  SDL_Rect visFrame;
  SDL_Rect typeFrame;
  SDL_Rect collFrame;

public:
  static CModel Control;

  void OnInit();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);

private:
  bool renderInfoWindow();
  bool renderVisWindow();
  bool renderTypeWindow();
  bool renderCollWindow();

private:
  bool renderInfo();
  bool renderArea();
  bool renderMap(CMap* map, const int& x_rel, const int& y_rel);

private:
  bool drawVisTile(const int& x_rel, const int& y_rel, const int& bg_ID, const int& fg_ID);
  bool drawTypeTile(const int& x_rel, const int& y_rel, const int& typeID);
  bool drawCollTile(const int& x_rel, const int& y_rel, const int& collID);
};

#endif
