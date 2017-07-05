#ifndef _C_FILEIO_H_
#define _C_FILEIO_H_

#include "CInform.h"
#include "CInterrupt.h"
#include "CEvent.h"
#include "CFont.h"
#include "CAsset.h"
#include "CArea.h"
#include "CEntityEdit.h"
#include "CSceneryEdit.h"

class CFileIO : public CEvent {
private:
  CFileIO();
  std::string prevName;
  std::string newName;

public:
  static CFileIO IOhandle;

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);
  bool renderResetMenu(const SDL_Point* m);
  bool renderLoadMenu(const SDL_Point* m);
  bool renderSaveMenu(const SDL_Point* m);

private:
  void handleIOrequest();
  void newData();
  void loadData();
  void saveData();
  void pushInform(const int& ID);

private:
  void backPath();
  void addToPath(const char& addSym);
};

#endif
