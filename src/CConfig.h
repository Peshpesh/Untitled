#ifndef _C_CONFIG_H_
#define _C_CONFIG_H_

#include <stdio.h>
#include "CEvent.h"
#include "Define.h"
#include "CControls.h"

struct ConfigKey {
  unsigned short sfx_volume;
  unsigned short bgm_volume;
  unsigned short tex_volume;
  bool stereo;
  bool fullscreen;
};

enum Configflag {
  CONFIG_NONE,
  CONFIG_SFX,
  CONFIG_BGM,
  CONFIG_TEX,
  CONFIG_AUDIOOUT,
  CONFIG_DISPLAY,
};

class CConfig : public CEvent {
  CConfig();
  ConfigKey key;

public:
  static CConfig control;

public:
	Configflag con_change;

private:
  bool OnInit();
public:
  void reset_all();
  void reset_audio();
  void reset_video();
private:
  void save();

public:
  void OnEvent(SDL_Event* Event);
private:
	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
private:
  void handleVolume(unsigned short& vol, const Gamecon& action);
  void handleAudioOut(const Gamecon& action);
  void handleDisplay(const Gamecon& action);
public:
  short getVolume(const Configflag& vol_type);
  bool isStereo();
  bool isFullscreen();
};

#endif
