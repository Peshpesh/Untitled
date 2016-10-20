#ifndef _CME_SCENERY_H_
#define _CME_SCENERY_H_

#include "CScenery.h"

enum scn_texture
{
  SCN_COSMO = 0,
  SCN_ARCH,
  SCN_WATER,
};

enum scenery
{
  SUN = 0,
  PILLAR,
  WATERFALL,
};

class CMEScenery
{
public:
  static CMEScenery ScnControl;

public:
  static std::vector<CScenery*> SceneList;
  static std::vector<SDL_Texture*> TexList;
  static std::vector<int> TexID_List;

public:
  int tex_ID; // ID for active texture
  int scn_ID; // ID for active scenery
  double Z;
  double Z_l;
  double Z_u;

  bool hori_repeat;
  bool vert_repeat;
  bool permanent;

  CMEScenery();

  bool LoadScenery();

  void SwitchObj(int queryID);

  bool GetObjInfo(int queryID, int& Xo, int& Yo, int& W, int& H, int& MaxFrames);

  void ConvertToTrue(const int& rX, const int& rY, int& tX, int& tY);

  void ConvertToRel(const int& tX, const int& tY, int& rX, int& rY);

  void SubObject(const int& Xc, const int& Yc);

  void AddObject(const int& Xc, const int& Yc);

  bool SaveScenery();
};

#endif
