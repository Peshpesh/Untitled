#include "CCamera.h"

CCamera CCamera::CameraControl;

CCamera::CCamera() {
  X = Y = 0;
  X_min = 0;
  Y_min = 0;
  X_max = (TILE_SIZE * MAP_WIDTH) - 1;
  Y_max = (TILE_SIZE * MAP_HEIGHT) - 1;
  follow_dom.x = follow_dom.y = 0;
  follow_dom.w = 60;
  follow_dom.h = 50;
  TargetX = TargetY = NULL;
  TargetW = TargetH = NULL;
  TargetMode = TARGET_MODE_NORMAL;
  uselimits = false;

  // usedisplace = true;
}

void CCamera::OnMove(int MoveX, int MoveY) {
  X += MoveX;
  Y += MoveY;
  enforceLims();
}

void CCamera::enforceLims() {
  if (uselimits) {
    if (X < X_min)                     X = X_min;
    else if (X + WWIDTH - 1 > X_max)   X = X_max - WWIDTH + 1;
    if (Y < Y_min)                     Y = Y_min;
    else if (Y + WHEIGHT - 1 > Y_max) Y = Y_max - WHEIGHT + 1;
  }
}

void CCamera::OnLoop() {
  if (TargetX && TargetY) {
    if (*TargetX < (float)(follow_dom.x)) follow_dom.x = *TargetX - (*TargetX < 0.0f);
    if (*TargetY < follow_dom.y) follow_dom.y = *TargetY - (*TargetY < 0.0f);
    if (TargetW) {
      if (*TargetX + *TargetW > follow_dom.x + follow_dom.w) {
        follow_dom.x = *TargetX + *TargetW - follow_dom.w - (*TargetX + *TargetW - follow_dom.w < 0.0f);
      }
    } else {
      if (*TargetX > follow_dom.x + follow_dom.w) {
        follow_dom.x = *TargetX - follow_dom.w - (*TargetX - follow_dom.w < 0.0f);
      }
    }
    if (TargetH) {
      if (*TargetY + *TargetH > follow_dom.y + follow_dom.h) {
        follow_dom.y = *TargetY + *TargetH - follow_dom.h - (*TargetY + *TargetH - follow_dom.y < 0.0f);
      }
    } else {
      if (*TargetY > follow_dom.y + follow_dom.h) {
        follow_dom.y = *TargetY - follow_dom.h - (*TargetY - follow_dom.h < 0.0f);
      }
    }
  }
}

void CCamera::SetPos(int X, int Y) {
  this->X = X;
  this->Y = Y;
}

void CCamera::SetTarget(float* X, float* Y) {
  TargetX = X;
  TargetY = Y;
  TargetW = TargetH = NULL;
  if (X && Y) {
    follow_dom.x = *X - (follow_dom.w / 2.0f) - (*X - (float)(follow_dom.w / 2.0f) < 0.0f);
    follow_dom.y = *Y - (follow_dom.h / 2.0f) - (*Y - (float)(follow_dom.h / 2.0f) < 0.0f);
  }
}

void CCamera::SetTarget(float* X, float* Y, int* W, int* H) {
  TargetX = X;
  TargetY = Y;
  TargetW = W;
  TargetH = H;
  if (X && Y && W && H) {
    follow_dom.x = *X + (*W / 2.0f) - (follow_dom.w / 2.0f) -
                  (*X + (*W / 2.0f) - (float)(follow_dom.w / 2.0f) < 0.0f);
    follow_dom.y = *Y + (*W / 2.0f) - (follow_dom.h / 2.0f) -
                  (*Y + (*W / 2.0f) - (float)(follow_dom.h / 2.0f) < 0.0f);
  }
}

void CCamera::FreeTarget() {
  TargetX = TargetY = NULL;
  TargetW = TargetH = NULL;
}

// int CCamera::GetX() {
//   if (TargetX != NULL) {
//     int x_disp = TargetW ? *TargetW / 2 : 0;
//     if (TargetMode == TARGET_MODE_FOLLOW) {
//       int current_X = *TargetX + x_disp - (WWIDTH / 2) - (*TargetX + x_disp < WWIDTH / 2);
//       if (current_X < X - (follow_w / 2)) X -= (X - (follow_w / 2)) - current_X;
//       else if (current_X > X + (follow_w / 2)) X += current_X - (X + follow_w / 2);
//       return LimX(X);
//     } else if (TargetMode == TARGET_MODE_CENTER) {
//       return LimX(*TargetX + x_disp - (WWIDTH / 2) - (*TargetX + x_disp < WWIDTH / 2));
//     }
//     return LimX(*TargetX + x_disp);
//   }
//   return LimX(X);
// }

