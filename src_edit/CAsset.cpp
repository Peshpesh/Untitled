#include "CAsset.h"

SDL_Texture* CAsset::paltex = NULL;
SDL_Texture* CAsset::arrtex = NULL;

namespace
{
  const SDL_Rect f_AL = {15, 15, ARR_SZ, ARR_SZ};
  const SDL_Rect f_AR = {0,  15, ARR_SZ, ARR_SZ};
  const SDL_Rect f_AU = {15, 0,  ARR_SZ, ARR_SZ};
  const SDL_Rect f_AD = {0,  0,  ARR_SZ, ARR_SZ};
  const SDL_Rect s_AL = {45, 15, ARR_SZ, ARR_SZ};
  const SDL_Rect s_AR = {30, 15, ARR_SZ, ARR_SZ};
  const SDL_Rect s_AU = {45, 0,  ARR_SZ, ARR_SZ};
  const SDL_Rect s_AD = {30, 0,  ARR_SZ, ARR_SZ};
}

CAsset::CAsset()
{
  //
}

bool CAsset::OnInit()
{
  if ((paltex = CSurface::OnLoad("../res_edit/palette.png")) == NULL)
	{
		return false;
	}
  if ((arrtex = CSurface::OnLoad("../res_edit/arrow.png")) == NULL)
	{
		return false;
	}

	return true;
}

SDL_Rect CAsset::getRect(unsigned int X, unsigned int Y, unsigned int W, unsigned int H)
{
	SDL_Rect rect;

	rect.x = X;
	rect.y = Y;
	rect.w = W;
	rect.h = H;

	return rect;
}

SDL_Rect CAsset::getRect(const SDL_Point* A, const SDL_Point* B)
{
  int xmin = (A->x <  B->x) ? A->x : B->x;
  int xmax = (A->x >= B->x) ? A->x : B->x;
  int ymin = (A->y <  B->y) ? A->y : B->y;
  int ymax = (A->y >= B->y) ? A->y : B->y;
  int w = xmax - xmin + 1;
  int h = ymax - ymin + 1;

  SDL_Rect rect = {xmin, ymin, w, h};

  return rect;
}

SDL_Rect CAsset::getTileRect(const SDL_Point* A, const SDL_Point* B)
{
  int xmin = (A->x <  B->x) ? A->x : B->x;
  int xmax = (A->x >= B->x) ? A->x : B->x;
  int ymin = (A->y <  B->y) ? A->y : B->y;
  int ymax = (A->y >= B->y) ? A->y : B->y;

  xmin -= (xmin >= 0) ? (xmin % TILE_SIZE) : (bool)(xmin % TILE_SIZE) * (TILE_SIZE + (xmin % TILE_SIZE));
  ymin -= (ymin >= 0) ? (ymin % TILE_SIZE) : (bool)(ymin % TILE_SIZE) * (TILE_SIZE + (ymin % TILE_SIZE));
  xmax += (xmax >= 0) ? (TILE_SIZE - (xmax % TILE_SIZE) - 1) : -((xmax + 1) % TILE_SIZE);
  ymax += (ymax >= 0) ? (TILE_SIZE - (ymax % TILE_SIZE) - 1) : -((ymax + 1) % TILE_SIZE);

  int w = xmax - xmin + 1;
  int h = ymax - ymin + 1;

  SDL_Rect rect = {xmin, ymin, w, h};

  return rect;
}

SDL_Point CAsset::getPos(int X, int Y)
{
  SDL_Point pos;
  pos.x = X;
  pos.y = Y;
  return pos;
}

SDL_Rect CAsset::getPixel(const SDL_Point* pix)
{
	SDL_Rect rect;

	rect.x = pix->x;
	rect.y = pix->y;
	rect.w = 1;
	rect.h = 1;

	return rect;
}

bool CAsset::inWorkspace(const SDL_Point* pos)
{
  return (pos->x >= 0 && pos->x < WWIDTH && pos->y >= 0 && pos->y < WHEIGHT);
}

bool CAsset::inWorkspace(const int& x, const int& y)
{
  return (x >= 0 && x < WWIDTH && y >= 0 && y < WHEIGHT);
}

