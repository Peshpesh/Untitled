#ifndef _C_SCENERY_H_
#define _C_SCENERY_H_

#include <vector>
#include "CSurface.h"
// #include "CAnimation.h"
#include "CCamera.h"
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
  static void removeLayerIndex(const int& idx);
  static void addLayer(const double& Z);

public:
  static std::vector<SceneryTexInfo>  texList;        // contains loaded texture info
  static std::vector<CScenery>        sceneryList;    // contains placed scenery info
  static std::vector<double>          layerList;      // contains layer info

public:
  SDL_Texture*   imgSrc;      // pointer to image source
  int            group_ID;    // scenery group ID number
  int            decor_ID;    // decoration ID in group
  SDL_Rect       srcR;        // source frame size & position
  SDL_Point      truePos;     // "true" position in area
  unsigned short layer;       // assigned Z layer index

public:
  CScenery(int group, int decor, const SDL_Point* m, unsigned short layer);

  bool OnRender();
};

#endif
