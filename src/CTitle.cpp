#include "CTitle.h"

CTitle CTitle::control;

CTitle::CTitle() {
  OnInit();
}

void CTitle::OnInit() {
  menu_kind = Title::MAIN;
  pos = 0;
}

void CTitle::OnEvent(SDL_Event* Event) {
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
  switch (sym) {
    case SDLK_DOWN: {
      if (++pos >= getNumOptions()) pos = 0;
      break;
    }
    case SDLK_UP: {
      if (--pos < 0) pos = getNumOptions() - 1;
      break;
    }
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
    case Title::OPTIONS:    break;
  }
  return val;
}
