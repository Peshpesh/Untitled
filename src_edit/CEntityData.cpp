#include "CEntityData.h"

// The CEntityData class should describe all essential
// information that identifies a given Entity, such as...
//
// - Source image (entity group)
// - X, Y position on source
// - W, H dimensions of a sprite's rendered frame
// - X, Y position on Area
// - X, Y position of hitbox relative to rendered frame
// - W, H dimensions of the hitbox

namespace Entities {
  namespace groups {
    const char* const name[] = {
      "Global",
      "Caves"
    };
  };  // namespace groups
  namespace global {
    const char* const name[] = {
      "Player",
      "Heart",
      "Amythyst",
      "Evil Player",
      "Live Bomb",
      "Blast"
    };
    // namespace src {
    //   const SDL_Rect r[] = {
    //     {,,,},
    //     {,,,},
    //     {,,,},
    //     {,,,},
    //     {,,,},
    //     {,,,}
    //   };
    // };
  };  // namespace global
  namespace caves {
    const char* const name[] = {
      "Metal Bars",
      "Wooden Box",
      "Loose Stalagmites",
      "Bloody Spikes",
      "Ball of Acid",
      "Wooden Door",
      "Save Point",
      "Wooden Sign"
    };
  }; // namespace caves
}; // namespace Entity_ID

CEntityData::CEntityData() {
  //
}

SDL_Texture* CEntityData::loadSrcTexture(const int& group) {
  using namespace Entities::groups;

  SDL_Texture* entity_tex = NULL;
  std::string filename;

  switch (group) {
    case GLOBAL:  filename = "global";  break;
    case CAVES:   filename = "caves";   break;
    default:      break;
  }

  if (!filename.empty()) {
    std::string path = "../res/npc/" + filename + ".png";
    entity_tex = CSurface::OnLoad(path.c_str());
  }

  return entity_tex;
}

SDL_Rect CEntityData::getEntityDims(const int& group, const int& entity) {
  using namespace Entities::groups;

  SDL_Rect srcRect = {0,0,0,0};

  switch (group) {
    case GLOBAL:  getDims_global(entity, srcRect);   break;
    case CAVES:   getDims_caves(entity, srcRect);    break;
    default:      break;
  }

  return srcRect;
}

void CEntityData::getDims_global(const int& entity, SDL_Rect& srcRect) {
  using namespace Entities::global;

  switch (entity) {
    case PLAYER:      srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case HEART:       srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case AMYTHYST:    srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case EVILPLAYER:  srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case BOMB:        srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case BLAST:       srcRect = CAsset::getRect(0, 0, 64, 64); break;
    default:          break;
  }
}

void CEntityData::getDims_caves(const int& entity, SDL_Rect& srcRect) {
  using namespace Entities::caves;

  switch (entity) {
    case BARS:        srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case BOX:         srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case SPIKEFALL:   srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case BLDSPK_UP:   srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case ACIDBALL:    srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case DOOR:        srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case SVPT:        srcRect = CAsset::getRect(0, 0, 32, 32); break;
    case SIGN:        srcRect = CAsset::getRect(0, 0, 32, 32); break;
    default:          break;
  }
}
