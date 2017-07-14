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
  dstP      = CCamera::CameraControl.GetCamRelPoint(m);
}

bool CEntity::OnInit() {
  if (loadTexInfo(Entities::groups::GLOBAL) == NULL) {
    return false;
  }
  return true;
}

bool CEntity::OnSave(const char* fname) {
  std::string filePath = io_path + fname + io_ext;
  FILE* FileHandle = fopen(filePath.c_str(), "w");

	if (FileHandle == NULL)	{
		CInform::InfoControl.pushInform("---CENTITY.OnSave---\nfailed to open new file");
		return false;
	}

  for (int i = 0; i < entityList.size(); i++) {
    // Output entity info
    fprintf(FileHandle, "%d:%d:%d:%d\n", entityList[i].group_ID, entityList[i].entity_ID, entityList[i].dstP.x, entityList[i].dstP.y);
  }
  fclose(FileHandle);
  return true;
}

bool CEntity::OnRender() {
  SDL_Point dstWinPos = CCamera::CameraControl.GetWinRelPoint(&dstP);
  return CSurface::OnDraw(sprtSrc, &srcR, &dstWinPos);
}

SDL_Texture* CEntity::getSrcTexture(const int& group) {
  SDL_Texture* retval = NULL;

  for (int i = 0; i < textureList.size(); i++) {
    if (group == textureList[i].group_ID) {
      retval = textureList[i].img;
      break;
    }
  }

  if (retval == NULL) retval = loadTexInfo(group);

  return retval;
}

SDL_Texture* CEntity::loadTexInfo(const int& group) {
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
