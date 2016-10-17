#ifndef _CME_SCENERY_H_
#define _CME_SCENERY_H_

#include "CScenery.h"

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
  double Z_lbound;
  double Z_ubound;

  bool hori_repeat;
  bool vert_repeat;
  bool permanent;

  CMEScenery();

  bool LoadScenery();

  void SubObject(const int& Xc, const int& Yc);

  void AddObject(const int& Xc, const int& Yc);

  bool SaveScenery();
};

#endif
