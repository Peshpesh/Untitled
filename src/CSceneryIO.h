#ifndef _C_SCENERYIO_H_
#define _C_SCENERYIO_H_

#include <stdio.h>
#include <string>
#include "CScenery.h"
#include "CSceneryData.h"

class CSceneryIO {
  CSceneryIO();

private:
  static void resetLevel();

public:
  static bool init();

  static bool Load(char const* File);

  static void Cleanup();

  static void addScenery(const int& group, const int& decor, const double& X, const double& Y, const int& layer);

private:
  static void addGlobal(const int& decor, CScenery*& newScn);

public:
  static void loadTexInfo(const int& group);
  static SDL_Texture* fetchTexture(const int& group);

private:
  static bool isTextureLoaded(const int& group);
  static bool isGroupUsed(const int& group);

public:
  static void purgeStaleTextures();
};

#endif
