#ifndef _C_SCENERYEDIT_H_
#define _C_SCENERYEDIT_H_

#include "CScenery.h"
#include "Define.h"
#include "CFont.h"
#include <cstring>
#include <string>
#include <stdio.h>

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

class CSceneryEdit
{
public:
  static CSceneryEdit ScnControl;

public:
  static std::vector<CScenery*> SceneList;
  static std::vector<int> ScnID_List;
  static std::vector<SDL_Texture*> TexList;
  static std::vector<int> TexID_List;

public:
  int scn_ID; // ID for active scenery
  double Z;
  double Zl;
  double Zu;

  bool hori_repeat;
  bool vert_repeat;
  bool permanent;

  CSceneryEdit();

  void resetSettings();

  void resetAll();

  bool LoadScenery(char const* sceneryfile);

  void SwitchObj(int queryID);

  void ConvertToTrue(const int& rX, const int& rY, const double& oZ, double& tX, double& tY);

  void ConvertToRel(const int& tX, const int& tY, const double& oZ, double& rX, double& rY);

  void SubObject(const int& Xc, const int& Yc);

  void AddObject(const int& Xc, const int& Yc);

  bool GetObjInfo(const int& queryID, int& tex_ID, int& Xo, int& Yo, int& W, int& H, int& MaxFrames);
  bool GetObjInfo(const int& queryID, int& tex_ID);

  bool AddTexture(const int& tex_ID);

  bool SaveScenery(char const* areaname);
  bool SaveTexPaths(FILE* ofile);

  bool RenderName(const int& fontID, const int& Xo, const int& Yo);
};

#endif
