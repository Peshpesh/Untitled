#ifndef _C_TILESET_H_
#define _C_TILESET_H_

#include <string>
#include "CInform.h"
#include "CInterrupt.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CFont.h"
#include "CAsset.h"

namespace Tileset_ID {
  const short num = 1;
  enum {
    TS_DEFAULT = 0,
  };
  const std::string name[] = {
    "default",
  };
};

class CTileset : public CEvent {
private:
  std::string file;
  std::string newF;

public:
  SDL_Texture* tileset;
  int ts_w, ts_h;
  bool succ;

public:
  static CTileset TSControl;

public:
	CTileset();

  bool OnInit();
  void OnTerminate();

  bool changeTileset(const short& fID);
  bool changeTileset(const std::string& fname);
  void changeTileset();

  void resetPath();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);

  std::string getFileName();
  std::string getFilePath();
  short getFileID(const std::string& fname);
  short getFileID();
  SDL_Rect getTileSrcR(const int& ID);

  bool wasSuccess();

private:
  void backPath();
  void addToPath(char addChar);
  void pushInform(const int& ID);
};

#endif
