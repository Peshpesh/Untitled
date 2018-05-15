#ifndef _C_PAUSE_H_
#define _C_PAUSE_H_

#include "CAsset.h"
#include "CType.h"
#include "CEvent.h"
#include "CControls.h"
#include "CConfig.h"

namespace pausemenu {
	enum menus {
    MAIN = 0,
    ADJUST_AUDIO,
    ADJUST_VIDEO,
    QUIT_GAME,
  };
	namespace audiomenu {
		//
	};
	namespace videomenu {
		//
	};
	namespace quitmenu {
		//
	};
};

class CPause : public CEvent {
	CPause();

  short menu_kind;
  short pos;

public:
  static CPause control;
  // bool call_terminate;

  void OnEvent(SDL_Event* Event);

  bool OnRender();

private:
	void reinit();
};
#endif
