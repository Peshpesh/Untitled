#ifndef _C_DRAFT_H_
#define _C_DRAFT_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CAsset.h"
#include "CCamera.h"
#include "CSurface.h"
#include "CInform.h"
#include "CMask.h"

class CDraft {
  CDraft();

  SDL_Texture* img;
  SDL_Rect srcR;
  CMask test;

  short alpha;
  int X;
  int Y;
  short Z;

public:
  static CDraft control;

  void OnInit();

  void OnLoad(const std::string& name);

  void OnRender();

  void OnCleanup();
};
#endif
