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

  unsigned short list_pg;
  short q_layer;
  bool delLayer, adjLayer, makeLayer;
  std::string z_string;

public:
  static CLayerEditor Control;

  void OnInit(const short& layer);

  void OnEvent(SDL_Event* Event);

  bool OnRender(const SDL_Point* m);

  void terminate();

  unsigned short getRecentLayer();
  unsigned short getZPrecision();

private:
  void resetLists();
  void enterZval(SDL_Keycode sym);
  void addToZ(const char& sym);
  void delFromZ();
  void deleteLayer();
  void adjustLayer();
  void makeNewLayer();
  void resetNewLayer();

private:
  void OnLButtonDown(int mX, int mY);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  bool handleChangeLayer(const SDL_Point* m);
  bool handleDeleteLayer(const SDL_Point* m);
  void handleDeleteLayer(SDL_Keycode sym);
  bool handleAdjustLayer(const SDL_Point* m);
  bool handleNewLayer(const SDL_Point* m);

private:
  bool drawCanvas();
  bool drawTitle();
  bool drawList(const SDL_Point* m);
  bool drawNewLayer(const SDL_Point* m);
  bool drawOptions(const SDL_Point* m);
};

#endif
