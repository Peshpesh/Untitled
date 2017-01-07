#ifndef _C_SCENERYMOD_H_
#define _C_SCENERYMOD_H_

#include "CScenery.h"
#include <stdio.h>
#include <cstring>
// #include "SDefault.h"

enum SCN_NAME
{
  TEST_A = 0,
  TEST_B, TEST_C,
  // SUN = 0,
  // PILLAR, WATERFALL,
};

class CSceneryMod {
public:
  CSceneryMod();

  // Empties FG, BG, and SDL_Texture containers for CScenery.
  // SDL_Textures are destroyed properly. Should call at prog. termination.
  static bool ClearAll();

  /*  Opens and reads a .scn (scenery) file.
  *   Scenery files must contain:
  *     - A header with the number of SDL_Textures to load
  *     - A list of paths to images to load
  *     - A list of object information; which includes a number
  *       to identify the texture used; an ID to identify the
  *       object as default-style or derivative; and X, Y, and Z
  *       coordinates.
  */
  static bool LoadScenery(char const* sceneryfile, SDL_Renderer* renderer);

  static bool GetInfo(const int& ID, int& X, int& Y, int& W, int& H, int& MaxFrames);
};

#endif
