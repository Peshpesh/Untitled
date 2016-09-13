#ifndef _DEFINE_ITEMS_H_
#define _DEFINE_ITEMS_H_

enum dyn_items
{
	ITEM_EMPTY = 0,   // no item (highlight box when rendered)
	ITEM_HPUP,        // restores HP
	ITEM_HPDW,        // reduces HP (debug)
	ITEM_BOMB,        // places a live bomb
	ITEM_CHARM,       // implicit access to special event without interact
	ITEM_KEY,         // explicit access to special event with interact
};

#define ICON_SIZE 32	// pixels

#endif
