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
	using namespace pausemenu::audiomenu;
  switch (action) {
    // case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    // case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    // case CON_ATTACK: {
    //   switch (pos) {
    //     case RESUME:     		unpause(); break;
    //     case AUDIO_MENU:    menu_kind = ADJUST_AUDIO; pos = 0; break;
    //     case VIDEO_MENU: 		menu_kind = ADJUST_VIDEO; pos = 0; break;
    //     case QUIT_MENU:    	menu_kind = QUIT_GAME; pos = 0; break;
    //     default: break;
    //   } break;
    // }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

void CPause::eventVideo(const Gamecon& action) {
	using namespace pausemenu::videomenu;
  switch (action) {
    // case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    // case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    // case CON_ATTACK: {
    //   switch (pos) {
    //     case RESUME:     		unpause(); break;
    //     case AUDIO_MENU:    menu_kind = ADJUST_AUDIO; pos = 0; break;
    //     case VIDEO_MENU: 		menu_kind = ADJUST_VIDEO; pos = 0; break;
    //     case QUIT_MENU:    	menu_kind = QUIT_GAME; pos = 0; break;
    //     default: break;
    //   } break;
    // }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

void CPause::eventQuit(const Gamecon& action) {
	using namespace pausemenu::quitmenu;
  switch (action) {
    // case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    // case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    // case CON_ATTACK: {
    //   switch (pos) {
    //     case RESUME:     		unpause(); break;
    //     case AUDIO_MENU:    menu_kind = ADJUST_AUDIO; pos = 0; break;
    //     case VIDEO_MENU: 		menu_kind = ADJUST_VIDEO; pos = 0; break;
    //     case QUIT_MENU:    	menu_kind = QUIT_GAME; pos = 0; break;
    //     default: break;
    //   } break;
    // }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

bool CPause::OnRender() {
	bool retval = false;
	CType::control.SetFont(FONT_MINI);

	switch (menu_kind) {
		case pausemenu::MAIN:       		retval = drawMain(); 	break;
		case pausemenu::ADJUST_AUDIO:   retval = drawAudio(); break;
		case pausemenu::ADJUST_VIDEO:  	retval = drawVideo(); break;
		case pausemenu::QUIT_GAME:    	retval = drawQuit();  break;
		default: break;
	}
	return retval;
}

bool CPause::drawMain() {
	using namespace pausemenu;

	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, stroke_w, c_col, s_col)) return false;

	SDL_Rect bar = {x, y, opt_w, opt_h};
	for (int i = 0; i < num_options; i++) {
		CType::NewCenterWrite(opt_list[i], bar, (i != pos) ? f_def : f_hov);
		bar.y += opt_h;
	}
	return true;
}

bool CPause::drawAudio() {
	using namespace pausemenu::audiomenu;
	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, pausemenu::stroke_w, pausemenu::c_col, pausemenu::s_col)) return false;

	SDL_Rect bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	CType::NewCenterWrite(header, bar, pausemenu::f_def);
	bar.y += pausemenu::opt_h;

	for (int i = 0; i < num_options; i++) {
		CType::NewCenterWrite(opt_list[i], bar, (i != pos) ? pausemenu::f_def : pausemenu::f_hov);
		bar.y += pausemenu::opt_h;
	}
	return true;
}

bool CPause::drawVideo() {
	using namespace pausemenu::videomenu;
	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, pausemenu::stroke_w, pausemenu::c_col, pausemenu::s_col)) return false;

	SDL_Rect bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	CType::NewCenterWrite(header, bar, pausemenu::f_def);
	bar.y += pausemenu::opt_h;

	SDL_Rect bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	for (int i = 0; i < num_options; i++) {
		CType::NewCenterWrite(opt_list[i], bar, (i != pos) ? pausemenu::f_def : pausemenu::f_hov);
		bar.y += pausemenu::opt_h;
	}
	return true;
}

bool CPause::drawQuit() {
	using namespace pausemenu::quitmenu;
	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, pausemenu::stroke_w, pausemenu::c_col, pausemenu::s_col)) return false;

	SDL_Rect bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	CType::NewCenterWrite(header, bar, pausemenu::f_def);
	bar.y += pausemenu::opt_h;

	SDL_Rect bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	for (int i = 0; i < num_options; i++) {
		CType::NewCenterWrite(opt_list[i], bar, (i != pos) ? pausemenu::f_def : pausemenu::f_hov);
		bar.y += pausemenu::opt_h;
	}
	return true;
}
