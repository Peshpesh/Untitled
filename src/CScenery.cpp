#include "CScenery.h"

std::vector<CScenery*> CScenery::SceneList;
std::vector<SDL_Texture*> CScenery::TexList;

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

void CScenery::OnPlace(const float& X, const float& Y, const float& Z, const bool& v_rep, const bool& h_rep, const bool& perm)
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
  // animation handling
}

bool CScenery::OnRender(SDL_Renderer* renderer)
{
  if (renderer == NULL) return false;
  if (Tex_Scenery == NULL)
  {
    SDL_Delay(5000);
    return false;
  }

  // float true_dx = CCamera::CameraControl.GetX() - X;
  // float true_dy = CCamera::CameraControl.GetY() - Y;
  // float x_distort = (true_dx / Z) * (Z - 1.0f);
  // float y_distort = (true_dy / Z) * (Z - 1.0f);
  // CSurface::OnDraw(renderer, Tex_Scenery, X - CCamera::CameraControl.GetX() + x_distort,
	// 	Y - CCamera::CameraControl.GetY() + y_distort, Xo, Yo, Width, Height);
  float X_win = (X - CCamera::CameraControl.GetX()) / Z;
  float Y_win = (Y - CCamera::CameraControl.GetY()) / Z;
  CSurface::OnDraw(renderer, Tex_Scenery, X_win, Y_win, Xo, Yo, Width, Height);

  return true;
}
