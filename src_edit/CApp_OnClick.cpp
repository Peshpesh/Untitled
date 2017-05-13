#include "CApp.h"

void CApp::OnClick()
{
	int mX, mY;
	//SDL_PumpEvents();
	if (SDL_GetMouseState(&mX, &mY) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (mX < WWIDTH && mY < WHEIGHT)
		{
			// Left-click hold will overwrite map tiles based on changing cursor position.
			// Note that this function does not (and should not) apply to entities or
			// scenery objects.
			if (Active_Mod == MODIFY_MAP)
			{
				if (Use_Fore)
				{
					CArea::AreaControl.ChangeTile(CCamera::CameraControl.GetX() + mX, CCamera::CameraControl.GetY() + mY,
						Current_Tile, Current_Fore, Current_Type, Current_Slope);
				}
				else
				{
					CArea::AreaControl.ChangeTile(CCamera::CameraControl.GetX() + mX, CCamera::CameraControl.GetY() + mY,
						Current_Tile, -1, Current_Type, Current_Slope);
				}
			}
		}
	}
}
