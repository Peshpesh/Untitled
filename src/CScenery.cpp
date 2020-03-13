#include "CScenery.h"

std::vector<SceneryTexInfo>  CScenery::texList;
std::vector<CScenery*>       CScenery::sceneryList;
std::vector<double>          CScenery::layerList;

CScenery::CScenery() {
  imgSrc = NULL;
  numFrames = 0;
  X = Y = 0.0;
  layer = 0;
  // vert_repeat = false;
  // hori_repeat = false;
  // permanent = false;
}

CScenery::~CScenery() {
  //
}

bool CScenery::OnLoad(SDL_Texture* img, const SDL_Rect& srcR, const double& X, const double& Y, const unsigned short& layer) {
  if (img == NULL) return false;
  imgSrc = img;
  this->srcR = srcR;
  this->X = X;
  this->Y = Y;
  this->layer = layer;
  return true;
}

// void CScenery::OnPlace(const int& X, const int& Y, const double& Z, const bool& v_rep, const bool& h_rep, const bool& perm) {
//   this->X = X;
//   this->Y = Y;
//   this->Z = Z;
//   vert_repeat = v_rep;
//   hori_repeat = h_rep;
//   permanent = perm;
// }

void CScenery::OnLoop() {
  Anim_Control.OnAnimate();
}

bool CScenery::OnRender() {
  double rel_x = CCamera::CameraControl.trueXToRel(X, layerList[layer]);
  double rel_y = CCamera::CameraControl.trueYToRel(Y, layerList[layer]);
  SDL_Point w_pos = CCamera::CameraControl.GetWinRelPoint(rel_x, rel_y);
  return CSurface::OnDraw(imgSrc, srcR, w_pos);
}

// bool CScenery::OnRender() {
//   if (renderer == NULL) return false;
//   if (Tex_Scenery == NULL) return false;
//
//   // float Xc = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
//   // float Yc = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);
//   int X_win, Y_win;
//   if (!permanent)
//   {
//     X_win = ((WWIDTH - 1) / 2.0) + ((X - (CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0))) / Z);
//     Y_win = ((WHEIGHT - 1) / 2.0) + ((Y - (CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0))) / Z);
//   }
//   else
//   {
//     X_win = X;
//     Y_win = Y;
//   }
//
//   if (!vert_repeat && !hori_repeat)
//   {
//     CSurface::OnDraw(renderer, Tex_Scenery, X_win, Y_win, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
//   }
//   else if (hori_repeat && !vert_repeat)
//   {
//     int X_disp = (X_win % Width) - Width;
//     while (X_disp < WWIDTH)
//     {
//       CSurface::OnDraw(renderer, Tex_Scenery, X_disp, Y_win, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
//       X_disp += Width;
//     }
//   }
//   else if (vert_repeat && !hori_repeat)
//   {
//     int Y_disp = (Y_win % Height) - Height;
//     while (Y_disp < WHEIGHT)
//     {
//       CSurface::OnDraw(renderer, Tex_Scenery, X_win, Y_disp, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
//       Y_disp += Height;
//     }
//   }
//   else if (vert_repeat && hori_repeat)
//   {
//     int X_disp = (X_win % Width) - Width;
//     while (X_disp < WWIDTH)
//     {
//       int Y_disp = (Y_win % Height) - Height;
//       while (Y_disp < WHEIGHT)
//       {
//         CSurface::OnDraw(renderer, Tex_Scenery, X_disp, Y_disp, Xo + (Anim_Control.GetCurrentFrame() * Width), Yo, Width, Height);
//         Y_disp += Height;
//       }
//       X_disp += Width;
//     }
//   }
//
//   return true;
// }

int CScenery::drawBackground() {
  int N = sceneryList.size();
  while (N > 0) {
    if (layerList[sceneryList[N-1]->layer] < 1.0) break;
    N--;
    if (!sceneryList[N]->OnRender()) return false;
  }
  return N;
}

void CScenery::drawForeground(int i) {
  // Draw foreground scenery
  while (i > 0) {
    if (layerList[sceneryList[i-1]->layer] > 1.0) break;
    i--;
    if (!sceneryList[i]->OnRender()) return;
  }
}
