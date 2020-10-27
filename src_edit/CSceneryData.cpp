#include "CSceneryData.h"

namespace Decorations {
  namespace groups {
    const short num = 3;
    const char* const name[] = {
      "global",
      "goldenrod",
      "newyrai",
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
  namespace newyrai {
    const short num = 86;
    const char* const name[] = {
      "HEDGE", "HDG S EDGE A", "HDG S EDGE B", "HDG N EDGE A", "HDG N EDGE B",  // 0-4
      "HDG W EDGE A", "HDG W EDGE B", "HDG E EDGE A", "HDG E EDGE B",           // 5-8
      "HDG NE CORN", "HDG NW CORN", "HDG SW CORN", "HDG SE CORN",               // 9-12
      "HDG NE EDGE", "HDG NW EDGE", "HDG SW EDGE", "HDG SE EDGE",               // 13-16
      "SIGN FRONT", "SIGN BACK", "ROOT LAMP", "BENCH Y", "BENCH X",             // 17-21
      "LO FENCE Y", "LO FENCE X A", "LO FENCE X B",                             // 22-24
      "LO FENCE NW", "LO FENCE NE", "LO FENCE SW", "LO FENCE SE",               // 25-28
      "LO FNC END N", "LO FNC END S",                                           // 29-30
      "LO FNC END W A", "LO FNC END W B", "LO FNC END E A", "LO FNC END E B",   // 31-34
      "WOOD FENCE W", "WOOD FENCE E", "WOOD FENCE N", "WOOD FENCE S",           // 35-38
      "WOOD FENCE NW", "WOOD FENCE NE", "WOOD FENCE SW", "WOOD FENCE SE",       // 39-42
      "WD FNC END W", "WD FNC DOOR N", "WD FNC DOOR S",                         // 43-45
      "HEDGETREE A", "HEDGETREE B", "HEDGETREE C", "ROOTED TREE",               // 46-49
      "BUSH", "BRIDGE", "BRIDG FRNT", "STUMP",                                  // 50-53
      "BLDBLOSSM A", "BLDBLOSSM B", "BLDBLOSSM C",                              // 54-56
      "MAGNOLIA A", "MAGNOLIA B", "MAGNOLIA C",                                 // 57-59
      "EMBERFLR A", "EMBERFLR B", "EMBERFLR C",                                 // 60-62
      "SOLARIS A", "SOLARIS B", "SOLARIS C",                                    // 63-65
      "AMIRORA A", "AMIRORA B", "AMIRORA C",                                    // 66-68
      "SPRGHERALD A", "SPRGHERALD B", "SPRGHERALD C",                           // 69-71
      "BLUE HOUSE", "SILV HOUSE", "GREEN HOUSE", "RED HOUSE",                   // 72-75
      "GOLD HOUSE W", "GOLD HOUSE E",                                           // 76-77
      "SHOP", "SHOP AWNING", "SCHOOL", "INN", "BLU PCKET S", "BLU PCKET N",     // 78-83
      "HOSPTAL SHOE", "HOSPTAL ENTY",                                           // 84-85
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
    case NEWYRAI: N = Decorations::newyrai::num; break;
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

  if (scenery_tex == NULL) {
    CInform::InfoControl.pushInform("---CSceneryData---\ncould not load texture");
  }

  return scenery_tex;
}

SDL_Texture* CSceneryData::loadSrcShadows(const int& group) {
  using namespace Decorations::groups;

  SDL_Texture* shadow_tex = NULL;
  std::string filename;

  if (group >= 0 && group < num) {
    filename = name[group];
  }

  if (!filename.empty()) {
    using namespace path;
    std::string filepath = dir + filename + "_shade" + imgtype;
    shadow_tex = CSurface::OnLoad(filepath.c_str());
  }

  if (shadow_tex == NULL) {
    CInform::InfoControl.pushInform("---CSceneryData---\ncould not load shadows");
  }

  return shadow_tex;
}

SDL_Rect CSceneryData::getDecorDims(const int& group, const int& decor) {
  using namespace Decorations::groups;

  SDL_Rect srcRect = {0,0,0,0};
  if (!(group < 0 || group >= num || decor < 0)) {
    switch (group) {
      case GLOBAL:    getDims_global(decor, srcRect);     break;
      case GOLDENROD: getDims_goldenrod(decor, srcRect);  break;
      case NEWYRAI:   getDims_newyrai(decor, srcRect);  break;
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
      case NEWYRAI:   getName_newyrai(decor, retval);   break;
      default:        break;
    }
  }
  return retval;
}

int CSceneryData::getYBase(const int& group, const int& decor, const int& Y, const int& W) {
  using namespace Decorations::groups;

  int retval = Y + W;
  if (!(group < 0 || group >= num || decor < 0)) {
    switch (group) {
      case NEWYRAI:   getYBase_newyrai(decor, retval); break;
      default:        break;
    }
  }
  return retval;
}

bool CSceneryData::hasShadow(const int& group, const int& decor) {
  using namespace Decorations::groups;
  bool has_shadow = false;
  if (!(group < 0 || group >= num || decor < 0)) {
    switch (group) {
      case NEWYRAI:   has_shadow = hasShadow_newyrai(decor); break;
      default:        break;
    }
  }
  return has_shadow;
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

void CSceneryData::getDims_newyrai(const int& decor, SDL_Rect& srcRect) {
  using namespace Decorations::newyrai;

  switch (decor) {
    case HEDGE:             srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case HEDGE_S_EDGE_A:    srcRect = CAsset::getRect(32, 0, 32, 32); break;
    case HEDGE_S_EDGE_B:    srcRect = CAsset::getRect(64, 0, 32, 32); break;
    case HEDGE_N_EDGE_A:    srcRect = CAsset::getRect(96, 0, 32, 32); break;
    case HEDGE_N_EDGE_B:    srcRect = CAsset::getRect(128, 0, 32, 32); break;
    case HEDGE_W_EDGE_A:    srcRect = CAsset::getRect(160, 0, 32, 32); break;
    case HEDGE_W_EDGE_B:    srcRect = CAsset::getRect(192, 0, 32, 32); break;
    case HEDGE_E_EDGE_A:    srcRect = CAsset::getRect(224, 0, 32, 32); break;
    case HEDGE_E_EDGE_B:    srcRect = CAsset::getRect(256, 0, 32, 32); break;
    case HEDGE_NE_CORNER:   srcRect = CAsset::getRect(32, 32, 32, 32); break;
    case HEDGE_NW_CORNER:   srcRect = CAsset::getRect(64, 32, 32, 32); break;
    case HEDGE_SW_CORNER:   srcRect = CAsset::getRect(96, 32, 32, 32); break;
    case HEDGE_SE_CORNER:   srcRect = CAsset::getRect(128, 32, 32, 32); break;
    case HEDGE_NE_EDGE:     srcRect = CAsset::getRect(160, 32, 32, 32); break;
    case HEDGE_NW_EDGE:     srcRect = CAsset::getRect(192, 32, 32, 32); break;
    case HEDGE_SW_EDGE:     srcRect = CAsset::getRect(224, 32, 32, 32); break;
    case HEDGE_SE_EDGE:     srcRect = CAsset::getRect(256, 32, 32, 32); break;
    case SIGN_FRONT:        srcRect = CAsset::getRect(288, 3, 50, 29); break;
    case SIGN_BACK:         srcRect = CAsset::getRect(288, 35, 50, 29); break;
    case ROOT_LAMP:         srcRect = CAsset::getRect(338, 2, 55, 62); break;
    case BENCH_Y:           srcRect = CAsset::getRect(341, 67, 24, 61); break;
    case BENCH_X:           srcRect = CAsset::getRect(365, 104, 64, 26); break;
    case LO_FENCE_Y:        srcRect = CAsset::getRect(0, 64, 11, 39); break;
    case LO_FENCE_X_A:      srcRect = CAsset::getRect(23, 77, 32, 14); break;
    case LO_FENCE_X_B:      srcRect = CAsset::getRect(23, 90, 32, 14); break;
    case LO_FENCE_NW:       srcRect = CAsset::getRect(55, 65, 31, 38); break;
    case LO_FENCE_NE:       srcRect = CAsset::getRect(86, 65, 37, 38); break;
    case LO_FENCE_SW:       srcRect = CAsset::getRect(123, 64, 31, 38); break;
    case LO_FENCE_SE:       srcRect = CAsset::getRect(154, 64, 37, 38); break;
    case LO_FENCE_END_N:    srcRect = CAsset::getRect(191, 77, 11, 26); break;
    case LO_FENCE_END_S:    srcRect = CAsset::getRect(202, 77, 11, 26); break;
    case LO_FENCE_END_W_A:  srcRect = CAsset::getRect(235, 77, 19, 13); break;
    case LO_FENCE_END_W_B:  srcRect = CAsset::getRect(235, 90, 19, 13); break;
    case LO_FENCE_END_E_A:  srcRect = CAsset::getRect(254, 77, 24, 13); break;
    case LO_FENCE_END_E_B:  srcRect = CAsset::getRect(254, 90, 24, 13); break;
    case WOOD_FENCE_W:      srcRect = CAsset::getRect(0, 103, 31, 65); break;
    case WOOD_FENCE_E:      srcRect = CAsset::getRect(31, 103, 33, 65); break;
    case WOOD_FENCE_N:      srcRect = CAsset::getRect(64, 130, 32, 38); break;
    case WOOD_FENCE_S:      srcRect = CAsset::getRect(96, 130, 32, 38); break;
    case WOOD_FENCE_NW:     srcRect = CAsset::getRect(128, 102, 32, 66); break;
    case WOOD_FENCE_NE:     srcRect = CAsset::getRect(160, 102, 59, 66); break;
    case WOOD_FENCE_SW:     srcRect = CAsset::getRect(219, 103, 32, 65); break;
    case WOOD_FENCE_SE:     srcRect = CAsset::getRect(251, 103, 59, 65); break;
    case WOOD_FENCE_END_W:  srcRect = CAsset::getRect(310, 103, 31, 65); break;
    case WOOD_FENCE_DOOR_N: srcRect = CAsset::getRect(341, 130, 32, 38); break;
    case WOOD_FENCE_DOOR_S: srcRect = CAsset::getRect(373, 130, 32, 38); break;
    case HEDGETREE_A:       srcRect = CAsset::getRect(0, 168, 277, 216); break;
    case HEDGETREE_B:       srcRect = CAsset::getRect(0, 384, 264, 208); break;
    case HEDGETREE_C:       srcRect = CAsset::getRect(0, 592, 256, 207); break;
    case ROOTED_TREE:       srcRect = CAsset::getRect(0, 800, 283, 273); break;
    case BUSH:              srcRect = CAsset::getRect(277, 168, 72, 58); break;
    case BRIDGE:            srcRect = CAsset::getRect(277, 226, 146, 94); break;
    case BRIDGE_FRONT:      srcRect = CAsset::getRect(277, 445, 128, 35); break;
    case STUMP:             srcRect = CAsset::getRect(277, 320, 122, 67); break;
    case BLOODBLOSSOM_A:    srcRect = CAsset::getRect(277, 387, 13, 14); break;
    case BLOODBLOSSOM_B:    srcRect = CAsset::getRect(290, 387, 14, 14); break;
    case BLOODBLOSSOM_C:    srcRect = CAsset::getRect(304, 387, 13, 14); break;
    case MAGNOLIA_A:        srcRect = CAsset::getRect(277, 401, 13, 14); break;
    case MAGNOLIA_B:        srcRect = CAsset::getRect(290, 401, 14, 14); break;
    case MAGNOLIA_C:        srcRect = CAsset::getRect(304, 401, 13, 14); break;
    case EMBERFLOWER_A:     srcRect = CAsset::getRect(277, 415, 13, 14); break;
    case EMBERFLOWER_B:     srcRect = CAsset::getRect(290, 415, 14, 14); break;
    case EMBERFLOWER_C:     srcRect = CAsset::getRect(304, 415, 13, 14); break;
    case SOLARIS_A:         srcRect = CAsset::getRect(277, 429, 12, 15); break;
    case SOLARIS_B:         srcRect = CAsset::getRect(289, 429, 14, 15); break;
    case SOLARIS_C:         srcRect = CAsset::getRect(303, 429, 13, 15); break;
    case AMIRORA_A:         srcRect = CAsset::getRect(317, 415, 13, 14); break;
    case AMIRORA_B:         srcRect = CAsset::getRect(330, 414, 14, 15); break;
    case AMIRORA_C:         srcRect = CAsset::getRect(344, 414, 13, 15); break;
    case SPRINGSHERALD_A:   srcRect = CAsset::getRect(317, 429, 13, 15); break;
    case SPRINGSHERALD_B:   srcRect = CAsset::getRect(330, 429, 14, 15); break;
    case SPRINGSHERALD_C:   srcRect = CAsset::getRect(344, 430, 13, 14); break;
    case BLUE_HOUSE:        srcRect = CAsset::getRect(448, 0, 224, 320); break;
    case SILVER_HOUSE:      srcRect = CAsset::getRect(672, 0, 256, 320); break;
    case GREEN_HOUSE:       srcRect = CAsset::getRect(928, 0, 352, 224); break;
    case RED_HOUSE:         srcRect = CAsset::getRect(928, 224, 320, 224); break;
    case GOLD_HOUSE_W:      srcRect = CAsset::getRect(448, 352, 120, 224); break;
    case GOLD_HOUSE_E:      srcRect = CAsset::getRect(568, 320, 200, 352); break;
    case SHOP:              srcRect = CAsset::getRect(768, 448, 416, 288); break;
    case SHOP_AWNING:       srcRect = CAsset::getRect(448, 672, 224, 128); break;
    case SCHOOL:            srcRect = CAsset::getRect(448, 800, 736, 480); break;
    case INN:               srcRect = CAsset::getRect(448, 1280, 608, 416); break;
    case BLU_PCKET_S:       srcRect = CAsset::getRect(1056, 1344, 320, 352); break;
    case BLU_PCKET_N:       srcRect = CAsset::getRect(1056, 1312, 320, 32); break;
    case HOSPITAL_SHOE:     srcRect = CAsset::getRect(448, 1696, 800, 704); break;
    case HOSPITAL_ENTRY:    srcRect = CAsset::getRect(0, 1696, 256, 432); break;
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

void CSceneryData::getName_newyrai(const int& decor, std::string& str) {
  if (decor < Decorations::newyrai::num) {
    str = Decorations::newyrai::name[decor];
  }
}

void CSceneryData::getYBase_newyrai(const int& decor, int& Y_base) {
  using namespace Decorations::newyrai;

  int offset = 0; // value to add to the default Y_base (= Y + H)
                  // to yield the actual Y_base

  switch (decor) {
    case HEDGE:             break;
    case HEDGE_S_EDGE_A:    break;
    case HEDGE_S_EDGE_B:    break;
    case HEDGE_N_EDGE_A:    break;
    case HEDGE_N_EDGE_B:    break;
    case HEDGE_W_EDGE_A:    break;
    case HEDGE_W_EDGE_B:    break;
    case HEDGE_E_EDGE_A:    break;
    case HEDGE_E_EDGE_B:    break;
    case HEDGE_NE_CORNER:   break;
    case HEDGE_NW_CORNER:   break;
    case HEDGE_SW_CORNER:   break;
    case HEDGE_SE_CORNER:   break;
    case HEDGE_NE_EDGE:     break;
    case HEDGE_NW_EDGE:     break;
    case HEDGE_SW_EDGE:     break;
    case HEDGE_SE_EDGE:     break;
    case SIGN_FRONT:        break;
    case SIGN_BACK:         break;
    case ROOT_LAMP:         offset = -7;  break;
    case BENCH_Y:           break;
    case BENCH_X:           break;
    case LO_FENCE_Y:        break;
    case LO_FENCE_X_A:      break;
    case LO_FENCE_X_B:      break;
    case LO_FENCE_NW:       offset = -25; break;
    case LO_FENCE_NE:       offset = -25; break;
    case LO_FENCE_SW:       break;
    case LO_FENCE_SE:       break;
    case LO_FENCE_END_N:    break;
    case LO_FENCE_END_S:    break;
    case LO_FENCE_END_W_A:  break;
    case LO_FENCE_END_W_B:  break;
    case LO_FENCE_END_E_A:  break;
    case LO_FENCE_END_E_B:  break;
    case WOOD_FENCE_W:      break;
    case WOOD_FENCE_E:      break;
    case WOOD_FENCE_N:      break;
    case WOOD_FENCE_S:      break;
    case WOOD_FENCE_NW:     offset = -28; break;
    case WOOD_FENCE_NE:     offset = -28; break;
    case WOOD_FENCE_SW:     break;
    case WOOD_FENCE_SE:     break;
    case WOOD_FENCE_END_W:  break;
    case WOOD_FENCE_DOOR_N: break;
    case WOOD_FENCE_DOOR_S: break;
    case HEDGETREE_A:       offset = -16; break;
    case HEDGETREE_B:       offset = -12; break;
    case HEDGETREE_C:       offset = -9;  break;
    case ROOTED_TREE:       offset = -50; break;
    case BUSH:              offset = -15; break;
    case BRIDGE:            offset = -66; break;
    case BRIDGE_FRONT:      break;
    case STUMP:             offset = -36; break;
    case BLOODBLOSSOM_A:    break;
    case BLOODBLOSSOM_B:    break;
    case BLOODBLOSSOM_C:    break;
    case MAGNOLIA_A:        break;
    case MAGNOLIA_B:        break;
    case MAGNOLIA_C:        break;
    case EMBERFLOWER_A:     break;
    case EMBERFLOWER_B:     break;
    case EMBERFLOWER_C:     break;
    case SOLARIS_A:         break;
    case SOLARIS_B:         break;
    case SOLARIS_C:         break;
    case AMIRORA_A:         break;
    case AMIRORA_B:         break;
    case AMIRORA_C:         break;
    case SPRINGSHERALD_A:   break;
    case SPRINGSHERALD_B:   break;
    case SPRINGSHERALD_C:   break;
    case BLUE_HOUSE:        offset = -32; break;
    case SILVER_HOUSE:      break;
    case GREEN_HOUSE:       break;
    case RED_HOUSE:         break;
    case GOLD_HOUSE_W:      break;
    case GOLD_HOUSE_E:      break;
    case SHOP:              offset = -34; break;
    case SHOP_AWNING:       break;
    case SCHOOL:            offset = -64; break;
    case INN:               break;
    case BLU_PCKET_S:       break;
    case BLU_PCKET_N:       break;
    case HOSPITAL_SHOE:     offset = -32; break;
    case HOSPITAL_ENTRY:    offset = -48; break;
    default:  break;
  }
  Y_base += offset;
}

bool CSceneryData::hasShadow_newyrai(const int& decor) {
  using namespace Decorations::newyrai;

  bool has_shadow = false;

  switch (decor) {
    case HEDGE:             break;
    case HEDGE_S_EDGE_A:    break;
    case HEDGE_S_EDGE_B:    break;
    case HEDGE_N_EDGE_A:    break;
    case HEDGE_N_EDGE_B:    break;
    case HEDGE_W_EDGE_A:    break;
    case HEDGE_W_EDGE_B:    break;
    case HEDGE_E_EDGE_A:    break;
    case HEDGE_E_EDGE_B:    break;
    case HEDGE_NE_CORNER:   break;
    case HEDGE_NW_CORNER:   break;
    case HEDGE_SW_CORNER:   break;
    case HEDGE_SE_CORNER:   break;
    case HEDGE_NE_EDGE:     break;
    case HEDGE_NW_EDGE:     break;
    case HEDGE_SW_EDGE:     break;
    case HEDGE_SE_EDGE:     break;
    case SIGN_FRONT:        has_shadow = true; break;
    case SIGN_BACK:         has_shadow = true; break;
    case ROOT_LAMP:         has_shadow = true; break;
    case BENCH_Y:           has_shadow = true; break;
    case BENCH_X:           has_shadow = true; break;
    case LO_FENCE_Y:        has_shadow = true; break;
    case LO_FENCE_X_A:      has_shadow = true; break;
    case LO_FENCE_X_B:      has_shadow = true; break;
    case LO_FENCE_NW:       has_shadow = true; break;
    case LO_FENCE_NE:       has_shadow = true; break;
    case LO_FENCE_SW:       has_shadow = true; break;
    case LO_FENCE_SE:       has_shadow = true; break;
    case LO_FENCE_END_N:    has_shadow = true; break;
    case LO_FENCE_END_S:    has_shadow = true; break;
    case LO_FENCE_END_W_A:  has_shadow = true; break;
    case LO_FENCE_END_W_B:  has_shadow = true; break;
    case LO_FENCE_END_E_A:  has_shadow = true; break;
    case LO_FENCE_END_E_B:  has_shadow = true; break;
    case WOOD_FENCE_W:      has_shadow = true; break;
    case WOOD_FENCE_E:      has_shadow = true; break;
    case WOOD_FENCE_N:      break;
    case WOOD_FENCE_S:      break;
    case WOOD_FENCE_NW:     has_shadow = true; break;
    case WOOD_FENCE_NE:     has_shadow = true; break;
    case WOOD_FENCE_SW:     break;
    case WOOD_FENCE_SE:     has_shadow = true; break;
    case WOOD_FENCE_END_W:  has_shadow = true; break;
    case WOOD_FENCE_DOOR_N: break;
    case WOOD_FENCE_DOOR_S: break;
    case HEDGETREE_A:       has_shadow = true; break;
    case HEDGETREE_B:       has_shadow = true; break;
    case HEDGETREE_C:       has_shadow = true; break;
    case ROOTED_TREE:       has_shadow = true; break;
    case BUSH:              has_shadow = true; break;
    case BRIDGE:            has_shadow = true; break;
    case BRIDGE_FRONT:      break;
    case STUMP:             has_shadow = true; break;
    case BLOODBLOSSOM_A:    break;
    case BLOODBLOSSOM_B:    break;
    case BLOODBLOSSOM_C:    break;
    case MAGNOLIA_A:        break;
    case MAGNOLIA_B:        break;
    case MAGNOLIA_C:        break;
    case EMBERFLOWER_A:     break;
    case EMBERFLOWER_B:     break;
    case EMBERFLOWER_C:     break;
    case SOLARIS_A:         break;
    case SOLARIS_B:         break;
    case SOLARIS_C:         break;
    case AMIRORA_A:         break;
    case AMIRORA_B:         break;
    case AMIRORA_C:         break;
    case SPRINGSHERALD_A:   break;
    case SPRINGSHERALD_B:   break;
    case SPRINGSHERALD_C:   break;
    case BLUE_HOUSE:        has_shadow = true; break;
    case SILVER_HOUSE:      has_shadow = true; break;
    case GREEN_HOUSE:       has_shadow = true; break;
    case RED_HOUSE:         has_shadow = true; break;
    case GOLD_HOUSE_W:      break;
    case GOLD_HOUSE_E:      has_shadow = true; break;
    case SHOP:              has_shadow = true; break;
    case SHOP_AWNING:       break;
    case SCHOOL:            has_shadow = true; break;
    case INN:               has_shadow = true; break;
    case BLU_PCKET_S:       has_shadow = true; break;
    case BLU_PCKET_N:       has_shadow = true; break;
    case HOSPITAL_SHOE:     has_shadow = true; break;
    case HOSPITAL_ENTRY:    break;
    default:  break;
  }
  return has_shadow;
}
