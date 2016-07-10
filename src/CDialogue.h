#ifndef _CDIALOGUE_H_
#define _CDIALOGUE_H_

#include "CFPS.h"
#include "Font.h"

class CDialogue {

public:
	static CDialogue DiaControl;
	CDialogue();

	int	OnSpeech(SDL_Renderer* renderer, char* message);

public:
	int		Timer;			// How much time has passed since the start of typing current page
	int		Length;			// How many characters allowed to type on current page
	int		Pagenum;		// Page number
	int		RecordFPS;	// FPS on record
	bool	FastType;		// True if user is advancing thru dialogue
	bool	Pageend;		// True if waiting at end of page
	bool	Typing;			// True if typing a page
	bool	Done;				// True if passed message is finished
};
#endif
