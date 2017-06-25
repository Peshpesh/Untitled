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
  if (!CSurface::OnDraw(palette, &srcR, box)) return false;

  return true;
}

bool CAsset::drawBoxFill(const SDL_Point* A, const SDL_Point* B, const SDL_Point* color)
{
  return true;
}

bool CAsset::drawButton(const SDL_Rect* box, const int& str_w, const SDL_Point* color)
{
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, &color::black, str_w)) return false;

  return true;
}

bool CAsset::drawButton(const SDL_Rect* box, const int& str_w, const SDL_Point* color, const SDL_Point* str_col)
{
  if (!drawBoxFill(box, color)) return false;
  if (!drawBox(box, str_col, str_w)) return false;

  return true;
}

void CAsset::OnCleanup()
{
  SDL_DestroyTexture(palette);
}
