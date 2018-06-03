#ifndef _CITEM_H_
#define _CITEM_H_

#include <vector>
#include "CSurface.h"
//#include "Font.h"
#include "Define_Items.h"

class CItem
{
public:
	 static const int			MAX_INV_SIZE = 20;		// Maximum amount of unique items
	// static CItem*				Inventory[20];			// List of Items (array)
	 static std::vector<CItem*>	Inventory;				// List of Items (vector)
	// static SDL_Texture*			Tex_Item;				// Item texture

public:
	char*			name;		// item name
	unsigned int	ename;		// item name (enum)
	char*			about;		// item description

public:
	int				quant;		// quantity of the item
	int				m_quant;	// maximum possible quantity of the item

public:
	CItem();

	virtual ~CItem();

public:
	// static member function that loads the static member SDL_Texture*, Tex_Item
//	static bool OnInit(SDL_Renderer* renderer);

	/*
	BRIEF
	* Attempts to add a quantity of an item to the Inventory array.
	PARAMS
	* quantity: number of the item added. Referenced to allow for
	* partial acquisition of an item (i.e., took only some of the item).
	RETURN
	* 1: some of the item was added.
	* 0: all of the item was added.
	* -1: the item was not added.
	*/
	//virtual int OnAdd(int& quantity);

//	virtual void OnLoop();

	virtual void OnRender(SDL_Renderer* renderer, SDL_Texture* texture,
		const int& xO, const int& yO, const int& tW, const int& tH);

//	void OnCleanup();

// public:
// 	virtual bool OnUse();
};

#endif
