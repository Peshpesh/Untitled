#ifndef _C_TYPE_H_
#define _C_TYPE_H_

#include <SDL.h>
#include <vector>
#include <math.h>
#include <string>
#include "CSurface.h"
#include "CAsset.h"
#include "CFPS.h"
#include "Define.h"

enum FONT_NAMES {
	FONT_DEFAULT = 0,
	FONT_MINI,
};

enum TEXT_JUST {
	H_JUST_L = 0x00000001,
	H_JUST_C = 0x00000002,
	H_JUST_R = 0x00000004,
	V_JUST_T = 0x00000008,
	V_JUST_C = 0x00000010,
	V_JUST_B = 0x00000020,
};

namespace speech_def {
	extern const short pause_l;
};

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in font image
class CType {
public:
	static CType control;
	SDL_Texture* CS_Font;
	SDL_Texture* Mini_Font;

private:
	bool dynamicText;
	short lastTime;
	short cursTimer;
	short cursAbsMaxTime;

private:
	const SDL_Color* def_rgb;
	short def_a;
	int def_ID;

public:
	CType();

	bool OnInit();

	void OnCleanup();

	void SetFont(const int& fontID);
	bool SetColor(const SDL_Color* col);
	bool SetOpacity(const short& A);
	void setDynamic();
	void renderCursor(const int& fontID, const SDL_Point& pos);

public:
	/*
	Preparatory function used to gather the font texture pointer for writing,
	as well as font-specific attributes like horizontal and vertical spacing between
	symbols and lines. Takes in an enumerated font identifier ("font"), and two
	initialized integers that are assigned spacing values by the function. Returns
	a font texture pointer on success, or NULL on failure.
	*/
	static SDL_Texture* GetInfo(const int& fontID, int& h_spacing, int& v_spacing);
	static SDL_Texture* GetFont(const int& fontID);
	static int GetHSpacing(const int& fontID);
	static int GetVSpacing(const int& fontID);
	static int GetSymH(const int& fontID);

private:
	static void changeFontColor(const int& fontID, const SDL_Color* col);
	static void resetFontColor(const int& fontID);
	static void changeFontColor(const SDL_Color* col);
	static void resetFontColor();
	static void changeFontAlpha(const int& fontID, const short& A);
	static void resetFontAlpha(const int& fontID);
	static void changeFontAlpha(const short& A);
	static void resetFontAlpha();

public:
	static void GetXY(const int& fontID, char symbol, int& X, int& Y, int& W, int& H);
	static void GetXY(const int& fontID, char symbol, SDL_Rect& symRec);
	static void GetXY_spec(const int& fontID, char symbol, int& X, int& Y, int& W, int& H);
	static void GetXY_spec(const int& fontID, char symbol, SDL_Rect& symRec);

	/* BRIEF: Static function that writes a one-line message
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or -99 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Write(const int& fontID, char const* message, int Mx, int My);
	static int Write(const int& fontID, char const* message, const SDL_Point& pos);
	static int Write(const int& fontID, char const* message, const SDL_Point& pos, const SDL_Color* col);

	static int WriteLine(const int& fontID, char const* line, const SDL_Point& pos);

	// static int Write(const int& fontID, char const* message, int color, bool flicker, int Mx, int My);

	/* BRIEF: Static function that writes a one-line message
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or -99 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param number : Integer to render
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Write(const int& fontID, int number, int Mx, int My);

	/* BRIEF: Static function that writes a one-line float
	***** using a loaded font as an SDL_Texture.
	* returns: horizontal size of written message (px), or 0 if no message written
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param number : Float to render
	* param precision: number of decimal places to render
	* param Mx : x-position of left edge of message
	* param My : y-position of top edge of message */
	static int Writef(const int& fontID, float number, unsigned int precision, int Mx, int My);

	/* BRIEF:	write a multi-lined, left-justified message in an
	*					area defined through passed parameters.
	*					Full message is rendered immediately.
	*	RETURNS:	true if a message was rendered successfully.
	*	param	tX:	x-coordinate of top-left corner of text box
	*	param	tY:	y-coordinate of top-left corner of text box
	* param tW:	width of text box
	* param tH:	height of text box
	*/
	static bool TextBox(const int& fontID, char const* message,
		int tX, int tY, int tW, int tH);

	/* BRIEF: Static function that writes a one-line message
	***** centered at (Mx,My) using a loaded font as an SDL_Texture.
	* param renderer : The renderer to draw a message upon
	* param font : Texture containing the font used
	* param message  : Pointer to char array/string (i.e., the message written)
	* param Mx : x-position of message center
	* param My : y-position of message center */
	static int OldCenterWrite(const int& fontID, char const* message, int Mx, int My);

	static int OldCenterWrite(const int& fontID, char const* message, const SDL_Rect& dstR);

	static int CenterWrite(const int& fontID, char const* message, const SDL_Rect& dstR, const SDL_Color* col);
	static int CenterWrite(const int& fontID, char const* message, const SDL_Point& dstC, const SDL_Color* col);
	static int CenterWrite(const int& fontID, char const* message, const SDL_Rect& dstR);
	static int CenterWrite(const int& fontID, char const* message, const SDL_Point& dstC);
	static int CenterWrite(char const* message, const SDL_Rect& dstR, const SDL_Color* col);
	static int CenterWrite(char const* message, const SDL_Point& dstC, const SDL_Color* col);
	static int CenterWrite(char const* message, const SDL_Rect& dstR);
	static int CenterWrite(char const* message, const SDL_Point& dstC);

	static int WriteBox(const int& fontID, char const* message, const short& lin, const SDL_Rect& dstR);

	static void getLineDims(const int& fontID, char const* message, int& msgWidth);
	static int getTextHeight(const int& fontID, char const* message, int maxWidth);
	static int getNumLines(const int& fontID, char const* message, int maxWidth);
	static std::string getLine(const int& fontID, char const* message, int& iterator, const int& maxWidth);
	static std::string getLine(const int& fontID, char const* message, int& iterator, const int& max_l, const int& maxWidth);
	static int getSpeakLength(char const* message);
	static std::string getSpeakSegment(char const* message, const short& l);
};
#endif
