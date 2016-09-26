#include "CSceneryMod.h"

CSceneryMod::CSceneryMod()
{
  //
}

bool CSceneryMod::ClearAll()
{
  if (CScenery::FG_SceneList.size() > 0)
  {
    for (int i = (CScenery::FG_SceneList.size() - 1); i >= 0; i--)
    {
      delete CScenery::FG_SceneList[i];
      CScenery::FG_SceneList.erase(CScenery::FG_SceneList.begin() + i);
    }
  }
  if (CScenery::BG_SceneList.size() > 0)
  {
    for (int i = (CScenery::BG_SceneList.size() - 1); i >= 0; i--)
    {
      delete CScenery::BG_SceneList[i];
      CScenery::BG_SceneList.erase(CScenery::BG_SceneList.begin() + i);
    }
  }
  if (CScenery::TexList.size() > 0)
  {
    for (int i = (CScenery::TexList.size() - 1); i >= 0; i--)
    {
      SDL_DestroyTexture(CScenery::TexList[i]);
      delete CScenery::TexList[i];
      CScenery::TexList.erase(CScenery::TexList.begin() + i);
    }
  }
  return true;
}

bool CSceneryMod::LoadScenery(char const* sceneryfile, SDL_Renderer* renderer)
{
	int num_tex, tex_ID, scn_ID, X_loc, Y_loc;
  float Z_loc;
  bool v_rep, h_rep, perm;

	// Try to open the .scn file
	FILE* FileHandle = fopen(sceneryfile, "r");
	if (FileHandle == NULL) return false;

	// The first entry in the data file is always the number of
  // textures to load.
	fscanf(FileHandle, "%d\n", &num_tex);

  // A list of image paths follows the header. Load all images.
  for (int i = 0; i < num_tex; i++)
  {
    char TexFile[255];
    fscanf(FileHandle, "%s\n", TexFile);

    SDL_Texture* tmp_tex = NULL;
    if ((tmp_tex = CSurface::OnLoad(TexFile, renderer)) == false)
    {
      fclose(FileHandle);
      return false;
    }
    CScenery::TexList.push_back(tmp_tex);
  }

  /* Lastly comes a map of information, with each line containing eight necessary values:
  * tex_ID: which texture is used for the object
  * scn_ID: what kind of scenery
  * X_loc:  true x-position in the area
  * Y_loc:  true y-position in the area
  * Z_loc:  depth of the scenery
  * v_rep:  vertical repetition flag
  * h_rep:  horizontal repetition flag
  * perm:   permanent position flag
  */
	while (fscanf(FileHandle, "%d:%d:%d:%d:%f:%d:%d:%d\n", &tex_ID, &scn_ID, &X_loc, &Y_loc, &Z_loc, &v_rep, &h_rep, &perm) == 8)
  {
    if (tex_ID >= num_tex || tex_ID < 0) return false;
    if (scn_ID < 0) return false;
    if (Z_loc < 0.0f) return false;

    int Xo = 0; int Yo = 0;
    int W = 0; int H = 0;
    int MaxFrames = 0;

    // the function returns false if a default scenery object is used
    if (!GetInfo(scn_ID, Xo, Yo, W, H, MaxFrames))
    {
      // default scenery object added to container
      SDefault tmp_scn;
      tmp_scn.OnLoad(CScenery::TexList[tex_ID], Xo, Yo, W, H, MaxFrames);
      tmp_scn.OnPlace(X_loc, Y_loc, Z_loc, v_rep, h_rep, perm);
    }
    else
    {
      // special scenery object added to container
    }
  }
  return true;
}

bool CSceneryMod::GetInfo(const int& ID, int& X, int& Y, int& W, int& H, int& MaxFrames)
{
  bool special_scn = false;
  switch (ID)
  {
    default: X = 0; Y = 0; W = 0; H = 0; MaxFrames = 0; break;
  }
  return special_scn;
}
