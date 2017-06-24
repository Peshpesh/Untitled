#include "CFont.h"

Font Font::FontControl;

Font::Font()
{
	Tex_Font = NULL;
	Mini_Font = NULL;
	Tex_HUD = NULL;
}

bool Font::OnInit()
{
	if ((Tex_Font = CSurface::OnLoad("../res/font.png")) == NULL) 	return false;
	if ((Mini_Font = CSurface::OnLoad("../res_edit/minifont.png")) == NULL) 	return false;
	if ((Tex_HUD = CSurface::OnLoad("../res/HUD.png")) == NULL)			return false;

	return true;
}

SDL_Texture* Font::GetInfo(const int& fontID, int& h_spacing, int& v_spacing)
{
	h_spacing = GetHSpacing(fontID);
	v_spacing = GetVSpacing(fontID);

	SDL_Texture* retptr = NULL;
	if (fontID == FONT_DEFAULT)		retptr = FontControl.Tex_Font;
	if (fontID == FONT_MINI)			retptr = FontControl.Mini_Font;

	return retptr;
}

int Font::GetHSpacing(const int& fontID)
{
	int h_spacing = 0;
	if (fontID == FONT_DEFAULT)		h_spacing = 2;
	if (fontID == FONT_MINI)			h_spacing = 1;
	return h_spacing;
}

