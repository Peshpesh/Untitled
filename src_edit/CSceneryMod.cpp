#include "CSceneryMod.h"

CSceneryMod::CSceneryMod()
{
  //
}

bool CSceneryMod::ClearAll()
{
  if (CScenery::SceneList.size() > 0)
  {
    for (int i = (CScenery::SceneList.size() - 1); i >= 0; i--)
    {
      delete CScenery::SceneList[i];
      CScenery::SceneList.erase(CScenery::SceneList.begin() + i);
    }
  }
  if (CScenery::TexList.size() > 0)
  {
    for (int i = (CScenery::TexList.size() - 1); i >= 0; i--)
    {
      SDL_DestroyTexture(CScenery::TexList[i]);
      CScenery::TexList.erase(CScenery::TexList.begin() + i);
    }
  }
  return true;
}

bool CSceneryMod::LoadScenery(char const* sceneryfile)
{
	// Try to open the .scn file
	FILE* FileHandle = fopen(sceneryfile, "r");
	if (FileHandle == NULL) return false;

	// The first entry in the data file is always the number of
  // textures to load.
  int num_tex;
	fscanf(FileHandle, "%d\n", &num_tex);

  // A list of image paths follows the header. Load all images.
  for (int i = 0; i < num_tex; i++)
  {
    char TexFile[255];
    fscanf(FileHandle, "%s\n", TexFile);

    SDL_Texture* tmp_tex = NULL;
    if ((tmp_tex = CSurface::OnLoad(TexFile)) == false)
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
  * Z_loc:  depth of the scenery (multiplied by 10000)
  * v_rep:  vertical repetition flag
  * h_rep:  horizontal repetition flag
  * perm:   permanent position flag
  */
  int tex_ID, scn_ID, X_loc, Y_loc;
  int Z_loc;
  int v_rep, h_rep, perm;
	// while (fscanf(FileHandle, "%d:%d:%d:%d:%lf:%d:%d:%d\n", &tex_ID, &scn_ID, &X_loc, &Y_loc, &Z_loc, &v_rep, &h_rep, &perm) == 8)
	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d:%d:%d\n", &tex_ID, &scn_ID, &X_loc, &Y_loc, &Z_loc, &v_rep, &h_rep, &perm) == 8)
  {
    if (tex_ID >= num_tex || tex_ID < 0) return false;
    if (scn_ID < 0) return false;
    if (Z_loc < 0) return false;

    double Zo = double(Z_loc) / 1000.0;
    int Xo = 0; int Yo = 0;
    int W = 0; int H = 0;
    int MaxFrames = 0;

    CScenery* tmp_scn;
    tmp_scn = new CScenery;
    // the function returns false if a default scenery object is used
    if (!GetInfo(scn_ID, Xo, Yo, W, H, MaxFrames))
    {
      // default scenery object added to container
      // SDefault tmp_scn;
      tmp_scn->OnLoad(CScenery::TexList[tex_ID], Xo, Yo, W, H, MaxFrames);
      tmp_scn->OnPlace(X_loc, Y_loc, Zo, v_rep, h_rep, perm);
    }
    else
    {
      // special scenery object added to container
    }
    CScenery::SceneList.push_back(tmp_scn);
  }
  return true;
}

bool CSceneryMod::GetInfo(const int& ID, int& X, int& Y, int& W, int& H, int& MaxFrames)
{
  bool special_scn = false;
  switch (ID)
  {
    // case TEST_A: X = 0; Y = 0; W = 64; H = 64; MaxFrames = 1; break;
    // case TEST_B: X = 0; Y = 0; W = 256; H = 256; MaxFrames = 1; break;
    // case TEST_C: X = 0; Y = 0; W = 126; H = 126; MaxFrames = 1; break;
    case TEST_A: X = 0; Y = 0; W = 100; H = 100; MaxFrames = 1; break;
    case TEST_B: X = 0; Y = 0; W = 32; H = 126; MaxFrames = 1; break;
    case TEST_C: X = 0; Y = 0; W = 32; H = 32; MaxFrames = 8; break;
    // case SUN: Xo = 0; Yo = 0; W = 100; H = 100; MaxFrames = 1; break;
    // case PILLAR: Xo = 0; Yo = 0; W = 32; H = 126; MaxFrames = 1; break;
    // case WATERFALL: Xo = 0; Yo = 0; W = 32; H = 32; MaxFrames = 8; break;
    default: X = 0; Y = 0; W = 0; H = 0; MaxFrames = 0; break;
  }
  return special_scn;
}
