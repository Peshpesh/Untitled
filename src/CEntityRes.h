#ifndef _C_ENTITYRES_H_
#define _C_ENTITYRES_H_

#include <cstring>
#include "CSurface.h"

enum EntitySet
{
  SET_DEBUG = 0
};
enum npc_common // NPC_ID order starts at 0 with commons
{
  YOSHI = 0,
  MAINCHAR,
  EVILMAIN,
  BOMB,
  EXPLODE
};
enum npc_debug // NPC_ID's from the Debug NPC table
{
  WSTAR = 0,
  BSTAR,
  BARS, BOX, SPIKEFALL, BLDSPK_UP,
  HEART, AMYTHYST, ACIDBALL, DOOR, SVPT, SIGN
};

class CEntityRes
{
public:
  // enum EntitySet
	// {
	// 	SET_DEBUG = 0
	// };
	// enum npc_common // NPC_ID order starts at 0 with commons
	// {
	// 	YOSHI = 0,
	// 	MAINCHAR,
	// 	EVILMAIN,
	// 	BOMB,
	// 	EXPLODE
	// };
	// enum npc_debug // NPC_ID's from the Debug NPC table
	// {
	// 	WSTAR = 0,
	// 	BSTAR,
	// 	BARS, BOX, SPIKEFALL, BLDSPK_UP,
	// 	HEART, AMYTHYST, ACIDBALL, DOOR, SVPT, SIGN
	// };

  CEntityRes();

  static bool OnInit(SDL_Renderer* renderer);

  static bool OnLoad(SDL_Renderer* renderer, const int& SetID);

  static SDL_Texture*	Com_Texture;	// Common (global) NPC Image pointer
  static SDL_Texture*	Unq_Texture;	// Unique (local) NPC Image pointer
  static SDL_Texture*	Arm_Texture;	// Arms Image pointer
  static SDL_Texture*	Bul_Texture;	// Bullets Image pointer
};

#endif
