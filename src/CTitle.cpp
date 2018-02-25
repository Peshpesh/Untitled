#include "CTitle.h"

CTitle CTitle::control;

CTitle::CTitle() {
  call_terminate = false;
  OnInit();
}

void CTitle::OnInit() {
  menu_kind = Title::MAIN;
  pos = 0;
}

void CTitle::OnEvent(SDL_Event* Event) {
  if (CControls::handler.con_change != CON_NONE) {
    CControls::handler.OnEvent(Event);
    return;
  } else if (CConfig::control.con_change != CONFIG_NONE) {
    CConfig::control.OnEvent(Event);
    return;
  }
  CEvent::OnEvent(Event);
}

bool CTitle::OnRender() {
  bool retval = false;
  CType::control.SetFont(FONT_MINI);

  switch (menu_kind) {
    case Title::MAIN:       retval = drawMainMenu(); break;
    case Title::NEW_GAME:   retval = drawNewGame();  break;
    case Title::LOAD_GAME:  retval = drawLoadGame(); break;
    case Title::OPTIONS:    retval = drawOptions();  break;
    default: break;
  }

  return retval;
}

void CTitle::OnLoop() {

}

void CTitle::OnCleanup() {

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//                                                                            //
//                                                                            //
//                                                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

void CTitle::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  Gamecon action = CControls::handler.getAction(sym, mod);

  if (action != CON_NONE) {
    switch (menu_kind) {
      case Title::MAIN:       eventTitle(action); break;
      case Title::NEW_GAME:   eventNewGame(action);  break;
      case Title::LOAD_GAME:  eventLoadGame(action); break;
      case Title::OPTIONS:    eventOptions(action);  break;
      default: break;
    }
  }
}

void CTitle::eventTitle(const Gamecon& action) {
  using namespace Title;
  switch (action) {
    case CON_DOWN: if (++pos >= getNumOptions()) pos = 0;    break;
    case CON_UP:   if (--pos < 0) pos = getNumOptions() - 1; break;
    case CON_ATTACK: {
      switch (pos) {
        case decision::DEC_NEW:     menu_kind = Title::NEW_GAME;  pos = 0; break;
        case decision::DEC_LOAD:    menu_kind = Title::LOAD_GAME; pos = 0; break;
        case decision::DEC_OPTIONS: menu_kind = Title::OPTIONS;   pos = 0; break;
        case decision::DEC_QUIT:    call_terminate = true;        break;
        default:                    break;
      }
      break;
    }
    case CON_PAUSE: {
      switch (pos) {
        case decision::DEC_NEW:     menu_kind = Title::NEW_GAME;  pos = 0; break;
        case decision::DEC_LOAD:    menu_kind = Title::LOAD_GAME; pos = 0; break;
        case decision::DEC_OPTIONS: menu_kind = Title::OPTIONS;   pos = 0; break;
        case decision::DEC_QUIT:    call_terminate = true;        break;
        default:                    break;
      }
      break;
    }
    default: break;
  }
}
void CTitle::eventNewGame(const Gamecon& action) {
  //
}
void CTitle::eventLoadGame(const Gamecon& action) {
  //
}
void CTitle::eventOptions(const Gamecon& action) {
  using namespace Title::options;

  switch (action) {
    case CON_DOWN: if (++pos >= getNumOptions()) pos = 0;    break;
    case CON_UP:   if (--pos < 0) pos = getNumOptions() - 1; break;
    case CON_ATTACK: {
      if (pos < num_controls) CControls::handler.con_change = controls_list[pos];
      else CConfig::control.con_change = config_list[pos - num_controls];
      break;
    }
    case CON_PAUSE: {
      if (pos < num_controls) CControls::handler.con_change = controls_list[pos];
      else CConfig::control.con_change = config_list[pos - num_controls];
      break;
    }
    case CON_JUMP: menu_kind = Title::MAIN; pos = 0; break;
    default: break;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//                                                                            //
//                                                                            //
//                                                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool CTitle::drawMainMenu() {
  using namespace Title;

  SDL_Rect bar = {x, y, w, dy};

  for (int i = 0; i < num_options; i++) {
    CAsset::drawStrBox(bar, stroke_w, (i != pos) ? o_def : o_hov);
    CType::NewCenterWrite(opt_list[i], bar, (i != pos) ? f_def : f_hov);
    bar.x += dx;
    bar.y += dy;
  }
  return true;
}

bool CTitle::drawNewGame() {
  using namespace Title::new_game;
  return true;
}

bool CTitle::drawLoadGame() {
  using namespace Title::load_game;
  return true;
}

bool CTitle::drawOptions() {
  using namespace Title::options;

  SDL_Rect l_bar = {x, y, name_w, dy};
  SDL_Rect r_bar = {x + name_w, y, val_w, dy};

  for (int i = 0; i < num_controls; i++) {
    bool modify = CControls::handler.con_change != CON_NONE;
    const SDL_Color* f_col = (i != pos) ? f_def : (modify ? f_act : f_hov);
    const SDL_Point* o_col = (i != pos) ? o_def : (modify ? o_act : o_hov);
    CAsset::drawStrBox(l_bar, stroke_w, o_col);
    CAsset::drawStrBox(r_bar, stroke_w, o_col);
    CType::NewCenterWrite(controls_text[i], l_bar, f_col);
    CType::NewCenterWrite(
      (char*)(SDL_GetKeyName(CControls::handler.getAssignKey(controls_list[i]))), r_bar, f_col);
    l_bar.x += dx; r_bar.x += dx;
    l_bar.y += dy; r_bar.y += dy;
  }

  for (int i = 0; i < num_config; i++) {
    bool modify = CConfig::control.con_change != CONFIG_NONE;
    const SDL_Color* f_col = (i != pos - num_controls) ? f_def : (modify ? f_act : f_hov);
    const SDL_Point* o_col = (i != pos - num_controls) ? o_def : (modify ? o_act : o_hov);
    CAsset::drawStrBox(l_bar, stroke_w, o_col);
    CAsset::drawStrBox(r_bar, stroke_w, o_col);
    CType::NewCenterWrite(config_text[i], l_bar, f_col);

    std::string val;
    if (config_list[i] == CONFIG_SFX || config_list[i] == CONFIG_BGM || config_list[i] == CONFIG_TEX) {
      double fill_fract = CConfig::control.getVolume(config_list[i]) / (double)(MAX_VOLUME);
      SDL_Rect bar_fill = {r_bar.x + stroke_w, r_bar.y + stroke_w, fill_fract * (r_bar.w - (stroke_w * 2)), r_bar.h - (stroke_w * 2)};
      CAsset::drawBoxFill(bar_fill, fill_col);
      val = CType::intToStr(CConfig::control.getVolume(config_list[i]));
    } else if (config_list[i] == CONFIG_AUDIOOUT) {
      if (CConfig::control.isStereo()) val = "Stereo";
      else val = "Mono";
    } else if (config_list[i] == CONFIG_DISPLAY) {
      if (CConfig::control.isFullscreen()) val = "Fullscreen";
      else val = "Windowed";
    } CType::NewCenterWrite(val.c_str(), r_bar, f_col);
    l_bar.x += dx; r_bar.x += dx;
    l_bar.y += dy; r_bar.y += dy;
  }

  return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//                                                                            //
//                                                                            //
//                                                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

short CTitle::getNumOptions() {
  short val = 0;
  switch (menu_kind) {
    case Title::MAIN:       val = Title::num_options; break;
    case Title::NEW_GAME:   break;
    case Title::LOAD_GAME:  break;
    case Title::OPTIONS:    val = Title::options::num_options; break;
  }
  return val;
}
