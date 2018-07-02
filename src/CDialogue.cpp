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
  const SDL_Color* text_col = &rgb::white;
  const SDL_Color* b_col = &rgb::light_cyan;
  const short num_rows = 3;
  const short f_A = 166;  // A for alpha
  const short f_w = 448;
  const short f_h = 128;
  const short f_x = (WWIDTH - f_w) / 2;
  const short f_y = 300;
  const SDL_Rect f = {f_x, f_y, f_w, f_h};
  const short t_w = f_w - 64;
  const short t_h = f_h - 48;
  const short t_x = (WWIDTH - t_w) / 2;
  const short t_y = f_y + ((f_h - t_h) / 2);
  const SDL_Rect t = {t_x, t_y, t_w, t_h};
  const short i_w = 47;
  const short i_h = 47;
  const short i_x = f_x - (i_w / 2) + 1;
  const short i_y = f_y - (i_h / 2) + 1;
  const double i_r = 45.0;
  const SDL_Rect i = {i_x, i_y, i_w, i_h};
};

void CPhrase::setRespLength() {
  resp_length = 0;
  for (int i = 0; i < response.size(); i++) {
    resp_length += CType::getSpeakLength(response[i].c_str());
  }
}

CDialogue::CDialogue() {
  prev_time = 0;
  cur_time = 0;
  end_time = 0;
  cur_idle = 0;
  cur_resp_time = 0;
  end_resp_time = 0;
  speed_up = false;
}

void CDialogue::resetTimer() {
  cur_time = cur_idle = cur_resp_time = 0;
  prev_time = SDL_GetTicks();
  if (!convo.empty()) {
    end_time = 1000.0f * (convo[0].length / convo[0].type_rate);
    if (!convo[0].response.empty()) {
      end_resp_time = 1000.0f * (convo[0].resp_length / convo[0].resp_rate);
    } else end_resp_time = 0;
  } else {
    end_time = 0;
    end_resp_time = 0;
  }
}

// unsigned int CDialogue::getEndRespTime(const std::vector<std::string>& resp) {
//   unsigned int val = 0;
//   for (int i = 0; i < resp.size(); i++) {
//     val += 1000.0f * (resp[i].size() / convo[0].resp_rate);
//   }
//   return val;
// }

void CDialogue::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CDialogue::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  Gamecon action = CControls::handler.getAction(sym, mod);
  if (!convo[0].response.empty() && cur_resp_time >= end_resp_time) {
    handleResponse(action);
  } else {
    handleSimpleTalk(action);
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

void CDialogue::handleSimpleTalk(const Gamecon& action) {
  switch (action) {
    case CON_ATTACK:  {
      if (cur_time < end_time) cur_time = end_time;
      else if (cur_resp_time < end_resp_time) cur_resp_time = end_resp_time;
      else {
        convo.erase(convo.begin());
        resetTimer();
        speed_up = false;
        if (convo.empty()) CInterrupt::removeFlag(INTRPT_DIALOGUE);
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

void CDialogue::handleResponse(const Gamecon& action) {
  switch (action) {
    case CON_ATTACK:  {
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

void CDialogue::OnLoop() {
  if (convo.empty()) return;
  if (!CInterrupt::isFlagOn(INTRPT_PAUSE)) {
    if (cur_time < end_time) {
      cur_time += (SDL_GetTicks() - prev_time) * (1 + (speed_up * 4));
    } else if (convo[0].idle_time >= 0 && cur_idle < convo[0].idle_time) {
      cur_idle += SDL_GetTicks() - prev_time + (speed_up * convo[0].idle_time);
      if (convo[0].response.empty() && cur_idle >= convo[0].idle_time) {
        convo.erase(convo.begin());
        resetTimer();
        speed_up = false;
        if (convo.empty()) CInterrupt::removeFlag(INTRPT_DIALOGUE);
        return;
      }
    } else if (cur_resp_time < end_resp_time) {
      cur_resp_time += (SDL_GetTicks() - prev_time) * (1 + (speed_up * 4));
    }
  }
  prev_time = SDL_GetTicks();
}

void CDialogue::OnRender() {
  if (convo.empty()) return;

  CAsset::paletteAlpha(frame::f_A);
  drawFrame();
  if (!convo[0].name.empty()) drawName();
  drawIcon();
  drawMessage();
  CAsset::paletteAlpha(MAX_RGBA);
}

void CDialogue::drawFrame() {
  CAsset::drawStrBox(frame::f, frame::str_w, *frame::fill_col, *frame::b_col);
}

void CDialogue::drawName() {

}

void CDialogue::drawIcon() {
  CAsset::drawRotStrBox(frame::i, frame::str_w, *frame::fill_col, *frame::b_col, frame::i_r);
}

void CDialogue::drawMessage() {
  using namespace frame;
  CType::control.SetColor(text_col);
  if (cur_time < end_time) {
    int vis_l = convo[0].length * (1.0 - ((double)(end_time - cur_time) / (double)(end_time)));
    std::string vis = CType::getSpeakSegment(convo[0].text.c_str(), vis_l);
    CType::WriteBox(FONT_MINI, vis.c_str(), num_rows, t);
  } else {
    CType::WriteBox(FONT_MINI, convo[0].text.c_str(), num_rows, t);
  }
}
