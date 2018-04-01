#include "CTitle.h"

CTitle CTitle::control;

CTitle::CTitle() {
  call_terminate = false;
  OnInit();
}

void CTitle::OnInit() {
  difficulty = 0;
  sel_difficulty = false;
  menu_kind = Title::MAIN;
  pos = 0;
}

void CTitle::OnLoop() {
	CTransition::control.OnLoop();
}

void CTitle::OnCleanup() {

}

void CTitle::returnToMain() {
  menu_kind = Title::MAIN; pos = 0;
}

short CTitle::getNumOptions() {
  short val = 0;
  switch (menu_kind) {
    case Title::MAIN:       val = Title::num_options; break;
    case Title::NEW_GAME:   val = Title::pick_game::num_options; break;
    case Title::LOAD_GAME:  val = Title::pick_game::num_options; break;
    case Title::OPTIONS:    val = Title::options::num_options; break;
  }
  return val;
}
