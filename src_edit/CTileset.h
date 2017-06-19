#ifndef _C_TILESET_H_
#define _C_TILESET_H_

#include <string>
#include "CSurface.h"
#include "CFont.h"
#include "CAsset.h"

class CTileset {
private:
  static std::string filename;
  static std::string newFilename;
  static const char* const ts_path;
  static const char* const extension;

public:
	CTileset();

	static bool OnLClick(const SDL_Point* mouse);

  static std::string getFilePath();
};

#endif
