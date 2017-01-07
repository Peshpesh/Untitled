#ifndef _CTILE_H_
#define _CTILE_H_

#include "Define.h"

enum 
{
	TILE_TYPE_NONE = 0,		// void tiles; these are (typically) not rendered!
	TILE_TYPE_HOLLOW,		// non-void non-filled tiles; rendered, no collision, some transparency!
	TILE_TYPE_NORMAL,		// non-void filled tiles; these are rendered and do not have collision!
	TILE_TYPE_BLOCK,		// blocking tiles; these are rendered and do have collision!
	TILE_TYPE_WATER,		// underwater tiles; these are rendered and alter motion!
	TILE_TYPE_ICE,			// icy tiles; these are rendered and alter horizontal motion!
	TILE_TYPE_FIRE,			// fire tiles; these are rendered and deal damage!
};

enum
{
	SLOPE_FLAT = 0,			// flat tiles
	SLOPE_ASC,				// sloped floor tiles that ascend FROM flat
	SLOPE_ASCE,				// sloped floor tiles continuing ascent possibly TO flat 
	SLOPE_DSC,				// sloped floor tiles that descend FROM flat
	SLOPE_DSCE,				// sloped floor tiles continuing descent possibly TO flat
	STEEP_ASC,				// steep ascending slopes possibly TO vertical
	STEEP_DSC,				// steep descending slopes possibly FROM vertical
	STEEP_ASCE,				// steep ascending slopes (NOT TO vertical)
	STEEP_DSCE,				// steep descending slopes (NOT FROM vertical)
};

class CTile
{
public:
	int		TileID;			// Middleground tile (ID) drawn
	int		ForeID;			// Foreground tile (ID) drawn
	int		TypeID;			// Tile characteristics
	int		Slope;			// Slope characteristics


public:
	CTile();
};

#endif