#include "CSceneryData.h"

namespace Decorations {
  namespace groups {
    const short num = 1;
    const char* const name[] = {
      "global"
    };
  };
  namespace global {
    const short num = 1;
    const char* const name[] = {
      "nothing"
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
      case GLOBAL:  getDims_global(decor, srcRect);   break;
      default:      break;
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
      case GLOBAL:  getName_global(decor, retval); break;
      default:      break;
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

void CSceneryData::getName_global(const int& decor, std::string& str) {
  if (decor < Decorations::global::num) {
    str = Decorations::global::name[decor];
  }
}
