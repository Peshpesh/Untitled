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
	row = col = 0;
  Tex_Item = NULL;
  query = NULL;
	maxrow = 4;
	maxcol = 5;
	// MENU_WIDTH = 540;
	// MENU_HEIGHT = 380;
	MENU_W = 540;
	INV_MENU_H = 260;
	DETAIL_MENU_H = 120;
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
	int Ncol = (int)(CItem::Inventory.size());
	if (Ncol > maxcol) Ncol = maxcol;
	int Nrow = 1 + ((int)(CItem::Inventory.size() - 1) / maxcol);
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
      col = Ncol - 1;
    // return;
  }
  if (sym == Config::ConfControl.right)
  {
    if (col != Ncol - 1)
      col++;
    else
      col = 0;
    // return;
  }
  if (sym == Config::ConfControl.down)
  {
    if (row != Nrow - 1)
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
      row = Nrow - 1;
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
	unsigned int xB = (WWIDTH - MENU_W) / 2;
	unsigned int iyB = (WHEIGHT - (INV_MENU_H + DETAIL_MENU_H)) / 2;
	unsigned int dyB = iyB + INV_MENU_H;
	Font::FontControl.DrawContainer(renderer, xB, iyB, MENU_W, INV_MENU_H, 'b');
	Font::FontControl.DrawContainer(renderer, xB, dyB, MENU_W, DETAIL_MENU_H, 'b');

	// what is the spacing between icons?
	unsigned int xS = (MENU_W - (maxcol * ICON_SIZE)) / (maxcol + 1);
	unsigned int yS = (INV_MENU_H - (maxrow * ICON_SIZE)) / (maxrow + 1);
	for (int i = 0; i < CItem::Inventory.size(); i++)
	{
		int xT = i % maxcol;
		int yT = i / maxcol;
		int xO = ((xT + 1) * xS) + (xT * ICON_SIZE) + xB;
		int yO = ((yT + 1) * yS) + (yT * ICON_SIZE) + iyB;
		CItem::Inventory[i]->OnRender(renderer, Tex_Item, xO, yO, TEX_WIDTH, TEX_HEIGHT);
		if (i == col + (row * maxcol))
		{
			CSurface::OnDraw(renderer, Tex_Item, xO, yO, 0, 0, ICON_SIZE, ICON_SIZE);
		}
	}
	//	xI, yI are coordinates for the top-left corner of the describing window
	//	beneath the inventory frame. We need to render the name of the highlighted
	//	item and its description.
	// int spacing = 20;
	// int aX = xI + spacing;
	// int title_Y = yI + spacing;
	// int aY = title_Y + spacing;
	// Font::TextBox(renderer, name, aX, title_Y, )
	// Font::TextBox(renderer, about, aX, aY, );
}

void CInventory::OnCleanup()
{
  if (Tex_Item)	SDL_DestroyTexture(Tex_Item);
	Tex_Item = NULL;
}
