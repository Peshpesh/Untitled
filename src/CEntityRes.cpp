#include "CEntityRes.h"

SDL_Texture* CEntityRes::Com_Texture = NULL;
SDL_Texture* CEntityRes::Unq_Texture = NULL;
SDL_Texture* CEntityRes::Arm_Texture = NULL;
SDL_Texture* CEntityRes::Bul_Texture = NULL;

CEntityRes::CEntityRes()
{
  //
}

bool CEntityRes::OnInit(SDL_Renderer* renderer)
{
  if ((Com_Texture = CSurface::OnLoad("../res/npc/common.png", renderer)) == NULL) return false;
	if ((Arm_Texture = CSurface::OnLoad("../res/npc/arms.png", renderer)) == NULL) return false;
	if ((Bul_Texture = CSurface::OnLoad("../res/npc/bullet.png", renderer)) == NULL) return false;
  return true;
}

bool CEntityRes::OnLoad(SDL_Renderer* renderer, const int& SetID)
{
  char* SpriteFile = new char[255];
  switch(SetID)
  {
    case SET_DEBUG: std::strcpy(SpriteFile, "../res/npc/debug.png"); break;
    default: break;
  }
  // Load the texture of unique NPCs.
  if ((Unq_Texture = CSurface::OnLoad(SpriteFile, renderer)) == NULL)	return false;

  return true;
}
