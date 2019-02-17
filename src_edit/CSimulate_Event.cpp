#include "CSimulate.h"

void CSimulate::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

void CSimulate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CSimulate::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
}

void CSimulate::OnRButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};
}

bool CSimulate::handleInterr(SDL_Event* Event) {
  return false;
}
