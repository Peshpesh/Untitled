#ifndef _C_MODEL_H_
#define _C_MODEL_H_

#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CAsset.h"
#include "CFont.h"
#include "CArea.h"
#include "CEntityEdit.h"

namespace model {
  extern const short mod_t_sz;        // Model tile size (px)
  extern const short b_sz;            // canvas border thickness (px)
  extern const SDL_Point* b_col;      // canvas border color
  extern const SDL_Point* canv_col;   // canvas color
}

class CModel : public CEvent {
  CModel();

private:
  int mW;
  int mH;
  SDL_Rect infoCanvas;
  SDL_Rect visCanvas;
  SDL_Rect typeCanvas;
  SDL_Rect collCanvas;

public:
  static CModel Control;

  void OnInit();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);

  bool renderInfoWindow();
  bool renderVisWindow();
  bool renderTypeWindow();
  bool renderCollWindow();
};

#endif
