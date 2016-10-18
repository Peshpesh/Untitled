#include "CME_NPC.h"

// enum Common_NPC
// {
// 	YOSHI = 0,
// 	MAINCHAR,
// 	EVILMAIN,
// 	BOMB,
// 	EXPLODE
// };
//
// // Note: NPCS after common must start in ID# after where common ends
// enum Debug_NPC
// {
// 	WSTAR = 5,
// 	BSTAR,
// 	BARS, BOX, SPIKEFALL, BLDSPK_UP,
// 	HEART, AMYTHYST, ACIDBALL, DOOR, SAVEPOINT, SIGN
// };

void CME_NPC::CWrite_Common(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	switch (NPC_ID)
	{
	/*ID*/
	/*00*/ case YOSHI: Font::Write(renderer, font, "YOSHI", X, Y); break;
	/*01*/ case MAINCHAR: Font::Write(renderer, font, "MAINCHAR", X, Y); break;
	/*02*/ case EVILMAIN: Font::Write(renderer, font, "EVILMAIN", X, Y); break;
	case BOMB: Font::Write(renderer, font, "BOMB", X, Y); break;
	case EXPLODE: Font::Write(renderer, font, "EXPLODE", X, Y); break;
	default: break;
	}
}

void CME_NPC::CWrite_Debug(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	switch (NPC_ID)
	{
	/*ID*/
	/*03*/ case WSTAR: Font::Write(renderer, font, "WHITE STAR", X, Y); break;
	/*04*/ case BSTAR: Font::Write(renderer, font, "BLACK STAR", X, Y); break;
	/*05*/ case BARS: Font::Write(renderer, font, "BARS", X, Y); break;
	/*06*/ case BOX: Font::Write(renderer, font, "BOX", X, Y); break;
	/*07*/ case SPIKEFALL: Font::Write(renderer, font, "SPIKEFALL", X, Y); break;
	/*08*/ case BLDSPK_UP: Font::Write(renderer, font, "BLDSPK UP", X, Y); break;
	/*09*/ case HEART: Font::Write(renderer, font, "HEART", X, Y); break;
	/*10*/ case AMYTHYST: Font::Write(renderer, font, "AMYTHYST", X, Y); break;
	/*11*/ case ACIDBALL: Font::Write(renderer, font, "ACIDBALL", X, Y); break;
	/*12*/ case DOOR: Font::Write(renderer, font, "DOOR", X, Y); break;
	/*13*/ case SVPT: Font::Write(renderer, font, "SAVEPT", X, Y); break;
	/*14*/ case SIGN: Font::Write(renderer, font, "SIGN", X, Y); break;
	default: break;
	}
}
