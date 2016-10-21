#include "CME_Scenery.h"

CMEScenery CMEScenery::ScnControl;

std::vector<CScenery*> CMEScenery::SceneList;
std::vector<SDL_Texture*> CMEScenery::TexList;
std::vector<int> CMEScenery::TexID_List;

CMEScenery::CMEScenery()
{
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
    case SUN: scn_ID = SUN; break;
    case PILLAR: scn_ID = PILLAR; break;
    case WATERFALL: scn_ID = WATERFALL; break;
    default: reset = false; break;
  }
  if (reset)
  {
    hori_repeat = vert_repeat = permanent = false;
  }
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

void CMEScenery::AddObject(SDL_Renderer* renderer, const int& Xc, const int& Yc)
{
  // convert relative X, Y to true coordinates
  int tX = 0;
  int tY = 0;
  ConvertToTrue(Xc, Yc, tX, tY);

  // get object-specific information (Xo, Yo, etc.)
  int tex_ID = 0;
  int Xo = 0, Yo = 0, W = 0, H = 0, MaxFrames = 0;
  if (!GetObjInfo(scn_ID, tex_ID, Xo, Yo, W, H, MaxFrames))
  {
    return;
  }

  // check scenery container for necessary texture
  int loc_ID = 0;
  while (loc_ID < CMEScenery::TexID_List.size())
  {
    if (tex_ID == CMEScenery::TexID_List[loc_ID]) break;
    loc_ID++;
  }
  if (loc_ID == CMEScenery::TexID_List.size())
  {
    // load texture, if not loaded
    AddTexture(renderer, tex_ID);
  }

  // locate index destination in scenery container based on Z
  int i = 0;
  while (i < CMEScenery::SceneList.size())
  {
    if (Z > CMEScenery::SceneList[i]->Z) break;
    i++;
  }

  // dynamically create "new" object and insert into container
  CScenery* tmp_scn;
  tmp_scn = new CScenery;
  tmp_scn->OnLoad(CMEScenery::TexList[loc_ID], Xo, Yo, W, H, MaxFrames);
  tmp_scn->OnPlace(tX, tY, Z, vert_repeat, hori_repeat, permanent);
  CMEScenery::SceneList.insert(CMEScenery::SceneList.begin() + i, tmp_scn);
}

bool CMEScenery::GetObjInfo(const int& queryID, int& tex_ID, int& Xo, int& Yo, int& W, int& H, int& MaxFrames)
{
  bool retval = true;
  switch (queryID)
  {
    case SUN: tex_ID = SCN_COSMO; Xo = 0; Yo = 0; W = 100; H = 100; MaxFrames = 1; break;
    case PILLAR: tex_ID = SCN_ARCH; Xo = 0; Yo = 0; W = 32; H = 126; MaxFrames = 1; break;
    case WATERFALL: tex_ID = SCN_WATER; Xo = 0; Yo = 0; W = 32; H = 32; MaxFrames = 8; break;
    default: retval = false; break;
  }
  return retval;
}

bool CMEScenery::AddTexture(SDL_Renderer* renderer, const int& tex_ID)
{
  bool retval = true;
  SDL_Texture* tmp_tex = NULL;

  switch (tex_ID)
  {
    case SCN_COSMO:
    {
      char TexFile[255] = "../res/scn/cosmic.png";
      if ((tmp_tex = CSurface::OnLoad(TexFile, renderer)) == false) retval = false;
      break;
    }
    case SCN_ARCH:
    {
      char TexFile[255] = "../res/scn/arch.png";
      if ((tmp_tex = CSurface::OnLoad(TexFile, renderer)) == false) retval = false;
      break;
    }
    case SCN_WATER:
    {
      char TexFile[255] = "../res/scn/water.png";
      if ((tmp_tex = CSurface::OnLoad(TexFile, renderer)) == false) retval = false;
      break;
    }
    default: retval = false; break;
  }

  if (retval)
  {
    CMEScenery::TexList.push_back(tmp_tex);   // push back the SDL_texture*
    CMEScenery::TexID_List.push_back(tex_ID); // push back the global texture ID
  }
  return retval;
}

bool CMEScenery::SaveScenery()
{
  return true;
}
