#include "CConfig.h"

CConfig CConfig::control;

namespace {
  const char* const key_path = "../data/game/config.key";
  unsigned short def_volume = 100;
};

CConfig::CConfig() {
  con_change = CONFIG_NONE;
  if (!OnInit()) {
    reset_all();
    save();
  }
}

bool CConfig::OnInit() {
  // load config key file if it exists
  FILE* FileHandle = fopen(key_path, "rb");

  if (FileHandle == NULL)	{
    // CInform::InfoControl.pushInform("---CScenery.OnLoad---\nfailed to open file");
    return false;
  }

  if (fread(&key, sizeof(ConfigKey), 1, FileHandle) != 1) {
    fclose(FileHandle);
    return false;
  }

  fclose(FileHandle);
  return true;
}

void CConfig::reset_all() {
  reset_audio();
  reset_video();
}

void CConfig::reset_audio() {
  key.sfx_volume = def_volume;
  key.bgm_volume = def_volume;
  key.tex_volume = def_volume;
  key.stereo = true;
}

void CConfig::reset_video() {
  key.fullscreen = false;
}

void CConfig::save() {
  // save config key file
  FILE* FileHandle = fopen(key_path, "wb");

  if (FileHandle == NULL) {
    // CInform::InfoControl.pushInform("---CSCENERY.Onsave---\nfailed to open new file");
    return;
  }

  if (fwrite(&key, sizeof(ConfigKey), 1, FileHandle) != 1) {
    // write error
    fclose(FileHandle);
    return;
  }

  fclose(FileHandle);
}

void CConfig::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CConfig::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  Gamecon action = CControls::handler.getAction(sym, mod);

  if (action != CON_NONE) {
    switch (con_change) {
      case CONFIG_SFX:      handleVolume(key.sfx_volume, action); break;
      case CONFIG_BGM:      handleVolume(key.bgm_volume, action); break;
      case CONFIG_TEX:      handleVolume(key.tex_volume, action); break;
      case CONFIG_AUDIOOUT: handleAudioOut(action);               break;
      case CONFIG_DISPLAY:  handleDisplay(action);                break;
      default:              break;
    }
  }
}

void CConfig::handleVolume(unsigned short& vol, const Gamecon& action) {
  if ((action == CON_LEFT || action == CON_DOWN) && vol > 0) {
    vol--;
  } else if ((action == CON_RIGHT || action == CON_UP) && vol < MAX_VOLUME) {
    vol++;
  } else if (action == CON_ATTACK || action == CON_PAUSE) {
    con_change = CONFIG_NONE;
    save();
  }
}

void CConfig::handleAudioOut(const Gamecon& action) {
  if (action == CON_LEFT || action == CON_DOWN || action == CON_RIGHT || action == CON_UP) {
    key.stereo = !(key.stereo);
  } else if (action == CON_ATTACK || action == CON_PAUSE) {
    con_change = CONFIG_NONE;
    save();
  }
}

void CConfig::handleDisplay(const Gamecon& action) {
  if (action == CON_LEFT || action == CON_DOWN || action == CON_RIGHT || action == CON_UP) {
    key.fullscreen = !(key.fullscreen);
  } else if (action == CON_ATTACK || action == CON_PAUSE) {
    con_change = CONFIG_NONE;
    save();
  }
}

short CConfig::getVolume(const Configflag& vol_type) {
  short val = -1;
  switch (vol_type) {
    case CONFIG_SFX: val = key.sfx_volume; break;
    case CONFIG_BGM: val = key.bgm_volume; break;
    case CONFIG_TEX: val = key.tex_volume; break;
  }
  return val;
}

bool CConfig::isStereo() {
  return key.stereo;
}

bool CConfig::isFullscreen() {
  return key.fullscreen;
}
