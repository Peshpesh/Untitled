#ifndef _C_MASK_H_
#define _C_MASK_H_

#include "CSurface.h"

class CMask {

  SDL_Texture* mask;
  SDL_Texture* canvas;
  SDL_Rect maskR;

public:
  CMask();

  /* specify the (part of) image to act as a mask for the canvas */
  void setMask(SDL_Texture* mask);
  void setMask(SDL_Texture* mask, const SDL_Rect& srcR);

  /* clear the canvas and reapply the mask */
  void resetCanvas();

  /* set the canvas as the rendering target */
  void enableRender();

  /* disable the canvas as a rendering target */
  void disableRender();

  /* enable rendering to the canvas, draw onto it, and disable rendering  */
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const int& X, const int& Y);
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Point& dstP);
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Rect& dstR);

  /* render the canvas to the window */
  void render(const int& X, const int& Y);

  /* destroy canvas */
  void cleanup();

};
#endif
