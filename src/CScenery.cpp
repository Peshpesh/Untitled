#include "CScenery.h"

std::vector<CScenery*> CScenery::SceneList;
std::vector<SDL_Texture*> CScenery::TexList;

CScenery::CScenery()
{
  Tex_Scenery = NULL;

  Xo = Yo = 0;
  Width = Height = 0;
  // MaxFrames = 0;

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
  Anim_Control.MaxFrames = MaxFrames;

  return true;
}

void CScenery::OnPlace(const int& X, const int& Y, const double& Z, const bool& v_rep, const bool& h_rep, const bool& perm)
{
  this->X = X;
  this->Y = Y;
  this->Z = Z;
  vert_repeat = v_rep;
  hori_repeat = h_rep;
  permanent = perm;
}

void CScenery::OnLoop()
{
  Anim_Control.OnAnimate();
}

bool CScenery::OnRender(SDL_Renderer* renderer)
{
  if (renderer == NULL) return false;
  if (Tex_Scenery == NULL)
  {
    return false;
  }
  // float Xc = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
  // float Yc = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);
  float X_win = ((WWIDTH - 1) / 2.0) + ((X - (CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0))) / Z);
  float Y_win = ((WHEIGHT - 1) / 2.0) + ((Y - (CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0))) / Z);

  if (hori_repeat)
  {
    CSurface::OnDraw(renderer, Tex_Scenery, X_win, Y_win, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
  }

  return true;
}
