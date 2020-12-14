#ifndef _C_MASK_H_
#define _C_MASK_H_

#include "CSurface.h"

class CMask {

  /* ------------------------------------------------------------- */
  /* members for creating and maintaining a dynamic compound image */
  /* ------------------------------------------------------------- */

  SDL_Texture* mask;      // the image to apply as a mask
  SDL_Texture* canvas;    // the working canvas upon which to apply a mask
  SDL_Texture* compound;  // the compound image of the masked canvas

  SDL_Rect maskR;

public:
  CMask();

  /* specify the (part of) image to act as a mask for the canvas */
  void setMask(SDL_Texture* mask);
  void setMask(SDL_Texture* mask, const SDL_Rect& srcR);

  /* clear the canvas */
  void clearCanvas();

  /* set the canvas as the rendering target */
  void beginDrawing();

  /* disable the canvas as a rendering target */
  void stopDrawing();

  /* enable rendering to the canvas, draw onto it, and then disable rendering */
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const int& X, const int& Y);
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Point& dstP);
  void drawToCanvas(SDL_Texture* src_img, const SDL_Rect& srcR, const SDL_Rect& dstR);

  /* combine the mask and canvas to yield the compound image */
  void makeCompound();

  /* render the compound (masked canvas) to the window */
  void render(const int& X, const int& Y);

  void cleanup();


  /* --------------------------------------------------------------------- */
  /* stand-alone functions for creating a static compound image on the fly */
  /* --------------------------------------------------------------------- */

  /* create & return a compound image using existing mask and canvas images */
  static SDL_Texture* createCompound(SDL_Texture* canvas, SDL_Texture* mask);
  static SDL_Texture* createCompound(SDL_Texture* canvas, SDL_Texture* mask,
                                     const SDL_Rect& srcR, const SDL_Rect& dstR,
                                     const SDL_Rect& maskR);

};
#endif
