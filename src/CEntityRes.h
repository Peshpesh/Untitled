#ifndef _C_ENTITYRES_H_
#define _C_ENTITYRES_H_

#include <cstring>
#include "CSurface.h"

class CEntityRes
{
public:
  enum EntitySet
	{
		SET_DEBUG = 0
	};

  CEntityRes();

  static bool OnInit(SDL_Renderer* renderer);

  static bool OnLoad(SDL_Renderer* renderer, const int& SetID);

  static SDL_Texture*	Com_Texture;	// Common (global) NPC Image pointer
  static SDL_Texture*	Unq_Texture;	// Unique (local) NPC Image pointer
  static SDL_Texture*	Arm_Texture;	// Arms Image pointer
  static SDL_Texture*	Bul_Texture;	// Bullets Image pointer
};

#endif
