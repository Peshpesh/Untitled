#include "CApp.h"

void CApp::OnClick()
{
	static int disable_init = 0;
	static int disable_timer = 0;
	if (Interrupt ^ INTRPT_NONE)
	{
		disable_init = SDL_GetTicks();
		if (disable_timer <= 0)
		{
			disable_timer = 1000;
		}
		return;
	}
	if (disable_timer > 0)
	{
		disable_timer += disable_init - SDL_GetTicks();
		disable_init = SDL_GetTicks();
		return;
	}

	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		if (mouseX < WWIDTH && mouseY < WHEIGHT)
		{
			// Left-click hold will overwrite map tiles based on changing cursor position.
			// Note that this function does not (and should not) apply to entities or
			// scenery objects.
			if (Active_Mod == MODIFY_MAP)
			{
				int mX = CCamera::CameraControl.GetX() + mouseX;
				int mY = CCamera::CameraControl.GetY() + mouseY;
				CArea::AreaControl.ChangeTile(mX, mY,	NoBack ? -1 : Current_Tile, NoFore ? -1 : Current_Fore, Current_Type, Current_Coll, OnTiles);
			}
		}
	}
}
