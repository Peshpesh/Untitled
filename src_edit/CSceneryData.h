#ifndef _C_SCENERYDATA_H_
#define _C_SCENERYDATA_H_

#include <string>
#include <vector>
#include <stdio.h>
#include "CAsset.h"
#include "CSurface.h"
#include "CInform.h"

namespace Decorations {
  namespace groups {
    extern const short num;
    extern const char* const name[];
    enum {
      GLOBAL = 0,
      GOLDENROD = 1,
      NEWYRAI = 2,
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
  namespace newyrai {
    extern const short num;
    extern const char* const name[];
    enum {
      HEDGE = 0, HEDGE_S_EDGE_A, HEDGE_S_EDGE_B, HEDGE_N_EDGE_A, HEDGE_N_EDGE_B, // 0-4
      HEDGE_W_EDGE_A, HEDGE_W_EDGE_B, HEDGE_E_EDGE_A, HEDGE_E_EDGE_B,            // 5-8
      HEDGE_NE_CORNER, HEDGE_NW_CORNER, HEDGE_SW_CORNER, HEDGE_SE_CORNER,        // 9-12
      HEDGE_NE_EDGE, HEDGE_NW_EDGE, HEDGE_SW_EDGE, HEDGE_SE_EDGE,                // 13-16
      SIGN_FRONT, SIGN_BACK, ROOT_LAMP, BENCH_Y, BENCH_X,                        // 17-21
      LO_FENCE_Y, LO_FENCE_X_A, LO_FENCE_X_B,                                    // 22-24
      LO_FENCE_NW, LO_FENCE_NE, LO_FENCE_SW, LO_FENCE_SE,                        // 25-28
      LO_FENCE_END_N, LO_FENCE_END_S,                                            // 29-30
      LO_FENCE_END_W_A, LO_FENCE_END_W_B, LO_FENCE_END_E_A, LO_FENCE_END_E_B,    // 31-34
      WOOD_FENCE_W, WOOD_FENCE_E, WOOD_FENCE_N, WOOD_FENCE_S,                    // 35-38
      WOOD_FENCE_NW, WOOD_FENCE_NE, WOOD_FENCE_SW, WOOD_FENCE_SE,                // 39-42
      WOOD_FENCE_END_W, WOOD_FENCE_DOOR_N, WOOD_FENCE_DOOR_S,                    // 43-45
      HEDGETREE_A, HEDGETREE_B, HEDGETREE_C, ROOTED_TREE, BUSH, BRIDGE,          // 46-51
      BRIDGE_FRONT, STUMP,                                                       // 52-53
      BLOODBLOSSOM_A, BLOODBLOSSOM_B, BLOODBLOSSOM_C,                            // 54-56
      MAGNOLIA_A, MAGNOLIA_B, MAGNOLIA_C,                                        // 57-59
      EMBERFLOWER_A, EMBERFLOWER_B, EMBERFLOWER_C,                               // 60-62
      SOLARIS_A, SOLARIS_B, SOLARIS_C,                                           // 63-65
      AMIRORA_A, AMIRORA_B, AMIRORA_C,                                           // 66-68
      SPRINGSHERALD_A, SPRINGSHERALD_B, SPRINGSHERALD_C,                         // 69-71
      // -----BUILDINGS/STRUCTURES---------------------------------------------- // N = 72
      BLUE_HOUSE, SILVER_HOUSE, GREEN_HOUSE, RED_HOUSE,                          // 72-75
      GOLD_HOUSE_W, GOLD_HOUSE_E,                                                // 76-77
      SHOP, SHOP_AWNING, SCHOOL, INN, BLU_PCKET_S, BLU_PCKET_N,                  // 78-83
      HOSPITAL_SHOE, HOSPITAL_ENTRY,                                             // 84-85
      // -----LATE ADDITIONS/MISC----------------------------------------------- // N = 86
      HEDGE_NW_CURVE, HEDGE_NE_CURVE, HEDGE_SW_CURVE, HEDGE_SE_CURVE,            // 86-89
      // ----------------------------------------------------------------------- // N = 90
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
  static SDL_Texture* loadSrcShadows(const int& group); // only for PV maps

public:
  static SDL_Rect getDecorDims(const int& group, const int& decor);
  static std::string getGroupName(const int& group);
  static std::string getDecorName(const int& group, const int& decor);
  static int getYBase(const int& group, const int& decor, const int& Y, const int& H); // only for PV maps
  static bool hasShadow(const int& group, const int& decor); // only for PV maps

private:
  static void getDims_global(const int& decor, SDL_Rect& srcRect);
  static void getDims_goldenrod(const int& decor, SDL_Rect& srcRect);
  static void getDims_newyrai(const int& decor, SDL_Rect& srcRect);

  static void getName_global(const int& decor, std::string& str);
  static void getName_goldenrod(const int& decor, std::string& str);
  static void getName_newyrai(const int& decor, std::string& str);

  static void getYBase_newyrai(const int& decor, int& Y_base);

  static bool hasShadow_newyrai(const int& decor);
};

#endif
