#ifndef _C_PLANENTITY_H_
#define _C_PLANENTITY_H_

#include "CSurface.h"
#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
// #include "CPlanArea.h"
// #include "CEntity.h"
#include "CCamera.h"
#include "CInterrupt.h"
#include "CInform.h"
#include "CError.h"
#include "Define.h"

class CPlanEntity : public CEvent {
  CPlanEntity();

public:
  static CPlanEntity control;

  bool OnInit();

  void getK(int& k);
  void setK(const int& k);

  void OnTerminate();

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point& mouse);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);
};

namespace pvmEntity {
  extern const short stroke_sz;
  extern const SDL_Point* btn_col;
  extern const SDL_Point* hov_col;
  extern const SDL_Point* nul_col;
  extern const SDL_Point* on_col;
  extern const SDL_Point* off_col;
  extern const SDL_Color* btn_fcol;
  extern const short outline_sz;
  extern const SDL_Point* outline_col;
  extern const SDL_Point* big_outline_col;
  extern const SDL_Point* domain_col;
  extern const SDL_Point* conf_domain_col;
} // planview map editor namespaces //

#endif
