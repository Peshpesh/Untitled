#include "CScenery.h"

std::vector<CScenery*> CScenery::SceneList;
std::vector<SDL_Texture*> CScenery::TexList;

CScenery::CScenery()
{
  Tex_Scenery = NULL;

  Xo = Yo = 0;
  Width = Height = 0;
  // MaxFrames = 0;

  X = Y = 0;
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

bool CScenery::OnRender()
{
  if (Tex_Scenery == NULL) return false;

  // float Xc = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
  // float Yc = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);
  int X_win, Y_win;
  if (!permanent)
  {
    X_win = ((WWIDTH - 1) / 2.0) + ((X - (CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0))) / Z);
    Y_win = ((WHEIGHT - 1) / 2.0) + ((Y - (CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0))) / Z);
  }
  else
  {
    X_win = X;
    Y_win = Y;
  }

  if (!vert_repeat && !hori_repeat)
  {
    CSurface::OnDraw(Tex_Scenery, X_win, Y_win, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
  }
  else if (hori_repeat && !vert_repeat)
  {
    int X_disp = (X_win % Width) - Width;
    while (X_disp < WWIDTH)
    {
      CSurface::OnDraw(Tex_Scenery, X_disp, Y_win, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
      X_disp += Width;
    }
  }
  else if (vert_repeat && !hori_repeat)
  {
    int Y_disp = (Y_win % Height) - Height;
    while (Y_disp < WHEIGHT)
    {
      CSurface::OnDraw(Tex_Scenery, X_win, Y_disp, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
      Y_disp += Height;
    }
  }
  else if (vert_repeat && hori_repeat)
  {
    int X_disp = (X_win % Width) - Width;
    while (X_disp < WWIDTH)
    {
      int Y_disp = (Y_win % Height) - Height;
      while (Y_disp < WHEIGHT)
      {
        CSurface::OnDraw(Tex_Scenery, X_disp, Y_disp, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
        Y_disp += Height;
      }
      X_disp += Width;
    }
  }

  return true;
}
