#include "Font.h"

Font Font::FontControl;

Font::Font()
{
	Tex_Font = NULL;
	Tex_HUD = NULL;
}

bool Font::OnInit(SDL_Renderer* renderer)
{
	if ((Tex_Font = CSurface::OnLoad("../res/font.png", renderer)) == NULL)
		return false;

	if ((Tex_HUD = CSurface::OnLoad("../res/HUD.png", renderer)) == NULL)
		return false;

	return true;
}

// Takes in a queried symbol, passes X and Y coords
// where to find the queried symbol in font.png
void Font::GetXY(char symbol, int& X, int& Y, int& W, int& H)
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
		case ' ': X = 53; Y = 60;  W = 6;  H = 14; break;   // this one will probably have to change in the future
		default:  X = 0;  Y = 0;   W = 0;  H = 0;  break;
	}
}

int Font::Write(SDL_Renderer* renderer, SDL_Texture* font, char* message, int Mx, int My)
{
	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;

	while (message[i] != '\0')
	{
		if (message[i] == '\n')
		{
			Mx = FirstMx;
			My += 16;
			i++;
			continue;
		}
		GetXY(message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		i++;
	}
	return Mx - FirstMx - 2;
}

int Font::Write(SDL_Renderer* renderer, SDL_Texture* font, char* message, int color, bool flicker, int Mx, int My)
{
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
			My += 16;
			i++;
			continue;
		}
		GetXY(message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		i++;
	}

	if (alpha <= 150) intensify = true;
	if (alpha >= 255) intensify = false;

	SDL_SetTextureColorMod(font, 255, 255, 255);
	if (flicker) SDL_SetTextureAlphaMod(font, 255);

	return Mx - FirstMx - 2;
}

int Font::Write(SDL_Renderer* renderer, SDL_Texture* font, int number, int Mx, int My)
{
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
			case 0: GetXY('0', Xo, Yo, W, H); break;
			case 1: GetXY('1', Xo, Yo, W, H); break;
			case 2: GetXY('2', Xo, Yo, W, H); break;
			case 3: GetXY('3', Xo, Yo, W, H); break;
			case 4: GetXY('4', Xo, Yo, W, H); break;
			case 5: GetXY('5', Xo, Yo, W, H); break;
			case 6: GetXY('6', Xo, Yo, W, H); break;
			case 7: GetXY('7', Xo, Yo, W, H); break;
			case 8: GetXY('8', Xo, Yo, W, H); break;
			case 9: GetXY('9', Xo, Yo, W, H); break;
			default: break;
		}

		if (!CSurface::OnDraw(renderer, font, Mx, My, Xo, Yo, W, H))
			return 0;

		Mx += W + 2;
		magnitude /= 10;
	}
	return Mx - FirstMx;
}

char Font::BoxWrite(SDL_Renderer* renderer, SDL_Texture* font, char* message,
	int bX, int bY, int bW, int bH, int tX, int tY, int tW, int tH, int length, int page)
{
	// Draw the box (container)
	if (!DrawContainer(renderer, bX, bY, bW, bH, 'r')) return '!';

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
			curr_tY += 20;
		}
		else
		{
			// Gather info for the current character being printed
			GetXY(message[i], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > tX + tW)
			{	// no
				curr_tX = tX;
				curr_tY += 20;
			}
			// Draw the current character
			if (!CSurface::OnDraw(renderer, font, curr_tX, curr_tY, Xo, Yo, W, H))
				return '!';
			if (message[i] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else curr_tX += W + 2;	// Move the position for the upcoming character
			char_count++;
		}
		i++;
	}
	return message[i];
}

int Font::CenterWrite(SDL_Renderer* renderer, SDL_Texture* font, char* message, int Mx, int My)
{
	int i = 0;
	int Xo, Yo, W, H;
	int FirstMx = Mx;
	int Length;

	while (message[i] != '\0')
	{
		GetXY(message[i], Xo, Yo, W, H);
		Mx += W + 2;
		i++;
	}

	Length = Mx - FirstMx - 2;
	i = 0;
	Mx = FirstMx - (Length / 2);

	while (message[i] != '\0')
	{
		GetXY(message[i], Xo, Yo, W, H);
		if (!CSurface::OnDraw(renderer, font, Mx, My - 7, Xo, Yo, W, H))
			return 0;
		Mx += W + 2;
		i++;
	}
	return Length;
}


char Font::CenterBoxWrite(SDL_Renderer* renderer, SDL_Texture* font, char* message,
	int bX, int bY, int bW, int bH, int tX, int length, int page)
{
	// Draw the box (container)
	DrawContainer(renderer, bX, bY, bW, bH, 'b');

	int PageLeft = page;
	int i = 0;
	int char_count = 0;
	int Xo, Yo, W, H;
	int curr_tX = tX;
	int curr_tY;
	int tH = 20;

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
			tH += 20;
		}
		else
		{
			GetXY(message[j], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > bX + bW - 8)
			{	// no
				curr_tX = tX;
				tH += 20;
			}
			if (message[j] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else
				curr_tX += W + 2;	// Move the position for the upcoming character
		}
		j++;
	}

	// Assign a value to curr_tY with tH found
	curr_tY = bY + (((bH + 8) - tH) / 2) - 1;
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
			curr_tY += 20;
		}
		else
		{
			// Gather info for the current character being printed
			GetXY(message[i], Xo, Yo, W, H);
			// Can the character fit on the line?
			if (curr_tX + W > bX + bW - 8)
			{	// no
				curr_tX = tX;
				curr_tY += 20;
			}
			// Draw the current character
			if (!CSurface::OnDraw(renderer, font, curr_tX, curr_tY, Xo, Yo, W, H))
				return '!';
			if (message[i] == ' ' && curr_tX == tX)
			{
				// Do nothing if the first character in a line is a space
			}
			else curr_tX += W + 2;	// Move the position for the upcoming character
			char_count++;
		}
		i++;
	}
	return message[i];
}

bool Font::DrawContainer(SDL_Renderer* renderer, const int &bX, const int &bY, const int &bW, const int &bH, const char &color)
{
	if (FontControl.Tex_HUD == NULL || renderer == NULL) return false;

	Uint8 color_mod = 0;
	switch (color)
	{
		case 'b':	break;
		case 'r':	color_mod = 1; break;
		default:	break;
	}

	// Draw the inside of the box (no borders)
	if (!CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX + 8, bY + 8, 108 + 8, color_mod * 16 + 8, 1, 1, bW - 16, bH - 16))
		return false;

	// Draw the borders
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX, bY + 8, 108, color_mod * 16 + 8 - 1, 8, 2, 8, bH - 16);						// left
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX + bW - 1 - 8, bY + 8, 108 + 8, color_mod * 16 + 8 - 1, 8, 2, 8, bH - 16);	// right
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX + 8, bY, 108 + 8 - 1, color_mod * 16, 2, 8, bW - 16, 8);						// top
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX + 8, bY + bH - 1 - 8, 108 + 8 - 1, color_mod * 16 + 8, 2, 8, bW - 16, 8);	// bottom

	// Draw the corners
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX, bY, 108, color_mod * 16, 8, 8);										// top left
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX + bW - 1 - 8, bY, 108 + 8, color_mod * 16, 8, 8);					// top right
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX, bY + bH - 1 - 8, 108, color_mod * 16 + 8, 8, 8);					// bottom left
	CSurface::OnDraw(renderer, FontControl.Tex_HUD, bX + bW - 1 - 8, bY + bH - 1 - 8, 108 + 8, color_mod * 16 + 8, 8, 8);	// bottom right

	return true;
}
