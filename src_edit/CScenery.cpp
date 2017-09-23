#include "CScenery.h"

std::vector<SceneryTexInfo>   CScenery::texList;        // contains loaded texture info
std::vector<CScenery>         CScenery::sceneryList;    // contains placed scenery info
std::vector<double>           CScenery::Z;              // contains layer depths

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

bool CScenery::isLayerUsed(const int& layer) {
  for (int i = 0; i < sceneryList.size(); i++) {
    if (layer == sceneryList[i].layer) return true;
  }
  return false;
}

bool CScenery::isTextureLoaded(const int& group) {
  for (int i = 0; i < texList.size(); i++) {
    if (group == texList[i].group_ID) return true;
  }
  return false;
}

SDL_Texture* CScenery::loadTexInfo(const int& group) {
  if (isTextureLoaded(group)) return fetchTexture(group);

  SDL_Texture* scenery_tex = NULL;
  scenery_tex = CSceneryData::loadSrcTexture(group);

  if (scenery_tex != NULL) {
    SceneryTexInfo newInfo;
    newInfo.group_ID = group;
    newInfo.img = scenery_tex;
    texList.push_back(newInfo);
  }
  return scenery_tex;
}

SDL_Texture* CScenery::fetchTexture(const int& group) {
  for (int i = 0; i < texList.size(); i++) {
    if (group == texList[i].group_ID) {
      return texList[i].img;
    }
  }
  return NULL;
}

void CScenery::purgeStaleTextures() {
  for (int i = texList.size() - 1; i >= 0; i--) {
    if (!isGroupUsed(texList[i].group_ID)) {
      SDL_DestroyTexture(texList[i].img);
      texList.erase(texList.begin() + i);
    }
  }
}

void CScenery::purgeStaleLayers() {
  for (int i = Z.size() - 1; i >= 0; i--) {
    if (!isLayerUsed(i)) removeLayerIndex(i);
  }
}

void CScenery::removeLayerIndex(const int& idx) {
  for (int i = sceneryList.size() - 1; i >= 0; i--) {
    if (sceneryList[i].layer > idx) --sceneryList[i].layer;
    else if (sceneryList[i].layer == idx) sceneryList.erase(sceneryList.begin() + i);
  }
  Z.erase(Z.begin() + idx);
}
