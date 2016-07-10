#include "CME_ChTile.h"

CME_ChTile CME_ChTile::UIControl;

CME_ChTile::CME_ChTile()
{
	//
}

int CME_ChTile::OnExecute(SDL_Renderer* renderer, SDL_Texture* tileset)
{
	SDL_QueryTexture(tileset, NULL, NULL, &W, &H);
	if (W <= WWIDTH && H <= WHEIGHT)
	{
		// Draw the full tileset in the center of the workspace
		Running =
			CSurface::OnDraw(renderer, tileset, (WWIDTH - W) / 2, (WHEIGHT - H) / 2, 0, 0, W, H);
		SDL_RenderPresent(renderer);
	}
	else
		Running = false;

	SDL_Event Event;
	// This loop will run endlessly until something makes the Running
	// flag false. That will happen, hopefully, by the user's decision.
	while (Running)
	{
		// Check for pending events; handle them
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
	}

	return GetID();
}

void CME_ChTile::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CME_ChTile::OnLButtonDown(int mX, int mY)
{
	if (mX >= (WWIDTH - W) / 2 && mX < (WWIDTH + W) / 2)
	{
		if (mY >= (WHEIGHT - H) / 2 && mY < (WHEIGHT + H) / 2)
		{
			this->X = mX;
			this->Y = mY;
			Running = false;
		}
	}
}

int CME_ChTile::GetID()
{
	int TileID;

	// Get X,Y relative to tileset display
	X -= (WWIDTH - W) / 2;
	Y -= (WHEIGHT - W) / 2; 

	TileID = X / TILE_SIZE;
	TileID += (Y / TILE_SIZE) * W / TILE_SIZE;

	return TileID;
}


