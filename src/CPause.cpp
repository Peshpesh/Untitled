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
	if (CConfig::control.con_change != CONFIG_NONE) {
    CConfig::control.OnEvent(Event);
    return;
  } CEvent::OnEvent(Event);
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
    case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    case CON_ATTACK: {
      switch (pos) {
				case RESUME: 			menu_kind = pausemenu::MAIN; pos = 0; break;
				case SFX_VOLUME: 	CConfig::control.con_change = CONFIG_SFX; break;
				case BGM_VOLUME: 	CConfig::control.con_change = CONFIG_BGM; break;
				case TYPE_VOLUME: CConfig::control.con_change = CONFIG_TEX; break;
				case AUDIO_OUT: 	CConfig::control.con_change = CONFIG_AUDIOOUT; break;
				case SET_DEFAULT: CConfig::control.reset_audio(); break;
        default: break;
      } break;
    }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

void CPause::eventVideo(const Gamecon& action) {
	using namespace pausemenu::videomenu;
  switch (action) {
    case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    case CON_ATTACK: {
      switch (pos) {
        case RESUME:		menu_kind = pausemenu::MAIN; pos = 0; break;
        case VIDEO_OUT: CConfig::control.con_change = CONFIG_DISPLAY; break;
        default: break;
      } break;
    }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

void CPause::eventQuit(const Gamecon& action) {
	using namespace pausemenu::quitmenu;
  switch (action) {
    case CON_DOWN: if (++pos >= num_options) pos = 0; 		break;
    case CON_UP:   if (--pos < 0) pos = num_options - 1; 	break;
    case CON_ATTACK: {
			if (pos == true) {
				// go to title screen
				call_quit = true;
			} else {
				menu_kind = pausemenu::MAIN; pos = 0; break;
			}
			break;
    }
    case CON_PAUSE: unpause(); break;
    default: break;
  }
}

bool CPause::OnRender() {
	bool retval = false;
	CType::control.SetFont(FONT_MINI);

	CAsset::paletteAlpha(pausemenu::fill_A);
	CAsset::fillScreen();
	CAsset::paletteAlpha(MAX_RGBA);

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
		CType::CenterWrite(opt_list[i], bar, (i != pos) ? f_def : f_hov);
		bar.y += opt_h;
	}
	return true;
}

bool CPause::drawAudio() {
	using namespace pausemenu::audiomenu;
	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, pausemenu::stroke_w, pausemenu::c_col, pausemenu::s_col)) return false;

	SDL_Rect name_bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	CType::CenterWrite(header, name_bar, pausemenu::f_def);

	name_bar.x = name_x;
	name_bar.y += pausemenu::opt_h;
	name_bar.w = name_w;
	SDL_Rect val_bar = {val_x, name_bar.y + (name_bar.h - val_h) / 2, val_w, val_h};
	for (int i = 0; i < num_options; i++) {
		std::string val;
		CType::CenterWrite(opt_list[i], name_bar, (i != pos) ? pausemenu::f_def : pausemenu::f_hov);
		switch (i) {
			case RESUME: 			break;
			case SFX_VOLUME: 	{
				if (!drawVolume(val_bar, CONFIG_SFX, val)) return false;
				break;
			}
			case BGM_VOLUME: 	{
				if (!drawVolume(val_bar, CONFIG_BGM, val)) return false;
				break;
			}
			case TYPE_VOLUME: {
				if (!drawVolume(val_bar, CONFIG_TEX, val)) return false;
				break;
			}
			case AUDIO_OUT:		{
				val = CConfig::control.isStereo() ? "Stereo" : "Mono";
				CType::CenterWrite(val.c_str(), val_bar, pausemenu::f_def);
				break;
			}
			case SET_DEFAULT: break;
		}
		name_bar.y += pausemenu::opt_h;
		val_bar.y += pausemenu::opt_h;
	}
	return true;
}

bool CPause::drawVideo() {
	using namespace pausemenu::videomenu;
	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, pausemenu::stroke_w, pausemenu::c_col, pausemenu::s_col)) return false;

	SDL_Rect name_bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	CType::CenterWrite(header, name_bar, pausemenu::f_def);

	name_bar.x = name_x;
	name_bar.y += pausemenu::opt_h;
	name_bar.w = name_w;
	SDL_Rect val_bar = {val_x, name_bar.y, val_w, pausemenu::opt_h};
	for (int i = 0; i < num_options; i++) {
		std::string val;
		CType::CenterWrite(opt_list[i], name_bar, (i != pos) ? pausemenu::f_def : pausemenu::f_hov);
		switch (i) {
			case RESUME: 			break;
			case VIDEO_OUT:		{
				val = CConfig::control.isFullscreen() ? "Fullscreen" : "Windowed";
				CType::CenterWrite(val.c_str(), val_bar, pausemenu::f_def);
				break;
			}
		}
		name_bar.y += pausemenu::opt_h;
		val_bar.y += pausemenu::opt_h;
	}
	return true;
}

bool CPause::drawQuit() {
	using namespace pausemenu::quitmenu;
	SDL_Rect canvas = {x, y, w, h};
	if (!CAsset::drawStrBox(canvas, pausemenu::stroke_w, c_col, s_col)) return false;

	SDL_Rect bar = {x, y, pausemenu::opt_w, pausemenu::opt_h};
	CType::CenterWrite(header, bar, f_def);
	bar.y += pausemenu::opt_h;

	for (int i = 0; i < num_options; i++) {
		CType::CenterWrite(opt_list[i], bar, (i != pos) ? f_def : f_hov);
		bar.y += pausemenu::opt_h;
	}
	return true;
}

bool CPause::drawVolume(const SDL_Rect& val_bar, const Configflag& vol_type, std::string& val) {
	bool modify = (CConfig::control.con_change == vol_type);
	short vol = CConfig::control.getVolume(vol_type);
	double fill_frac = vol / (double)(MAX_VOLUME);
	SDL_Rect fill_bar = {val_bar.x, val_bar.y, fill_frac * val_bar.w, val_bar.h};
	if (!CAsset::drawBoxFill(val_bar,	pausemenu::audiomenu::empty_col)) return false;
	if (!CAsset::drawBoxFill(fill_bar, modify ?
		pausemenu::audiomenu::mod_col :
		pausemenu::audiomenu::fill_col)) return false;
	val = CAsset::intToStr(vol);
	CType::CenterWrite(val.c_str(), val_bar, pausemenu::audiomenu::ftex_col);
	return true;
}
