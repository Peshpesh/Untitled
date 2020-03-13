#include "CDialogue.h"

CDialogue CDialogue::control;
std::vector<CPhrase> CDialogue::convo;

namespace dia {
  const float def_rate = 32.0f; // default type rate
  const short rec_idle = 3000;  // recommended idle time
  const SDL_Color* def_sel_col = &rgb::yellow;
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
  const short r_w = t_w;
  const short r_h = t_h / num_rows;
  const short r_x = (WWIDTH - r_w) / 2;
  const short r_y = t_y + (t_h - r_h);
  const short i_w = 47;
  const short i_h = 47;
  const short i_x = f_x - (i_w / 2) + 1;
  const short i_y = f_y - (i_h / 2) + 1;
  const double i_r = 45.0;
  const SDL_Rect i = {i_x, i_y, i_w, i_h};
};

void CPhrase::setResponses(const std::string& A, const std::string& B, const std::string& C) {
  response.clear();
  response.push_back(A);
  response.push_back(B);
  response.push_back(C);
  setRespLength();
}

void CPhrase::setResponses(const std::string& A, const std::string& B) {
  response.clear();
  response.push_back(A);
  response.push_back(B);
  setRespLength();
}

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
  sel = 0;
  receiver = NULL;
  sel_col = dia::def_sel_col;
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

void CDialogue::setReceiver(short* R) {
  receiver = R;
}

void CDialogue::receiveResp() {
  if (receiver == NULL) return;
  *receiver = sel + 1;
}

void CDialogue::resetResp() {
  sel = 0;
  receiver = NULL;
}

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
      receiveResp();
      convo.erase(convo.begin());
      resetTimer();
      resetResp();
      speed_up = false;
      if (convo.empty()) CInterrupt::removeFlag(INTRPT_DIALOGUE);
      break;
    }
    case CON_DEFEND:  {
      speed_up = true;
      break;
    }
    case CON_LEFT: {
      if (sel == 0) sel = convo[0].response.size() - 1;
      else sel--;
      break;
    }
    case CON_RIGHT: {
      if (sel == convo[0].response.size() - 1) sel = 0;
      else sel++;
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
  drawIcon();
  drawMessage();
  if (!convo[0].response.empty() && cur_resp_time) drawResponse();
  CAsset::paletteAlpha(MAX_RGBA);
}

void CDialogue::drawFrame() {
  CAsset::drawStrBox(frame::f, frame::str_w, *frame::fill_col, *frame::b_col);
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

void CDialogue::drawResponse() {
  using namespace frame;

  SDL_Rect r = {r_x, r_y, r_w / convo[0].response.size(), r_h};
  if (cur_resp_time < end_resp_time) {
    int vis_l = convo[0].resp_length * (1.0 - ((double)(end_resp_time - cur_resp_time) / (double)(end_resp_time)));
    int total_l = 0;
    for (int i = 0; i < convo[0].response.size(); i++) {
      int len = CType::getSpeakLength(convo[0].response[i].c_str());
      if (total_l + len <= vis_l) {
        CType::CenterWrite(FONT_MINI, convo[0].response[i].c_str(), r);
        total_l += len;
        r.x += r.w;
      } else {
        std::string vis = CType::getSpeakSegment(convo[0].response[i].c_str(), vis_l - total_l);
        CType::CenterWrite(FONT_MINI, vis.c_str(), r);
        break;
      }
    }
  } else {
    for (int i = 0; i < convo[0].response.size(); i++) {
      std::string val = (i == sel) ? "$R" + convo[0].response[i] : convo[0].response[i];
      CType::CenterWrite(FONT_MINI, val.c_str(), r, (i == sel) ? sel_col : text_col);
      r.x += r.w;
    }
  }
}
