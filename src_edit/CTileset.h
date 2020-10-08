#ifndef _C_TILESET_H_
#define _C_TILESET_H_

#include <string>
#include "CInform.h"
#include "CInterrupt.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CFont.h"
#include "CAsset.h"
#include "CTile.h"

namespace Tileset_ID {
  const short num = 2;
  enum {
    TS_DEFAULT = 0,
    NEW_YRAI_PV = 1,
  };
  const std::string name[] = {
    "default",
    "newyraipv",
  };
  const std::string fullname[] = {
    "Default",
    "New Yrai Planview",
  };
};

class CTileset : public CEvent {
private:
  short active_ID; // ID of active tileset
  short select_ID; // ID of selected tileset

public:
  SDL_Texture* tileset;
  SDL_Texture* grid_tileset;
  SDL_Texture* type_tileset;
  SDL_Texture* coll_tileset;
  int ts_w, ts_h;
  int tile_alpha;           // Current Opacity of the tileset
  int type_alpha;           // Current Opacity of the Type overlay
  int coll_alpha;           // Current Opacity of the Collision overlay
  int grid_alpha;           // Current Opacity of grid (and solid PVM tile) overlay
  int grid_w, grid_h;       // Grid texture dimension (tiles)
  int type_w, type_h;       // Typeset texture dimension (tiles)
  int coll_w, coll_h;       // Collset texture dimension (tiles)
  bool succ;

public:
  static CTileset TSControl;

public:
  CTileset();

  bool OnInit();
  void OnTerminate();

  bool changeTileset(const short& fID);
  bool changeTileset();
  void changeTileAlpha(const int& a);
  void changeTypeAlpha(const int& a);
  void changeCollAlpha(const int& a);
  void maxTileAlpha();
  void maxTypeAlpha();
  void maxCollAlpha();
  void refreshTileAlpha();
  void refreshTypeAlpha();
  void refreshCollAlpha();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);
  bool pickTileset(const SDL_Point& m);

  bool OnRender(const SDL_Point* m);
  void drawOptions(const SDL_Point* m);
  short drawTile(const int& ID, const int& X, const int& Y);
  bool drawFill(const int& X, const int& Y);
  bool drawSolid(const int& X, const int& Y);
  short drawType(const short& tiletype, const int& X, const int& Y);

  std::string getFileName();
  std::string getFilePath();
  short getFileID(const std::string& fname);
  short getFileID();
  SDL_Rect getTileSrcR(const int& ID);

  bool wasSuccess();

private:
  void pushInform(const int& ID);
};

#endif