// int CCamera::GetY() {
//   if (TargetY != NULL) {
//     // int y_disp = (usedisplace && TargetH) ? *TargetH / 2 : 0;
//     int y_disp = TargetH ? *TargetH / 2 : 0;
//     if (TargetMode == TARGET_MODE_FOLLOW) {
//       int current_Y = *TargetY + y_disp - (WHEIGHT / 2) - (*TargetY + y_disp < WHEIGHT / 2);
//       if (current_Y < Y - (follow_h / 2)) Y -= (Y - (follow_h / 2)) - current_Y;
//       else if (current_Y > Y + (follow_h / 2)) Y += current_Y - (Y + follow_h / 2);
//       return LimY(Y);
//     } else if (TargetMode == TARGET_MODE_CENTER) {
//       return LimY(*TargetY + y_disp - (WHEIGHT / 2) - (*TargetY + y_disp < WHEIGHT / 2));
//     }
//     return LimY(*TargetY + y_disp);
//   }
//   return LimY(Y);
// }

int CCamera::GetX() {
  int retval = 0;
  if (TargetX != NULL) {
    switch (TargetMode) {
      case TARGET_MODE_NORMAL: retval = *TargetX + (TargetW ? *TargetW / 2.0f : 0.0f); break;
      case TARGET_MODE_CENTER: retval = *TargetX + (TargetW ? *TargetW / 2.0f : 0.0f) - (WWIDTH / 2); break;
      case TARGET_MODE_FOLLOW: retval = follow_dom.x - (WWIDTH - follow_dom.w) / 2; break;
      default: break;
    }
  } else {
    retval = X;
  }
  return LimX(retval);
}

int CCamera::GetY() {
  int retval = 0;
  if (TargetY != NULL) {
    switch (TargetMode) {
      case TARGET_MODE_NORMAL: retval = *TargetY + (TargetH ? *TargetH / 2.0f : 0.0f); break;
      case TARGET_MODE_CENTER: retval = *TargetY + (TargetH ? *TargetH / 2.0f : 0.0f) - (WHEIGHT / 2); break;
      case TARGET_MODE_FOLLOW: retval = follow_dom.y - (WHEIGHT - follow_dom.h) / 2; break;
      default: break;
    }
  } else {
    retval = Y;
  }
  return LimY(retval);
}

int CCamera::LimX(const int& X) {
  if (uselimits) {
    if (X < X_min) return X_min;
    if (X + WWIDTH - 1 > X_max) return X_max + 1 - WWIDTH;
  }
  return X;
}

int CCamera::LimY(const int& Y) {
  if (uselimits) {
    if (Y < Y_min) return Y_min;
    if (Y + WHEIGHT - 1 > Y_max) return Y_max + 1 - WHEIGHT;
  }
  return Y;
}

SDL_Point CCamera::GetPoint() {
  SDL_Point retval = {GetX(), GetY()};
  return retval;
}

void CCamera::GetNormalXY(int& X, int& Y) {
  X = this->X;
  Y = this->Y;
}

SDL_Point CCamera::GetWinRelPoint(const SDL_Point& absPos) {
  SDL_Point retval = {absPos.x - GetX(), absPos.y - GetY()};
  return retval;
}

SDL_Point CCamera::GetWinRelPoint(const double& rel_x, const double& rel_y) {
  SDL_Point retval = {rel_x - GetX(), rel_y - GetY()};
  return retval;
}

SDL_Point CCamera::GetWinRelPoint(const int& rel_x, const int& rel_y) {
  SDL_Point retval = {rel_x - GetX(), rel_y - GetY()};
  return retval;
}

SDL_Point CCamera::GetCamRelPoint(const SDL_Point& winPos) {
  SDL_Point retval = {winPos.x + GetX(), winPos.y + GetY()};
  return retval;
}

SDL_Point CCamera::GetCamRelPoint(const int& win_x, const int& win_y) {
  SDL_Point retval = {win_x + GetX(), win_y + GetY()};
  return retval;
}

