#include "CPause.h"

CPause CPause::control;

CPause::CPause() {
	reinit();
}

void CPause::unpause() {
	CInterrupt::removeFlag(INTRPT_PAUSE);
	reinit();
}

void CPause::reinit() {
	menu_kind = pausemenu::MAIN;
	pos = 0;
	call_quit = false;
}

void CPause::OnEvent(SDL_Event* Event) {
	CEvent::OnEvent(Event);
}

void CPause::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  Gamecon action = CControls::handler.getAction(sym, mod);

  if (action != CON_NONE) {
    switch (menu_kind) {
      case pausemenu::MAIN:       		eventMain(action); 		break;
      case pausemenu::ADJUST_AUDIO:   eventAudio(action);  	break;
      case pausemenu::ADJUST_VIDEO:  	eventVideo(action); 	break;
      case pausemenu::QUIT_GAME:    	eventQuit(action);  	break;
      default: break;
    }
  }
}

void CPause::eventMain(const Gamecon& action) {
	using namespace pausemenu;
  switch (action) {
    case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    case CON_ATTACK: {
      switch (pos) {
        case RESUME:     		unpause(); break;
        case AUDIO_MENU:    menu_kind = ADJUST_AUDIO; pos = 0; break;
        case VIDEO_MENU: 		menu_kind = ADJUST_VIDEO; pos = 0; break;
        case QUIT_MENU:    	menu_kind = QUIT_GAME; pos = 0; break;
        default: break;
      } break;
    }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

void CPause::eventAudio(const Gamecon& action) {

}

void CPause::eventVideo(const Gamecon& action) {

}

void CPause::eventQuit(const Gamecon& action) {

}

bool CPause::OnRender() {
	return true;
}
