#include "CInventory.h"

CInventory CInventory::InvControl;
//std::vector<CItem*> CInventory::Inventory;

enum
{
	USE = 0,
	DROP,
	CANCEL,
};

CInventory::CInventory()
{
  active = false;
	TEX_WIDTH = TEX_HEIGHT = 0;
  row = 0;
  col = 0;
  Tex_Item = NULL;
  query = NULL;
}

bool CInventory::OnInit(SDL_Renderer* renderer)
{
	if ((Tex_Item = CSurface::OnLoad("../res/item.png", renderer)) == NULL) return false;

	int tW;
	int tH;

 	SDL_QueryTexture(Tex_Item, NULL, NULL, &tW, &tH);

	TEX_WIDTH = tW / ICON_SIZE;
	TEX_HEIGHT = tH / ICON_SIZE;

	// TESTING
	for (int i = 0; i < 5; i++)
	{
		CItem::Inventory.push_back(new IHPDW());
		CItem::Inventory.push_back(new IHPDW());
	}
	return true;
}

bool CInventory::OnEvent(SDL_Keycode sym)
{
  if (sym == Config::ConfControl.confirm)
  {
    query = new CMenu;
    query->Active = query->Breakable = true;
    query->OnInit("\
             %USE\
            \n%DROP\
            \n%CANCEL");

    CMenu::MenuList.push_back(query);
    // return;
  }
  if (sym == Config::ConfControl.left)
  {
    if (col != 0)
      col--;
    else
      col = maxcol - 1;
    // return;
  }
  if (sym == Config::ConfControl.right)
  {
    if (col != maxcol - 1)
      col++;
    else
      col = 0;
    // return;
  }
  if (sym == Config::ConfControl.down)
  {
    if (row != maxrow - 1)
      row++;
    else
      row = 0;
    // return;
  }
  if (sym == Config::ConfControl.up)
  {
    if (row != 0)
      row--;
    else
      row = maxrow - 1;
    // return;
  }
  if (sym == SDLK_ESCAPE)
  {
	 	active = false;
    // return;
  }
	return active;
}

void CInventory::OnLoop()
{
  if (query)
  {
    if (query->Break)
    {
      query->OnCleanup();
      delete CMenu::MenuList[CMenu::MenuList.size() - 1];
      CMenu::MenuList.erase(CMenu::MenuList.begin() + CMenu::MenuList.size() - 1);
      query = NULL;
    }
    else if (query->Submit)
    {
      switch (query->GetResponse())
      {
        case USE:
        {
          // use highlighted item
          // step1 : use row, col to get the highlighted item index
          // step2 : use item index to find out what kind of item is highlighted
          // step3 : perform necessary tasks (defined in CItemProcess class)
          // step4 : update the Inventory (e.g., subtract item from vector)
        //  CItemProcess::OnLoop(CItem::Inventory[col+row*maxcol]->ename); // ???
					CItemProcess::OnLoop(CItem::Inventory[0]->ename);
          break;
        }
        case DROP:
        {
          // drop highlighted item
          break;
        }
        case CANCEL:
        {
          // quit query menu; do nothing else
          break;
        }
        default: 	break;
      }
      query->OnCleanup();
      delete CMenu::MenuList[CMenu::MenuList.size() - 1];
      CMenu::MenuList.erase(CMenu::MenuList.begin() + CMenu::MenuList.size() - 1);
      query = NULL;
    }
  }
//  return active;
}

void CInventory::OnRender(SDL_Renderer* renderer)
{
  if (Tex_Item == NULL || renderer == NULL)
	{
		return;
	}
	unsigned int xB = (WWIDTH - MENU_WIDTH) / 2;
	unsigned int yB = (WHEIGHT - MENU_HEIGHT) / 2;
	Font::FontControl.DrawContainer(renderer, xB, yB, MENU_WIDTH, MENU_HEIGHT, 'b');

	// what is the spacing between icons?
	unsigned int xS = (MENU_WIDTH - (maxcol * ICON_SIZE)) / (maxcol + 1);
	unsigned int yS = (MENU_HEIGHT - (maxrow * ICON_SIZE)) / (maxrow + 1);
	for (int i = 0; i < CItem::Inventory.size(); i++)
	{
		int xT = i % maxcol;
		int yT = i / maxcol;
		int xO = ((xT + 1) * xS) + (xT * ICON_SIZE) + xB;
		int yO = ((yT + 1) * yS) + (yT * ICON_SIZE) + yB;
		CItem::Inventory[i]->OnRender(renderer, Tex_Item, xO, yO, TEX_WIDTH, TEX_HEIGHT);
	}
}

void CInventory::OnCleanup()
{
  if (Tex_Item)	SDL_DestroyTexture(Tex_Item);
	Tex_Item = NULL;
}
