#include "CSurface.h"

CSurface::CSurface()
{
	// Empty constructor
}

/* Loads an image using a specified renderer.
* param File     : character string of the file name
* param renderer : renderer in use
*/
SDL_Texture* CSurface::OnLoad(char const* File, SDL_Renderer *renderer)
{
	// Initialize texture and surface pointers to null
	SDL_Texture* Surf_Text = NULL;
	SDL_Surface* Surf_Return = NULL;

	// Try loading image
	if ((Surf_Return = IMG_Load(File)) == NULL)	return NULL;

	// Load the image onto a SDL_Texture
	if ((Surf_Text = SDL_CreateTextureFromSurface(renderer, Surf_Return)) == 0)
	{
		return NULL;
	}

	// Get rid of our SDL_Surface
	SDL_FreeSurface(Surf_Return);
	return Surf_Text;
}

/* Draw a loaded texture onto a renderer.
* param Surf_Dest : a renderer; where the texture is drawn
* param Surf_Src : the texture used
* param X : horizontal position (Q-II) to draw texture
* param Y : vertical position (Q-II) to draw texture
*/
bool CSurface::OnDraw(SDL_Renderer* Surf_Dest, SDL_Texture* Surf_Src, int X, int Y)
{
	if (Surf_Dest == NULL || Surf_Src == NULL) return false;

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
	SDL_QueryTexture(Surf_Src, NULL, NULL, &DestR.w, &DestR.h);

	SDL_RenderCopy(Surf_Dest, Surf_Src, NULL, &DestR);
	return true;
}

bool CSurface::OnDraw(SDL_Renderer* Surf_Dest, SDL_Texture* Surf_Src, int X, int Y, int Xo, int Yo, int W, int H)
{
	if (Surf_Dest == NULL || Surf_Src == NULL) return false;

	SDL_Rect DestR;

	DestR.x = X;
	DestR.y = Y;
//	SDL_QueryTexture(Surf_Src, NULL, NULL, &DestR.w, &DestR.h);

	SDL_Rect SrcR;

	SrcR.x = Xo;
	SrcR.y = Yo;
	SrcR.w = W;
	SrcR.h = H;
	DestR.w = W;  // This will make the drawn image have the same
	DestR.h = H;  // resolution as the source image

	SDL_RenderCopy(Surf_Dest, Surf_Src, &SrcR, &DestR);
	return true;
}

bool CSurface::OnDraw(SDL_Renderer* Surf_Dest, SDL_Texture* Surf_Src, int X, int Y, int Xo, int Yo, int Wo, int Ho, int W, int H)
{
	if (Surf_Dest == NULL || Surf_Src == NULL)
		return false;

	SDL_Rect DestR;
	DestR.x = X;
	DestR.y = Y;
	DestR.w = W;
	DestR.h = H;

	SDL_Rect SrcR;
	SrcR.x = Xo;
	SrcR.y = Yo;
	SrcR.w = Wo;
	SrcR.h = Ho;

	SDL_RenderCopy(Surf_Dest, Surf_Src, &SrcR, &DestR);
	return true;
}
