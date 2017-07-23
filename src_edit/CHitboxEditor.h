#ifndef _C_HITBOXEDITOR_H_
#define _C_HITBOXEDITOR_H_

#include <string>
#include <vector>

#include "CEvent.h"
#include "CFont.h"
#include "CAsset.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CEntity.h"

class CHitboxEditor : public CEvent {
  CHitboxEditor();

  std::vector<SDL_Rect> hitboxList;
  int group_ID;
  int entity_ID;

public:
  static CHitboxEditor Control;

  bool OnInit(const int& group, const int& entity);

  void OnEvent(SDL_Event* Event);
  void OnLButtonDown(int mX, int mY);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

public:
  bool OnRender(const SDL_Point* m);
};

#endif