bool CAsset::drawLine(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick)
{
  return true;
}

bool CAsset::drawBox(const SDL_Rect* box, const SDL_Point* color, const int& thick)
{
  if (box == NULL || color == NULL) return false;

  SDL_Rect srcR = getPixel(color);
  SDL_Rect dstR;

  // top side
  dstR = getRect(box->x, box->y, box->w, thick);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  // bottom side
  dstR = getRect(box->x, box->y + box->h - thick, box->w, thick);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  // left side
  dstR = getRect(box->x, box->y, thick, box->h);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  // right side
  dstR = getRect(box->x + box->w - thick, box->y, thick, box->h);
  CSurface::OnDraw(paltex, &srcR, &dstR);

  return true;
}

bool CAsset::drawBox(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color, const int& thick)
{
  SDL_Rect box = getRect(A, B);
  return drawBox(&box, color, thick);
}

bool CAsset::drawBoxFill(const SDL_Rect* box, const SDL_Point* color)
{
  if (box == NULL || color == NULL) return false;

  SDL_Rect srcR = getPixel(color);
  if (!CSurface::OnDraw(paltex, &srcR, box)) return false;

  return true;
}

bool CAsset::drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color)
{
  SDL_Rect dstR = getRect(A, B);
  return drawBoxFill(&dstR, color);
}

bool CAsset::drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color)
{
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, &palette::black, str_w)) return false;

  return true;
}

bool CAsset::drawStrBox(const SDL_Rect* box, const int& str_w, const SDL_Point* color, const SDL_Point* str_col)
{
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, str_col, str_w)) return false;

  return true;
}

bool CAsset::drawArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb)
{
  bool retval = false;

  SDL_SetTextureColorMod(arrtex, rgb->r, rgb->g, rgb->b);

  switch (dir)
  {
    case 'L': retval = CSurface::OnDraw(arrtex, &s_AL, dstR); break;
    case 'R': retval = CSurface::OnDraw(arrtex, &s_AR, dstR); break;
    case 'U': retval = CSurface::OnDraw(arrtex, &s_AU, dstR); break;
    case 'D': retval = CSurface::OnDraw(arrtex, &s_AD, dstR); break;
    default: break;
  }

  return retval;
}

bool CAsset::drawArrowFill(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb)
{
  bool retval = false;

  SDL_SetTextureColorMod(arrtex, rgb->r, rgb->g, rgb->b);

  switch (dir)
  {
    case 'L': retval = CSurface::OnDraw(arrtex, &f_AL, dstR); break;
    case 'R': retval = CSurface::OnDraw(arrtex, &f_AR, dstR); break;
    case 'U': retval = CSurface::OnDraw(arrtex, &f_AU, dstR); break;
    case 'D': retval = CSurface::OnDraw(arrtex, &f_AD, dstR); break;
    default: break;
  }

  return retval;
}

bool CAsset::drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb)
{
  if (!drawArrowFill(dstR, dir, rgb))       return false;
  if (!drawArrow(dstR, dir, &rgb::black))   return false;

  return true;
}

bool CAsset::drawStrArrow(const SDL_Rect* dstR, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb)
{
  if (!drawArrowFill(dstR, dir, rgb))   return false;
  if (!drawArrow(dstR, dir, str_rgb))   return false;

  return true;
}

bool CAsset::drawArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawArrow(&dstR, dir, rgb);
}

bool CAsset::drawArrowFill(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawArrowFill(&dstR, dir, rgb);
}

bool CAsset::drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawStrArrow(&dstR, dir, rgb);
}

bool CAsset::drawStrArrow(const SDL_Point* dstPos, const char& dir, const SDL_Color* rgb, const SDL_Color* str_rgb)
{
  SDL_Rect dstR = {dstPos->x, dstPos->y, ARR_SZ, ARR_SZ};
  return drawStrArrow(&dstR, dir, rgb, str_rgb);
}

void CAsset::OnCleanup()
{
  SDL_DestroyTexture(paltex);
  SDL_DestroyTexture(arrtex);
}
