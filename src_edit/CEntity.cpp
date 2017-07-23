#include "CEntity.h"

std::vector<EntityTexInfo> CEntity::textureList;
std::vector<CEntity> CEntity::entityList;

namespace {
  const std::string io_path = "../data/maps/";
  const std::string io_ext = ".ent";
}

CEntity::CEntity(int group, int entity, const SDL_Point* m) {
  sprtSrc   = getSrcTexture(group);
  group_ID  = group;
  entity_ID = entity;
  srcR      = CEntityData::getEntityDims(group, entity);
  hitR      = CEntityData::getHitboxDims(group, entity);
  dstP      = CCamera::CameraControl.GetCamRelPoint(m);
}

bool CEntity::OnInit() {
  if (loadTexInfo(Entities::groups::GLOBAL) == NULL) {
    return false;
  }
  return true;
}

bool CEntity::OnLoad(const char* fname) {
  std::string filePath = io_path + fname + io_ext;
  FILE* FileHandle = fopen(filePath.c_str(), "rb");

	if (FileHandle == NULL)	{
		CInform::InfoControl.pushInform("---CENTITY.OnLoad---\nfailed to open new file");
		return false;
	}

  entityList.clear();

  int N;
  fread(&N, sizeof(int), 1, FileHandle);
  for (int i = 0; i < N; i++) {
    // read entity info
    int entry[4];
    fread(entry, sizeof(int), sizeof(entry)/sizeof(entry[0]), FileHandle);
    const int group_ID = entry[0];
    if (!isTextureLoaded(group_ID)) loadTexInfo(group_ID);
    const int entity_ID = entry[1];
    const SDL_Point dstP = {entry[2], entry[3]};
    CEntity newEntity(group_ID, entity_ID, &dstP);
    entityList.push_back(newEntity);
  }
  fclose(FileHandle);
  return true;
}

bool CEntity::OnSave(const char* fname) {
  std::string filePath = io_path + fname + io_ext;
  FILE* FileHandle = fopen(filePath.c_str(), "wb");

	if (FileHandle == NULL)	{
		CInform::InfoControl.pushInform("---CENTITY.OnSave---\nfailed to open new file");
		return false;
	}

  const int N = entityList.size();
  fwrite(&N, sizeof(int), 1, FileHandle);
  for (int i = 0; i < entityList.size(); i++) {
    // Output entity info
    int entry[] = {
      entityList[i].group_ID,
      entityList[i].entity_ID,
      entityList[i].dstP.x,
      entityList[i].dstP.y
    };
    fwrite(entry, sizeof(int), sizeof(entry)/sizeof(entry[0]), FileHandle);
  }
  fclose(FileHandle);
  return true;
}

bool CEntity::isGroupUsed(const int& group) {
  for (int i = 0; i < entityList.size(); i++) {
    if (group == entityList[i].group_ID) return true;
  }
  return false;
}

bool CEntity::isEntityUsed(const int& group, const int& entity) {
  for (int i = 0; i < entityList.size(); i++) {
    if (group == entityList[i].group_ID && entity == entityList[i].entity_ID) return true;
  }
  return false;
}

bool CEntity::isTextureLoaded(const int& group) {
  for (int i = 0; i < textureList.size(); i++) {
    if (group == textureList[i].group_ID) return true;
  }
  return false;
}

bool CEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(&dstP);
  return CSurface::OnDraw(sprtSrc, &srcR, &dstWinPos);
}

bool CEntity::OnRenderHitbox() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(&dstP);
  SDL_Rect dstR = {dstWinPos.x + hitR.x, dstWinPos.y + hitR.y, hitR.w, hitR.h};
  return CAsset::drawBox(&dstR, &palette::red);
}

SDL_Texture* CEntity::getSrcTexture(const int& group) {
  for (int i = 0; i < textureList.size(); i++) {
    if (group == textureList[i].group_ID) {
      return textureList[i].img;
    }
  }
  return NULL;
}

SDL_Texture* CEntity::loadTexInfo(const int& group) {
  if (isTextureLoaded(group)) return getSrcTexture(group);

  SDL_Texture* entity_tex = NULL;
  entity_tex = CEntityData::loadSrcTexture(group);

  if (entity_tex != NULL) {
    EntityTexInfo newInfo;
    newInfo.group_ID = group;
    newInfo.img = entity_tex;
    textureList.push_back(newInfo);
  }
  return entity_tex;
}

void CEntity::purgeStaleTextures() {
  for (int i = textureList.size() - 1; i >= 0; i--)
  {
    if (!isGroupUsed(textureList[i].group_ID))
    {
      SDL_DestroyTexture(textureList[i].img);
      textureList.erase(textureList.begin() + i);
    }
  }
}
