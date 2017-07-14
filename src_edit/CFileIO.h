#ifndef _C_FILEIO_H_
#define _C_FILEIO_H_

#include "CInform.h"
#include "CInterrupt.h"
#include "CEvent.h"
#include "CFont.h"
#include "CAsset.h"
#include "CArea.h"
#include "CEntity.h"
#include "CSceneryEdit.h"
#include "CCamera.h"

class CFileIO : public CEvent {
private:
  CFileIO();
  std::string prevName;
  std::string newName;
  void initMenus();

private:
  struct prompt {
    const SDL_Point* canvCol;
    const SDL_Point* titleBoxCol;
    const SDL_Point* fBoxCol;
    const SDL_Point* bCol;
    const SDL_Color* textCol;
    const SDL_Color* fnameCol;
    const SDL_Point* optCol;
    const SDL_Point* optHovCol;

    const char* title;
    const char* prevTitle;
    const char* newTitle;
    const char* okText;
    const char* cancText;

    const char* info;
  } reset, load, save;

public:
  static CFileIO IOhandle;

  void OnEvent(SDL_Event* Event);

  void OnKeyDown(SDL_Keycode sym, Uint16 mod);

  void OnLButtonDown(int mX, int mY);

  bool OnRender(const SDL_Point* m);

  bool renderMenu(const prompt& menu, const SDL_Point* m);

  std::string getPrevName();

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
