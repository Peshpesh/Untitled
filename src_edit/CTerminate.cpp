#include "CTerminate.h"

CTerminate CTerminate::control;

namespace display {
  const short w = 200;
  const short h = 150;
  const short x = (WWIDTH - w) / 2;
  const short y = (WHEIGHT - h) / 2;

  const SDL_Rect frame = CAsset::getRect(x, y, w, h);
  const SDL_Rect info_frame = CAsset::getRect(x, y, w, (2 * h) / 3);

  const short but_w = 50;
  const short but_h = 13;
  const short but_spacing = 10;
  const short opt_x = x + (w - (but_w * 2) - but_spacing) / 2;
  const short opt_y = info_frame.y + info_frame.h + ((h - info_frame.h - but_h) / 2);
  const short b_sz = 2;

  const SDL_Point* bg = &palette::white;
  const SDL_Color* fcol = &rgb::black;

  const SDL_Rect but_ok = CAsset::getRect(opt_x, opt_y, but_w, but_h);
  const SDL_Rect but_cancel = CAsset::getRect(opt_x + but_w + but_spacing, opt_y, but_w, but_h);

  const SDL_Point* hov_ok = &palette::light_red;
  const SDL_Point* hov_cancel = &palette::light_green;

  const char* const txt_confirm = "Quit";
  const char* const txt_cancel = "Cancel";
  const char* const info = "\
    Exit Editor\n\
    --------------------\n\
    If you quit, all unsaved information will be lost.\n\n\
    Press Enter or click Quit to exit.\n\n\
    Press Esc or click Cancel to continue editing.";
}

CTerminate::CTerminate() {
  confirm_termination = false;
}

void CTerminate::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CTerminate::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (SDL_PointInRect(&m, &display::but_ok)) {
    confirm_termination = true;
    CInterrupt::removeFlag(INTRPT_EXIT);
  } else if (SDL_PointInRect(&m, &display::but_cancel)) {
    CInterrupt::removeFlag(INTRPT_EXIT);
  }
}

void CTerminate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_RETURN: {
      confirm_termination = true;
      CInterrupt::removeFlag(INTRPT_EXIT);
      break;
    }
    case SDLK_ESCAPE: CInterrupt::removeFlag(INTRPT_EXIT); break;
    default: break;
  }
}

bool CTerminate::OnRender(const SDL_Point& m) {
  using namespace display;

  if (!CAsset::drawStrBox(&frame, b_sz, bg)) return false;
  if (!CAsset::drawStrBox(&but_ok, b_sz, SDL_PointInRect(&m, &but_ok) ? hov_ok : bg)) return false;
  if (!CAsset::drawStrBox(&but_cancel, b_sz, SDL_PointInRect(&m, &but_cancel) ? hov_cancel : bg)) return false;

  Font::FontControl.SetFont(FONT_MINI);
  Font::NewCenterWrite(info, &info_frame, fcol);
  Font::NewCenterWrite(txt_confirm, &but_ok, fcol);
  Font::NewCenterWrite(txt_cancel, &but_cancel, fcol);

  return true;
}

bool CTerminate::willTerminate() {
  return confirm_termination;
}
