#include "CApp.h"

void CApp::OnLoop() {
	if (CInterrupt::isNone() && (CSimulate::control.getStatus() == INACTIVE || CSimulate::control.getStatus() == PLACE)) {
		if (pan_l) CCamera::CameraControl.OnMove(-6, 0);
		if (pan_r) CCamera::CameraControl.OnMove(6, 0);
		if (pan_u) CCamera::CameraControl.OnMove(0, -6);
		if (pan_d) CCamera::CameraControl.OnMove(0, 6);
	}

	CInform::InfoControl.OnLoop();

	int mX, mY;
	int tX = 0, tY = 0;
	SDL_GetMouseState(&mouseX, &mouseY);
	mouse.x = mouseX;
	mouse.y = mouseY;
	if (mouseX < WWIDTH && mouseY < WHEIGHT && mouseX >= 0 && mouseY >= 0) {
		mX = mouseX + CCamera::CameraControl.GetX();
		mY = mouseY + CCamera::CameraControl.GetY();
		tX = TILE_SIZE * (mX / TILE_SIZE);
		tY = TILE_SIZE * (mY / TILE_SIZE);

		if (mX < 0) tX -= TILE_SIZE;
		if (mY < 0)	tY -= TILE_SIZE;
	}	else {
		mX = -404404;
		mY = -404404;
	}

	CSimulate::control.OnLoop(&mouse);

	if (SDL_GetWindowFlags(Map_Display) & SDL_WINDOW_MINIMIZED) {
		SDL_RestoreWindow(Map_Display);
	}

	CFPS::FPSControl.OnLoop();
	return;
}
