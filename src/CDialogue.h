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
};

/* CPhrase structs are "dialogue boxes" that have a few properties:
  - name: Source of dialogue. This string can be empty.
  - text: Contents of the text box. Could be empty, but why?
  - type_rate:  How fast the text is "typed out" (in char/s). Has a default value.
  - idle_time:  After the text is "fully typed," wait this long (ms) before auto-advancing.
                Has a default value of -1, which means to wait forever (user must force).
*/

struct CPhrase {
  std::string name;
  std::string text;
  int length;      // renderable character length
  float type_rate; // char per s typed to screen
  int idle_time;
  CPhrase(const std::string& n, const std::string& t, const float& t_r, const int& i_t):
    name(n),text(t),type_rate(t_r),idle_time(i_t),length(CType::getLength(t.c_str())){};
  CPhrase(const std::string& t, const float& t_r, const int& i_t):
    name(""),text(t),type_rate(t_r),idle_time(i_t),length(CType::getLength(t.c_str())){};
  CPhrase(const std::string& t):
    name(""),text(t),type_rate(dia::def_rate),idle_time(-1),length(CType::getLength(t.c_str())){};
};

class CDialogue : public CEvent {
  CDialogue();

private:
  unsigned long long prev_time;
  unsigned int cur_time;
  unsigned int end_time;
  unsigned int cur_idle;
  bool speed_up;

public:
  void resetTimer();

public:
  static CDialogue control;
  static std::vector<CPhrase> convo;

  void OnEvent(SDL_Event* Event);

  void OnLoop();

  void OnRender();

private:
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnKeyUp(SDL_Keycode sym, Uint16 mod);
private:
  void drawFrame();
  void drawName();
  void drawIcon();
  void drawMessage();
};

#endif
