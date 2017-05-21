#ifndef _CTILE_H_
#define _CTILE_H_

#include "Define.h"

enum
{
  ENABLE_NONE 	= 0,
	ENABLE_BTILE	= 0x00000001,		// Place background tiles
  ENABLE_FTILE 	= 0x00000002,		// Place foreground tiles
  ENABLE_TYPE 	= 0x00000004,		// Place tile types
	ENABLE_COLL 	= 0x00000008,		// Place collision types
};

enum
{
	// TILE_TYPE_NONE = 0,		// void tiles; these are (typically) not rendered!
	// TILE_TYPE_HOLLOW,		// non-void non-filled tiles; rendered, no collision, some transparency!
	// TILE_TYPE_NORMAL,		// non-void filled tiles; these are rendered and do not have collision!
	// TILE_TYPE_BLOCK,		// blocking tiles; these are rendered and do have collision!
	// TILE_TYPE_WATER,		// underwater tiles; these are rendered and alter motion
	// TILE_TYPE_ICE,			// icy tiles; these are rendered and alter horizontal motion
	// TILE_TYPE_FIRE,			// fire tiles; these are rendered and deal damage

  TILE_TYPE_NORMAL = 0,   // Nothing unusual about these tiles
  TILE_TYPE_WATER,        // reduced speed when colliding with these tiles
  TILE_TYPE_ICE,          // increased inertia when colliding with these tiles
  TILE_TYPE_FIRE,         // persistent damage when colliding with these tiles
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
	int		TileID;			// Background tile (ID) drawn
	int		ForeID;			// Foreground tile (ID) drawn
	int		TypeID;			// Tile characteristics
	int		CollID;		  // Collision characteristics

public:
	CTile();
};

#endif
