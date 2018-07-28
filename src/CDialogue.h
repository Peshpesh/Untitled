#ifndef _C_DIALOGUE_H_
#define _C_DIALOGUE_H_

#include <string>
#include <vector>

#include "CFPS.h"
#include "CAsset.h"
#include "CType.h"
#include "CSound.h"
#include "CEvent.h"
#include "CInterrupt.h"
#include "CControls.h"

namespace dia {
  extern const float def_rate;  // default type rate
  extern const short rec_idle;  // recommended idle time
  extern const SDL_Color* def_sel_col; // default selection color
};

/* CPhrase structs are "dialogue boxes" that have a few properties:
  - name: Source of dialogue. This string can be empty.
  - text: Contents of the text box. Could be empty, but why?
  - type_rate:  How fast the text is "typed out" (in char/s). Has a default value.
  - idle_time:  After the text is "fully typed," wait this long (ms) before either:
                  a) displaying responses, if there are any
                  b) auto-advancing, if there are no responses
*/

struct CPhrase {
  std::string text;
  std::vector<std::string> response;
  float type_rate; // char per s typed to screen
  float resp_rate;
  int length;      // renderable character length
  int resp_length;
  int idle_time;
  CPhrase(const std::string& t, const float& t_r, const int& i_t):
    text(t),type_rate(t_r),resp_rate(t_r),
    length(CType::getSpeakLength(t.c_str())),resp_length(0),idle_time(i_t){};
  CPhrase(const std::string& t):
    text(t),type_rate(dia::def_rate),resp_rate(dia::def_rate),
    length(CType::getSpeakLength(t.c_str())),resp_length(0),idle_time(-1){};
  void setResponses(const std::string& A, const std::string& B, const std::string& C);
  void setResponses(const std::string& A, const std::string& B);
  void setRespLength();
};

class CDialogue : public CEvent {
  CDialogue();

private:
  unsigned long long prev_time;
  unsigned int cur_time;
  unsigned int end_time;
  unsigned int cur_idle;
  unsigned int cur_resp_time;
  unsigned int end_resp_time;
  bool speed_up;
  unsigned short sel;
  short* receiver;
  const SDL_Color* sel_col;

// private:
  // unsigned int getEndRespTime(const std::vector<std::string>& resp);

public:
  void resetTimer();
  void setReceiver(short* R);
  void receiveResp();
  void resetResp();

public:
  static CDialogue control;
  static std::vector<CPhrase> convo;

  void OnEvent(SDL_Event* Event);

  void OnLoop();

  void OnRender();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnKeyUp(SDL_Keycode sym, Uint16 mod);
  void handleSimpleTalk(const Gamecon& action);
  void handleResponse(const Gamecon& action);
private:
  void drawFrame();
  void drawName();
  void drawIcon();
  void drawMessage();
  void drawResponse();
};

#endif
