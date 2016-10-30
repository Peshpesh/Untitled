#ifndef _CME_SCENERY_H_
#define _CME_SCENERY_H_

#include "CScenery.h"
#include "Font.h"
#include <cstring>

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
  int scn_ID; // ID for active scenery
  double Z;
  double Zl;
  double Zu;

  bool hori_repeat;
  bool vert_repeat;
  bool permanent;

  CMEScenery();

  bool LoadScenery();

  void SwitchObj(int queryID);

  void ConvertToTrue(const int& rX, const int& rY, float& tX, float& tY);

  void ConvertToRel(const int& tX, const int& tY, int& rX, int& rY);

  void SubObject(const int& Xc, const int& Yc);

  void AddObject(SDL_Renderer* renderer, const int& Xc, const int& Yc);

  bool GetObjInfo(const int& queryID, int& tex_ID, int& Xo, int& Yo, int& W, int& H, int& MaxFrames);

  bool AddTexture(SDL_Renderer* renderer, const int& tex_ID);

  bool SaveScenery();

  bool RenderName(SDL_Renderer* renderer, SDL_Texture* Font, const int& Xo, const int& Yo);
};

#endif