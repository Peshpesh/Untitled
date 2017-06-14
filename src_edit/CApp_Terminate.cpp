#include "CApp.h"

void CApp::OnExit()
{
	Running = false;
}

void CApp::OnTerminate()
{
	SDL_DestroyWindow(Map_Display);
	CSurface::OnCleanup();
	SDL_DestroyTexture(Map_Interface);
	CAsset::OnCleanup();
	CEditMap::MapEditor.OnTerminate();
}
