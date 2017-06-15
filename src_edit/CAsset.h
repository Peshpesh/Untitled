#ifndef _C_ASSET_H_
#define _C_ASSET_H_

#include "CSurface.h"
#include "Define.h"

namespace color
{
  const SDL_Point red      = {0, 0};
  const SDL_Point orange   = {1, 0};
  const SDL_Point yellow   = {2, 0};
  const SDL_Point green    = {3, 0};
  const SDL_Point cyan     = {4, 0};
  const SDL_Point blue     = {5, 0};
  const SDL_Point indigo   = {6, 0};
  const SDL_Point violet   = {7, 0};
  const SDL_Point magenta  = {8, 0};
  const SDL_Point gray     = {9, 0};

  const SDL_Point light_red     = {0, 1};
  const SDL_Point light_orange  = {1, 1};
  const SDL_Point light_yellow  = {2, 1};
  const SDL_Point light_green   = {3, 1};
  const SDL_Point light_cyan    = {4, 1};
  const SDL_Point light_blue    = {5, 1};
  const SDL_Point light_indigo  = {6, 1};
  const SDL_Point light_violet  = {7, 1};
  const SDL_Point light_magenta = {8, 1};
  const SDL_Point white         = {9, 1};

  const SDL_Point dark_red      = {0, 2};
  const SDL_Point dark_orange   = {1, 2};
  const SDL_Point dark_yellow   = {2, 2};
  const SDL_Point dark_green    = {3, 2};
  const SDL_Point dark_cyan     = {4, 2};
  const SDL_Point dark_blue     = {5, 2};
  const SDL_Point dark_indigo   = {6, 2};
  const SDL_Point dark_violet   = {7, 2};
  const SDL_Point dark_magenta  = {8, 2};
  const SDL_Point black         = {9, 2};
}

class CAsset
{
	public:
		CAsset();
		static bool OnInit();         // Initialization function
		static void OnCleanup();      // Termination function

	private:
		static SDL_Texture* palette;  // color palette

  public:
    // returns a SDL_Rect struct for given X, Y, W, H. Ideal for drawing.
  	static SDL_Rect getRect(unsigned int X, unsigned int Y, unsigned int W, unsigned int H);
    static SDL_Rect getRect(const SDL_Point* A, const SDL_Point* B);

    // returns a SDL_Rect struct with W and H equal to 1, given (X, Y).
    // Good for grabbing a pixel of a particular color.
		static SDL_Rect getPixel(const SDL_Point* pix);

	public:
    static bool drawLine(SDL_Point* A, SDL_Point* B, SDL_Point* color, const int& thick);

    static bool drawBox(SDL_Rect* box, const SDL_Point* color, const int& thick);
    static bool drawBox(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick);

		static bool drawBoxFill(SDL_Rect* box, SDL_Point* color);
    static bool drawBoxFill(SDL_Point* A, SDL_Point* B, SDL_Point* color);
};

#endif
