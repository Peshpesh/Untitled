#include "CFileIO.h"

CFileIO CFileIO::IOhandle;

namespace {
  //
}

CFileIO::CFileIO()
{
  //
}

void CFileIO::OnEvent(SDL_Event* Event)
{
  CEvent::OnEvent(Event);
}

void CFileIO::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
  //
}

void CFileIO::OnLButtonDown(int mX, int mY)
{
  //
}

bool CFileIO::OnRender()
{
  return true;
}

void CFileIO::addToPath(const char& addSym)
{
  newFile.push_back(addSym);
}
