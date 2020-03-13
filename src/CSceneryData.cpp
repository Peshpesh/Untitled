#include "CSceneryData.h"

namespace Decorations {
  namespace groups {
    const short num = 2;
    const char* const name[] = {
      "global",
      "goldenrod",
    };
  };
  namespace global {
    const short num = 1;
    const char* const name[] = {
      "nothing"
    };
  };
  namespace goldenrod {
    const short num = 21;
    const char* const name[] = {
      "Large Tree A", "Large Tree B", "Large Tree C", "Large Tree D",
      "Large Shrub A", "Large Shrub B", "Large Shrub C",
      "Medium Tree A", "Medium Tree B", "Medium Tree C", "Medium Tree D",
      "Medium Shrub A", "Medium Shrub B", "Medium Shrub C",
      "Small Tree A", "Small Tree B", "Small Tree C", "Small Tree D",
      "Small Shrub A", "Small Shrub B", "Small Shrub C",
    };
  };
};

namespace path {
  const char* const dir = "../res/scn/";
  const char* const imgtype = ".png";
};

CSceneryData::CSceneryData() {
  //
}

short CSceneryData::getNumGroups() {
  return Decorations::groups::num;
}

short CSceneryData::getNumDecor(const int& group) {
  using namespace Decorations::groups;

  short N = 0;
  switch (group) {
    case GLOBAL: N = Decorations::global::num; break;
    case GOLDENROD: N = Decorations::goldenrod::num; break;
  }
  return N;
}

SDL_Texture* CSceneryData::loadSrcTexture(const int& group) {
  using namespace Decorations::groups;

  SDL_Texture* scenery_tex = NULL;
  std::string filename;

  if (group >= 0 && group < num) {
    filename = name[group];
  }

  if (!filename.empty()) {
    using namespace path;
    std::string filepath = dir + filename + imgtype;
    scenery_tex = CSurface::OnLoad(filepath.c_str());
  }
  return scenery_tex;
}

SDL_Rect CSceneryData::getDecorDims(const int& group, const int& decor) {
  using namespace Decorations::groups;

  SDL_Rect srcRect = {0,0,0,0};
  if (!(group < 0 || group >= num || decor < 0)) {
    switch (group) {
      case GLOBAL:    getDims_global(decor, srcRect);     break;
      case GOLDENROD: getDims_goldenrod(decor, srcRect);  break;
      default:        break;
    }
  }
  return srcRect;
}

std::string CSceneryData::getGroupName(const int& group) {
  if (group < 0 || group >= Decorations::groups::num) return "";
  return Decorations::groups::name[group];
}

std::string CSceneryData::getDecorName(const int& group, const int& decor) {
  using namespace Decorations::groups;

  std::string retval = "";
  if (!(group < 0 || group >= num || decor < 0)) {
    switch (group) {
      case GLOBAL:    getName_global(decor, retval);    break;
      case GOLDENROD: getName_goldenrod(decor, retval); break;
      default:        break;
    }
  }
  return retval;
}

void CSceneryData::getDims_global(const int& decor, SDL_Rect& srcRect) {
  using namespace Decorations::global;
  switch (decor) {
    case NOTHING: srcRect = CAsset::getRect(0, 0, 64, 64); break;
    default:  break;
  }
}

void CSceneryData::getDims_goldenrod(const int& decor, SDL_Rect& srcRect) {
  using namespace Decorations::goldenrod;
  switch (decor) {
    case L_TREE_A: srcRect = CAsset::getRect(0, 0, 422, 356); break;
    case L_TREE_B: srcRect = CAsset::getRect(422, 0, 407, 356); break;
    case L_TREE_C: srcRect = CAsset::getRect(829, 0, 400, 356); break;
    case L_TREE_D: srcRect = CAsset::getRect(1229, 0, 387, 356); break;
    case L_SHRUB_A: srcRect = CAsset::getRect(0, 356, 363, 89); break;
    case L_SHRUB_B: srcRect = CAsset::getRect(363, 356, 388, 89); break;
    case L_SHRUB_C: srcRect = CAsset::getRect(751, 356, 383, 89); break;
    case M_TREE_A: srcRect = CAsset::getRect(0, 445, 332, 296); break;
    case M_TREE_B: srcRect = CAsset::getRect(332, 445, 316, 273); break;
    case M_TREE_C: srcRect = CAsset::getRect(648, 445, 296, 282); break;
    case M_TREE_D: srcRect = CAsset::getRect(944, 445, 326, 282); break;
    case M_SHRUB_A: srcRect = CAsset::getRect(332, 727, 322, 55); break;
    case M_SHRUB_B: srcRect = CAsset::getRect(654, 727, 319, 55); break;
    case M_SHRUB_C: srcRect = CAsset::getRect(973, 727, 336, 55); break;
    case S_TREE_A: srcRect = CAsset::getRect(1309, 356, 224, 182); break;
    case S_TREE_B: srcRect = CAsset::getRect(1533, 356, 199, 182); break;
    case S_TREE_C: srcRect = CAsset::getRect(1309, 538, 216, 192); break;
    case S_TREE_D: srcRect = CAsset::getRect(1525, 538, 244, 196); break;
    case S_SHRUB_A: srcRect = CAsset::getRect(1309, 741, 242, 41); break;
    case S_SHRUB_B: srcRect = CAsset::getRect(1554, 741, 251, 41); break;
    case S_SHRUB_C: srcRect = CAsset::getRect(0, 741, 286, 41); break;
    default:  break;
  }
}

void CSceneryData::getName_global(const int& decor, std::string& str) {
  if (decor < Decorations::global::num) {
    str = Decorations::global::name[decor];
  }
}

void CSceneryData::getName_goldenrod(const int& decor, std::string& str) {
  if (decor < Decorations::goldenrod::num) {
    str = Decorations::goldenrod::name[decor];
  }
}
