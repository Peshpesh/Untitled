#include "CApp.h"

void CApp::OnExit()
{
	Running = false;
}

void CApp::OnTerminate()
{
	SDL_DestroyWindow(Map_Display);
	// SDL_DestroyRenderer(Map_Renderer);
	CSurface::SurfControl.OnCleanup();
	SDL_DestroyTexture(Main_Tileset);
	SDL_DestroyTexture(Map_Interface);
	SDL_DestroyTexture(Type_Tileset);
	// SDL_DestroyTexture(Font);
	//CArea::AreaControl.OnCleanup();

	return;
}
