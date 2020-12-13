#include "CMask.h"

CMask::CMask() {
  mask    = NULL;
  canvas  = NULL;
  maskR.x = maskR.y = maskR.w = maskR.h = 0;
}

void CMask::setMask(SDL_Texture* mask) {
  if (mask == NULL) return;

  this->mask = mask;
  maskR.x = maskR.y = 0;
  SDL_QueryTexture(mask, NULL, NULL, &maskR.w, &maskR.h);

  if (canvas) SDL_DestroyTexture(canvas);
  canvas = CSurface::CreateTargetTexture(maskR.w, maskR.h);

  SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_NONE);
  SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
  resetCanvas();
}

void CMask::setMask(SDL_Texture* mask, const SDL_Rect& srcR) {
  if (mask == NULL) return;

  this->mask = mask;
  maskR = srcR;

  if (canvas) SDL_DestroyTexture(canvas);
  canvas = CSurface::CreateTargetTexture(maskR.w, maskR.h);

  SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_NONE);
  SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
  resetCanvas();
}

void CMask::resetCanvas() {
  if (mask == NULL || canvas == NULL) return;
  SDL_Point origin;
  origin.x = origin.y = 0;
  CSurface::ClearTargetTexture(canvas);
  enableRender();
  CSurface::OnDraw(mask, &maskR, &origin);
  disableRender();
}

void CMask::enableRender() {
  if (canvas == NULL) return;
  CSurface::SetTargetTexture(canvas, false);
}

void CMask::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const int& X, const int& Y) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  SDL_BlendMode src_blend;
  SDL_GetTextureBlendMode(src_img, &src_blend);
  if (src_blend != SDL_BLENDMODE_ADD) {
    SDL_SetTextureBlendMode(src_img, SDL_BLENDMODE_ADD);
  }

  SDL_Point dstP;
  dstP.x = X;
  dstP.y = Y;

  CSurface::OnDraw(src_img, &srcR, &dstP);

  if (src_blend != SDL_BLENDMODE_ADD) {
    SDL_SetTextureBlendMode(src_img, src_blend);
  }

  CSurface::FreeTargetTexture();
}

void CMask::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Point& dstP) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  SDL_BlendMode src_blend;
  SDL_GetTextureBlendMode(src_img, &src_blend);
  if (src_blend != SDL_BLENDMODE_ADD) {
    SDL_SetTextureBlendMode(src_img, SDL_BLENDMODE_ADD);
  }

  CSurface::OnDraw(src_img, &srcR, &dstP);

  if (src_blend != SDL_BLENDMODE_ADD) {
    SDL_SetTextureBlendMode(src_img, src_blend);
  }

  CSurface::FreeTargetTexture();
}

void CMask::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Rect& dstR) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  SDL_BlendMode src_blend;
  SDL_GetTextureBlendMode(src_img, &src_blend);
  if (src_blend != SDL_BLENDMODE_ADD) {
    SDL_SetTextureBlendMode(src_img, SDL_BLENDMODE_ADD);
  }

  CSurface::OnDraw(src_img, &srcR, &dstR);

  if (src_blend != SDL_BLENDMODE_ADD) {
    SDL_SetTextureBlendMode(src_img, src_blend);
  }

  CSurface::FreeTargetTexture();
}

void CMask::disableRender() {
  CSurface::FreeTargetTexture();
}

void CMask::render(const int& X, const int& Y) {
  if (mask == NULL || canvas == NULL) return;
  CSurface::OnDraw(canvas, X, Y);
}

void CMask::cleanup() {
  SDL_DestroyTexture(mask);
  SDL_DestroyTexture(canvas);
}
