#include "IDebug.h"

IHPUP::IHPUP()
{
	name = "HP UP";
	ename = HPUP;
	about = "INCREASES HEALTH BY 5";

//	Xo = Yo = 0;

	quant = 0;
	m_quant = 1;
}

// int IHPUP::OnAdd(int& quantity)
// {
// 	for (int i = 0; i < MAX_INV_SIZE; i++)
// 	{
// 		if (Inventory[i] == NULL)
// 		{
// 			Inventory[i] = new IHPUP;
// 			quantity = 0;
// 		}
// 	}
// 	return 0;
// }
//
// void IHPUP::OnLoop()
// {
//
// }

void IHPUP::OnRender(SDL_Renderer* renderer, SDL_Texture* texture,
	const int& xO, const int& yO, const int& tW, const int& tH)
{
	CItem::OnRender(renderer, texture, xO, yO, tW, tH);
}

// bool IHPUP::OnUse(int& hp, const int& maxhp)
// {
// 	// Don't use if HP is already full!
// 	if (hp == maxhp)
// 		return false;
//
// 	int inc = 5;
// 	if (hp + inc < maxhp)
// 		hp += inc;
// 	else
// 		hp = maxhp;
//
// 	return true;
// }




///////////////////////////////



IHPDW::IHPDW()
{
	name = "HP DOWN";
	ename = HPDW;
	about = "ONLY FOR DEBUGGING\nREDUCES HEALTH BY 5";

//	Xo = Yo = 0;

	quant = 0;
	m_quant = 1;
}

// int IHPDW::OnAdd(int& quantity)
// {
// 	for (int i = 0; i < MAX_INV_SIZE; i++)
// 	{
// 		if (Inventory[i] == NULL)
// 		{
// 			Inventory[i] = new IHPDW;
// 			quantity = 0;
// 		}
// 	}
// 	return 0;
// }
//
// void IHPDW::OnLoop()
// {
//
// }

void IHPDW::OnRender(SDL_Renderer* renderer, SDL_Texture* texture,
	const int& xO, const int& yO, const int& tW, const int& tH)
{
	CItem::OnRender(renderer, texture, xO, yO, tW, tH);
}

// bool IHPDW::OnUse(int& hp)
// {
// 	int dec = 1;
//
// 	hp -= dec;
//
// 	return true;
// }
