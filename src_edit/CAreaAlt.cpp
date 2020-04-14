#include "CAreaAlt.h"

CAreaAlt CAreaAlt::control;

CAreaAlt::CAreaAlt() {
  //
}

void CAreaAlt::OnInit()	{
	MapList.clear();
  DepthList.clear();
	AreaHeight = AreaWidth = 1;

	CMap tempMap;
	tempMap.OnLoad();

	MapList.push_back(tempMap);
}

void CAreaAlt::GetDims(int& mW, int& mH)	{
	mW = AreaWidth;
	mH = AreaHeight;
}

void CAreaAlt::OnRender(const int& CameraX, const int& CameraY, const int& Z) {
  // The area is layered vertically (Z).
  // Layers are rendered one at a time, with the
  // lowest Z (height) being rendered first.
  // For each layer, draw---in order:
  //  1) the static-size surface tiles (grass, dirt, etc.)
  //  2) shadows cast upon surface from objects and otherwise
  //  3) objects (entities, scenery, etc.)
  // IDEA:  it's possible to render the surface tiles in an order to
  //        create the illusion of depth, while also having only one
  //        dimension to the Maplist (which would be "flattened"). Tiles
  //        would have a Z variable to determine rendering order.
  //        This would be nice for efficiency but is probably not necessary.
  //        A 20x20 (400 maps) area with 5 layers should require ~5MB of memory;
  //        can't imagine an area requiring too much more than that.

  if (Z < 0 || Z >= DepthList.size()) {
    CError::handler.ReportErr("CAreaAlt::OnRender -> Bad Z-layer request.");
    return;
  }

  int MapW = MAP_WIDTH * TILE_SIZE;         // in px
  int MapH = MAP_HEIGHT * TILE_SIZE;        // in px
  short Yoffset = DepthList[Z] * TILE_SIZE; // in px

  // Offset is included to account for "vertical" displacement
  // of maps, which appears as a negative shift in Y
  // EX: A depth of 1 is a Yoffset of 32px; ID=0 for this depth should be
  // rendered as if it was placed at Y=-32px, NOT Y=0px.
  int FirstID = -CameraX / MapW;
  FirstID += ((-CameraY + Yoffset) / MapH) * AreaWidth;

  int maxMaps = 4;
  int loopMax = (maxMaps <= MapList.size()) ? mapMaps : MapList.size();

  for (int i = 0; i < loopMax; i++) {
    int ID = FirstID + ((i / 2) * AreaWidth) + (i % 2);
    if (ID < 0 || ID >= MapList.size()) continue;

    int X = ((ID % AreaWidth) * MapW) + CameraX;
    int Y = ((ID / AreaWidth) * MapH) + CameraY - Yoffset;

    MapList[ID].OnRender(X, Y);
  }
}

bool CAreaAlt::OnLoad(char const* File)	{
	// try to load area/maps
  std::string fpath = "../data/maps/";
  std::string ext = ".area";
  std::string fname = fpath + std::string(File) + ext;

	// FILE* FileHandle = fopen(fname.c_str(), "r");
	FILE* FileHandle = fopen(fname.c_str(), "rb");
	if (FileHandle == NULL) {
		CInform::InfoControl.pushInform("---CAREA.Onload---\nfailed to open area file");
		return false;
	}

	// Grab the ID of the tileset for the area
	short setID;
	fread(&setID, sizeof(short), 1, FileHandle);

	// Output AreaWidth & AreaHeight
	fread(&AreaWidth, sizeof(int), 1, FileHandle);
	fread(&AreaHeight, sizeof(int), 1, FileHandle);

	if (!CTileset::TSControl.changeTileset(setID)) {
		CInform::InfoControl.pushInform("---CAREA.Onload---\ncould not load tileset");
		return false;
	}

	MapList.clear();

	for (int X = 0; X < AreaWidth; X++) {
		for (int Y = 0; Y < AreaHeight; Y++) {
			CMap tempMap;
			if (tempMap.OnLoad(FileHandle) == false) {
				fclose(FileHandle);
				return false;
			}
			MapList.push_back(tempMap);
		}
	}
	fclose(FileHandle);
	return true;
}

bool CAreaAlt::OnSave(char const* File) {
	// try to save area/maps
	std::string fpath = "../data/maps/";
	std::string ext = ".area";
	std::string fname = fpath + std::string(File) + ext;
	// FILE* FileHandle = fopen(fname.c_str(), "w");
	FILE* FileHandle = fopen(fname.c_str(), "wb");

	if (FileHandle == NULL)	{
		CInform::InfoControl.pushInform("---CAREA.OnSave---\nfailed to open new area file");
		return false;
	}

	// Output the ID of the tileset for the area
	short setID = CTileset::TSControl.getFileID();
	fwrite(&setID, sizeof(short), 1, FileHandle);

	// Output AreaWidth & AreaHeight
	fwrite(&AreaWidth, sizeof(int), 1, FileHandle);
	fwrite(&AreaHeight, sizeof(int), 1, FileHandle);

	// Output map data to .area file
	for (int Y = 0; Y < AreaHeight; Y++) {
		for (int X = 0; X < AreaWidth; X++) {
			int ID = X + (Y * AreaWidth);
			if (!MapList[ID].OnSave(FileHandle)) return false;
		}
	}

	fclose(FileHandle);
	return true;
}
