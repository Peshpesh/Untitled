#ifndef _FONT_H_
#define _FONT_H_

#include <SDL.h>
#include <vector>
#include "CSurface.h"
#include "CFPS.h"
//#include "CHUD.h"

enum FONT_COLORS
{
	F_RED = 0,
	F_ORANGE, F_YELLOW,
	F_GREEN, F_CYAN, F_BLUE,
	F_INDIGO, F_VIOLET
};

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in font.png
class Font
{
public:
	static Font	FontControl;
	SDL_Texture* Tex_Font;
	SDL_Texture* Tex_HUD;

	Font();

	bool OnInit(SDL_Renderer* renderer);

public:
	static void GetXY(char symbol, int& X, int& Y, int& W, int& H);

	/* BRIEF: Static function that writes a one-line message
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or -2 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Write(SDL_Renderer* renderer, SDL_Texture* font, char const* message, int Mx, int My);

	static int Write(SDL_Renderer* renderer, SDL_Texture* font, char const* message, int color, bool flicker, int Mx, int My);

	/* BRIEF: Static function that writes a one-line message
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or 0 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param number : Integer to render
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Write(SDL_Renderer* renderer, SDL_Texture* font, int number, int Mx, int My);

	/* BRIEF: Static function that writes a message within a box
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or -2 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param bX : x-position of left edge of box
	* param bY : y-position of top edge of box
	* param bW : Width of box
	* param bH : Height of box
	* param tX : x-position of left edge of message
	* param tY : y-position of top edge of message
	* param tW : Width of message
	* param tH : Height of message
	* param speed: rate of type (char per second)
	*/
	static char BoxWrite(SDL_Renderer* renderer, SDL_Texture* font, char const* message,
		int bX, int bY, int bW, int bH, int tX, int tY, int tW, int tH, int length, int page);

	/* BRIEF:	write a multi-lined, left-justified message in an
	*					area defined through passed parameters.
	*					Full message is rendered immediately.
	*	RETURNS:	true if a message was rendered successfully.
	*	param	tX:	x-coordinate of top-left corner of text box
	*	param	tY:	y-coordinate of top-left corner of text box
	* param tW:	width of text box
	* param tH:	height of text box
	*/
	static bool TextBox(SDL_Renderer* renderer, char const* message,
		int tX, int tY, int tW, int tH);

	/* BRIEF: Static function that writes a one-line message
	***** centered at (Mx,My) using a loaded font as an SDL_Texture.
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param Mx : x-position of message center
	* param My : y-position of message center */
	static int CenterWrite(SDL_Renderer* renderer, SDL_Texture* font, char const* message, int Mx, int My);

	static char CenterBoxWrite(SDL_Renderer* renderer, SDL_Texture* font, char const* message,
		int bX, int bY, int bW, int bH, int tX, int length, int page);

	static bool	DrawContainer(SDL_Renderer* renderer, const int &bX, const int &bY,
		const int &bW, const int &bH, const char &color);
};
#endif
