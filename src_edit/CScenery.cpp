#include "CScenery.h"

std::vector<SceneryTexInfo>   CScenery::texList;        // contains loaded texture info
std::vector<CScenery>         CScenery::sceneryList;    // contains placed scenery info
std::vector<double>           CScenery::layerList;      // contains layer info

CScenery::CScenery(int group, int decor, const SDL_Point* p, unsigned short layer) {
  imgSrc          = fetchTexture(group);
  group_ID        = group;
  decor_ID        = decor;
  this->layer     = layer;
  srcR            = CSceneryData::getDecorDims(group, decor);

  SDL_Point r_pos = CCamera::CameraControl.GetCamRelPoint(p);
  truePos         = CCamera::CameraControl.ConvertToTrue(&r_pos, layerList[layer]);
}

bool CScenery::OnRender() {
  SDL_Point r_pos = CCamera::CameraControl.ConvertToRel(&truePos, layerList[layer]);
  SDL_Point w_pos = CCamera::CameraControl.GetWinRelPoint(&r_pos);
  return CSurface::OnDraw(imgSrc, &srcR, &w_pos);
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

bool CScenery::isSceneryUsed(const int& group, const int& decor) {
  for (int i = 0; i < sceneryList.size(); i++) {
    if (group == sceneryList[i].group_ID && decor == sceneryList[i].decor_ID) return true;
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
  for (int i = layerList.size() - 1; i >= 0; i--) {
    if (!isLayerUsed(i)) removeLayerIndex(i);
  }
}

int CScenery::adjustLayerDepth(const int& idx, const double& new_Z) {
  if (idx < 0 || idx >= layerList.size() || new_Z <= 0.0) return -1;

  // locate destination idx in layer (z) container
  // Pretend that we temporarily "remove" the adjusted layer,
  // and then we find the index where the layer would be if it were
  // added to the layers list as new
  int d_idx = 0;
  while (d_idx < layerList.size() - 1) {
    if (new_Z < layerList[(d_idx >= idx) ? (d_idx + 1) : d_idx]) break;
    d_idx++;
  }

  // Update true positions of affected objects (preserve relative position)
  for (int i = 0; i < sceneryList.size(); i++) {
    if (sceneryList[i].layer == idx) {
      SDL_Point r_pos = CCamera::CameraControl.ConvertToRel(&sceneryList[i].truePos, layerList[idx]);
      sceneryList[i].truePos = CCamera::CameraControl.ConvertToTrue(&r_pos, new_Z);
    }
  }

  if (d_idx != idx) {
    int i = idx;
    if (d_idx < idx) {
      // the destination index is less than the layer's original index.
      // All layers with (index >= d_idx && index < idx) will have their
      // index "pushed up" one.
      while (i > d_idx) layerList[i] = layerList[--i];
    }
    else if (d_idx > idx) {
      // the destination index is greater than the layer's original index.
      // All layers with (index > idx && index =< d_idx) will have their
      // index "pushed down" one.
      while (i < d_idx) layerList[i] = layerList[++i];
    }
    swapLayerIndex(idx, d_idx);
  }
  // update the layer depth
  layerList[d_idx] = new_Z;
  return d_idx;
}

void CScenery::swapLayerIndex(const int& idx, const int& d_idx) {
  if (idx < 0                    ||
      d_idx < 0                  ||
      idx >= layerList.size()    ||
      d_idx >= layerList.size()  ||
      idx == d_idx)              return;

  // Purpose: swap the layer index of objects with index "idx" with
  //          "d_idx". Rearrange the sceneryList vector such that the
  //          lowest layer-index objects are at the front of the container.
  // P. S.  : this is ASS

  std::vector<CScenery> swapList;
  int src_init  = -1;
  int dest_init = -1;
  int N = 0;
  for (int i = 0; i < sceneryList.size(); i++) {
    if (dest_init < 0 && sceneryList[i].layer >= d_idx) dest_init = i;
    if (sceneryList[i].layer == idx) {
      if (src_init < 0) src_init = i;
      swapList.push_back(sceneryList[i]);
      swapList[N++].layer = d_idx;
    }
  }
  // if src_init is still -1, then there are no objects to swap.
  // if src_init == dest_init, then no swapping of objects is necessary
  // (i.e., the objects are already at their destination in sceneryList)
  if (src_init < 0 || src_init == dest_init) return;

  if (d_idx < idx) {
    // swapped layer's objects are destined for lower i in the container.
    // All objects at and ahead of dest_init must be "pushed forward" to "make room"
    // for the swapped objects. They are pushed forward by the number of swapped objects.
    // Note that if there are objects to swap but no objects to swap WITH,
    // then src_init == dest_init because d_idx < idx (which results in "return" above)
    int i = src_init + N - 1; // start with the end of the swapping region
    while (i >= dest_init + N) {
      sceneryList[i] = sceneryList[i - N];
      i--;
    }
  }
  else if (d_idx > idx) {
    // swapped layer's objects are destined for higher (or equal) i in the container.
    // All objects at and ahead of src_init AND behind dest_init
    // must be "pushed backward" to "make room" for the swapped objects.
    // They are pushed backward by the number of swapped objects.
    // Note: it may be possible that no dest_init was ever detected, which means
    //       there are no objects with layer >= d_idx. However, there may still
    //       be objects *ahead* of the swapped objects, which would have a layer index
    //       less than d_idx. In this case, swapping is still necessary; swapped
    //       objects are placed at the end of the sceneryList container.
    if (dest_init < 0) dest_init = sceneryList.size() - N;
    int i = src_init;     // start with the beginning of the swapping region
    while (i < dest_init) {
      sceneryList[i] = sceneryList[i + N];
      i++;
    }
  }
  for (int i = 0; i < N; i++) sceneryList[dest_init + i] = swapList[i];
  swapList.clear();
}

void CScenery::removeLayerIndex(const int& idx) {
  if (idx < 0 || idx >= layerList.size()) return;

  for (int i = sceneryList.size() - 1; i >= 0; i--) {
    if (sceneryList[i].layer > idx) --sceneryList[i].layer;
    else if (sceneryList[i].layer == idx) sceneryList.erase(sceneryList.begin() + i);
  }
  layerList.erase(layerList.begin() + idx);
}

bool CScenery::addScenery(int group, int decor, const SDL_Point* p, unsigned short layer) {
  if (p == NULL) return false;

  CScenery newDecor(group, decor, p, layer);
  if (newDecor.imgSrc == NULL) return false;

  // locate index destination in scenery container;
  // place new scenery object at the "end" of objects sharing the same layer
  int i = 0;
  while (i < sceneryList.size()) {
    if (layer < sceneryList[i].layer) break;
    i++;
  }
  sceneryList.insert(sceneryList.begin() + i, newDecor);
  return true;
}

int CScenery::addLayer(const double& Z) {
  if (Z <= 0.0) return -1;

  // locate index destination in layer (z) container
  int i = 0;
  while (i < layerList.size()) {
    if (Z < layerList[i]) break;
    i++;
  }

  // place the new depth value in the layer container
  layerList.insert(layerList.begin() + i, Z);
  // update the layer indices of scenery with greater (farther) depth
  for (int j = 0; j < sceneryList.size(); j++) {
    if (sceneryList[j].layer >= i) sceneryList[j].layer++;
  }
  return i;
}