int Font::GetVSpacing(const int& fontID)
{
	int v_spacing = 0;
	if (fontID == FONT_DEFAULT)		v_spacing = 16;
	if (fontID == FONT_MINI)			v_spacing = 6;
	return v_spacing;
}

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in a font texture
void Font::GetXY(const int& fontID, char symbol, int& X, int& Y, int& W, int& H)
{
	switch (fontID)
	{
		case FONT_DEFAULT:
		{
			switch (symbol)
			{
				case '0': X = 0;  Y = 0;   W = 14; H = 14; break;
				case '1': X = 15; Y = 0;   W = 12; H = 14; break;
				case '2': X = 28; Y = 0;   W = 14; H = 14; break;
				case '3': X = 43; Y = 0;   W = 13; H = 14; break;
				case '4': X = 0;  Y = 15;  W = 14; H = 14; break;
				case '5': X = 15; Y = 15;  W = 14; H = 14; break;
				case '6': X = 30; Y = 15;  W = 14; H = 14; break;
				case '7': X = 45; Y = 15;  W = 14; H = 14; break;
				case '8': X = 0;  Y = 30;  W = 14; H = 14; break;
				case '9': X = 15; Y = 30;  W = 14; H = 14; break;
				case 'a': X = 30; Y = 30;  W = 14; H = 14; break;
				case 'b': X = 45; Y = 30;  W = 14; H = 14; break;
				case 'c': X = 0;  Y = 45;  W = 14; H = 14; break;
				case 'd': X = 15; Y = 45;  W = 14; H = 14; break;
				case 'e': X = 30; Y = 45;  W = 12; H = 14; break;
				case 'f': X = 43; Y = 45;  W = 12; H = 14; break;
				case 'g': X = 0;  Y = 60;  W = 14; H = 14; break;
				case 'h': X = 15; Y = 60;  W = 12; H = 14; break;
				case 'i': X = 28; Y = 60;  W = 12; H = 14; break;
				case 'j': X = 41; Y = 60;  W = 12; H = 14; break;
				case 'k': X = 0;  Y = 75;  W = 13; H = 14; break;
				case 'l': X = 14; Y = 75;  W = 12; H = 14; break;
				case 'm': X = 27; Y = 75;  W = 14; H = 14; break;
				case 'n': X = 42; Y = 75;  W = 14; H = 14; break;
				case 'o': X = 0;  Y = 90;  W = 14; H = 14; break;
				case 'p': X = 15; Y = 90;  W = 12; H = 14; break;
				case 'q': X = 28; Y = 90;  W = 14; H = 14; break;
				case 'r': X = 43; Y = 90;  W = 12; H = 14; break;
				case 's': X = 0;  Y = 105; W = 14; H = 14; break;
				case 't': X = 15; Y = 105; W = 12; H = 14; break;
				case 'u': X = 28; Y = 105; W = 12; H = 14; break;
				case 'v': X = 41; Y = 105; W = 14; H = 14; break;
				case 'w': X = 0;  Y = 120; W = 14; H = 14; break;
				case 'x': X = 15; Y = 120; W = 14; H = 14; break;
				case 'y': X = 30; Y = 120; W = 14; H = 14; break;
				case 'z': X = 45; Y = 120; W = 14; H = 14; break;
				case 'A': X = 30; Y = 30;  W = 14; H = 14; break;
				case 'B': X = 45; Y = 30;  W = 14; H = 14; break;
				case 'C': X = 0;  Y = 45;  W = 14; H = 14; break;
				case 'D': X = 15; Y = 45;  W = 14; H = 14; break;
				case 'E': X = 30; Y = 45;  W = 12; H = 14; break;
				case 'F': X = 43; Y = 45;  W = 12; H = 14; break;
				case 'G': X = 0;  Y = 60;  W = 14; H = 14; break;
				case 'H': X = 15; Y = 60;  W = 12; H = 14; break;
				case 'I': X = 28; Y = 60;  W = 12; H = 14; break;
				case 'J': X = 41; Y = 60;  W = 12; H = 14; break;
				case 'K': X = 0;  Y = 75;  W = 13; H = 14; break;
				case 'L': X = 14; Y = 75;  W = 12; H = 14; break;
				case 'M': X = 27; Y = 75;  W = 14; H = 14; break;
				case 'N': X = 42; Y = 75;  W = 14; H = 14; break;
				case 'O': X = 0;  Y = 90;  W = 14; H = 14; break;
				case 'P': X = 15; Y = 90;  W = 12; H = 14; break;
				case 'Q': X = 28; Y = 90;  W = 14; H = 14; break;
				case 'R': X = 43; Y = 90;  W = 12; H = 14; break;
				case 'S': X = 0;  Y = 105; W = 14; H = 14; break;
				case 'T': X = 15; Y = 105; W = 12; H = 14; break;
				case 'U': X = 28; Y = 105; W = 12; H = 14; break;
				case 'V': X = 41; Y = 105; W = 14; H = 14; break;
				case 'W': X = 0;  Y = 120; W = 14; H = 14; break;
				case 'X': X = 15; Y = 120; W = 14; H = 14; break;
				case 'Y': X = 30; Y = 120; W = 14; H = 14; break;
				case 'Z': X = 45; Y = 120; W = 14; H = 14; break;
				case '.': X = 0;  Y = 135; W = 4;  H = 14; break;
				case '-': X = 5;  Y = 135; W = 9;  H = 14; break;
				case ' ': X = 53; Y = 60;  W = 6;  H = 14; break;   // this one will probably have to change in the future
				default:  X = 0;  Y = 0;   W = 0;  H = 0;  break;
			}
			break;
		}
		case FONT_MINI:
		{
			// All symbols in minifont are the same width and on one line
			Y = 0; W = 5;	H = 5;
			switch (symbol)
			{
				case '0': X = 156;  break;
				case '1': X = 162; 	break;
				case '2': X = 168; 	break;
				case '3': X = 174; 	break;
				case '4': X = 180;  break;
				case '5': X = 186; 	break;
				case '6': X = 192; 	break;
				case '7': X = 198; 	break;
				case '8': X = 204;  break;
				case '9': X = 210; 	break;
				case 'a': X = 0; 		break;
				case 'b': X = 6; 		break;
				case 'c': X = 12;  	break;
				case 'd': X = 18; 	break;
				case 'e': X = 24; 	break;
				case 'f': X = 30; 	break;
				case 'g': X = 36;  	break;
				case 'h': X = 42; 	break;
				case 'i': X = 48; 	break;
				case 'j': X = 54; 	break;
				case 'k': X = 60;  	break;
				case 'l': X = 66; 	break;
				case 'm': X = 72; 	break;
				case 'n': X = 78; 	break;
				case 'o': X = 84;  	break;
				case 'p': X = 90; 	break;
				case 'q': X = 96; 	break;
				case 'r': X = 102; 	break;
				case 's': X = 108;  break;
				case 't': X = 114; 	break;
				case 'u': X = 120; 	break;
				case 'v': X = 126; 	break;
				case 'w': X = 132;  break;
				case 'x': X = 138; 	break;
				case 'y': X = 144; 	break;
				case 'z': X = 150; 	break;
				case 'A': X = 0; 		break;
				case 'B': X = 6; 		break;
				case 'C': X = 12;  	break;
				case 'D': X = 18; 	break;
				case 'E': X = 24; 	break;
				case 'F': X = 30; 	break;
				case 'G': X = 36;  	break;
				case 'H': X = 42; 	break;
				case 'I': X = 48; 	break;
				case 'J': X = 54; 	break;
				case 'K': X = 60; 	break;
				case 'L': X = 66; 	break;
				case 'M': X = 72; 	break;
				case 'N': X = 78; 	break;
				case 'O': X = 84;  	break;
				case 'P': X = 90; 	break;
				case 'Q': X = 96; 	break;
				case 'R': X = 102; 	break;
				case 'S': X = 108;  break;
				case 'T': X = 114; 	break;
				case 'U': X = 120; 	break;
				case 'V': X = 126; 	break;
				case 'W': X = 132; 	break;
				case 'X': X = 138; 	break;
				case 'Y': X = 144; 	break;
				case 'Z': X = 150; 	break;
				case '.': X = 216; 	break;
				case '?': X = 222; 	break;
				case '!': X = 228; 	break;
				// case '...': X = 234; break;
				case '_': X = 240; 	break;
				case '-': X = 246; 	break;
				// case '!!!': X = 252; break;
				case ' ': X = 258; 	break;
				default:  X = 0; W = 0; H = 0; break;
			}
			break;
		}
		default: X = 0; Y = 0; W = 0; H = 0; break;
	}
}

