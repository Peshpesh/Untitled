#include "CTitle.h"

void CTitle::OnEvent(SDL_Event* Event) {
  if (CTransition::control.isActive()) return;

  if (CControls::handler.con_change != CON_NONE) {
    CControls::handler.OnEvent(Event);
    return;
  } else if (CConfig::control.con_change != CONFIG_NONE) {
    CConfig::control.OnEvent(Event);
    return;
  }
  CEvent::OnEvent(Event);
}

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
    case CON_DOWN: {
      if (++pos >= getNumOptions()) pos = 0;
      else if (pos == decision::DEC_LOAD && !CGameIO::control.getNumSavedGames()) ++pos;
      break;
    }
    case CON_UP: {
      if (--pos < 0) pos = getNumOptions() - 1;
      else if (pos == decision::DEC_LOAD && !CGameIO::control.getNumSavedGames()) --pos;
      break;
    }
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
  using namespace Title::pick_game;

  if (sel_difficulty) {
    if (handleDifficulty(action)) {
      // make new game with current difficulty value
      if (!handleNewGame()) {
        // error
      } else {

      }
    }
    return;
  }

  switch (action) {
    case CON_DOWN:    if (++pos >= getNumOptions()) pos = 0;    break;
    case CON_UP:      if (--pos < 0) pos = getNumOptions() - 1; break;
    case CON_ATTACK:  {
      if (pos < slot::num) sel_difficulty = true;
      else returnToMain();
      break;
    }
    case CON_PAUSE:   {
      if (pos < slot::num) sel_difficulty = true;
      else returnToMain();
      break;
    }
    case CON_DEFEND:  returnToMain(); break;
    case CON_JUMP:    returnToMain(); break;
    default:          break;
  }
}

void CTitle::eventLoadGame(const Gamecon& action) {
  using namespace Title::pick_game;
  switch (action) {
    case CON_DOWN:    if (++pos >= getNumOptions()) pos = 0;    break;
    case CON_UP:      if (--pos < 0) pos = getNumOptions() - 1; break;
    case CON_ATTACK:  {
      if (pos < slot::num && !handleLoadGame()) {

      } // this will execute if the load failed
      else returnToMain();
      break;
    }
    case CON_PAUSE:   {
      if (pos < slot::num && !handleLoadGame()) {

      } // this will execute if the load failed
      else returnToMain();
      break;
    }
    case CON_JUMP:    returnToMain(); break;
    default:          break;
  }
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
    case CON_DEFEND: returnToMain(); break;
    case CON_JUMP: returnToMain(); break;
    default: break;
  }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
//                                                                            //
//                                                                            //
//                                                                            //
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//

bool CTitle::handleDifficulty(const Gamecon& action) {
  using namespace Title::pick_game::difficulty;
  bool retval = false;

  switch (action) {
    case CON_DOWN:    if (++difficulty >= num) difficulty = 0;    break;
    case CON_UP:      if (--difficulty < 0) difficulty = num - 1; break;
    case CON_ATTACK:  {
      retval = true;
      sel_difficulty = false;
      break;
    }
    case CON_PAUSE:   {
      retval = true;
      sel_difficulty = false;
      break;
    }
    case CON_JUMP:    sel_difficulty = false; break;
    default:          break;
  }
  return retval;
}

bool CTitle::handleNewGame() {
  if (CGameIO::control.newGamedata(pos, Title::pick_game::difficulty::d_list[difficulty])) {
    CTransition::control.reqTrans(location::DEFAULT, 0, 0);
    CTransition::control.reqMode(APP_MODE_GAME);
    return true;
  } return false;
}

bool CTitle::handleLoadGame() {
  if (CGameIO::control.loadGamedata(pos)) {
    CMode::changeFlag(APP_MODE_GAME);
    return true;
  } return false;
}
