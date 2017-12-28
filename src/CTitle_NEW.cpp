#include "CTitle.h"

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

  switch (menu) {
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

}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//                                                                            //
//                                                                            //
//                                                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool CTitle::drawMainMenu() {
  using namespace Title;

  while (int i = 0; i < num_options; i++) {

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
