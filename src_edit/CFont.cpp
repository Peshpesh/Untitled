#include "CFont.h"

Font Font::FontControl;

Font::Font()
{
	CS_Font = NULL;
	Mini_Font = NULL;

	def_rgb = &fontrgb::black;
	def_ID = 0;
}

bool Font::OnInit()
{
	if ((CS_Font = CSurface::OnLoad("../res/font.png")) == NULL) 	return false;
	if ((Mini_Font = CSurface::OnLoad("../res_edit/minifont.png")) == NULL) 	return false;

	def_ID = FONT_MINI;
	resetFontColor();
	resetFontColor(FONT_DEFAULT);

	return true;
}

void Font::SetFont(const int& fontID)
{
	def_ID = fontID;
}

bool Font::SetColor(const SDL_Color* col)
{
	if (col == NULL || def_rgb == col) return false;

	def_rgb = col;
	return true;
}

void Font::changeFontColor(const int& fontID, const SDL_Color* col)
{
	if (col == NULL) return;
	SDL_Texture* font = GetFont(fontID);
	if (font != NULL) SDL_SetTextureColorMod(font, col->r, col->g, col->b);
}

void Font::resetFontColor(const int& fontID)
{
	changeFontColor(fontID, FontControl.def_rgb);
}

void Font::changeFontColor(const SDL_Color* col)
{
	changeFontColor(FontControl.def_ID, col);
}

void Font::resetFontColor()
{
	resetFontColor(FontControl.def_ID);
}

int Font::Write(const int& fontID, char const* message, int Mx, int My)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
 	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return -99;

	int i = 0;
	int Xo, Yo, W, H;
	const int FirstMx = Mx;

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
		{
			return 0;
		}
		Mx += W + h_spacing;
		i++;
	}
	return Mx - FirstMx - h_spacing;
}

int Font::Write(const int& fontID, char const* message, const SDL_Point* pos)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	int lineH = GetSymH(fontID);
 	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return -2;

	int i = 0;
	const int FirstMx = pos->x;

	SDL_Point symPos = {pos->x, pos->y};
	SDL_Rect symRec;

	while (message[i] != '\0')
	{
		const char sym = message[i++];
		if (sym == '\n')
		{
			symPos.x = FirstMx;
			symPos.y += lineH + v_spacing;
			continue;
		}
		GetXY(fontID, sym, symRec);
		if (!CSurface::OnDraw(font, &symRec, &symPos)) return -1;
		symPos.x += symRec.w + h_spacing;
	}
	return 0;
}

int Font::WriteLine(const int& fontID, char const* line, const SDL_Point* pos)
{
	SDL_Texture* font = NULL;
	int h_spacing = 0;
	int v_spacing = 0;
	if ((font = GetInfo(fontID, h_spacing, v_spacing)) == NULL) return -2;

	int i = 0;

	const int FirstMx = pos->x;
	SDL_Point symPos = {pos->x, pos->y};
	SDL_Rect symRec;

	while (line[i] != '\0' && line[i] != '\n')
	{
		GetXY(fontID, line[i], symRec);
		if (!CSurface::OnDraw(font, &symRec, &symPos)) return -1;
		symPos.x += symRec.w + h_spacing;
		i++;
	}

	return (pos->x - FirstMx - h_spacing);
}

