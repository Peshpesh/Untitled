#include "CME_Scenery.h"

CME_Scenery::CME_Scenery()
{
  tex_ID = 0;
  scn_ID = 0;
  Z = 1.0f;
  Z_lbound = 0.00f;
  Z_ubound = 2.00f;

  hori_repeat = false;
  vert_repeat = false;
  permanent = false;
}

bool CME_Scenery::LoadScenery()
{
  return true;
}

void CME_Scenery::SubObject(const int& Xc, const int& Yc)
{

}

void CME_Scenery::AddObject(const int& Xc, const int& Yc)
{

}

bool CME_Scenery::SaveScenery()
{
  return true;
}
