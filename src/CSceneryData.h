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
      GOLDENROD = 1,
    };
  };
  namespace global {
    extern const short num;
    extern const char* const name[];
    enum {
      NOTHING = 0,
    };
  };
  namespace goldenrod {
    extern const short num;
    extern const char* const name[];
    enum {
      L_TREE_A = 0, L_TREE_B, L_TREE_C, L_TREE_D, L_SHRUB_A, L_SHRUB_B, L_SHRUB_C,
      M_TREE_A, M_TREE_B, M_TREE_C, M_TREE_D, M_SHRUB_A, M_SHRUB_B, M_SHRUB_C,
      S_TREE_A, S_TREE_B, S_TREE_C, S_TREE_D, S_SHRUB_A, S_SHRUB_B, S_SHRUB_C,
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
  static void getDims_goldenrod(const int& decor, SDL_Rect& srcRect);
  static void getName_global(const int& decor, std::string& str);
  static void getName_goldenrod(const int& decor, std::string& str);
};

#endif
