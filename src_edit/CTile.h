#ifndef _C_TILE_H_
#define _C_TILE_H_

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

  /*    GENTLE SLOPES   */
  SOLID_U_BL_MR,        // tile is solid Under Bottom-Left to Middle-Right line
  SOLID_U_ML_TR,        // tile is solid Under Middle-Left to Top-Right line
  SOLID_U_TL_MR,        // tile is solid Under Top-Left to Middle-Right line
  SOLID_U_ML_BR,        // tile is solid Under Middle-Left to Bottom-Right line
  SOLID_A_BL_MR,        // tile is solid Above Bottom-Left to Middle-Right line
  SOLID_A_ML_TR,        // tile is solid Above Middle-Left to Top-Right line
  SOLID_A_TL_MR,        // tile is solid Above Top-Left to Middle-Right line
  SOLID_A_ML_BR,        // tile is solid Above Middle-Left to Bottom-Right line

  /*    STEEP SLOPES    */
  SOLID_U_LT_MB,        // tile is solid Under Left-top to Middle-bottom line
  SOLID_U_MT_RB,        // tile is solid Under Middle-top to Right-bottom line
  SOLID_U_RT_MB,        // tile is solid Under Right-top to Middle-bottom line
  SOLID_U_MT_LB,        // tile is solid Under Middle-top to Left-bottom line

  /*    FLAT TILES      */
  SOLID_HALF_TH,        // top-half of tile is solid
  SOLID_HALF_BH,        // bottom-half of tile is solid
};

class CTile
{
public:
	short		bg_ID;			// Background tile (ID) drawn
	short		fg_ID;			// Foreground tile (ID) drawn
	short		TypeID;			// Tile characteristics
	short		CollID;		  // Collision characteristics

public:
	CTile();
};

#endif
