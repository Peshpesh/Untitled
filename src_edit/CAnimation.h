#ifndef _C_ANIMATION_H_
#define _C_ANIMATION_H_

#include <SDL.h>

class CAnimation {
private:
  int  CurrentFrame;
  int  FrameInc;

private:
  int    FrameRate;
  long  OldTime;

public:
  int  MaxFrames;
  int  Oscillate;

public:
  CAnimation();

  void OnAnimate();

public:
  void SetFrameRate(int Rate);

  void SetCurrentFrame(int Frame);

  int GetCurrentFrame();
};

#endif
