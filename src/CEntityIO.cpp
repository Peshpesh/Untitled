#include "CEntityIO.h"

CEntityIO::CEntityIO() {
  //
}

bool CEntityIO::Init() {
  resetLevel();
  loadTexInfo(Entities::groups::GLOBAL);
  if (getSrcTexture(Entities::groups::GLOBAL) == NULL) {
    return false;
  }
  return true;
}

bool CEntityIO::Load(const int& location_ID) {
  std::string abbrname = CLocation::getAbbrname(location_ID);
	if (abbrname.empty()) return false;

	// try to load entity file
  std::string fpath = "../data/maps/";
  std::string ext = ".ent";
  std::string fname = fpath + std::string(abbrname) + ext;

	FILE* FileHandle = fopen(fname.c_str(), "rb");
	if (FileHandle == NULL) {
		// ERROR: failed to open .ent file
		return false;
	}

  resetLevel();

	// Grab the number of entities to load
	int num;
	fread(&num, sizeof(int), 1, FileHandle);

  for (int i = 0; i < num; i++) {
    // read entity info
    int entry[4];
    fread(entry, sizeof(int), sizeof(entry)/sizeof(entry[0]), FileHandle);

    if (!isTextureLoaded(entry[0])) loadTexInfo(entry[0]);
    addEntity(entry[0], entry[1], entry[2], entry[3]);
    // CEntity newEntity(group_ID, entity_ID, &dstP);
    // entityList.push_back(newEntity);
  }
  purgeStaleTextures();
	fclose(FileHandle);
	return true;
}

void CEntityIO::Cleanup() {
  for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
    if (!CEntity::EntityList[i]->Permanent) delete CEntity::EntityList[i];
    CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
  } CEntity::EntityList.clear();
  purgeStaleTextures();
}

void CEntityIO::resetLevel() {
  for (int i = CEntity::EntityList.size() - 1; i >= 0; i--) {
    if (!CEntity::EntityList[i]->Permanent) {
      delete CEntity::EntityList[i];
      CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
    }
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CEntityIO::addEntity(const int& group, const int& entity, const int& X, const int& Y) {
  using namespace Entities::groups;
  switch (group) {
    case GLOBAL:  addGlobal(entity, X, Y);  break;
    case CAVES:   addCaves(entity, X, Y);   break;
    default: break;
  }
}

void CEntityIO::addGlobal(const int& entity, const int& X, const int& Y) {
  using namespace Entities::global;
  switch (entity) {
    case PLAYER:        break;
    case HEART:         break;
    case AMYTHYST:      break;
    case EVILPLAYER:    break;
    case BOMB:          break;
    case BLAST:         break;
    default: break;
  }
}

void CEntityIO::addCaves(const int& entity, const int& X, const int& Y) {
  using namespace Entities::caves;
  switch (entity) {
    case BARS:        break;
    case BOX:         break;
    case SPIKEFALL:   break;
    case BLDSPK_UP:   break;
    case ACIDBALL:    break;
    case DOOR:        break;
    case SVPT:        break;
    case SIGN:        break;
    default: break;
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CEntityIO::loadTexInfo(const int& group) {
  SDL_Texture* entity_tex = NULL;
  entity_tex = CEntityData::loadSrcTexture(group);

  if (entity_tex != NULL) {
    EntityTexInfo newInfo;
    newInfo.group_ID = group;
    newInfo.img = entity_tex;
    CEntity::TextureList.push_back(newInfo);
  }
}

bool CEntityIO::isTextureLoaded(const int& group) {
  for (int i = 0; i < CEntity::TextureList.size(); i++) {
    if (group == CEntity::TextureList[i].group_ID) return true;
  }
  return false;
}

bool CEntityIO::isTextureUsed(const int& group) {
  SDL_Texture* tex = getSrcTexture(group);
  if (tex != NULL) {
    for (int i = 0; i < CEntity::EntityList.size(); i++) {
      if (tex == CEntity::EntityList[i]->sprtSrc) return true;
    }
  }
  return false;
}

SDL_Texture* CEntityIO::getSrcTexture(const int& group) {
  for (int i = 0; i < CEntity::TextureList.size(); i++) {
    if (group == CEntity::TextureList[i].group_ID) {
      return CEntity::TextureList[i].img;
    }
  }
  return NULL;
}

void CEntityIO::purgeStaleTextures() {
  for (int i = CEntity::TextureList.size() - 1; i >= 0; i--) {
    if (!isTextureUsed(CEntity::TextureList[i].group_ID)) {
      SDL_DestroyTexture(CEntity::TextureList[i].img);
      CEntity::TextureList.erase(CEntity::TextureList.begin() + i);
    }
  }
}
