#include "CME_Scenery.h"

CMEScenery CMEScenery::ScnControl;

std::vector<CScenery*> CMEScenery::SceneList;
std::vector<SDL_Texture*> CMEScenery::TexList;
std::vector<int> CMEScenery::TexID_List;

CMEScenery::CMEScenery()
{
  tex_ID = 0;
  scn_ID = 0;
  Z = 1.0f;
  Z_l = 0.00f;
  Z_u = 2.00f;

  hori_repeat = false;
  vert_repeat = false;
  permanent = false;
}

bool CMEScenery::LoadScenery()
{
  return true;
}

void CMEScenery::SubObject(const int& Xc, const int& Yc)
{

}

void CMEScenery::AddObject(const int& Xc, const int& Yc)
{

}

bool CMEScenery::SaveScenery()
{
  return true;
}
