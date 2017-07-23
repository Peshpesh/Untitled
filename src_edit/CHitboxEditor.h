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

  SDL_Texture* Group_Tex;
  std::vector<SDL_Rect> hitboxList;
  std::vector<SDL_Rect> entityList;
  int group_ID;
  int entity_ID;
  int anchors;

public:
  static CHitboxEditor Control;

  bool OnInit(const int& group, const int& entity);

  void OnEvent(SDL_Event* Event);

private:
  void OnLButtonDown(int mX, int mY);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

public:
  bool OnRender(const SDL_Point* m);
private:
  bool drawList(const SDL_Point* m);
  bool drawEntity();
  bool drawHitbox();
  bool drawDials(const SDL_Point* m);
};

#endif
