#ifndef _C_ASSET_H_
#define _C_ASSET_H_

#include "CSurface.h"
#include "Define.h"

namespace rgb
{
  const SDL_Color red      = {255, 10, 20};
  const SDL_Color orange   = {255, 148, 21};
  const SDL_Color yellow   = {255, 241, 0};
  const SDL_Color green    = {0, 238, 33};
  const SDL_Color cyan     = {0, 174, 239};
  const SDL_Color blue     = {0, 98, 188};
  const SDL_Color indigo   = {0, 6, 192};
  const SDL_Color violet   = {185, 0, 179};
  const SDL_Color magenta  = {255, 2, 84};
  const SDL_Color gray     = {161, 161, 161};

  const SDL_Color light_red     = {255, 91, 97};
  const SDL_Color light_orange  = {255, 183, 98};
  const SDL_Color light_yellow  = {255, 246, 84};
  const SDL_Color light_green   = {73, 255, 98};
  const SDL_Color light_cyan    = {73, 205, 255};
  const SDL_Color light_blue    = {69, 149, 224};
  const SDL_Color light_indigo  = {69, 74, 228};
  const SDL_Color light_violet  = {222, 69, 217};
  const SDL_Color light_magenta = {255, 85, 140};
  const SDL_Color white         = {255, 255, 255};

  const SDL_Color dark_red      = {170, 0, 7};
  const SDL_Color dark_orange   = {178, 96, 0};
  const SDL_Color dark_yellow   = {164, 154, 0};
  const SDL_Color dark_green    = {0, 153, 21};
  const SDL_Color dark_cyan     = {0, 111, 154};
  const SDL_Color dark_blue     = {0, 63, 121};
  const SDL_Color dark_indigo   = {0, 4, 123};
  const SDL_Color dark_violet   = {119, 0, 114};
  const SDL_Color dark_magenta  = {165, 0, 53};
  const SDL_Color black         = {0, 0, 0};
}

namespace palette
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
		static SDL_Texture* paltex;  // color palette
		static SDL_Texture* arrtex;   // arrows texture

  public:
    // returns a SDL_Rect struct for given X, Y, W, H. Ideal for drawing.
  	static SDL_Rect getRect(unsigned int X, unsigned int Y, unsigned int W, unsigned int H);
    static SDL_Rect getRect(const SDL_Point* A, const SDL_Point* B);
    static SDL_Rect getTileRect(const SDL_Point* A, const SDL_Point* B);
    static SDL_Point getPos(int X, int Y);

    // returns a SDL_Rect struct with W and H equal to 1, given (X, Y).
    // Good for grabbing a pixel of a particular color.
		static SDL_Rect getPixel(const SDL_Point* pix);

  public:
    static bool inWorkspace(const SDL_Point* pos);
    static bool inWorkspace(const int& x, const int& y);

	public:
    static bool drawLine(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick);

    static bool drawBox(const SDL_Rect* box, const SDL_Point* color, const int& thick);
    static bool drawBox(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick);

		static bool drawBoxFill(const SDL_Rect* box, const SDL_Point* color);
    static bool drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color);

    static bool drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color);
    static bool drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color, const SDL_Point* str_col);

    static bool drawArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb);
    static bool drawArrowFill(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb);
    static bool drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb);
    static bool drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb);

};

#endif
