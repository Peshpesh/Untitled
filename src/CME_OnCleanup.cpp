#include "CMapEdit.h"

void CMapEdit::OnCleanup()
{
	SDL_DestroyWindow(Map_Display);
	SDL_DestroyRenderer(Map_Renderer);
	SDL_DestroyTexture(Main_Tileset);
	SDL_DestroyTexture(Map_Interface);
	SDL_DestroyTexture(Type_Tileset);
	SDL_DestroyTexture(Font);
	//CArea::AreaControl.OnCleanup();

	return;
}