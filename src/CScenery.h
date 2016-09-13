#ifndef _CSCENERY_H_
#define _CSCENERY_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CSurface.h"
#include "CAnimation.h"

class CScenery {
public:
	SDL_Texture*   Tex_Scenery;    // Scenery texture
  CAnimation     Anim_Control;

public:
  unsigned int Xo;             // X-position on texture
  unsigned int Yo;             // Y-position on texture
  unsigned int Width;          // width of scenery piece within texture
  unsigned int Height;         // height of scenery piece within texture
  unsigned int MaxFrames;      // number of frames for animated scenery

public:
  float X;            // X-position on screen
  float Y;            // Y-position on screen
  unsigned float Z;   /* "Depth" of scenery; 1.0f is at map-level,
                       * greater is farther, lesser is closer
                       */

public:
  bool vert_repeat;   // texture repeats itself vertically
  bool hori_repeat;   // texture repeats itself horizontally
  bool permanent;     // texture does not move on the screen

public:
	CScenery();

public:
	bool OnLoad(SDL_Texture* scenery,
    const unsigned int& Xo, const unsigned int& Yo, const unsigned int& Width, const unsigned int& Height, const unsigned int& MaxFrames);

  void OnLoop();

	bool OnRender(SDL_Renderer* renderer);
};

#endif
