#include "CScenery.h"

std::vector<SceneryTexInfo>   CScenery::texList;        // contains loaded texture info
std::vector<CScenery>         CScenery::sceneryList;    // contains placed scenery info
std::vector<double>           CScenery::layerList;      // contains layer info

namespace {
  const std::string io_path = "../data/maps/";
  const std::string io_ext = ".scn";
}

CScenery::CScenery(int group, int decor, const SDL_Point* p, unsigned short layer) {
  imgSrc          = fetchTexture(group);
  group_ID        = group;
  decor_ID        = decor;
  this->layer     = layer;
  srcR            = CSceneryData::getDecorDims(group, decor);

  SDL_Point r_pos = CCamera::CameraControl.GetCamRelPoint(*p);
  true_x          = CCamera::CameraControl.relXToTrue(r_pos.x, layerList[layer]);
  true_y          = CCamera::CameraControl.relYToTrue(r_pos.y, layerList[layer]);
}

CScenery::CScenery(int group, int decor, const double& X, const double& Y, unsigned short layer) {
  imgSrc          = fetchTexture(group);
  group_ID        = group;
  decor_ID        = decor;
  this->layer     = layer;
  srcR            = CSceneryData::getDecorDims(group, decor);
  true_x          = X;
  true_y          = Y;
}

bool CScenery::OnRender() {
  double rel_x = CCamera::CameraControl.trueXToRel(true_x, layerList[layer]);
  double rel_y = CCamera::CameraControl.trueYToRel(true_y, layerList[layer]);
  SDL_Point w_pos = CCamera::CameraControl.GetWinRelPoint(rel_x, rel_y);
  return CSurface::OnDraw(imgSrc, &srcR, &w_pos);
}

bool CScenery::OnInit() {
  sceneryList.clear();
  layerList.clear();
  purgeStaleTextures();
  texList.clear();

  if (loadTexInfo(Decorations::groups::GLOBAL) == NULL) {
    return false;
  }

  return true;
}

bool CScenery::OnLoad(const char* fname) {
  std::string filePath = io_path + fname + io_ext;
  FILE* FileHandle = fopen(filePath.c_str(), "rb");

  if (FileHandle == NULL)  {
    CInform::InfoControl.pushInform("---CScenery.OnLoad---\nfailed to open file");
    return false;
  }

  sceneryList.clear();
  layerList.clear();

  int N, L;
  fread(&N, sizeof(int), 1, FileHandle);
  fread(&L, sizeof(int), 1, FileHandle);

  for (int i = 0; i < N; i++) {
    // read scenery info
    int IDs[2];
    fread(IDs, sizeof(int), sizeof(IDs)/sizeof(IDs[0]), FileHandle);
    const int group_ID = IDs[0];
    if (!isTextureLoaded(group_ID)) loadTexInfo(group_ID);
    const int decor_ID = IDs[1];

    double true_pos[2];
    fread(true_pos, sizeof(double), sizeof(true_pos)/sizeof(true_pos[0]), FileHandle);
    const double true_x = true_pos[0];
    const double true_y = true_pos[1];

    int layer_info[1];
    fread(layer_info, sizeof(int), sizeof(layer_info)/sizeof(layer_info[0]), FileHandle);
    const int layer = layer_info[0];

    CScenery newScenery(group_ID, decor_ID, true_x, true_y, layer);
    sceneryList.push_back(newScenery);
  }

  double Z;
  for (int i = 0; i < L; i++) {
    // read layer details
    fread(&Z, sizeof(double), 1, FileHandle);
    if (Z > 0.0) layerList.push_back(Z);
  }

  fclose(FileHandle);
  return true;
}

bool CScenery::OnSave(const char* fname) {
  std::string filePath = io_path + fname + io_ext;
  FILE* FileHandle = fopen(filePath.c_str(), "wb");

  if (FileHandle == NULL) {
    CInform::InfoControl.pushInform("---CSCENERY.OnSave---\nfailed to open new file");
    return false;
  }

  const int N = sceneryList.size();
  const int L = layerList.size();
  fwrite(&N, sizeof(int), 1, FileHandle);
  fwrite(&L, sizeof(int), 1, FileHandle);

  for (int i = 0; i < N; i++) {
    // Output scenery info
    int IDs[] = {
      sceneryList[i].group_ID,
      sceneryList[i].decor_ID,
    };
    double true_pos[] = {
      sceneryList[i].true_x,
      sceneryList[i].true_y,
    };
    int layer_info[] = {
      sceneryList[i].layer,
    };
    fwrite(IDs, sizeof(int), sizeof(IDs)/sizeof(IDs[0]), FileHandle);
    fwrite(true_pos, sizeof(double), sizeof(true_pos)/sizeof(true_pos[0]), FileHandle);
    fwrite(layer_info, sizeof(int), sizeof(layer_info)/sizeof(layer_info[0]), FileHandle);
  }

  for (int i = 0; i < L; i++) {
    // Output layer details
    const double Z = layerList[i];
    fwrite(&Z, sizeof(double), 1, FileHandle);
  }

  fclose(FileHandle);
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
      double rel_x = CCamera::CameraControl.trueXToRel(sceneryList[i].true_x, layerList[idx]);
      double rel_y = CCamera::CameraControl.trueYToRel(sceneryList[i].true_y, layerList[idx]);
      sceneryList[i].true_x = CCamera::CameraControl.relXToTrue(rel_x, new_Z);
      sceneryList[i].true_y = CCamera::CameraControl.relYToTrue(rel_y, new_Z);
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

bool CScenery::addScenery(int group, int decor, const double& rel_X, const double& rel_Y, unsigned short layer) {
  if (layer >= layerList.size()) return false;
  double true_X = CCamera::CameraControl.relXToTrue(rel_X, layerList[layer]);
  double true_Y = CCamera::CameraControl.relYToTrue(rel_Y, layerList[layer]);

  CScenery newDecor(group, decor, true_X, true_Y, layer);
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

double CScenery::getLayerZ(unsigned short layer) {
  return (layer >= layerList.size()) ? 0.0 : layerList[layer];
}
