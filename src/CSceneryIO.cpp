#include "CSceneryIO.h"

bool CSceneryIO::Init() {
  loadTexInfo(Decorations::groups::GLOBAL);
  if (fetchTexture(Decorations::groups::GLOBAL) == NULL) {
    return false;
  }
  return true;
}

bool CSceneryIO::Load(const char* File) {
  // try to load scenery file
  std::string fpath = "../data/maps/";
  std::string ext = ".scn";
  std::string fname = fpath + std::string(File) + ext;
  // std::string filePath = io_path + fname + io_ext;

  FILE* FileHandle = fopen(fname.c_str(), "rb");

	if (FileHandle == NULL)	{
		// CInform::InfoControl.pushInform("---CScenery.OnLoad---\nfailed to open file");
		return false;
	}

  // delete all scenery objects; clear layer list
  resetLevel();

  int N;  // number of scenery to load
  int L;  // number of layers
  fread(&N, sizeof(int), 1, FileHandle);
  fread(&L, sizeof(int), 1, FileHandle);

  for (int i = 0; i < N; i++) {
    // read scenery info
    int IDs[2];
    fread(IDs, sizeof(int), sizeof(IDs)/sizeof(IDs[0]), FileHandle);
    // const int group_ID = IDs[0];
    // const int decor_ID = IDs[1];
    loadTexInfo(IDs[0]);

    double true_pos[2];
    fread(true_pos, sizeof(double), sizeof(true_pos)/sizeof(true_pos[0]), FileHandle);
    // const double true_x = true_pos[0];
    // const double true_y = true_pos[1];

    int layer_info[1];
    fread(layer_info, sizeof(int), sizeof(layer_info)/sizeof(layer_info[0]), FileHandle);
    // const int layer = layer_info[0];

    addScenery(IDs[0], IDs[1], true_pos[0], true_pos[1], layer_info[0]);
    // CScenery newScenery(group_ID, decor_ID, true_x, true_y, layer);
    // sceneryList.push_back(newScenery);
  }

  double Z;
  for (int i = 0; i < L; i++) {
    // read layer details
    fread(&Z, sizeof(double), 1, FileHandle);
    if (Z > 0.0) CScenery::layerList.push_back(Z);
  }
  purgeStaleTextures();
  fclose(FileHandle);
  return true;
}

void CSceneryIO::resetLevel() {
  for (int i = CScenery::sceneryList.size() - 1; i >= 0; i--) {
    delete CScenery::sceneryList[i];
    CScenery::sceneryList.erase(CScenery::sceneryList.begin() + i);
  } CScenery::layerList.clear();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void CSceneryIO::addScenery(const int& group, const int& decor, const double& X, const double& Y, const int& layer) {
  using namespace Decorations::groups;
  CScenery* newScn = NULL;
  switch (group) {
    case GLOBAL: addGlobal(decor, newScn); break;
    default: break;
  }

  if (newScn != NULL) {
    SDL_Rect srcR = CSceneryData::getDecorDims(group, decor);
    if (!newScn->OnLoad(fetchTexture(group), srcR, X, Y, layer)) {
      // bad load
    }
    CScenery::sceneryList.push_back(newScn);
  }
}

void CSceneryIO::addGlobal(const int& decor, CScenery*& newScn) {
  using namespace Decorations::global;
  switch (decor) {
    case NOTHING: newScn = new CScenery; break;
    default: break;
  }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

bool CSceneryIO::isTextureLoaded(const int& group) {
  for (int i = 0; i < CScenery::texList.size(); i++) {
    if (group == CScenery::texList[i].group_ID) return true;
  }
  return false;
}

bool CSceneryIO::isGroupUsed(const int& group) {
  SDL_Texture* tex = fetchTexture(group);
  if (tex != NULL) {
    for (int i = 0; i < CScenery::sceneryList.size(); i++) {
      if (tex == CScenery::sceneryList[i]->imgSrc) return true;
    }
  }
  return false;
}

void CSceneryIO::loadTexInfo(const int& group) {
  if (isTextureLoaded(group)) return;

  SDL_Texture* scenery_tex = NULL;
  scenery_tex = CSceneryData::loadSrcTexture(group);

  if (scenery_tex != NULL) {
    SceneryTexInfo newInfo;
    newInfo.group_ID = group;
    newInfo.img = scenery_tex;
    CScenery::texList.push_back(newInfo);
  }
}

SDL_Texture* CSceneryIO::fetchTexture(const int& group) {
  for (int i = 0; i < CScenery::texList.size(); i++) {
    if (group == CScenery::texList[i].group_ID) {
      return CScenery::texList[i].img;
    }
  }
  return NULL;
}

void CSceneryIO::purgeStaleTextures() {
  for (int i = CScenery::texList.size() - 1; i >= 0; i--) {
    if (!isGroupUsed(CScenery::texList[i].group_ID)) {
      SDL_DestroyTexture(CScenery::texList[i].img);
      CScenery::texList.erase(CScenery::texList.begin() + i);
    }
  }
}