void CCamera::MakeWinRel(int& X, int& Y) {
  X -= GetX();
  Y -= GetY();
}

void CCamera::MakeCamRel(int& X, int& Y) {
  X += GetX();
  Y += GetY();
}

int CCamera::GetCamRelX(const int& X) {
  return X + GetX();
}

int CCamera::GetCamRelY(const int& Y) {
  return Y + GetY();
}

SDL_Point CCamera::ConvertToRel(const SDL_Point& t_pos, const double& Z) {
  SDL_Point r_pos;
  if (Z <= 0.0) return r_pos;

  double half_width  = WWIDTH  / 2.0;
  double half_height = WHEIGHT / 2.0;

  // window center positions
  long double cX = GetX() + half_width;
  long double cY = GetY() + half_height;

  long double dX = t_pos.x - cX;
  long double dY = t_pos.y - cY;

  // relative X, Y positions
  r_pos.x = cX + (dX / Z);
  r_pos.y = cY + (dY / Z);

  return r_pos;
}

SDL_Point CCamera::ConvertToTrue(const SDL_Point& r_pos, const double& Z) {
  SDL_Point t_pos;
  if (Z <= 0.0) return t_pos;

  // window center positions
  long double cX = GetX() + (WWIDTH  / 2.0);
  long double cY = GetY() + (WHEIGHT / 2.0);

  long double dX = r_pos.x - cX;
  long double dY = r_pos.y - cY;

  // true X, Y positions
  t_pos.x = cX + (dX * Z);
  t_pos.y = cY + (dY * Z);

  return t_pos;
}

double CCamera::trueXToRel(const double& true_x, const double& Z) {
  if (Z <= 0.0) return 0.0;

  double half_width = WWIDTH  / 2.0;

  // window center position
  long double cX = GetX() + half_width;

  // separation of true_x from center of camera
  // (no separation means that the object's relative X is at its true X)
  long double dX = true_x - cX;

  // relative X position
  return cX + (dX / Z);
}

double CCamera::trueYToRel(const double& true_y, const double& Z) {
  if (Z <= 0.0) return 0.0;

  double half_height = WHEIGHT / 2.0;

  // window center position
  long double cY = GetY() + half_height;

  // separation of true_y from center of camera
  // (no separation means that the object's relative Y is at its true Y)
  long double dY = true_y - cY;

  // relative Y position
  return cY + (dY / Z);
}

double CCamera::relXToTrue(const double& rel_x, const double& Z) {
  if (Z <= 0.0) return 0.0;

  // window center position
  long double cX = GetX() + (WWIDTH  / 2.0);

  // separation of rel_x from center of camera
  // (no separation means that the object's relative X is at its true X)
  long double dX = rel_x - cX;

  // true X position
  return cX + (dX * Z);
}

double CCamera::relYToTrue(const double& rel_y, const double& Z) {
  // window center position
  long double cY = GetY() + (WHEIGHT / 2.0);

  // separation of rel_y from center of camera
  // (no separation means that the object's relative Y is at its true Y)
  long double dY = rel_y - cY;

  // true Y position
  return cY + (dY * Z);
}

void CCamera::EnableLim() {
  uselimits = true;
}

void CCamera::DisableLim() {
  uselimits = false;
}

void CCamera::ToggleLim() {
  uselimits = !uselimits;
}

bool CCamera::isLim() {
  return uselimits;
}

void CCamera::SetLimits(const int& X_min, const int& Y_min, const int& X_max, const int& Y_max) {
  this->X_min = X_min;
  this->Y_min = Y_min;
  this->X_max = X_max;
  this->Y_max = Y_max;
}

void CCamera::GetLimits(int& X_min, int& Y_min, int& X_max, int& Y_max) {
  X_min = this->X_min;
  Y_min = this->Y_min;
  X_max = this->X_max;
  Y_max = this->Y_max;
}

void CCamera::SetFollowDims(const unsigned int& w, const unsigned int& h) {
  follow_dom.w = w;
  follow_dom.h = h;
}

void CCamera::GetFollowDims(unsigned int& w, unsigned int& h) {
  w = follow_dom.w;
  h = follow_dom.h;
}

SDL_Rect CCamera::GetFollow() {
  return follow_dom;
}

//////////////////////////////////////
//////////////////////////////////////

// void CCamera::D_toggle_displace() {
//   usedisplace = !usedisplace;
// }
