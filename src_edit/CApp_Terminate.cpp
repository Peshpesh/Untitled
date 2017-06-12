#include "CApp.h"

void CApp::OnExit()
{
	Running = false;
}

void CApp::OnTerminate()
{
	SDL_DestroyWindow(Map_Display);
	CSurface::SurfControl.OnCleanup();
	SDL_DestroyTexture(Map_Interface);
	CEditMap::MapEditor.OnTerminate();
}
