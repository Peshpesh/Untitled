#ifndef _C_LAYEREDITOR_H_
#define _C_LAYEREDITOR_H_

#include "CAsset.h"
#include "CEvent.h"
#include "CFont.h"
#include "CInform.h"
#include "CInterrupt.h"
#include "CScenery.h"

class CLayerEditor : public CEvent {
  CLayerEditor();

  std::vector<SDL_Rect> layerList;
  std::vector<SDL_Rect> depthList;

  bool makeLayer;
  std::string z_string;

public:
  static CLayerEditor Control;

  void OnInit();

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point* m);

  void terminate();

private:
  void resetLists();
  void enterZval(SDL_Keycode sym);
  void addToZ(const char& sym);
  void delFromZ();
  void newLayer();

private:
  void OnLButtonDown(int mX, int mY);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

private:
  bool drawCanvas();
  bool drawList(const SDL_Point* m);
  bool drawOptions(const SDL_Point* m);
};

#endif
