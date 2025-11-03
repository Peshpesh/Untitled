#ifndef _C_PLANSIMENTITY_H_
#define _C_PLANSIMENTITY_H_

#include "CArea.h"
#include "CEntity.h"

namespace PlanEntityflags {
  enum {
    NONE    = 0,
    GHOST   = 0x00000001,  // Entity can translate thru walls
    HOLLOW  = 0x00000002,  // Entity allows other entities to translate thru it (collisions ON)
  };
};

class CPlanSimEntity {

public:
  SDL_Texture* sprtSrc;
  float  X;  // sprite x-position
  float  Y;  // sprite y-position
  SDL_Rect spriteR;  // sprite position & size on texture
  SDL_Rect hitboxR;  // X and Y are offset values relative to sprite
  char direction; // facing up 'U', down 'D', left 'L', or right 'R'
  bool idle; // is the entity idle?

public:
  int   Flags;

protected:
  float  SpeedX; // pixels / idealframe
  float  SpeedY; // pixels / idealframe

public:
  float  MaxSpeed; // pixels / idealframe

public:
  CPlanSimEntity();

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
  int CollGround(const int& collID, const int& X_offset, const int& Y_offset);
  int CollWall(const int& collID, const int& X_offset, const int& Y_offset);
  bool CheckPathXY(const int& destXl, const int& destXr, const int& destYt, const int& destYb);
  bool CollTile(const SDL_Point& tilepos, const SDL_Point& tl, const SDL_Point& br);
};

#endif
