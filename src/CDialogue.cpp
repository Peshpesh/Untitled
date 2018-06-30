#include "CDialogue.h"

CDialogue CDialogue::control;
std::vector<CPhrase> CDialogue::convo;

namespace dia {
  const float def_rate = 32.0f; // default type rate
  const short rec_idle = 3000;  // recommended idle time
};

CDialogue::CDialogue() {
  prev_time = 0;
  cur_time = 0;
  end_time = 0;
  cur_idle = 0;
}

CDialogue::resetTimer() {
  cur_time = cur_idle = 0;
  prev_time = SDL_GetTicks();
  if (!convo.empty()) {
    end_time = 1000.0f * (convo[0].text.size() / convo[0].type_rate);
  } else end_time = 0;
}

void CDialogue::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CDialogue::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (CControls::handler.getAction(sym, mod)) {
    case CON_ATTACK:    {
      // Hero.Attack();
      break;
    }
    case CON_DEFEND:    {
      // Hero.Defend();
      break;
    }
    case CON_JUMP:      {
      // CHero::Hero.Jump();
      break;
    }
    case CON_PAUSE:     {
      CInterrupt::appendFlag(INTRPT_PAUSE);
      break;
    }
    default: break;
  }
}

void CDialogue::OnLoop() {
  if (convo.empty()) return;

  if (cur_time < end_time) {

  } else if (convo[0].idle_time >= 0) {
    cur_idle += SDL_GetTicks() - prev_time;
    if (cur_idle >= convo[0].idle_time) {

    }
  }
}

void CDialogue::OnRender() {

}
