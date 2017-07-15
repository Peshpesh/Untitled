#ifndef _C_ENTITYDATA_H_
#define _C_ENTITYDATA_H_

#include <string>
#include "CAsset.h"
#include "CSurface.h"

namespace Entities {
  namespace groups {
    enum {
      GLOBAL      = 0,
      CAVES       = 1,
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
}; // namespace Entity_ID

class CEntityData {

  CEntityData();

public:
  static short getNumGroups();
  static short getNumEntities(const int& group);

public:
  static SDL_Texture* loadSrcTexture(const int& group);
  static SDL_Rect getEntityDims(const int& group, const int& entity);
  static std::string getEntityName(const int& group, const int& entity);

private:
  static void getDims_global(const int& entity, SDL_Rect& srcRect);
  static void getDims_caves(const int& entity, SDL_Rect& srcRect);

private:
  static void getName_global(const int& entity, std::string& str);
  static void getName_caves(const int& entity, std::string& str);
};

#endif
