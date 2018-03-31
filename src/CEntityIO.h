#ifndef _C_ENTITYIO_H_
#define _C_ENTITYIO_H_

#include <stdio.h>
#include <string>
#include "CEntity.h"
#include "CEntityData.h"

// All entities

class CEntityIO {
  CEntityIO();
private:
  static void resetLevel();

public:
  static bool Load(char const* File);

  static void addEntity(const int& group, const int& entity, const int& X, const int& Y);

private:
  static void addGlobal(const int& entity, const int& X, const int& Y);
  static void addCaves(const int& entity, const int& X, const int& Y);

private:
  static void loadTexInfo(const int& group);

  static bool isTextureLoaded(const int& group);
  static bool isTextureUsed(const int& group);
  static SDL_Texture* getSrcTexture(const int& group);

  static void purgeStaleTextures();
};

#endif
