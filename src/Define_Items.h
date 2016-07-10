#ifndef _DEFINE_ITEMS_H_
#define _DEFINE_ITEMS_H_

enum dyn_items
{
	EMPTY = 0,   // no item
	HPUP,        // restores HP
	HPDW,        // reduces HP (debug)
	BOMB,        // places a live bomb
	CHARM,       // allows access to special event via interact
	KEY,         // implicit access to special event (without interact)
};

#define ICON_SIZE 32	// pixels

#endif
