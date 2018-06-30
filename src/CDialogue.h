#ifndef _C_DIALOGUE_H_
#define _C_DIALOGUE_H_

#include <string>
#include <vector>

#include "CFPS.h"
#include "CAsset.h"
#include "CType.h"
#include "CSound.h"
#include "CEvent.h"
#include "CInterrupt.h"
#include "CControls.h"

struct CPhrase {
  std::string name;
  std::string text;
  unsigned int text_rate; // char per ms typed to screen
  int idle_time;
};

class CDialogue : public CEvent {
  CDialogue();

private:
  unsigned long long init_time; // SDL_ticks at phrase init

private:
  void resetTimer();

  // int		Timer;			// How much time has passed since the start of typing current page
  // int		Length;			// How many characters allowed to type on current page
  // int		Pagenum;		// Page number
  // int		RecordFPS;	// FPS on record
  // bool	FastType;		// True if user is advancing thru dialogue
  // bool	Pageend;		// True if waiting at end of page
  // bool	Typing;			// True if typing a page
  // bool	Done;				// True if passed message is finished

public:
  static CDialogue control;
  static std::vector<CPhrase> convo;

  void OnEvent(SDL_Event* Event);

  void OnLoop();

  void OnRender();
};

#endif
