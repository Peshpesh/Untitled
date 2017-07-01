#ifndef _C_TILESET_H_
#define _C_TILESET_H_

#include <string>
#include "CInterrupt.h"
#include "CEvent.h"
#include "CSurface.h"
#include "CFont.h"
#include "CAsset.h"

class CTileset : public CEvent {
private:
  std::string file;
  std::string newF;
  bool changeTS;

public:
  static CTileset PickTS;

public:
	CTileset();

  SDL_Texture* changeTileset();

  void resetPath();

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

	void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);

  std::string getFilePath();

  bool reqChange();

private:
  void backPath();
  void addToPath(char addChar);

};

#endif
