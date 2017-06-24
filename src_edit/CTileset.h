#ifndef _C_TILESET_H_
#define _C_TILESET_H_

#include <string>
#include "CInterrupt.h"
#include "CSurface.h"
#include "CFont.h"
#include "CAsset.h"

class CTileset {
private:
  static std::string file;
  static std::string newF;
  static const char* const ts_path;
  static const char* const extension;

public:
	CTileset();

  static SDL_Texture* changeTileset();

  static void resetPath();

  static bool OnKeyDown(SDL_Keycode sym, Uint16 mod);

	static bool OnLButtonDown(const SDL_Point* mouse);

  static bool OnRender();

  static std::string getFilePath();

private:

  static void backPath();

  static void addToPath(char addChar);

};

#endif
