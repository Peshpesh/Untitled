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

SDL_Rect CAsset::getPixel(const SDL_Point* pix)
{
	SDL_Rect rect;

	rect.x = pix->x;
	rect.y = pix->y;
	rect.w = 1;
	rect.h = 1;

	return rect;
}

bool CAsset::drawLine(SDL_Point* A, SDL_Point* B, SDL_Point* color, const int& thick)
{
  return true;
}

bool CAsset::drawBox(SDL_Rect* box, const SDL_Point* color, const int& thick)
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

bool CAsset::drawBox(SDL_Point* A, SDL_Point* B, SDL_Point* color, const int& thick)
{
  return true;
}

bool CAsset::drawBoxFill(SDL_Rect* box, SDL_Point* color)
{
  if (box == NULL || color == NULL) return false;

  SDL_Rect srcR = getPixel(color);
  CSurface::OnDraw(palette, &srcR, box);

  return true;
}

bool CAsset::drawBoxFill(SDL_Point* A, SDL_Point* B, SDL_Point* color)
{
  return true;
}

void CAsset::OnCleanup()
{
  SDL_DestroyTexture(palette);
}
