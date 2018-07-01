#include "CDialogue.h"

CDialogue CDialogue::control;
std::vector<CPhrase> CDialogue::convo;

namespace dia {
  const float def_rate = 32.0f; // default type rate
  const short rec_idle = 3000;  // recommended idle time
};

namespace frame {
  const short str_w = 2;
  const SDL_Color* fill_col = &rgb::black;
  const SDL_Color* b_col = &rgb::light_cyan;
  const short t_w = 448;
  const short t_h = 128;
  const short t_x = (WWIDTH - t_w) / 2;
  const short t_y = 300;
  const SDL_Rect t = {t_x, t_y, t_w, t_h};
  const short i_w = 48;
  const short i_h = 48;
  const short i_x = t_x - (i_w / 2);
  const short i_y = t_y - (i_h / 2);
  const double i_r = 45.0;
  const SDL_Rect i = {i_x, i_y, i_w, i_h};
};

CDialogue::CDialogue() {
  prev_time = 0;
  cur_time = 0;
  end_time = 0;
  cur_idle = 0;
  speed_up = false;
}

void CDialogue::resetTimer() {
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
    case CON_ATTACK:  {
      if (cur_time < end_time) cur_time = end_time;
      else {
        convo.erase(convo.begin());
        resetTimer();
      }
      break;
    }
    case CON_DEFEND:  {
      speed_up = true;
      break;
    }
    case CON_PAUSE:   {
      CInterrupt::appendFlag(INTRPT_PAUSE);
      break;
    }
    default: break;
  }
}

void CDialogue::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
  switch (CControls::handler.getAction(sym, mod)) {
    case CON_DEFEND: {
      speed_up = false;
      break;
    }
    default: break;
  }
}

void CDialogue::OnLoop() {
  if (convo.empty()) return;

  if (!CInterrupt::isFlagOn(INTRPT_PAUSE)) {
    if (cur_time < end_time) {
      cur_time += (SDL_GetTicks() - prev_time) * (1 + (speed_up * 2));
    } else if (convo[0].idle_time >= 0) {
      cur_idle += SDL_GetTicks() - prev_time + (speed_up * convo[0].idle_time);
      if (cur_idle >= convo[0].idle_time) {
        convo.erase(convo.begin());
        resetTimer();
        return;
      }
    }
  }
  prev_time = SDL_GetTicks();
}

void CDialogue::OnRender() {
  if (convo.empty()) return;

  drawFrame();
  if (!convo[0].name.empty()) drawName();
  drawIcon();
  drawMessage();
}

void CDialogue::drawFrame() {
  CAsset::drawStrBox(frame::t, frame::str_w, *frame::fill_col, *frame::b_col);
}

void CDialogue::drawName() {

}

void CDialogue::drawIcon() {
  CAsset::drawRotStrBox(frame::i, frame::str_w, *frame::fill_col, *frame::b_col, frame::i_r);
}

void CDialogue::drawMessage() {
  
}
