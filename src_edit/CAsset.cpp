#include "CAsset.h"

SDL_Texture* CAsset::palette = NULL;

CAsset::CAsset()
{
  //
}

bool CAsset::OnInit()
{
  if ((palette = CSurface::OnLoad("../res_edit/palette.png")) == NULL)
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

SDL_Rect CAsset::getPixel(const SDL_Point* pix)
{
	SDL_Rect rect;

	rect.x = pix->x;
	rect.y = pix->y;
	rect.w = 1;
	rect.h = 1;

	return rect;
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
  CSurface::OnDraw(palette, &srcR, &dstR);

  // bottom side
  dstR = getRect(box->x, box->y + box->h - thick, box->w, thick);
  CSurface::OnDraw(palette, &srcR, &dstR);

  // left side
  dstR = getRect(box->x, box->y, thick, box->h);
  CSurface::OnDraw(palette, &srcR, &dstR);

  // right side
  dstR = getRect(box->x + box->w - thick, box->y, thick, box->h);
  CSurface::OnDraw(palette, &srcR, &dstR);

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
  CSurface::OnDraw(palette, &srcR, box);

  return true;
}

bool CAsset::drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color)
{
  return true;
}

void CAsset::OnCleanup()
{
  SDL_DestroyTexture(palette);
}
