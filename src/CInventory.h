#ifndef _CINVENTORY_H_
#define _CINVENTORY_H_

#include "CMenu.h"
#include "CItem.h"
#include "CItemProcess.h"
#include "Define.h"

#include "IDebug.h"

class CInventory
{
public:
	static CInventory    InvControl;

public:
  bool active;

public:
	SDL_Texture*			Tex_Item;				      // Item texture

private:
	int TEX_WIDTH;		// in number of ICON_SIZE
	int TEX_HEIGHT;		// in number of ICON_SIZE

private:
  unsigned short maxrow;
  unsigned short maxcol;
  unsigned short row;
  unsigned short col;
 	unsigned int MENU_W;
	unsigned int INV_MENU_H;
	unsigned int DETAIL_MENU_H;

private:
  CMenu* query;

public:
	CInventory();

public:
	// static member function that loads the static member SDL_Texture*, Tex_Item
	bool OnInit(SDL_Renderer* renderer);

  bool OnEvent(SDL_Keycode sym);

	void OnLoop();

	void OnRender(SDL_Renderer* renderer);

	void OnCleanup();
};

#endif
