#include "CSceneryEdit.h"

CSceneryEdit CSceneryEdit::ScnControl;

std::vector<CScenery*> CSceneryEdit::SceneList;
std::vector<int> CSceneryEdit::ScnID_List;
std::vector<SDL_Texture*> CSceneryEdit::TexList;
std::vector<int> CSceneryEdit::TexID_List;

CSceneryEdit::CSceneryEdit() {
  resetSettings();
}

void CSceneryEdit::resetSettings() {
  scn_ID = 0;
  Z = 1.00f;
  Zl = 0.00f;
  Zu = 2.00f;
  hori_repeat = false;
  vert_repeat = false;
  permanent = false;
}

void CSceneryEdit::resetAll() {
  resetSettings();

  for (int i = 0; i < SceneList.size(); i++) {
    delete SceneList[i];
  }

  SceneList.clear();

  for (int i = 0; i < TexList.size(); i++) {
    SDL_DestroyTexture(TexList[i]);
  }

  TexList.clear();

  ScnID_List.clear();
  TexID_List.clear();
}

bool CSceneryEdit::LoadScenery(char const* sceneryfile) {
  // NOTE: The local texture ID, or the texture ID relative to the
  // Z position of groups of textures, is meaningless in the scenery editor.
  // Thus, number of textures at the start of the file, the paths to textures,
  // and the local texture IDs are not necessary. We can use the scenery object
  // IDs to load textures as we normally would in the editor; and if/when we save,
  // local texture IDs will be derived and recorded.

  // Try to open the .scn file
  std::string fpath = "../data/maps/";
  std::string ext = ".scn";
  std::string fname = fpath + std::string(sceneryfile) + ext;
	FILE* FileHandle = fopen(fname.c_str(), "r");
	if (FileHandle == NULL) return false;

  resetAll();

	// The first entry in the data file is always the number of
  // textures to load.
  int num_tex;
	fscanf(FileHandle, "%d\n", &num_tex);

  // A list of image paths follows the header. Scan all, but do nothing more.
  for (int i = 0; i < num_tex; i++) {
    char TexFile[255];
    fscanf(FileHandle, "%s\n", TexFile);
  }

  /* Lastly comes a map of information, with each line containing eight values:
  * t_ID: which texture is used for the object (not used here)
  * s_ID: scenery object ID
  * X_loc:  true x-position in the area
  * Y_loc:  true y-position in the area
  * Z_loc:  depth of the scenery (multiplied by 1000)
  * v_rep:  vertical repetition flag
  * h_rep:  horizontal repetition flag
  * perm:   permanent position flag
  */
  int t_ID, s_ID, X_loc, Y_loc;
  int Z_loc;
  int v_rep, h_rep, perm;
	while (fscanf(FileHandle, "%d:%d:%d:%d:%d:%d:%d:%d\n", &t_ID, &s_ID, &X_loc, &Y_loc, &Z_loc, &v_rep, &h_rep, &perm) == 8)
  {
    if (s_ID < 0) return false;
    if (Z_loc < 0) return false;

    // Get the scenery object's static info, including global texture ID
    double Zo = double(Z_loc) / 1000.0;
    int Xo; int Yo;
    int W; int H;
    int MaxFrames;
    if (!GetObjInfo(s_ID, t_ID, Xo, Yo, W, H, MaxFrames)) return false;

    // check texture ID container for scenery's required texture
    int loc_ID = 0;
    while (loc_ID < TexID_List.size())
    {
      if (t_ID == TexID_List[loc_ID]) break;
      loc_ID++;
    }
    if (loc_ID == TexID_List.size())
    {
      // load texture, if not loaded
      if (!AddTexture(t_ID)) return false;
    }

    // dynamically create "new" object and insert into container
    CScenery* tmp_scn;
    tmp_scn = new CScenery;
    tmp_scn->OnLoad(TexList[loc_ID], Xo, Yo, W, H, MaxFrames);
    tmp_scn->OnPlace(X_loc, Y_loc, Zo, v_rep, h_rep, perm);
    SceneList.push_back(tmp_scn);
    ScnID_List.push_back(s_ID);
  }
  return true;
}

void CSceneryEdit::SwitchObj(int queryID)
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

void CSceneryEdit::ConvertToTrue(const int& rX, const int& rY, const double& oZ, double& tX, double& tY)
{
  // window center positions
  double cX = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
  double cY = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);
  // true X, Y positions
  tX = (cX * (1 - oZ)) + (rX * oZ);
  tY = (cY * (1 - oZ)) + (rY * oZ);
}

