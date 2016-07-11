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
	MENU_W = 440;
	INV_MENU_H = 260;
	DETAIL_MENU_H = 120;
	DETAIL_TEXT_W = 400;
	DETAIL_TEXT_H = 100;
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
	for (int i = 0; i < 8; i++)
	{
		CItem::Inventory.push_back(new IHPUP());
		CItem::Inventory.push_back(new IHPDW());
	}
	for (int i = 0; i < CItem::Inventory.size(); i++)
	{
		if (CItem::Inventory[i]->ename == HPUP)
		{
			CItem::Inventory[i]->quant++;
			CItem::Inventory[i]->quant++;
		}
	}
	for (int i = 0; i < CItem::Inventory.size(); i++)
	{
		if (CItem::Inventory[i]->quant > CItem::Inventory[i]->m_quant)
		{
			CItem::Inventory[i]->quant = CItem::Inventory[i]->m_quant;
		}
	}
	return true;
}

bool CInventory::OnEvent(SDL_Keycode sym)
{
	if (CItem::Inventory.size() > 0)
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
	  }
	  if (sym == Config::ConfControl.left && Ncol > 1)
	  {
	    if (col != 0)
	      col--;
	    else
			{
				if ((row * maxcol) + Ncol > CItem::Inventory.size())
					col = (CItem::Inventory.size() % maxcol) - 1;
				else
					col = Ncol - 1;
			}
	  }
	  if (sym == Config::ConfControl.right && Ncol > 1)
	  {
			if (row != Nrow - 1 || Nrow == 1)
			{
		    if (col != Ncol - 1)
		      col++;
		    else
		      col = 0;
			}
			else
			{
				if (col != (CItem::Inventory.size() % maxcol) - 1)
					col++;
				else
					col = 0;
			}
	  }
	  if (sym == Config::ConfControl.down && Nrow > 1)
	  {
			if (row == Nrow - 1 || CItem::Inventory.size() <= (col + (row + 1) * maxcol))
				row = 0;
			else
				row++;
	  }
	  if (sym == Config::ConfControl.up && Nrow > 1)
	  {
	    if (row != 0)
	      row--;
	    else
			{
				if (CItem::Inventory.size() <= (col + (Nrow - 1) * maxcol))
					row = Nrow - 2;
				else
					row = Nrow - 1;
			}
	  }
	}
  if (sym == SDLK_ESCAPE)
  {
	 	active = false;
		row = col = 0;
  }
	return active;
}

bool CInventory::OnLoop()
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
			int highlight = col + (row * maxcol);
      switch (query->GetResponse())
      {
        case USE:
        {
          // use highlighted item
          // step1 : use row, col to get the highlighted item index
          // step2 : use item index to find out what kind of item is highlighted
          // step3 : perform necessary tasks (defined in CItemProcess class)
          // step4 : update the Inventory (e.g., subtract item from vector)
					CItemProcess::OnLoop(CItem::Inventory[highlight]->ename);
					CItem::Inventory[highlight]->quant--;
					if (CItem::Inventory[highlight]->quant <= 0)
					{
						delete CItem::Inventory[highlight];
						CItem::Inventory.erase(CItem::Inventory.begin() + highlight);
					}
					active = false;
					row = col = 0;
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
	return active;
}

void CInventory::OnRender(SDL_Renderer* renderer)
{
  if (Tex_Item == NULL || renderer == NULL)
	{
		return;
	}
	int spacing = 20;	// padding between text and border of box
	unsigned int xB = (WWIDTH - MENU_W) / 2;
	unsigned int iyB = (WHEIGHT - (INV_MENU_H + DETAIL_MENU_H)) / 2;
	unsigned int dyB = iyB + INV_MENU_H;
	Font::FontControl.DrawContainer(renderer, xB, iyB, MENU_W, INV_MENU_H, 'b');
	Font::FontControl.DrawContainer(renderer, xB, dyB, MENU_W, DETAIL_MENU_H, 'b');

	// what is the spacing between icons?
	unsigned int xS = (MENU_W - (maxcol * ICON_SIZE)) / (maxcol + 1);
	unsigned int yS = (INV_MENU_H - (maxrow * ICON_SIZE)) / (maxrow + 1);

	// what is the currently highlighted item?
	int highlight = col + (row * maxcol);

	// render all inventory item icons & highlight box
	for (int i = 0; i < CItem::Inventory.size(); i++)
	{
		int xT = i % maxcol;
		int yT = i / maxcol;
		int xO = ((xT + 1) * xS) + (xT * ICON_SIZE) + xB;
		int yO = ((yT + 1) * yS) + (yT * ICON_SIZE) + iyB;
		CItem::Inventory[i]->OnRender(renderer, Tex_Item, xO, yO, TEX_WIDTH, TEX_HEIGHT);
		if (i == highlight)
		{
			CSurface::OnDraw(renderer, Tex_Item, xO, yO, 0, 0, ICON_SIZE, ICON_SIZE);
			// render highlighted item's information
			int tX = xB + ((MENU_W - DETAIL_TEXT_W) / 2);
			int tY = dyB + ((DETAIL_MENU_H - DETAIL_TEXT_H) / 2);
			Font::FontControl.TextBox(renderer, CItem::Inventory[highlight]->name, tX, tY, DETAIL_TEXT_W, DETAIL_TEXT_H);
			Font::FontControl.TextBox(renderer, CItem::Inventory[highlight]->about, tX, tY + spacing, DETAIL_TEXT_W, DETAIL_TEXT_H);
		}
	}
}

void CInventory::OnCleanup()
{
  if (Tex_Item)	SDL_DestroyTexture(Tex_Item);
	Tex_Item = NULL;
}
