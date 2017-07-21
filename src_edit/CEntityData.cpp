#include "CEntityData.h"

std::vector<HitboxData> CEntityData::hitboxList;

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
    const short num = 2;
    const char* const name[] = {
      "global",
      "caves"
    };
  };  // namespace groups
  namespace global {
    const short num = 6;
    const char* const name[] = {
      "Player",
      "Heart",
      "Amythyst",
      "Evil Player",
      "Live Bomb",
      "Blast"
    };
  };  // namespace global
  namespace caves {
    const short num = 8;
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

namespace path {
  const char* const dir = "../res/npc/";
  const char* const imgtype = ".png";
  const char* const hittype = ".phb";
};

CEntityData::CEntityData() {
  //
}

bool CEntityData::init() {
  for (int i = 0; i < Entities::groups::num; i++) {
    if (!load_phb(i)) return false;
  }
  return true;
}

bool CEntityData::load_phb(const int& group) {
  using namespace Entities::groups;

  std::string filename;
  int N = 0;

  if (group >= 0 && group < num) {
    filename = name[group];
    N = getNumEntities(group);
  }

  if (!filename.empty()) {
    using namespace path;
    std::string filepath = dir + filename + hittype;
    FILE* FileHandle = fopen(filepath.c_str(), "rb");
    if (FileHandle == NULL) { //could not open binary hitbox data file
      CInform::InfoControl.pushInform("--warning--\ncould not open hitbox data");
      for (int i = 0; i < N; i++) {
        HitboxData newdata = {group, i, getEntityDims(group, i)};
        hitboxList.push_back(newdata);
      }
    }
    else {  // opened binary hitbox data
      fclose(FileHandle);
    }
  }
  return true;
}

short CEntityData::getNumGroups() {
  return Entities::groups::num;
}

short CEntityData::getNumEntities(const int& group) {
  using namespace Entities::groups;

  short N = 0;
  switch (group) {
    case GLOBAL: N = Entities::global::num; break;
    case CAVES:  N = Entities::caves::num;  break;
  }
  return N;
}

SDL_Texture* CEntityData::loadSrcTexture(const int& group) {
  using namespace Entities::groups;

  SDL_Texture* entity_tex = NULL;
  std::string filename;

  if (group >= 0 && group < num) {
    filename = name[group];
  }

  if (!filename.empty()) {
    using namespace path;
    std::string filepath = dir + filename + imgtype;
    entity_tex = CSurface::OnLoad(filepath.c_str());
  }

  return entity_tex;
}

SDL_Rect CEntityData::getEntityDims(const int& group, const int& entity) {
  using namespace Entities::groups;

  SDL_Rect srcRect = {0,0,0,0};
  if (group < 0 || group >= num || entity < 0) return srcRect;

  switch (group) {
    case GLOBAL:  getDims_global(entity, srcRect);   break;
    case CAVES:   getDims_caves(entity, srcRect);    break;
    default:      break;
  }
  return srcRect;
}

SDL_Rect CEntityData::getHitboxDims(const int& group, const int& entity) {
  using namespace Entities::groups;

  SDL_Rect srcRect = {0,0,0,0};
  if (group < 0 || group >= num || entity < 0) return srcRect;

  for (int i = 0; i < hitboxList.size(); i++) {
    if (group > hitboxList[i].group) continue;
    if (group < hitboxList[i].group) break;
    if (entity == hitboxList[i].entity) {
      srcRect = hitboxList[i].hitR;
      break;
    }
  }
  return srcRect;
}

std::string CEntityData::getGroupName(const int& group) {
  if (group < 0 || group >= Entities::groups::num) return "";
  return Entities::groups::name[group];
}

std::string CEntityData::getEntityName(const int& group, const int& entity) {
  using namespace Entities::groups;

  std::string retval = "";
  if (group < 0 || group >= num || entity < 0) return retval;

  switch (group) {
    case GLOBAL:  getName_global(entity, retval); break;
    case CAVES:   getName_caves(entity, retval);  break;
    default:      break;
  }
  return retval;
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

void CEntityData::getName_global(const int& entity, std::string& str) {
  if (entity < Entities::global::num) {
    str = Entities::global::name[entity];
  }
}

void CEntityData::getName_caves(const int& entity, std::string& str) {
  if (entity < Entities::caves::num) {
    str = Entities::caves::name[entity];
  }
}