void CSceneryEdit::ConvertToRel(const int& tX, const int& tY, const double& oZ, double& rX, double& rY)
{
  // window center positions
  double cX = CCamera::CameraControl.GetX() + ((WWIDTH - 1) / 2.0);
  double cY = CCamera::CameraControl.GetY() + ((WHEIGHT - 1) / 2.0);
  // relative X, Y positions
  rX = (tX - (cX * (1 - oZ))) / oZ;
  rY = (tY - (cY * (1 - oZ))) / oZ;
}

void CSceneryEdit::SubObject(const int& Xc, const int& Yc)
{
  // initialize variables for identifying an object to remove
  float dZ_min = 0.0f;
  int i_scn = -1;
  for (int i = SceneList.size() - 1; i >= 0; i--)
  {
    if (SceneList[i]->Z < Zl) continue; // Z out of bounds; continue in loop
    if (SceneList[i]->Z > Zu) break;    // Z and all following (greater) Z's are out of bounds; break loop
    // Using the scn object's true X, Y, Z-- get X, Y relative to window PLUS camera displacement
    double Xi, Yi;
    ConvertToRel(SceneList[i]->X, SceneList[i]->Y, SceneList[i]->Z, Xi, Yi);
    double Xf = Xi + SceneList[i]->Width - 1;
    double Yf = Yi + SceneList[i]->Height - 1;
    // Xc and Yc are position of the click relative to window PLUS camera displacement
    // Check to see if the click is within the perimeter of current object in loop
    if ((Xc >= Xi) && (Xc <= Xf) && (Yc >= Yi) && (Yc <= Yf))
    {
      // click is over scenery object
      float dZ = SceneList[i]->Z - Z;
      if (dZ < 0.0f)
      {
        dZ = -dZ;
      }
      if ((i_scn < 0) || (dZ < dZ_min))
      {
        dZ_min = dZ;
        i_scn = i;
      }
    }
  }
  // remove scenery object, if one was identified
  if (i_scn >= 0)
  {
    // Find the local texture index associated with the targeted scenery
    int i_tex;
    for (int i = 0; i < TexList.size(); i++)
    {
      if (SceneList[i_scn]->Tex_Scenery == TexList[i])
      {
        i_tex = i;
        break;
      }
    }
    // Destroy the scenery object and ID
    delete SceneList[i_scn];
    SceneList.erase(SceneList.begin() + i_scn);
    ScnID_List.erase(ScnID_List.begin() + i_scn);

    // Scan remaining objects for texture associated with deleted object
    bool del_tex = true;
    for (int i = 0; i < SceneList.size(); i++)
    {
      if (SceneList[i]->Tex_Scenery == TexList[i_tex])
      {
        del_tex = false;
        break;
      }
    }
    // If the SDL_texture associated with the delted object is no longer needed...
    if (del_tex)
    {
      // Destroy that texture.
      SDL_DestroyTexture(TexList[i_tex]);
      TexList.erase(TexList.begin() + i_tex);
      // Destroy that texture's global ID.
      TexID_List.erase(TexID_List.begin() + i_tex);
    }
  }
}

void CSceneryEdit::AddObject(const int& Xc, const int& Yc)
{
  // convert relative X, Y to true coordinates
  double tX = 0.0;
  double tY = 0.0;
  if (!permanent)
  {
    ConvertToTrue(Xc, Yc, Z, tX, tY);
  }
  else
  {
    tX = Xc - CCamera::CameraControl.GetX();
    tY = Yc - CCamera::CameraControl.GetY();
  }

  // get object-specific information (Xo, Yo, etc.)
  int tex_ID = 0;
  int Xo = 0, Yo = 0, W = 0, H = 0, MaxFrames = 0;
  if (!GetObjInfo(scn_ID, tex_ID, Xo, Yo, W, H, MaxFrames))
  {
    return;
  }

  // check scenery container for necessary texture
  int loc_ID = 0;
  while (loc_ID < CSceneryEdit::TexID_List.size())
  {
    if (tex_ID == CSceneryEdit::TexID_List[loc_ID]) break;
    loc_ID++;
  }
  if (loc_ID == CSceneryEdit::TexID_List.size())
  {
    // load texture, if not loaded
    AddTexture(tex_ID);
  }

  // locate index destination in scenery container based on Z
  int i = 0;
  while (i < CSceneryEdit::SceneList.size())
  {
    if (Z > CSceneryEdit::SceneList[i]->Z) break;
    i++;
  }

  // dynamically create "new" object and insert into container
  CScenery* tmp_scn;
  tmp_scn = new CScenery;
  tmp_scn->OnLoad(CSceneryEdit::TexList[loc_ID], Xo, Yo, W, H, MaxFrames);
  tmp_scn->OnPlace(tX, tY, Z, vert_repeat, hori_repeat, permanent);
  CSceneryEdit::SceneList.insert(CSceneryEdit::SceneList.begin() + i, tmp_scn);
  CSceneryEdit::ScnID_List.insert(CSceneryEdit::ScnID_List.begin() + i, scn_ID);
}

