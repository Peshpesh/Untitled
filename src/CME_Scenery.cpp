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

void CMEScenery::SwitchObj(int queryID)
{
  bool reset = true;
  switch (queryID)
  {
    case SUN: scn_ID = SUN; tex_ID = SCN_COSMO; break;
    case PILLAR: scn_ID = PILLAR; tex_ID = SCN_ARCH; break;
    case WATERFALL: scn_ID = WATERFALL; tex_ID = SCN_WATER; break;
    default: reset = false; break;
  }
  if (reset)
  {
    hori_repeat = vert_repeat = permanent = false;
  }
}

bool CMEScenery::GetObjInfo(int queryID, int& Xo, int& Yo, int& W, int& H, int& MaxFrames)
{
  bool retval = true;
  switch (queryID)
  {
    case SUN: Xo = 0; Yo = 0; W = 100; H = 100; MaxFrames = 1; break;
    case PILLAR: Xo = 0; Yo = 0; W = 32; H = 126; MaxFrames = 1; break;
    case WATERFALL: Xo = 0; Yo = 0; W = 32; H = 32; MaxFrames = 8; break;
    default: retval = false; break;
  }
  return retval;
}

void CMEScenery::ConvertToTrue(const int& rX, const int& rY, int& tX, int& tY)
{

}

void CMEScenery::ConvertToRel(const int& tX, const int& tY, int& rX, int& rY)
{

}

void CMEScenery::SubObject(const int& Xc, const int& Yc)
{

}

void CMEScenery::AddObject(const int& Xc, const int& Yc)
{
  // How to add new scenery object:
  // #1: convert relative X, Y to true coordinates
  // #2a: check scenery container for necessary texture
  // #2b: load texture, if not loaded
  // #3: locate index destination in scenery container based on Z
  // #4: get object-specific information (Xo, Yo, etc.)
  // #5: dynamically "new" object and insert into container
  int tX = 0;
  int tY = 0;
  ConvertToTrue(Xc, Yc, tX, tY);

  int loc_ID = 0;
  while (loc_ID < CMEScenery::TexID_List.size())
  {
    if (tex_ID == CMEScenery::TexID_List[loc_ID]) break;
    loc_ID++;
  }
  if (loc_ID == CMEScenery::TexID_List.size())
  {
    // tex_id was not found in container of global ID
    // implies that texture required is not yet loaded...
  }

  
}

bool CMEScenery::SaveScenery()
{
  return true;
}
