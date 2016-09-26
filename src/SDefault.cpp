#include "SDefault.h"

SDefault::SDefault()
{
  //
}

bool SDefault::OnLoad(SDL_Texture* scenery,
  const unsigned int& Xo, const unsigned int& Yo, const unsigned int& Width, const unsigned int& Height, const unsigned int& MaxFrames)
{
  // if (!CScenery::OnLoad(SDL_Texture* scenery,
  //   const unsigned int& Xo, const unsigned int& Yo, const unsigned int& Width, const unsigned int& Height, const unsigned int& MaxFrames))
  // {
  //   return false;
  // }
  // return true;
  return CScenery::OnLoad(SDL_Texture* scenery,
    const unsigned int& Xo, const unsigned int& Yo, const unsigned int& Width, const unsigned int& Height, const unsigned int& MaxFrames);
}

void SDefault::OnPlace(const int& X, const int& Y, const float& Z, const bool& v_rep, const bool& h_rep, const bool& perm)
{
  CScenery::OnPlace(const int& X, const int& Y, const float& Z, const bool& v_rep, const bool& h_rep, const bool& perm);
}

void SDefault::OnLoop()
{
  CScenery::OnLoop();
}

bool SDefault::OnRender(SDL_Renderer* renderer)
{
  return CScenery(renderer);
}