bool CSceneryEdit::GetObjInfo(const int& queryID, int& tex_ID, int& Xo, int& Yo, int& W, int& H, int& MaxFrames)
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

bool CSceneryEdit::GetObjInfo(const int& queryID, int& tex_ID)
{
  bool retval = true;
  switch (queryID)
  {
    case SUN: tex_ID = SCN_COSMO; break;
    case PILLAR: tex_ID = SCN_ARCH; break;
    case WATERFALL: tex_ID = SCN_WATER; break;
    default: retval = false; break;
  }
  return retval;
}

bool CSceneryEdit::AddTexture(const int& tex_ID)
{
  bool retval = true;
  SDL_Texture* tmp_tex = NULL;

  switch (tex_ID)
  {
    case SCN_COSMO:
    {
      char TexFile[255] = "../res/scn/cosmic.png";
      if ((tmp_tex = CSurface::OnLoad(TexFile)) == false) retval = false;
      break;
    }
    case SCN_ARCH:
    {
      char TexFile[255] = "../res/scn/arch.png";
      if ((tmp_tex = CSurface::OnLoad(TexFile)) == false) retval = false;
      break;
    }
    case SCN_WATER:
    {
      char TexFile[255] = "../res/scn/water.png";
      if ((tmp_tex = CSurface::OnLoad(TexFile)) == false) retval = false;
      break;
    }
    default: retval = false; break;
  }

  if (retval)
  {
    CSceneryEdit::TexList.push_back(tmp_tex);   // push back the SDL_texture*
    CSceneryEdit::TexID_List.push_back(tex_ID); // push back the global texture ID
  }
  else
  {

  }
  return retval;
}

bool CSceneryEdit::SaveScenery(char const* areaname)
{
  char pre[] = "../data/maps/";
  char ext[] = ".scn";
  char* filename = new char[std::strlen(areaname) + std::strlen(pre) + std::strlen(ext) + 1];
  std::strcpy(filename, pre);
  std::strcat(filename, areaname);
  std::strcat(filename, ext);
  FILE* FileHandle = fopen(filename, "w");
  delete filename;

  if (FileHandle == NULL)	{
    return false;
  }

  // Output number of textures to load
  fprintf(FileHandle, "%d\n", TexList.size());

  // Output the texture file paths
  if (!SaveTexPaths(FileHandle))
  {
    fclose(FileHandle);
    return false;
  }

  // Output list of object information
  for (int i = 0; i < SceneList.size(); i++)
  {
    int t_ID;
    if (!GetObjInfo(ScnID_List[i], t_ID))
    {
      fclose(FileHandle);
      return false;
    }
    int j = 0;
    while (j < TexList.size())
    {
      if (t_ID ==  TexID_List[j])
      {
        t_ID = j;
        break;
      }
      j++;
    }
    int s_ID = ScnID_List[i];
    int X = SceneList[i]->X;
    int Y = SceneList[i]->Y;
    int Z_mag =  SceneList[i]->Z * Z_MAGNIFIER;
    int VR_flag = SceneList[i]->vert_repeat;
    int HR_flag = SceneList[i]->hori_repeat;
    int P_flag = SceneList[i]->permanent;

    fprintf(FileHandle, "%d:%d:%d:%d:%d:%d:%d:%d\n", t_ID, s_ID, X, Y, Z_mag, VR_flag, HR_flag, P_flag);
  }
  fclose(FileHandle);
  return true;
}

bool CSceneryEdit::SaveTexPaths(FILE* ofile)
{
  if (ofile == NULL) return false;

  for (int i = 0; i < TexList.size(); i++)
  {
    int ID = TexID_List[i];
    switch (ID)
    {
      case SCN_COSMO:
      {
        char TexFile[255] = "../res/scn/cosmic.png";
        fprintf(ofile, "%s\n", TexFile);
        break;
      }
      case SCN_ARCH:
      {
        char TexFile[255] = "../res/scn/arch.png";
        fprintf(ofile, "%s\n", TexFile);
        break;
      }
      case SCN_WATER:
      {
        char TexFile[255] = "../res/scn/water.png";
        fprintf(ofile, "%s\n", TexFile);
        break;
      }
      default: break;
    }
  }
  return true;
}

bool CSceneryEdit::RenderName(const int& fontID, const int& Xo, const int& Yo)
{
  bool retval = true;
  char scnname[10];
  switch (scn_ID)
  {
    case SUN: std::strcpy(scnname, "SUN"); break;
    case PILLAR: std::strcpy(scnname, "PILLAR"); break;
    case WATERFALL: std::strcpy(scnname, "WATRFL"); break;
    default: retval = false; break;
  }
  if (retval) Font::Write(fontID, scnname, Xo, Yo);
  return retval;
}
