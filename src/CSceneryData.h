#ifndef _C_SCENERYDATA_H_
#define _C_SCENERYDATA_H_

#include <string>
#include <vector>
#include <stdio.h>
#include "CAsset.h"
#include "CSurface.h"

namespace Decorations {
  namespace groups {
    extern const short num;
    extern const char* const name[];
    enum {
      GLOBAL = 0,
    };
  };
  namespace global {
    extern const short num;
    extern const char* const name[];
    enum {
      NOTHING = 0,
    };
  };
};

class CSceneryData {
  CSceneryData();

public:
  static short getNumGroups();
  static short getNumDecor(const int& group);

public:
  static SDL_Texture* loadSrcTexture(const int& group);

public:
  static SDL_Rect getDecorDims(const int& group, const int& decor);
  static std::string getGroupName(const int& group);
  static std::string getDecorName(const int& group, const int& decor);

private:
  static void getDims_global(const int& decor, SDL_Rect& srcRect);
  static void getName_global(const int& decor, std::string& str);
};

#endif
