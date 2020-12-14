#include "CMask.h"

CMask::CMask() {
  mask     = NULL;
  canvas   = NULL;
  compound = NULL;
  maskR.x  = maskR.y = maskR.w = maskR.h = 0;
}

void CMask::setMask(SDL_Texture* mask) {
  if (mask == NULL) return;

  this->mask = mask;
  maskR.x = maskR.y = 0;
  SDL_QueryTexture(mask, NULL, NULL, &maskR.w, &maskR.h);

  if (canvas) SDL_DestroyTexture(canvas);
  canvas = CSurface::CreateTargetTexture(maskR.w, maskR.h);

  if (compound) SDL_DestroyTexture(compound);
  compound = CSurface::CreateTargetTexture(maskR.w, maskR.h);

  SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_NONE);
  // SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
  SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(compound, SDL_BLENDMODE_BLEND);
  clearCanvas();
}

void CMask::setMask(SDL_Texture* mask, const SDL_Rect& srcR) {
  if (mask == NULL) return;

  this->mask = mask;
  maskR = srcR;

  if (canvas) SDL_DestroyTexture(canvas);
  canvas = CSurface::CreateTargetTexture(maskR.w, maskR.h);

  if (compound) SDL_DestroyTexture(compound);
  compound = CSurface::CreateTargetTexture(maskR.w, maskR.h);

  SDL_SetTextureBlendMode(mask, SDL_BLENDMODE_NONE);
  // SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_BLEND);
  SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_ADD);
  SDL_SetTextureBlendMode(compound, SDL_BLENDMODE_BLEND);
  clearCanvas();
}

void CMask::clearCanvas() {
  if (canvas == NULL) return;
  CSurface::ClearTargetTexture(canvas);
}

void CMask::beginDrawing() {
  if (canvas == NULL) return;
  CSurface::SetTargetTexture(canvas, false);
}

void CMask::stopDrawing() {
  CSurface::FreeTargetTexture();
}

void CMask::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const int& X, const int& Y) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  SDL_Point dstP;
  dstP.x = X;
  dstP.y = Y;

  CSurface::OnDraw(src_img, &srcR, &dstP);

  CSurface::FreeTargetTexture();
}

void CMask::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Point& dstP) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  CSurface::OnDraw(src_img, &srcR, &dstP);

  CSurface::FreeTargetTexture();
}

void CMask::drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Rect& dstR) {
  if (src_img == NULL || canvas == NULL) return;

  CSurface::SetTargetTexture(canvas, false);

  CSurface::OnDraw(src_img, &srcR, &dstR);

  CSurface::FreeTargetTexture();
}

void CMask::makeCompound() {
  if (mask == NULL || canvas == NULL || compound == NULL) return;

  CSurface::SetTargetTexture(compound, true);

  SDL_Point origin;
  origin.x = origin.y = 0;

  // apply mask
  CSurface::OnDraw(mask, &maskR, &origin);

  // apply canvas
  CSurface::OnDraw(canvas, &maskR, &origin);

  CSurface::FreeTargetTexture();
}

void CMask::render(const int& X, const int& Y) {
  if (compound == NULL) return;
  CSurface::OnDraw(compound, X, Y);
}

void CMask::cleanup() {
  SDL_DestroyTexture(mask);
  SDL_DestroyTexture(canvas);
  SDL_DestroyTexture(compound);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

SDL_Texture* CMask::createCompound(SDL_Texture* canvas, SDL_Texture* mask) {
  if (canvas == NULL || mask == NULL) return NULL;

  int W, H;
  SDL_QueryTexture(mask, NULL, NULL, &W, &H);

  SDL_Rect srcR;
  srcR.x = srcR.y = 0;
  srcR.w = W;
  srcR.h = H;

  SDL_Point origin;
  origin.x = origin.y = 0;

  SDL_Texture* compound = NULL;
  compound = CSurface::CreateTargetTexture(W, H);
  SDL_SetTextureBlendMode(compound, SDL_BLENDMODE_BLEND);

  SDL_BlendMode src_blend;
  SDL_GetTextureBlendMode(canvas, &src_blend);
  if (src_blend != SDL_BLENDMODE_ADD && src_blend != SDL_BLENDMODE_MOD) {
    // set to "add" by default
    SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_ADD);
  }

  // set and clear target for drawing
  CSurface::SetTargetTexture(compound, true);

  // apply mask
  CSurface::OnDraw(mask, &srcR, &origin);

  // apply canvas
  CSurface::OnDraw(canvas, &srcR, &origin);

  CSurface::FreeTargetTexture();

  if (src_blend != SDL_BLENDMODE_ADD && src_blend != SDL_BLENDMODE_MOD) {
    SDL_SetTextureBlendMode(canvas, src_blend);
  }

  return compound;
}

SDL_Texture* CMask::createCompound(SDL_Texture* canvas, SDL_Texture* mask,
/*<><><><><><><><><><><><><><><>*/ const SDL_Rect& srcR, const SDL_Rect& dstR,
/*<><><><><><><><><><><><><><><>*/ const SDL_Rect& maskR) {
  if (canvas == NULL || mask == NULL) return NULL;

  SDL_Point origin;
  origin.x = origin.y = 0;

  SDL_Texture* compound = NULL;
  compound = CSurface::CreateTargetTexture(maskR.w, maskR.h);
  SDL_SetTextureBlendMode(compound, SDL_BLENDMODE_BLEND);

  SDL_BlendMode src_blend;
  SDL_GetTextureBlendMode(canvas, &src_blend);
  if (src_blend != SDL_BLENDMODE_ADD && src_blend != SDL_BLENDMODE_MOD) {
    // set to "add" by default
    SDL_SetTextureBlendMode(canvas, SDL_BLENDMODE_ADD);
  }

  // set and clear target for drawing
  CSurface::SetTargetTexture(compound, true);

  // apply mask (draw maskR from mask image to origin)
  CSurface::OnDraw(mask, &maskR, &origin);

  // apply canvas (draw srcR from canvas image to dstR)
  CSurface::OnDraw(canvas, &srcR, &dstR);

  CSurface::FreeTargetTexture();

  if (src_blend != SDL_BLENDMODE_ADD && src_blend != SDL_BLENDMODE_MOD) {
    SDL_SetTextureBlendMode(canvas, src_blend);
  }

  return compound;
}
