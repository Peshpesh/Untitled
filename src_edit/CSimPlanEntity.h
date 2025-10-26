#ifndef _C_SIMPLANENTITY_H_
#define _C_SIMPLANENTITY_H_

#include "CArea.h"
#include "CEntity.h"

namespace PlanEntityflags {
  enum {
    NONE    = 0,
    GHOST   = 0x00000001,  // Entity can translate thru walls
    HOLLOW  = 0x00000002,  // Entity allows other entities to translate thru it (collisions ON)
  };
};

class CSimPlanEntity {

public:
  SDL_Texture* sprtSrc;
  float  X;  // sprite x-position
  float  Y;  // sprite y-position
  SDL_Rect spriteR;  // sprite position & size on texture
  SDL_Rect hitboxR;  // X and Y are offset values relative to sprite
  char direction; // facing up 'U', down 'D', left 'L', or right 'R'
  bool ismoving; // is the entity currently moving?

public:
  int   Flags;

protected:
  float  SpeedX; // pixels / idealframe
  float  SpeedY; // pixels / idealframe

public:
  float  MaxSpeed; // pixels / idealframe

public:
  CSimPlanEntity();

public:
  void OnLoad();

  void OnLoop();

  bool OnRender();
  void OnRenderHitbox();

  void OnCleanup();

protected:
  void OnMove(float MoveX, float MoveY);

protected:
  void Translate(double NewX, double NewY);
  int getVertDeflect(const double& NewX, const double& NewY);
  int getHorzDeflect(const double& NewX, const double& NewY);
  int CollGround(const int& collID, const int& X_offset, const int& Y_offset);
  int CollWall(const int& collID, const int& X_offset, const int& Y_offset);
  bool CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb);
  bool CollTile(const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br);
};

#endif
