#ifndef _C_TILESET_H_
#define _C_TILESET_H_

#include <string>
#include "CInform.h"
#include "CInterrupt.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CFont.h"
#include "CAsset.h"

class CTileset : public CEvent {
private:
  std::string file;
  std::string newF;

public:
  SDL_Texture* tileset;
  int ts_w, ts_h;

public:
  static CTileset PickTS;

public:
	CTileset();

  bool OnInit();

  bool changeTileset(const char* fname);
  void changeTileset();

  void resetPath();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);

  std::string getFilePath();

private:
  void backPath();
  void addToPath(char addChar);
  void pushInform(const int& ID);
};

#endif
