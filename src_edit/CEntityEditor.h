#ifndef _C_ENTITYEDITOR_H_
#define _C_ENTITYEDITOR_H_

#include "CEvent.h"
#include "CAsset.h"
#include "CFont.h"
#include "CEntity.h"
#include "CInterrupt.h"
#include "CInform.h"
#include "CCamera.h"
#include "Define.h"

class CEntityEditor : public CEvent {
private:
  CEntityEditor();

  bool showEntity;
  bool showHitbox;
  unsigned short entity_alpha;
  unsigned short hitbox_alpha;

public:
  static CEntityEditor Control;

public:
  bool OnInit();
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);
private:
  bool handleInterr(SDL_Event* Event);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
  void OnRButtonDown(int mX, int mY);

public:
  bool OnRender(const SDL_Point* m);
  bool drawEntities();
  bool drawHitboxes();
};

#endif
