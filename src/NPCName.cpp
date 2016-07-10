#include "CME_NPC.h"

enum Common_NPC
{
	YOSHI = 0,
	MAINCHAR,
	EVILMAIN
};

// Note: NPCS after common must start in ID# after where common ends
enum Debug_NPC
{
	WSTAR = 3,
	BSTAR,
	BARS, BOX, SPIKEFALL, BLDSPK_UP,
	HEART, AMYTHYST, ACIDBALL, DOOR, SAVEPOINT, SIGN
};

void CME_NPC::CWrite_Common(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	switch (NPC_ID)
	{
	/*ID*/
	/*00*/ case YOSHI: Font::CenterWrite(renderer, font, "YOSHI", X, Y); break;
	/*01*/ case MAINCHAR: Font::CenterWrite(renderer, font, "MAINCHAR", X, Y); break;
	/*02*/ case EVILMAIN: Font::CenterWrite(renderer, font, "EVILMAIN", X, Y); break;
	default: break;
	}
}

void CME_NPC::CWrite_Debug(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	switch (NPC_ID)
	{
	/*ID*/ 
	/*03*/ case WSTAR: Font::CenterWrite(renderer, font, "WHITE STAR", X, Y); break;
	/*04*/ case BSTAR: Font::CenterWrite(renderer, font, "BLACK STAR", X, Y); break;
	/*05*/ case BARS: Font::CenterWrite(renderer, font, "BARS", X, Y); break;
	/*06*/ case BOX: Font::CenterWrite(renderer, font, "BOX", X, Y); break;
	/*07*/ case SPIKEFALL: Font::CenterWrite(renderer, font, "SPIKEFALL", X, Y); break;
	/*08*/ case BLDSPK_UP: Font::CenterWrite(renderer, font, "BLDSPK UP", X, Y); break;
	/*09*/ case HEART: Font::CenterWrite(renderer, font, "HEART", X, Y); break;
	/*10*/ case AMYTHYST: Font::CenterWrite(renderer, font, "AMYTHYST", X, Y); break;
	/*11*/ case ACIDBALL: Font::CenterWrite(renderer, font, "ACIDBALL", X, Y); break;
	/*12*/ case DOOR: Font::CenterWrite(renderer, font, "DOOR", X, Y); break;
	/*13*/ case SAVEPOINT: Font::CenterWrite(renderer, font, "SAVEPT", X, Y); break;
	/*14*/ case SIGN: Font::CenterWrite(renderer, font, "SIGN", X, Y); break;
	default: break;
	}
}

