#include "CMapEdit.h"

void CMapEdit::OnMotion()
{
	SDL_PumpEvents();
		if (state[SDL_SCANCODE_LEFT])
			CCamera::CameraControl.OnMove(-6, 0);
		if (state[SDL_SCANCODE_UP])
			CCamera::CameraControl.OnMove(0, -6);
		if (state[SDL_SCANCODE_DOWN])
			CCamera::CameraControl.OnMove(0, 6);
		if (state[SDL_SCANCODE_RIGHT])
			CCamera::CameraControl.OnMove(6, 0);

}