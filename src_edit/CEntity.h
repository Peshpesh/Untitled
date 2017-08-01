#ifndef _C_ENTITY_H_
#define _C_ENTITY_H_

#include <stdio.h>
#include <string>
#include <vector>

#include "CAsset.h"
#include "CEntityData.h"
#include "CInform.h"
#include "CCamera.h"

//////////////////////////////////////////////////////////////
// NOTE:  THIS CLASS IS A SIMPLIFIED DATA STRUCTURE         //
//        THAT IS MEANT TO RESEMBLE--NOT REPLICATE--        //
//        ENTITY DATA STRUCTURES IN THE MAIN APPLICATION    //
//                                                          //
//        ----ONLY FOR USE IN THE EDITING ENGINE---         //
//////////////////////////////////////////////////////////////

struct EntityTexInfo {
  int group_ID;
  SDL_Texture* img;
};

class CEntity {
public:
  static std::vector<EntityTexInfo> textureList;
  static std::vector<CEntity> entityList;
  static bool OnInit();
  static bool OnLoad(const char* fname);
  static bool OnSave(const char* fname);
  static bool isGroupUsed(const int& group);
  static bool isEntityUsed(const int& group, const int& entity);
  static bool isTextureLoaded(const int& group);
  static SDL_Texture* getSrcTexture(const int& group);
  static SDL_Texture* loadTexInfo(const int& group);
  static void updateHitboxes(const int& group, const int& entity);
  static void purgeStaleTextures();

public:
  SDL_Texture* sprtSrc;
  int group_ID;
  int entity_ID;
  SDL_Rect srcR;
  SDL_Rect hitR;
  SDL_Point dstP;

  CEntity(int group, int entity, const SDL_Point* m);

  bool OnRender();

  bool OnRenderHitbox();
};

#endif
