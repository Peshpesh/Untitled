#include "CDialogue.h"

CDialogue CDialogue::DiaControl;

CDialogue::CDialogue()
{
	Timer = 0;
	Length = 0;
	Pagenum = 0;
	Pageend = false;
	Typing = true;
	Done = false;
	FastType = false;
	RecordFPS = 0;
}

int CDialogue::OnSpeech(SDL_Renderer* renderer, char const* message)
{
	if (RecordFPS == 0) RecordFPS = CFPS::FPSControl.GetFPS();

	if (Typing)	// The scene dialogue is still typing to the window.
	{
		if (!FastType)	// If user has not indicated they want to advance through the dialogue
		{
			Timer++;
			Length = Timer / (RecordFPS / 20);
		}
		else	// User has indicated they want to skip dialogue
		{
			Length = 1000;
			FastType = false;
		}
	}
	else if (FastType)
	{
		FastType = false;
		Typing = true;
		Length = Timer = 0;
		if (!Done)	// Not typing, but the dialogue isn't finished (more pages)
		{
			Pagenum++;
		}
		else	// Dialogue is finished and user wants to end the scene
		{
			Pagenum = RecordFPS = 0;
			Pageend = Done = false;
			return 0;
		}
	}
	switch (Font::CenterBoxWrite(renderer, FONT_DEFAULT,
		message, 100, 300, 300, 150, 115, Length, Pagenum))
	{
		case '|':
		{
			Typing = false;
			break;
		}
		case '\0':
		{
			Typing = false;
			Done = true;
		}
		case '!':
		{
			return -1;
			break;
		}
		default: break;
	}
	return 1;
}
