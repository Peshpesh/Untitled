#include "CConfig.h"

CConfig CConfig::control;

namespace {
  const char* const key_path = "../data/game/config.key";
};

CConfig::CConfig() {
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
  key.sfx_volume = MAX_VOLUME;
  key.bgm_volume = MAX_VOLUME;
  key.tex_volume = MAX_VOLUME;
}

void CConfig::reset_video() {
  //
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

}
