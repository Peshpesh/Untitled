#include "CTile.h"

CTile::CTile()
{
	reset();
}

void CTile::reset()
{
	bg_ID = -1;
	fg_ID = -1;
	TypeID = TILE_TYPE_NORMAL;
	CollID = SOLID_NONE;
}
