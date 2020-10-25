#ifndef _C_CHANGESCENERY_H_
#define _C_CHANGESCENERY_H_

#include "CAsset.h"
#include "CEvent.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CScenery.h"
#include "Define.h"

class CChangeScenery : public CEvent {
public:
  static CChangeScenery Control;

private:
  std::vector<SDL_Rect> groupButtons;
  std::vector<SDL_Rect> decorButtons;

public:
  bool planview;

private:
  SDL_Texture* Group_Tex;
  bool succ;       // SUCC
  short group_ID;
  short decor_ID;

public:
  CChangeScenery();

  void OnInit(const short& group_ID, const short& decor_ID);
  void OnInit(const short& group_ID, const short& decor_ID, SDL_Texture* tex); // for pvm
  void handleChanges(short& group_ID, short& decor_ID);

public:
  void OnEvent(SDL_Event* Event);

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);
  bool handleConfirm(const SDL_Point* m);
  bool handleCancel(const SDL_Point* m);
  bool handleGroup(const SDL_Point* m);
  bool handleScenery(const SDL_Point* m);

public:
  bool OnRender(const SDL_Point* m);
  bool drawTitle();
  bool drawGroupButtons(const SDL_Point* m);
  bool drawSceneryButtons(const SDL_Point* m);
  bool drawConfirmButtons(const SDL_Point* m);
  bool drawSampleScenery(const SDL_Point* m);

private:
  SDL_Texture* updateTexture();
  void updateSceneryButtons();
};

#endif
