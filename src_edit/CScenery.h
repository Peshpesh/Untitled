#ifndef _C_SCENERY_H_
#define _C_SCENERY_H_

#include <vector>
#include "CSurface.h"
#include "CAnimation.h"
#include "CCamera.h"
#include "Define.h"

	/*************************************************************************
	*	This virtual base class is designed to provide a foundational
	*	standard for non-interactive visuals on-screen ("scenery"), which
	*	are subject to parallaxing effects. This is done to create
	*	the illusion of depth.
	*
	*	By default, CScenery objects have a few simple functions outside
	*	of construction and destruction:
	*		1.	Loading, whereby the object receives its appropriate pointer
	*				to a SDL_Texture, as well as information on texture position,
	*				size, and number of frames.
	*		2.	Movement and animation (gameloop functions); objects with
	*				MaxFrames > 1 have CurrentFrame updated, and are repositioned
	*				relative to camera motion. Repositioning is weighted by Z.
	*		3.	Standard rendering. ..._repeat flags are checked, and additional
	*				rendering is done if necessary.
	*
	*	In the application's rendering function, CScenery with Z >= 1.0 is rendered
	*	first (before map tiles, entities, etc.). SceneList is rendered
	*	only before HUD objects and menus.
	*
	*	Derivative classes may have additional looping functions. For example,
	* a class may only be animated in certain situations and static in others.
	* The base CScenery class cannot predict all possible evolutions of
	*	scenery, so derivative classes can be made to handle special scenery.
	* In this way, CScenery is structured and implemented similar to CEntity.
	*
	*	CScenery objects require pointers to SDL_Textures, which are often
	*	shared across multiple CScenery objects. To prevent duplicates of
	*	SDL_Texture, TexList contains all CScenery SDL_Texture*s for the active
	*	area. TexList is populated by virtue of "CSceneryMod" functions, as is
	*	SceneList.
	*
	*	Positional values for CScenery objects are "true" values. Due to
	* parallaxing effects, x and y positions recorded in .scn files are
	*	true only if they coincide with the center of the camera.
	*	When a set of scenery is loaded (as in an area change), the true
	*	positions must be used to derive positions relative to the initial
	*	camera location.
	**************************************************************************/

class CScenery {
public:
	static std::vector<CScenery*> SceneList; // All Scenery (polymorphic)

public:
	static std::vector<SDL_Texture*> TexList;		// Container of necessary SDL_Textures

public:
	SDL_Texture*   Tex_Scenery;    // Scenery texture
  CAnimation     Anim_Control;

public:	// texture attributes
  unsigned int Xo;             // X-position on texture
  unsigned int Yo;             // Y-position on texture
  unsigned int Width;          // width of scenery piece within texture
  unsigned int Height;         // height of scenery piece within texture
  // unsigned int MaxFrames;      // number of frames for animated scenery

public:	// dynamic attributes
  int X;           		// True X-position
  int Y;           		// True Y-position
	double Z;   				/* "Depth" of scenery; 1.0f is at map-level,
                       * greater is farther, lesser is closer
											 * see parallax concept .ai file for info
                       */

public:	// placement attributes
  bool vert_repeat;   // texture repeats itself vertically
  bool hori_repeat;   // texture repeats itself horizontally
  bool permanent;     // texture does not move on the screen

public:
	CScenery();
	virtual ~CScenery();

public:
	virtual bool OnLoad(SDL_Texture* scenery,
    const unsigned int& Xo, const unsigned int& Yo, const unsigned int& Width, const unsigned int& Height, const unsigned int& MaxFrames);

	virtual void OnPlace(const int& X, const int& Y, const double& Z, const bool& v_rep, const bool& h_rep, const bool& perm);

	virtual void OnLoop();

	virtual bool OnRender(SDL_Renderer* renderer);
};
#endif
