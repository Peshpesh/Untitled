#include "CTile.h"

CTile::CTile() {
	bg_ID 	= -1;
	fg_ID 	= -1;
	TypeID 	= TILE_TYPE_NORMAL;
	CollID 	= SOLID_NONE;
}

CPlanTile::CPlanTile() {
	ID 		= -1;
	type 	= TILE_TYPE_NORMAL;
	solid = false;
}
