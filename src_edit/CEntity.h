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

class CPlanEntity {
  // Each entity has the following attributes:
  //  - position (X, Y, Z)
  //  - kind/ID
  // ... And the ID is used to identify what to render
  //     from an image file with all the stage's entities.
  //     This requires a look-up table that tells where each
  //     entity is on the image file.
  //
  // Rendering: For the purposes of rendering, the camera looks "from above".
  //            Y-coordinate takes precedence (render lowest-Y scenery FIRST
  //            so it appears "behind" high-Y objects) over the Z-coordinate
  //            (for given Y, render lowest-Z FIRST so it's "underneath" layers
  //            above)
public:
  int group_ID;
  int ID;
  int X; // left-right as seen in PVM camera
  int Y; // up-down (on horizontal plane) as seen in PVM camera
  int Y_base; // this is the Y used for rendering order
  short Z; // toward-away (vertical plane)

  SDL_Texture* sprtSrc;
  SDL_Rect srcR;
  SDL_Rect hitR;
  bool coll;

  CPlanEntity(int group, int entity, const int& X, const int& Y, const short& Z);

  bool OnRender();

  bool OnRenderHitbox();

  bool Collides(const SDL_Point& oP, const SDL_Rect& oR);
};

class CEntity {
public:
  static std::vector<EntityTexInfo> textureList;
  static std::vector<CEntity> entityList;
  static std::vector<CPlanEntity> entList_back;
  static std::vector<CPlanEntity> entList_front;
  static const bool* planview;

  static bool OnInit();
  static void CheckCollide();
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
  bool coll;

  CEntity(int group, int entity, const SDL_Point* m);

  bool OnRender();

  bool OnRenderHitbox();

  bool Collides(const SDL_Point& oP, const SDL_Rect& oR);
};


#endif