int Font::Write(const int& fontID, char const* message, int Mx, int My)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
 	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL)
	{
		return -99;
	}

	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;

	while (message[i] != '\0')
	{
		if (message[i] == '\n')
		{
			Mx = FirstMx;
			My += v_spacing;
			i++;
			continue;
		}
		GetXY(fontID, message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + h_spacing;
		i++;
	}
	return Mx - FirstMx - h_spacing;
}

int Font::Write(const int& fontID, char const* message, int color, bool flicker, int Mx, int My)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL)
	{
		return -99;
	}

	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	static int alpha = 255;
	static bool intensify = false;

	if (intensify) alpha += 5;
	else alpha -= 5;

	switch (color)
	{
		case F_RED:		SDL_SetTextureColorMod(font, 237, 28, 36);	break;
		case F_ORANGE:	SDL_SetTextureColorMod(font, 242, 101, 34); break;
		case F_YELLOW:	SDL_SetTextureColorMod(font, 255, 242, 0);	break;
		case F_GREEN:	SDL_SetTextureColorMod(font, 57, 181, 74);	break;
		case F_CYAN:	SDL_SetTextureColorMod(font, 0, 174, 239);	break;
		case F_BLUE:	SDL_SetTextureColorMod(font, 0, 84, 166);	break;
		case F_INDIGO:	SDL_SetTextureColorMod(font, 46, 49, 146);	break;
		case F_VIOLET:	SDL_SetTextureColorMod(font, 102, 45, 145); break;
		default: break;
	}
	if (flicker) SDL_SetTextureAlphaMod(font, alpha);

	while (message[i] != '\0')
	{
		if (message[i] == '\n')
		{
			Mx = FirstMx;
			My += v_spacing;
			i++;
			continue;
		}
		GetXY(fontID, message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + h_spacing;
		i++;
	}

	if (alpha <= 150) intensify = true;
	if (alpha >= 255) intensify = false;

	SDL_SetTextureColorMod(font, 255, 255, 255);
	if (flicker) SDL_SetTextureAlphaMod(font, 255);

	return Mx - FirstMx - h_spacing;
}

