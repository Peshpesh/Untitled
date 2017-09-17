#ifndef _C_SCENERY_H_
#define _C_SCENERY_H_

#include <vector>
#include "CSurface.h"
// #include "CAnimation.h"
#include "CCamera.h"
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
  static std::vector<CScenery> sceneryList;
  static std::vector<SceneryTexInfo> textureList;

public:
  CScenery();
};

#endif
