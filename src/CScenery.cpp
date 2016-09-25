#include "CScenery.h"

CScenery::CScenery()
{
  Tex_Scenery = NULL;

  Xo = Yo = 0;
  Width = Height = 0;
  MaxFrames = 0;

  X = Y = 0.0f;
  Z = 1.0f;

  vert_repeat = false;
  hori_repeat = false;
  permanent = false;
}

CScenery::~CScenery()
{
  //  Empty Destructor
}

bool CScenery::OnLoad(SDL_Texture* scenery,
  const unsigned int& Xo, const unsigned int& Yo,
  const unsigned int& Width, const unsigned int& Height,
  const unsigned int& MaxFrames)
{
  Tex_Scenery = scenery;
  if (Tex_Scenery == NULL) return false;

  this->Xo = Xo;
  this->Yo = Yo;
  this->Width = Width;
  this->Height = Height;
  this->MaxFrames = MaxFrames;

  return true;
}

void CScenery::OnLoop()
{
  // animation handling
}

bool CScenery::OnRender(SDL_Renderer* renderer)
{
  if (renderer == NULL) return false;



  return true;
}
