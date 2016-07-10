#include "CMapEdit.h"

void CMapEdit::OnClick()
{
	int mX, mY;
	//SDL_PumpEvents();
	if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (mX < WWIDTH && mY < WHEIGHT)
		{
			if (Active_Mod == MODIFY_MAP)
			{
				CArea::AreaControl.ChangeTile
					(CCamera::CameraControl.GetX() + mX,
					CCamera::CameraControl.GetY() + mY,
					Current_Tile, Current_Fore, Current_Type, Current_Slope);
			}
		}
	}
}