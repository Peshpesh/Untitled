#include "CApp.h"

void CApp::OnMotion(const Uint8 *state)
{
	if (CInterrupt::isNone())
	{
		if (state[SDL_SCANCODE_LEFT])
			CCamera::CameraControl.OnMove(-6, 0);
		if (state[SDL_SCANCODE_UP])
			CCamera::CameraControl.OnMove(0, -6);
		if (state[SDL_SCANCODE_DOWN])
			CCamera::CameraControl.OnMove(0, 6);
		if (state[SDL_SCANCODE_RIGHT])
			CCamera::CameraControl.OnMove(6, 0);
	}
}
