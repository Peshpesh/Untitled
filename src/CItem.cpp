#include "CItem.h"

//CItem* CItem::Inventory[MAX_INV_SIZE] = { NULL };
std::vector<CItem*> CItem::Inventory;
//SDL_Texture* CItem::Tex_Item = NULL;

CItem::CItem()
{
//	name = NULL;
//	about = NULL;
	ename = EMPTY;

//	Xo = Yo = 0;

	quant = 0;
	m_quant = 1;
}

CItem::~CItem()
{
//	name = NULL;
//	about = NULL;
}

// bool CItem::OnInit(SDL_Renderer* renderer)
// {
// /*	if ((Tex_Item = CSurface::OnLoad("../res/item.png", renderer)) == NULL)
// 		return false;
// */
// 	return true;
// }

// void CItem::OnLoop()
// {
//
// }

void CItem::OnRender(SDL_Renderer* renderer, SDL_Texture* texture,
	const int &xO, const int& yO, const int& tW, const int& tH)
{
	if (texture == NULL || renderer == NULL)
	{
		return;
	}
	// xO, yO are positions on the window to render the item icon.
	// Still need to know position of the item icon in the texture file.
	// We can query the texture for sizes, and knowing the constant icon size,
	// and given that the order of enumerated item definitions is in concert with
	// the order of icons in the texture, the position of the icons is determined.
	int xI = ICON_SIZE * (ename % tW); // xposition of icon in texture
	int yI = ICON_SIZE * (ename / tW); // yposition of ...

	CSurface::OnDraw(renderer, texture, xO, yO, xI, yI, ICON_SIZE, ICON_SIZE);
}

// void CItem::OnCleanup()
// {
// 	/*
// 	if (Tex_Item)
// 	{
// 		SDL_DestroyTexture(Tex_Item);
// 	}
// 	Tex_Item = NULL;
// 	*/
// }

// bool CItem::OnUse()
// {
// 	return true;
// }