int Font::Write(const int& fontID, int number, int Mx, int My)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return -99;

	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int magnitude = 1;

	// How big is this number? (how many digits is key)
	while (number / (magnitude * 10) != 0)
	{
		// if the loop condition is nonzero, then that means the denominator
		// isn't large enough to reduce the fraction to zero...
		// The fraction reduces to zero IF the denominator exceeds
		// the numerator, which is what we're looking for.
		// EX: First loop does N / 10. If zero, then abs(N) is less than 10 (Magnitude of 10^0, or 1).
		//     Otherwise, next loop does N / 100. If zero, then abs(N) is less than 100. (Mag 10^1, or 10)
		//     Next loop would be N / 1000... And on until the loop ends.
		magnitude *= 10;
	}

	while (magnitude != 0)
	{
		// First, mod the number by current mag*10 to get rid of following digits.
		// Second, divide the resulting number by mag to get rid of leading digits.
		switch ((number % (magnitude * 10)) / magnitude)
		{
			case 0: GetXY(fontID, '0', Xo, Yo, W, H); break;
			case 1: GetXY(fontID, '1', Xo, Yo, W, H); break;
			case 2: GetXY(fontID, '2', Xo, Yo, W, H); break;
			case 3: GetXY(fontID, '3', Xo, Yo, W, H); break;
			case 4: GetXY(fontID, '4', Xo, Yo, W, H); break;
			case 5: GetXY(fontID, '5', Xo, Yo, W, H); break;
			case 6: GetXY(fontID, '6', Xo, Yo, W, H); break;
			case 7: GetXY(fontID, '7', Xo, Yo, W, H); break;
			case 8: GetXY(fontID, '8', Xo, Yo, W, H); break;
			case 9: GetXY(fontID, '9', Xo, Yo, W, H); break;
			default: break;
		}

		if (!CSurface::OnDraw(font, Mx, My, Xo, Yo, W, H))
			return 0;

		Mx += W + h_spacing;
		magnitude /= 10;
	}
	return Mx - FirstMx + W;
}

