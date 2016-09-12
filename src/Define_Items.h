#ifndef _DEFINE_ITEMS_H_
#define _DEFINE_ITEMS_H_

enum dyn_items
{
	ITEM_EMPTY = 0,   // no item (highlight box when rendered)
	ITEM_HPUP,        // restores HP
	ITEM_HPDW,        // reduces HP (debug)
	ITEM_BOMB,        // places a live bomb
	ITEM_CHARM,       // allows access to special event via interact
	ITEM_KEY,         // implicit access to special event (without interact)
};

#define ICON_SIZE 32	// pixels

#endif
