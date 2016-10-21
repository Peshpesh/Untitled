#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include <SDL.h>
#include <SDL_image.h>

class CSurface
{
	public:
		CSurface();

	public:
		static SDL_Texture* OnLoad(char const* File, SDL_Renderer *renderer);

		static bool OnDraw(SDL_Renderer* Surf_Dest, SDL_Texture* Surf_Src, int X, int Y);

		/* Draw from a loaded texture onto a renderer.
		* param Surf_Dest : a renderer; where the texture is drawn
		* param Surf_Src : the texture used
		* param X : horizontal position (Q-II) to draw texture
		* param Y : vertical position (Q-II) to draw texture
		* param Xo : horizontal position (Q-II) to grab from texture
		* param Yo : vertical position (Q-II) to grab from texture
		* param W : width of the area of texture to use
		* param H : height of the area of texture to use
		*/
		static bool OnDraw(SDL_Renderer* Surf_Dest, SDL_Texture* Surf_Src, int X, int Y, int Xo, int Yo, int W, int H);

		/* Draw from a loaded texture onto a renderer.
		* param Surf_Dest : a renderer; where the texture is drawn
		* param Surf_Src : the texture used
		* param X : horizontal position (Q-II) to draw texture
		* param Y : vertical position (Q-II) to draw texture
		* param Xo : horizontal position (Q-II) to grab from texture
		* param Yo : vertical position (Q-II) to grab from texture
		* param Wo : source area width
		* param Ho : source area height
		* param W : destination area width
		* param H : destination area height
		*/
		static bool OnDraw(SDL_Renderer* Surf_Dest, SDL_Texture* Surf_Src, int X, int Y, int Xo, int Yo, int Wo, int Ho, int W, int H);

};

#endif
