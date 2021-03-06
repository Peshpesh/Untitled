#ifndef _C_SCENERY_H_
#define _C_SCENERY_H_

#include <vector>
#include "CSurface.h"
// #include "CAnimation.h"
#include "CCamera.h"
#include "CInform.h"
#include "CSceneryData.h"
#include "Define.h"

//////////////////////////////////////////////////////////////
// NOTE:  THIS CLASS IS A SIMPLIFIED DATA STRUCTURE         //
//        THAT IS MEANT TO RESEMBLE--NOT REPLICATE--        //
//        SCENERY DATA STRUCTURES IN THE MAIN APPLICATION   //
//                                                          //
//        ----ONLY FOR USE IN THE EDITING ENGINE---         //
//////////////////////////////////////////////////////////////

struct SceneryTexInfo {
  int group_ID;
  SDL_Texture* img;
};

class CScenery {
public:
  static bool OnInit();
  static bool OnLoad(const char* fname);
  static bool OnSave(const char* fname);
  static bool isGroupUsed(const int& group);
  static bool isLayerUsed(const int& layer);
  static bool isSceneryUsed(const int& group, const int& decor);
  static bool isTextureLoaded(const int& group);
  static SDL_Texture* loadTexInfo(const int& group);
  static SDL_Texture* fetchTexture(const int& group);
  static void purgeStaleTextures();
  static void purgeStaleLayers();
  static int adjustLayerDepth(const int& idx, const double& new_Z);
  static void swapLayerIndex(const int& idx, const int& d_idx);
  static void removeLayerIndex(const int& idx);
  static bool addScenery(int group, int decor, const SDL_Point* p, unsigned short layer);
  static bool addScenery(int group, int decor, const double& rel_X, const double& rel_Y, unsigned short layer);
  static int addLayer(const double& Z);
  static double getLayerZ(unsigned short layer);

public:
  static std::vector<SceneryTexInfo>  texList;        // contains loaded texture info
  static std::vector<CScenery>        sceneryList;    // contains placed scenery info
  static std::vector<double>          layerList;      // contains layer info

public:
  SDL_Texture*   imgSrc;      // pointer to image source
  int            group_ID;    // scenery group ID number
  int            decor_ID;    // decoration ID in group
  SDL_Rect       srcR;        // source frame size & position
  double         true_x, true_y;
  unsigned short layer;       // assigned Z layer index

public:
  CScenery(int group, int decor, const SDL_Point* p, unsigned short layer);
  CScenery(int group, int decor, const double& X, const double& Y, unsigned short layer);

  bool OnRender();
};

#endif
