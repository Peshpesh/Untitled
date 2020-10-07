#ifndef _C_CHANGEENTITY_H_
#define _C_CHANGEENTITY_H_

#include "CAsset.h"
#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CEntity.h"
#include "Define.h"

class CChangeEntity : public CEvent {
public:
  static CChangeEntity Control;

private:
  std::vector<SDL_Rect> groupButtons;
  std::vector<SDL_Rect> entityButtons;

private:
  SDL_Texture* Group_Tex;
  bool succ;       // SUCC
  short group_ID;
  short entity_ID;

public:
  CChangeEntity();

  void OnInit(const short& group_ID, const short& entity_ID);
  void handleChanges(short& group_ID, short& entity_ID);

public:
  void OnEvent(SDL_Event* Event);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);
  bool handleConfirm(const SDL_Point* m);
  bool handleCancel(const SDL_Point* m);
  bool handleGroup(const SDL_Point* m);
  bool handleEntity(const SDL_Point* m);

public:
  bool OnRender(const SDL_Point* m);
  bool drawTitle();
  bool drawGroupButtons(const SDL_Point* m);
  bool drawEntityButtons(const SDL_Point* m);
  bool drawConfirmButtons(const SDL_Point* m);
  bool drawSampleEntity(const SDL_Point* m);

private:
  SDL_Texture* updateTexture();
  void updateEntityButtons();
};

#endif
