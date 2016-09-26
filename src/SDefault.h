#ifndef _S_DEFAULT_H_
#define _S_DEFAULT_H_

#include "CScenery.h"

class SDefault : public CScenery {
public:
  SDefault();

  bool OnLoad(SDL_Texture* scenery,
    const unsigned int& Xo, const unsigned int& Yo, const unsigned int& Width, const unsigned int& Height, const unsigned int& MaxFrames);

  void OnPlace(const int& X, const int& Y, const float& Z, const bool& v_rep, const bool& h_rep, const bool& perm);

  void OnLoop();

  bool OnRender(SDL_Renderer* renderer);
};
#endif
