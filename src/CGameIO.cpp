#include "CGameIO.h"

CGameIO CGameIO::control;

namespace {
  const char* const glob_path = "../data/game/glo.bin";
};

CGameinfo::CGameinfo() {
  // hero;
  // inv;
  diff = NORMAL;
  N_load = 0;
  N_save = 0;
  N_death = 0;
  time = 0;
}

CGameIO::CGameIO() {
  if (!loadGlobal()) {
    // inform user of missing data?
    saveGlobal();
  }
}

bool CGameIO::loadGlobal() {
  // load global data file if it exists
  FILE* FileHandle = fopen(glob_path, "rb");

  if (FileHandle == NULL)	{
    // CInform::InfoControl.pushInform("---CScenery.OnLoad---\nfailed to open file");
    return false;
  }

  CGlobinfo data;
  if (fread(&data, sizeof(CGlobinfo), 1, FileHandle) != 1) {
    fclose(FileHandle);
    return false;
  }

  CGlobal::control.push_data(data);

  fclose(FileHandle);
  return true;
}

void CGameIO::saveGlobal() {
  // save config key file
  FILE* FileHandle = fopen(glob_path, "wb");

  if (FileHandle == NULL) {
    // CInform::InfoControl.pushInform("---CSCENERY.Onsave---\nfailed to open new file");
    return;
  }

  CGlobinfo data = CGlobal::control.pull_data(); data.uptime += SDL_GetTicks();
  if (fwrite(&data, sizeof(CGlobinfo), 1, FileHandle) != 1) {
    // write error
    fclose(FileHandle);
    return;
  }

  fclose(FileHandle);
}
