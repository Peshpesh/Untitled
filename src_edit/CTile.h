#ifndef _CTILE_H_
#define _CTILE_H_

#include "Define.h"

enum
{
  TILE_TYPE_NORMAL = 0,   // Nothing unusual about these tiles
  TILE_TYPE_WATER,        // reduced speed when colliding with these tiles
  TILE_TYPE_ICE,          // increased inertia when colliding with these tiles
  TILE_TYPE_FIRE,         // persistent damage when colliding with these tiles
};

enum
{
  ENABLE_NONE 	 = 0,
	ENABLE_BG	     = 0x00000001,		// Place background tiles
  ENABLE_FG 	   = 0x00000002,		// Place foreground tiles
  ENABLE_TYPE 	 = 0x00000004,		// Place tile types
	ENABLE_COLL 	 = 0x00000008,		// Place collision types
};

enum
{
  SOLID_NONE = 0,       // tile is solid nowhere
  SOLID_ALL,            // tile is solid everywhere
  SOLID_U_BL_MR,        // tile is solid Under Bottom-Left to Middle-Right line
  SOLID_U_ML_TR,        // tile is solid Under Middle-Left to Top-Right line
  SOLID_U_TL_MR,        // tile is solid Under Top-Left to Middle-Right line
  SOLID_U_ML_BR,        // tile is solid Under Middle-Left to Bottom-Right line
  SOLID_A_BL_MR,        // tile is solid Above Bottom-Left to Middle-Right line
  SOLID_A_ML_TR,        // tile is solid Above Middle-Left to Top-Right line
  SOLID_A_TL_MR,        // tile is solid Above Top-Left to Middle-Right line
  SOLID_A_ML_BR,        // tile is solid Above Middle-Left to Bottom-Right line
};

class CTile
{
public:
	int		bg_ID;			// Background tile (ID) drawn
	int		fg_ID;			// Foreground tile (ID) drawn
	int		TypeID;			// Tile characteristics
	int		CollID;		  // Collision characteristics

public:
	CTile();

  void reset();
};

#endif
