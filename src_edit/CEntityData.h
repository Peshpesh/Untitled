#ifndef _C_ENTITYDATA_H_
#define _C_ENTITYDATA_H_

#include <string>
#include <vector>
#include <stdio.h>
#include "CAsset.h"
#include "CSurface.h"
#include "CInform.h"

namespace Entities {
  namespace groups {
    enum {
      GLOBAL      = 0,
      CAVES       = 1,
      PV_GLOBAL   = 2,
    };
    extern const short num;
    extern const char* const name[];
  }; // namespace groups

  namespace global {
    enum {
      PLAYER      = 0,
      HEART       = 1,
      AMYTHYST    = 2,
      EVILPLAYER  = 3,
      BOMB        = 4,
      BLAST       = 5,
    };
    extern const short num;
    extern const char* const name[];
    // namespace src {
    //   extern const SDL_Rect r[];
    // };
  };  // namespace global

  namespace caves {
    enum {
      BARS        = 0,
      BOX         = 1,
      SPIKEFALL   = 2,
      BLDSPK_UP   = 3,
      ACIDBALL    = 4,
      DOOR        = 5,
      SVPT        = 6,
      SIGN        = 7,
    };
    extern const short num;
    extern const char* const name[];
    // namespace src {
    //   extern const SDL_Rect r[];
    // };
  }; // namespace caves
  namespace pv_global {
    enum {
      PLAYER      = 0,
    };
    extern const short num;
    extern const char* const name[];
  };  // namespace pv_global
}; // namespace Entities


struct HitboxData {
  short group;
  short entity;
  SDL_Rect hitR;
};

class CEntityData {
  CEntityData();
  static std::vector<HitboxData> hitboxList;

public:
  static bool init();
  static bool load_phb(const int& group); // load primary hitboxes
  static void save_phb(const int& group); // save primary hitboxes
  static void updateHitbox(const int& group, const int& entity, const SDL_Rect& newR);

public:
  static short getNumGroups();
  static short getNumEntities(const int& group);

public:
  static SDL_Texture* loadSrcTexture(const int& group);
  static SDL_Rect getEntityDims(const int& group, const int& entity);
  static SDL_Rect getHitboxDims(const int& group, const int& entity);
  static std::string getGroupName(const int& group);
  static std::string getEntityName(const int& group, const int& entity);

private:
  static void getDims_global(const int& entity, SDL_Rect& srcRect);
  static void getDims_caves(const int& entity, SDL_Rect& srcRect);
  static void getDims_pv_global(const int& entity, SDL_Rect& srcRect);

private:
  static void getName_global(const int& entity, std::string& str);
  static void getName_caves(const int& entity, std::string& str);
  static void getName_pv_global(const int& entity, std::string& str);
};

#endif
