#include "CGameIO.h"

CGameIO CGameIO::control;

namespace {
  const char* const path = "../data/game/";
  const short num_games = 3;
  const char* const game_file[] = {
    "alpha.bin",
    "beta.bin",
    "gamma.bin",
  };
  const char* const glob_file = "glo.bin";
};

CGameIO::CGameIO() {
  //
}

bool CGameIO::init() {
  if (!loadGlobal()) {
    // inform user of missing data?
    saveGlobal();
  }
  loadAllGameinfo();
  return true;
}

bool CGameIO::loadGlobal() {
  // load global data file if it exists
  std::string file = std::string(path) + std::string(glob_file);
  FILE* FileHandle = fopen(file.c_str(), "rb");

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
  std::string file = std::string(path) + std::string(glob_file);
  FILE* FileHandle = fopen(file.c_str(), "wb");

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

void CGameIO::loadAllGameinfo() {
  for (int i = 0; i < num_games; i++) {
    std::string file = std::string(path) + std::string(game_file[i]);
    FILE* FileHandle = fopen(file.c_str(), "rb");

    if (FileHandle == NULL) {
      // CInform::InfoControl.pushInform("---CSCENERY.Onsave---\nfailed to open new file");
      CGameinfo::infolist.push_back(NULL);
      // DEBUG_makeDummyData(i);
      continue;
    }

    CGameinfo *data = new CGameinfo;
    if (fread(data, sizeof(CGameinfo), 1, FileHandle) != 1) {
      CGameinfo::infolist.push_back(NULL);
      fclose(FileHandle);
      continue;
    }
    CGameinfo::infolist.push_back(data);
    fclose(FileHandle);
  }
}

bool CGameIO::newGamedata(const short& slot, const Difficulty& d) {
  for (int i = 0; i < num_games; i++) {
    if (i != slot && CGameinfo::infolist[i]) {
      // get rid of gameinfo that we won't need
      delete CGameinfo::infolist[i];
      CGameinfo::infolist[i] = NULL;  // fix dangling pointer
    } else {
      if (CGameinfo::infolist[slot]) {
        // gameinfo has already been loaded into the requested slot;
        // reset the gameinfo structure for the new game
        CGameinfo::infolist[slot]->reset(d);
      } else {
        // no game info has been loaded into the requested slot;
        // construct a new gameinfo structure for the slot
        CGameinfo::infolist[slot] = new CGameinfo(d);
      }
    }
  }
  return true;
}

bool CGameIO::loadGamedata(const short& slot) {
  std::string file = std::string(path) + std::string(game_file[slot]);
  FILE* FileHandle = fopen(file.c_str(), "rb");

  if (FileHandle == NULL) {
    // CInform::InfoControl.pushInform("---CSCENERY.Onsave---\nfailed to open new file");
    return false;
  }

  fseek(FileHandle, sizeof(CGameinfo), SEEK_SET);

  if (fread(&CGamedata::control, sizeof(CGamedata), 1, FileHandle) != 1) {
    fclose(FileHandle);
    return false;
  }

  fclose(FileHandle);
  return true;
}

bool CGameIO::saveGame() {
  short slot = getActiveSlot();
  std::string file = std::string(path) + std::string(game_file[slot]);
  FILE* FileHandle = fopen(file.c_str(), "wb");

  if (FileHandle == NULL) return false;

  if (fwrite(&CGameinfo::infolist[slot], sizeof(CGameinfo), 1, FileHandle) != 1) {
    // error: failed to output gameinfo
    fclose(FileHandle);
    return false;
  }
  if (fwrite(&CGamedata::control, sizeof(CGamedata), 1, FileHandle) != 1) {
    // error: failed to output gamedata
    fclose(FileHandle);
    return false;
  }
  fclose(FileHandle);
  return true;
}

short CGameIO::getActiveSlot() {
  short i = 0;
  while (i < num_games) {
    if (CGameinfo::infolist[i]) break;
    i++;
  } return i;
}

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////

void CGameIO::DEBUG_makeDummyData(short game_num) {
  CGameinfo data;
  std::string file = std::string(path) + std::string(game_file[game_num]);
  FILE* FileHandle = fopen(file.c_str(), "wb");

  if (FileHandle == NULL) return;

  if (fwrite(&data, sizeof(CGameinfo), 1, FileHandle) != 1) {
    // write error
    fclose(FileHandle);
    return;
  }

  fclose(FileHandle);
}
