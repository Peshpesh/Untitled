#include "CInform.h"

CInform CInform::InfoControl;

namespace {
  const short min_h = 25;
  const short texBuf = 4;
  const short bsiz = 2;
}

CInform::CInform()
{
  lastTime = 0;
  timeLeft = 0;

  frame.x = frame.y = 0;
  texBox.x = texBox.y = texBuf;

  texBox.w = 200;
  frame.w = texBox.w + (texBuf * 2);
}

void CInform::pushInform(const char* info)
{
  // get frame dims; set timer and info string
  timeLeft = 3000;
  lastTime = SDL_GetTicks();

  texBox.h = getTextHeight(FONT_MINI, info, texBox.w);
  if (texBox.h < min_h) {
    texBox.h = min_h;
  }

  frame.h = texBox.h + (texBuf * 2);

  this->info = info;
}

void CInform::OnLoop()
{
  if (timeLeft > 0) {
    timeLeft -= SDL_GetTicks() - lastTime;
    lastTime = SDL_GetTicks();
  }
  else {
    info.clear();
  }

}

bool CInform::OnRender()
{
  if (timeLeft > 0) {
    CAsset::drawStrBox(&frame, bsiz, &palette::dark_blue, &palette::light_blue);
    CFont::NewCenterWrite(FONT_MINI, info.c_str(), &texBox, &rgb::light_green);
  }

  return true;
}