int Font::Write(const int& fontID, char const* message, const SDL_Point* pos, const SDL_Color* col)
{
	changeFontColor(fontID, col);
	int retval = Write(fontID, message, pos);
	resetFontColor(fontID);

	return retval;
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

int Font::NewCenterWrite(const int& fontID, char const* message, const SDL_Rect* dstR, const SDL_Color* col)
{
	changeFontColor(fontID, col);
	int retval = NewCenterWrite(fontID, message, dstR);
	resetFontColor(fontID);

	return retval;
}

int Font::NewCenterWrite(const int& fontID, char const* message, const SDL_Point* dstC, const SDL_Color* col)
{
	changeFontColor(fontID, col);
	int retval = NewCenterWrite(fontID, message, dstC);
	resetFontColor(fontID);

	return retval;
}

int Font::NewCenterWrite(const int& fontID, char const* message, const SDL_Rect* dstR)
{
	int centerX = dstR->x + (dstR->w / 2);
	int centerY = dstR->y + (dstR->h / 2);

	int msgWidth = 0;
	int msgHeight = getTextHeight(fontID, message, dstR->w);

	int lineW = 0;
	int lineH = GetSymH(fontID);
	int v_spacing = GetVSpacing(fontID);

	SDL_Point pos;
	pos.y = centerY - (msgHeight / 2);

	int i = 0;
	std::string currentLine;
	while (message[i] != '\0')
	{
		if (message[i] == '\n') i++;
		currentLine = getLine(fontID, message, i, dstR->w);
		getLineDims(fontID, currentLine.c_str(), lineW);
		pos.x = centerX - (lineW / 2);
		WriteLine(fontID, currentLine.c_str(), &pos);
		pos.y += lineH + v_spacing;
	}

	return 0;
}

int Font::NewCenterWrite(const int& fontID, char const* message, const SDL_Point* dstC)
{
	int msgWidth = 0;
	int msgHeight = GetSymH(fontID);
	getLineDims(fontID, message, msgWidth);

	SDL_Point pos = {dstC->x - (msgWidth / 2), dstC->y - (msgHeight / 2)};

	return WriteLine(fontID, message, &pos);
}

int Font::NewCenterWrite(char const* message, const SDL_Rect* dstR, const SDL_Color* col)
{
	changeFontColor(col);
	int retval = NewCenterWrite(message, dstR);
	resetFontColor();

	return retval;
}

int Font::NewCenterWrite(char const* message, const SDL_Point* dstC, const SDL_Color* col)
{
	changeFontColor(col);
	int retval = NewCenterWrite(message, dstC);
	resetFontColor();

	return retval;
}

int Font::NewCenterWrite(char const* message, const SDL_Rect* dstR)
{
	return NewCenterWrite(FontControl.def_ID, message, dstR);
}

int Font::NewCenterWrite(char const* message, const SDL_Point* dstC)
{
	return NewCenterWrite(FontControl.def_ID, message, dstC);
}

int Font::getTextHeight(const int& fontID, char const* message, int maxWidth)
{
	int h_spacing = GetHSpacing(fontID);
	int v_spacing = GetVSpacing(fontID);
	int lineH = GetSymH(fontID);

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
	int h_spacing = GetHSpacing(fontID);
	int v_spacing = GetVSpacing(fontID);

	int i = iterator;
	SDL_Rect symRec;
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

		GetXY(fontID, sym, symRec);
		if (linWidth + wrdWidth != 0) symRec.w += h_spacing;
		if (linWidth + wrdWidth + symRec.w > maxWidth) break;

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
		wrdWidth += symRec.w;

		i++;
	}
	if (linWidth == 0)
	{
		lin = wrd;
		iterator = i + 1;
	}
	return lin;
}

void Font::getLineDims(const int& fontID, char const* message, int& msgWidth)
{
	int h_spacing = GetHSpacing(fontID);

	int i = 0;
	SDL_Rect symRec;
	msgWidth = 0;

	while (message[i] != '\0')
	{
		if (i > 0) msgWidth += h_spacing;
		GetXY(fontID, message[i++], symRec);
		msgWidth += symRec.w;
	}
}

std::string Font::intToStr(const int& val)
{
	std::string retstr;
	int magnitude = 1;

	// How big is this number? (how many digits is key)
	while (val / (magnitude * 10) != 0)
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
		switch ((val % (magnitude * 10)) / magnitude)
		{
			case 0: retstr.push_back('0'); break;
			case 1: retstr.push_back('1'); break;
			case 2: retstr.push_back('2'); break;
			case 3: retstr.push_back('3'); break;
			case 4: retstr.push_back('4'); break;
			case 5: retstr.push_back('5'); break;
			case 6: retstr.push_back('6'); break;
			case 7: retstr.push_back('7'); break;
			case 8: retstr.push_back('8'); break;
			case 9: retstr.push_back('9'); break;
			default: break;
		}
		magnitude /= 10;
	}
	return retstr;
}