int Font::Writef(const int& fontID, float number, unsigned int precision, int Mx, int My)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return -99;

	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int magnitude = 1;
	bool negative = false;
	float magnifier = pow(10.0, precision);

	if (number < 0.0)
	{
		negative = true;
		number = -number;
	}

	int truncated = ((magnifier)*(number - (int)(number)));

	// if (truncated == 0) return Write(font, ((int)(number)) * (1 - (2*negative)), Mx, My);

	// How big is this truncated, magnified number? (how many digits is key)
	while (truncated / (magnitude * 10) != 0)
	{
		// if the loop condition is nonzero, then that means the denominator
		// isn't large enough to reduce the fraction to zero...
		// The fraction reduces to zero IF the denominator exceeds
		// the numerator, which is what we're looking for.
		// EX: First loop does N / 10. If zero, then abs(N) is less than 10 (Magnitude of 10^0, or 1).
		//     Otherwise, next loop does N / 100. If zero, then abs(N) is less than 100. (Mag 10^1, or 10)
		//     Next loop would be N / 1000... And on until the loop ends.
		magnitude *= 10;
	}

	// Add a minus first if necessary
	if (negative)
	{
		GetXY(fontID, '-', Xo, Yo, W, H);
		if (!CSurface::OnDraw(font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + h_spacing;
	}

	// Write the integer part of the number, and then add a decimal point
	Mx += Write(fontID, (int)(number), Mx, My);
	GetXY(fontID, '.', Xo, Yo, W, H);
	if (!CSurface::OnDraw(font, Mx, My, Xo, Yo, W, H))
		return 0;
	Mx += W + h_spacing;

	// Add any zeroes after the decimal point
	while (magnitude * 10 < (int)(magnifier))
	{
		GetXY(fontID, '0', Xo, Yo, W, H);
		if (!CSurface::OnDraw(font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + h_spacing;
		magnitude *= 10;
	}

	Mx += Write(fontID, truncated, Mx, My);

	return Mx - FirstMx;
}

char Font::BoxWrite(const int& fontID, char const* message,
	int bX, int bY, int bW, int bH, int tX, int tY, int tW, int tH, int length, int page)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
 	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return '!';

	// Draw the box (container)
	if (!DrawContainer(bX, bY, bW, bH, 'r')) return '!';

	int PageLeft = page;
	int i = 0;
	int char_count = 0;
	int Xo, Yo, W, H;
	int curr_tX = tX;
	int curr_tY = tY;

	while (PageLeft != 0)
	{
		if (message[i++] == '|')
		{
			PageLeft--;
		}
	}

	// Run through the message until it's null-terminated
	while (message[i] != '\0' && message[i] != '|' && char_count < length)
	{
		if (message[i] == '\t' || message[i] == '\f' || message[i] == '\r')
		{
			//
		}
		else if (message[i] == '\n')
		{
			curr_tX = tX;
			curr_tY += v_spacing;
		}
		else
		{
			// Gather info for the current character being printed
			GetXY(fontID, message[i], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > tX + tW)
			{	// no
				curr_tX = tX;
				curr_tY += v_spacing;
			}
			// Draw the current character
			if (!CSurface::OnDraw(font, curr_tX, curr_tY, Xo, Yo, W, H))
				return '!';
			if (message[i] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else curr_tX += W + h_spacing;	// Move the position for the upcoming character
			char_count++;
		}
		i++;
	}
	return message[i];
}

bool Font::TextBox(const int& fontID, char const* message,
	int tX, int tY, int tW, int tH)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return false;

	int i = 0;
	int Xo, Yo, W, H;
	int curr_tX = tX;
	int curr_tY = tY;

	// Run through the message until it's null-terminated
	while (message[i] != '\0')
	{
		if (message[i] == '\t' || message[i] == '\f' || message[i] == '\r')
		{
			//
		}
		else if (message[i] == '\n')
		{
			curr_tX = tX;
			curr_tY += v_spacing;
		}
		else
		{
			// Gather info for the current character being printed
			GetXY(fontID, message[i], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > tX + tW)
			{	// no
				curr_tX = tX;
				curr_tY += v_spacing;
			}
			// Draw the current character
			if (!CSurface::OnDraw(font, curr_tX, curr_tY, Xo, Yo, W, H))
				return false;
			if (message[i] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else curr_tX += W + h_spacing;	// Move the position for the upcoming character
		}
		i++;
	}
	return true;
}

int Font::CenterWrite(const int& fontID, char const* message, int Mx, int My)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL)
	{
		return -99;
	}

	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int Length;

	while (message[i] != '\0')
	{
		GetXY(fontID, message[i], Xo, Yo, W, H);
		Mx += W + h_spacing;
		i++;
	}

	Length = Mx - FirstMx - h_spacing;
	i = 0;
	Mx = FirstMx - (Length / 2);

	while (message[i] != '\0')
	{
		GetXY(fontID, message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(font, Mx, My - (v_spacing / 2), Xo, Yo, W, H))
			return 0;
		Mx += W + h_spacing;
		i++;
	}
	return Length;
}

int Font::CenterWrite(const int& fontID, char const* message, const SDL_Rect* dstR)
{
	int centerX = dstR->x + (dstR->w / 2);
	int centerY = dstR->y + (dstR->h / 2);
	return CenterWrite(fontID, message, centerX, centerY);
}

int Font::NewCenterWrite(const int& fontID, char const* message, const SDL_Rect* dstR, int col)
{
	int centerX = dstR->x + (dstR->w / 2);
	int centerY = dstR->y + (dstR->h / 2);

	int msgWidth = 0;
	int msgHeight = 0;
	// getLineDims(fontID, message, msgWidth, msgHeight);

	// int leftX = centerX - (msgWidth / 2);
	// int topY = centerY - (msgHeight / 2);

	// return Write(fontID, message, col, false, leftX, topY);
	int lineW = 0;
	int lineH = 0;
	int h_spacing, v_spacing;
	GetInfo(fontID, h_spacing, v_spacing);

	msgHeight = getTextHeight(fontID, message, dstR->w);
	int topY = centerY - (msgHeight / 2);

	int i = 0;
	std::string currentLine;
	while (message[i] != '\0')
	{
		if (message[i] == '\n') i++;
		currentLine = getLine(fontID, message, i, dstR->w);
		getLineDims(fontID, currentLine.c_str(), lineW, lineH);
		int leftX = centerX - (lineW / 2);
		Write(fontID, currentLine.c_str(), col, false, leftX, topY);
		topY += lineH + v_spacing;
	}
	return 0;
}

int Font::getTextHeight(const int& fontID, char const* message, int maxWidth)
{
	int h_spacing, v_spacing;
	if (GetInfo(fontID, h_spacing, v_spacing) == NULL) return 0;
	int Xo, Yo, W, lineH;

	GetXY(fontID, 'A', Xo, Yo, W, lineH);

	int tH = 0;
	int i = 0;
	while (message[i] != '\0')
	{
		if (message[i] == '\n') i++;
		tH += lineH + ((bool)(i) * v_spacing);
		getLine(fontID, message, i, maxWidth);
	}
	return tH;
}

std::string Font::getLine(const int& fontID, char const* message, int& iterator, const int& maxWidth)
{
	int h_spacing, v_spacing;
	if (GetInfo(fontID, h_spacing, v_spacing) == NULL) return "";

	int i = iterator;
	int Xo, Yo, W, H;
	std::string lin;
	std::string wrd;
	int linWidth = 0;
	int wrdWidth = 0;
	while (true)
	{
		char sym = message[i];
		if (sym == '\0' || sym == '\n')
		{
			if (wrd != " ")
			{
				lin += wrd;
				linWidth += wrdWidth;
			}
			iterator = i;
			break;
		}

		GetXY(fontID, sym, Xo, Yo, W, H);
		if (linWidth + wrdWidth != 0) W += h_spacing;
		if (linWidth + wrdWidth + W > maxWidth) break;

		if (sym == ' ')
		{
			if (wrd != " ")
			{
				lin += wrd;
				linWidth += wrdWidth;
				iterator = i + 1;
			}
			wrd.clear();
			wrdWidth = 0;
		}
		wrd.push_back(sym);
		wrdWidth += W;

		i++;
	}
	return lin;
}

int Font::NewCenterWrite(const int& fontID, char const* message, const SDL_Point* dstC, int col)
{
	int msgWidth = 0;
	int msgHeight = 0;
	getLineDims(fontID, message, msgWidth, msgHeight);

	int leftX = dstC->x - (msgWidth / 2);
	int topY = dstC->y - (msgHeight / 2);

	return Write(fontID, message, col, false, leftX, topY);
}

void Font::getLineDims(const int& fontID, char const* message, int& msgWidth, int& msgHeight)
{
	int h_spacing, v_spacing;
	if (GetInfo(fontID, h_spacing, v_spacing) == NULL) return;

	int i = 0;
	int Xo, Yo, W, H;
	msgWidth = 0;
	msgHeight = 0;

	while (message[i] != '\0')
	{
		if (i > 0) msgWidth += h_spacing;
		GetXY(fontID, message[i++], Xo, Yo, W, H);
		msgWidth += W;
		if (!msgHeight) msgHeight = H;
	}
}

char Font::CenterBoxWrite(const int& fontID, char const* message,
	int bX, int bY, int bW, int bH, int tX, int length, int page)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return '!';

	// Draw the box (container)
	DrawContainer(bX, bY, bW, bH, 'b');

	int PageLeft = page;
	int i = 0;
	int char_count = 0;
	int Xo, Yo, W, H;
	int curr_tX = tX;
	int curr_tY;
	int tH = v_spacing;

	// This loop places the index, i, at the start of the correct page.
	while (PageLeft != 0)
	{
		if (message[i++] == '|')
		{
			PageLeft--;
		}
	}

	int j = i;	// Let index j also start on the correct page
	// This loop will give us an idea of how tall our page is.
	// With this info, we can properly center the text in the box.
	while (message[j] != '|' && message[j] != '\0') // "Hello\0"
	{
		if (message[j] == '\t' || message[j] == '\f' || message[j] == '\r')
		{
			//
		}
		else if (message[j] == '\n')
		{
			curr_tX = tX;
			tH += v_spacing;
		}
		else
		{
			GetXY(fontID, message[j], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > bX + bW - 8)
			{	// no
				curr_tX = tX;
				tH += v_spacing;
			}
			if (message[j] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else
				curr_tX += W + h_spacing;	// Move the position for the upcoming character
		}
		j++;
	}

	// Assign a value to curr_tY with tH found
	curr_tY = bY + (((bH + (v_spacing / 2)) - tH) / 2) - 1;
	curr_tX = tX;

	// Run through the message until it's NT, at end of page, or exceeds current allowance of print
	while (message[i] != '\0' && message[i] != '|' && char_count < length)
	{
		if (message[i] == '\t' || message[i] == '\f' || message[i] == '\r')
		{
			//
		}
		else if (message[i] == '\n')
		{
			curr_tX = tX;
			curr_tY += v_spacing;
		}
		else
		{
			// Gather info for the current character being printed
			GetXY(fontID, message[i], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > bX + bW - (v_spacing / 2))
			{	// no
				curr_tX = tX;
				curr_tY += v_spacing;
			}
			// Draw the current character
			if (!CSurface::OnDraw(font, curr_tX, curr_tY, Xo, Yo, W, H))
				return '!';
			if (message[i] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else curr_tX += W + h_spacing;	// Move the position for the upcoming character
			char_count++;
		}
		i++;
	}
	return message[i];
}

bool Font::DrawContainer(const int &bX, const int &bY, const int &bW, const int &bH, const char &color)
{
	if (FontControl.Tex_HUD == NULL) return false;

	Uint8 color_mod = 0;
	switch (color)
	{
		case 'b':	break;
		case 'r':	color_mod = 1; break;
		default:	break;
	}

	// Draw the inside of the box (no borders)
	if (!CSurface::OnDraw(FontControl.Tex_HUD, bX + 8, bY + 8, 108 + 8, color_mod * 16 + 8, 1, 1, bW - 16, bH - 16))
		return false;

	// Draw the borders
	CSurface::OnDraw(FontControl.Tex_HUD, bX, bY + 8, 108, color_mod * 16 + 8 - 1, 8, 2, 8, bH - 16);						// left
	CSurface::OnDraw(FontControl.Tex_HUD, bX + bW - 1 - 8, bY + 8, 108 + 8, color_mod * 16 + 8 - 1, 8, 2, 8, bH - 16);	// right
	CSurface::OnDraw(FontControl.Tex_HUD, bX + 8, bY, 108 + 8 - 1, color_mod * 16, 2, 8, bW - 16, 8);						// top
	CSurface::OnDraw(FontControl.Tex_HUD, bX + 8, bY + bH - 1 - 8, 108 + 8 - 1, color_mod * 16 + 8, 2, 8, bW - 16, 8);	// bottom

	// Draw the corners
	CSurface::OnDraw(FontControl.Tex_HUD, bX, bY, 108, color_mod * 16, 8, 8);										// top left
	CSurface::OnDraw(FontControl.Tex_HUD, bX + bW - 1 - 8, bY, 108 + 8, color_mod * 16, 8, 8);					// top right
	CSurface::OnDraw(FontControl.Tex_HUD, bX, bY + bH - 1 - 8, 108, color_mod * 16 + 8, 8, 8);					// bottom left
	CSurface::OnDraw(FontControl.Tex_HUD, bX + bW - 1 - 8, bY + bH - 1 - 8, 108 + 8, color_mod * 16 + 8, 8, 8);	// bottom right

	return true;
}
