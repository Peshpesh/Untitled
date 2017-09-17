#include "CScenery.h"

std::vector<SceneryTexInfo>  CScenery::textureList;    // contains loaded texture info
std::vector<CScenery>        CScenery::sceneryList;    // contains placed scenery info
std::vector<unsigned double> CScenery::Z;              // contains layer depths

CScenery::CScenery(int group, int decor, const SDL_Point* m, unsigned short layer) {
  if ((imgSrc = fetchTexture(group)) == NULL) {
    //
  };

  group_ID = group;
  decor_ID = decor;
  this->layer = layer;

  srcR      = CSceneryData::getDecorDims(group, decor);
  // truePos   = CCamera::CameraControl.GetCamRelPoint(m);
}

bool CScenery::OnInit() {
  if (loadTexInfo(Decorations::groups::GLOBAL) == NULL) {
    return false;
  }
  return true;
}

bool CScenery::OnLoad(const char* fname) {
  return true;
}

bool CScenery::OnSave(const char* fname) {
  return true;
}

bool CScenery::isGroupUsed(const int& group) {
  for (int i = 0; i < sceneryList.size(); i++) {
    if (group == sceneryList[i].group_ID) return true;
  }
  return false;
}

bool CScenery::isTextureLoaded(const int& group) {
  for (int i = 0; i < texList.size(); i++) {
    if (group == texList[i].group_ID) return true;
  }
  return false;
}

void CScenery::purgeStaleTextures() {
  for (int i = texList.size() - 1; i >= 0; i--)
  {
    if (!isGroupUsed(texList[i].group_ID))
    {
      SDL_DestroyTexture(texList[i].img);
      texList.erase(texList.begin() + i);
    }
  }
}

SDL_Texture* CScenery::loadTexInfo(const int& group) {
  return NULL;
}

SDL_Texture* CScenery::fetchTexture(const int& group) {
  return NULL;
}
