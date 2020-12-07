#include "CPlanArea.h"

CPlanArea CPlanArea::control;

namespace {
  std::string FPATH = "../data/maps/";
  std::string EXT = ".pvm";
}

CPlanArea::CPlanArea() {
  //
}

void CPlanArea::OnInit()  {
  LayerList.clear();
  AreaHeight = AreaWidth = 1;

  CPlanMap tempMap;
  tempMap.OnLoad();

  CPlanLayer tempLayer;
  tempLayer.MapList.push_back(tempMap);

  LayerList.push_back(tempLayer);
}

void CPlanArea::addLayer(const short& K, const short& Z) {
  if (K < 0 || K > LayerList.size()) return;   // second condition has no =
                                               // as we're adding a layer

  // load an empty map
  CPlanMap tempMap;
  tempMap.OnLoad();

  // if the requested Z is below all the existing layers,
  // then "lift" them such that the new layer is the new 0-layer.
  if (Z < 0) {
    for (int k = 0; k < LayerList.size(); k++) LayerList[k].Z -= Z;
  }

  // create new layer at target Z with W * H empty maps
  CPlanLayer tempLayer;
  tempLayer.Z = (Z >= 0) ? Z : 0;
  for (int i = 0; i < AreaWidth * AreaHeight; i++) {
    tempLayer.MapList.push_back(tempMap);
  }
  // insert the new layer into the LayerList vector
  LayerList.insert(LayerList.begin() + K, tempLayer);
}

void CPlanArea::delLayer(const short& K) {
  if (K < 0 || K >= LayerList.size()) return;
  LayerList[K].MapList.clear();  // not sure if this is necessary to clear memory,
                                 // but just in case...
  LayerList.erase(LayerList.begin() + K);
}

void CPlanArea::GetDims(int& mW, int& mH)  {
  mW = AreaWidth;
  mH = AreaHeight;
}



// CPlanMap* CPlanArea::GetMap(int X, int Y, int k) {
//   // Note that X and Y .
//
// }
//
CPlanTile* CPlanArea::GetTile(const int& X, const int& Y, const int& k) {
  if (X < 0 || Y < 0 || k < 0 \
            || X >= (AreaWidth * MAP_WIDTH * TILE_SIZE) \
            || Y >= (AreaHeight * MAP_HEIGHT * TILE_SIZE) \
            || k >= LayerList.size()) return NULL;

  int mapWidth = MAP_WIDTH * TILE_SIZE;
  int mapHeight = MAP_HEIGHT * TILE_SIZE;
  int ID = (X / mapWidth) + (Y / mapHeight) * AreaWidth;
  return LayerList[k].MapList[ID].GetTile(X % mapWidth, Y % mapHeight);
}

// CPlanTile* CPlanArea::GetTileCopy(const int& X, const int& Y, const int& k) {
//   if (X < 0 || Y < 0 || k < 0 \
//             || X >= (AreaWidth * MAP_WIDTH * TILE_SIZE) \
//             || Y >= (AreaHeight * MAP_HEIGHT * TILE_SIZE) \
//             || k >= LayerList.size()) return false;
//
//   int mapWidth = MAP_WIDTH * TILE_SIZE;
//   int mapHeight = MAP_HEIGHT * TILE_SIZE;
//   int ID = (X / mapWidth) + (Y / mapHeight) * AreaWidth;
//   CPlanTile* tmp = LayerList[k].MapList[ID].GetTile(X % mapWidth, Y % mapHeight);
//   return true;
// }

int CPlanArea::getZ(const int& k) {
  if (k < 0 || k >= LayerList.size()) return 0;
  return LayerList[k].Z;
}

int CPlanArea::getMaxZ() {
  if (LayerList.empty()) return 0;

  int max_k = LayerList.size() - 1;
  return LayerList[max_k].Z;
}

bool CPlanArea::doesZexist(const int& z) {
  for (int i = 0; i < LayerList.size(); i++) {
    if (z == LayerList[i].Z) return true;
  }
  return false;
}

void CPlanArea::getCoords(const int& mX, const int& mY, const int& k, int& X, int& Y, short& Z) {
  X = CCamera::CameraControl.GetCamRelX(mX);
  Z = getZ(k);
  Y = CCamera::CameraControl.GetCamRelY(mY) + (Z * TILE_SIZE);
}

void CPlanArea::getTileCoords(const int& mX, const int& mY, const int& k, int& X, int& Y, short& Z) {
  getCoords(mX, mY, k, X, Y, Z);
  X -= (X % TILE_SIZE) + (X < 0) * TILE_SIZE;
  Y -= (Y % TILE_SIZE) + (Y < 0) * TILE_SIZE;
}

void CPlanArea::OnRender(const int& CamX, const int& CamY, const int& k, const short& visflag, const short& opacity) {
  // The area is layered vertically (by k).
  // Layers are rendered one at a time, with the
  // lowest k-index (height) being rendered first.
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

  // if (Z < 0 || Z >= DepthList.size()) {
  //   CError::handler.ReportErr("CPlanArea::OnRender -> Bad Z-layer request.");
  //   return;
  // }

  if (!visflag || (opacity == 0 && visflag == pvm_visflags::MAP)) return;
  if (k < 0 || k >= LayerList.size()) {
    CError::handler.ReportErr("CPlanArea::OnRender -> Bad Z-layer request.");
    return;
  }

  int MapW = MAP_WIDTH * TILE_SIZE;         // in px
  int MapH = MAP_HEIGHT * TILE_SIZE;        // in px
  // short Yoffset = DepthList[Z] * TILE_SIZE; // in px
  short Yoffset = LayerList[k].Z * TILE_SIZE; // in px

  // Offset is included to account for "vertical" displacement
  // of maps, which appears as a negative shift in Y
  // EX: A depth of 1 is a Yoffset of 32px; ID=0 for this depth should be
  // rendered as if it was placed at Y=-32px, NOT Y=0px.
  int FirstID = -CamX / MapW;
  FirstID += ((-CamY + Yoffset) / MapH) * AreaWidth;
  // FirstID += Z * AreaWidth * AreaHeight;

  int maxMaps = 4;
  int nMaps = AreaWidth * AreaHeight; // n of maps on a layer
  int loopMax = (nMaps > maxMaps) ? maxMaps : nMaps;

  CTileset::TSControl.changeTileAlpha(LayerList[k].force_opacity ? LayerList[k].opacity : opacity);

  for (int i = 0; i < loopMax; i++) {
    int ID = FirstID + ((i / 2) * AreaWidth) + (i % 2);
    if (ID < 0 || ID >= LayerList[k].MapList.size()) continue;

    int X = ((ID % AreaWidth) * MapW) + CamX;
    int Y = ((ID / AreaWidth) * MapH) + CamY - Yoffset;

    if (visflag & pvm_visflags::FILL)   LayerList[k].MapList[ID].OnRenderFill(X, Y);
    if (visflag & pvm_visflags::MAP)    LayerList[k].MapList[ID].OnRender(X, Y);
    if (visflag & pvm_visflags::SOLID)  LayerList[k].MapList[ID].OnRenderSolid(X, Y);
    if (visflag & pvm_visflags::TYPE)   LayerList[k].MapList[ID].OnRenderType(X, Y);
  }
}

bool CPlanArea::changeTile(const int& X, const int& Y, const int& k, const CPlanTile& tile, const int& useTiles) {
  if (X < 0 || Y < 0 || k < 0 \
            || X >= (AreaWidth * MAP_WIDTH * TILE_SIZE) \
            || Y >= (AreaHeight * MAP_HEIGHT * TILE_SIZE) \
            || k >= LayerList.size()) return false;

  int mapWidth = MAP_WIDTH * TILE_SIZE;
  int mapHeight = MAP_HEIGHT * TILE_SIZE;
  int ID = (X / mapWidth) + (Y / mapHeight) * AreaWidth;
  LayerList[k].MapList[ID].changeTile(X % mapWidth, Y % mapHeight, tile, useTiles);
  return true;
}


// In principle, expanding/reducing maps horizontally should be the same as
// is done for the platforming maps. All that should change is that
// the expansion occurs across each layer.
void CPlanArea::expandRight() {
  // This resize will make the necessary amount of empty maps.
  // When we expand one map in width, we need the number of ROWS (or height)
  // of maps we are currently using. We make that amount of empty maps.
  // Or, mathematically, 1 (# of new columns) x AreaHeight = # of new maps.
  int init_mapsize = AreaWidth * AreaHeight;
  for (int k = 0; k < LayerList.size(); k++) {
    LayerList[k].MapList.resize(init_mapsize + AreaHeight);

    // Move (copy) our existing maps around, so that their
    // orientation is preserved.
    for (int Y = AreaHeight - 1; Y > 0; Y--) {
      for (int X = AreaWidth - 1; X >= 0; X--) {
        LayerList[k].MapList[X + Y * (AreaWidth + 1)] = LayerList[k].MapList[X + Y * AreaWidth];
      }
    }
  }

  AreaWidth++;  // We "officially" make our Area's width one map larger

  for (int k = 0; k < LayerList.size(); k++) {
    // Empty out/refresh our new maps (rightmost column)
    for (int i = 1; i <= AreaHeight; i++) {
      CPlanMap tempMap;
      tempMap.OnLoad();
      LayerList[k].MapList[i*AreaWidth - 1] = tempMap;
    }
  }
}

void CPlanArea::expandLeft() {
  // This resize will make the necessary amount of empty maps.
  // When we expand one map in width, we need the number of ROWS (or height)
  // of maps we are currently using. We make that amount of empty maps.
  // Or, mathematically, 1 (# of new columns) x AreaHeight = # of new maps.
  int init_mapsize = AreaWidth * AreaHeight;
  for (int k = 0; k < LayerList.size(); k++) LayerList[k].MapList.resize(init_mapsize + AreaHeight);

  AreaWidth++;

  for (int k = 0; k < LayerList.size(); k++) {
    // Move (copy) our existing maps around, so that their
    // orientation is preserved.
    for (int Y = AreaHeight - 1; Y >= 0; Y--) {
      for (int X = AreaWidth - 1; X > 0; X--) {
        int ID = X + Y * AreaWidth;
        LayerList[k].MapList[ID] = LayerList[k].MapList[ID - (Y + 1)];
      }
    }
    // Empty out/refresh our new maps (leftmost column)
    for (int i = 0; i < AreaHeight; i++) {
      CPlanMap tempMap;
      tempMap.OnLoad();
      LayerList[k].MapList[i*AreaWidth] = tempMap;
    }
  }
}

void CPlanArea::expandUp() {
  // This resize will make the necessary amount of empty maps.
  // When we expand one map in height, we need the number of COLUMNS (or width)
  // of maps we are currently using. We make that amount of empty maps.
  // Or, mathematically, 1 (# of new rows) x AreaWidth = # of new maps.
  int init_mapsize = AreaWidth * AreaHeight;
  for (int k = 0; k < LayerList.size(); k++) LayerList[k].MapList.resize(init_mapsize + AreaWidth);
  AreaHeight++;  // We "officially" make our Area's height one map larger

  for (int k = 0; k < LayerList.size(); k++) {
    // Move (copy) our existing maps around, so that their
    // orientation is preserved.
    for (int Y = AreaHeight - 1; Y > 0; Y--) {
      for (int X = AreaWidth - 1; X >= 0; X--) {
        int ID = X + Y * AreaWidth;
        LayerList[k].MapList[ID] = LayerList[k].MapList[ID - AreaWidth];
      }
    }
    // Make our new maps (top row)
    for (int i = 0; i < AreaWidth; i++) {
      CPlanMap tempMap;
      tempMap.OnLoad();
      LayerList[k].MapList[i] = tempMap;
    }
  }
}

void CPlanArea::expandDown() {
  // This resize will make the necessary amount of empty maps.
  // When we expand one map in height, we need the number of COLUMNS (or width)
  // of maps we are currently using. We make that amount of empty maps.
  // Or, mathematically, 1 (# of new rows) x AreaWidth = # of new maps.
  int init_mapsize = AreaWidth * AreaHeight;
  for (int k = 0; k < LayerList.size(); k++) {
    LayerList[k].MapList.resize(init_mapsize + AreaWidth);

    // No movement of maps is necessary! :D-\-<
    // Make our new maps (bottom row)
    for (int i = 0; i < AreaWidth; i++) {
      CPlanMap tempMap;
      tempMap.OnLoad();
      // tempMap.Tex_Tileset = MapList[0].Tex_Tileset;
      LayerList[k].MapList[i + AreaHeight * AreaWidth] = tempMap;
    }
  }
  AreaHeight++;  // We "officially" make our Area's height one map larger
                // We waited until after making new maps. Otherwise,
                // we can just sub in (AreaHeight - 1) into the last
                // statement in the "for" loop above.
                // It makes little difference, I think.
}

bool CPlanArea::reduceRight() {
  if (AreaWidth <= 1) return false;
  int mapsize = AreaWidth * AreaHeight;
  AreaWidth--;  // We "officially" make our Area's width one map smaller

  for (int k = 0; k < LayerList.size(); k++) {
    // Move (copy) our existing maps around, so that their
    // orientation is preserved.
    for (int Y = 1; Y < AreaHeight; Y++) {
      for (int X = 0; X < AreaWidth; X++) {
        LayerList[k].MapList[X + Y * AreaWidth] = LayerList[k].MapList[X + Y + Y * AreaWidth];
      }
    }
    LayerList[k].MapList.resize(mapsize - AreaHeight);
  }
  return true;
}

bool CPlanArea::reduceLeft() {
  if (AreaWidth <= 1) return false;
  int mapsize = AreaWidth * AreaHeight;
  AreaWidth--;  // We "officially" make our Area's width one map smaller

  for (int k = 0; k < LayerList.size(); k++) {
    // Move (copy) our existing maps around, so that their
    // orientation is preserved.
    for (int Y = 0; Y < AreaHeight; Y++) {
      for (int X = 0; X < AreaWidth; X++) {
        LayerList[k].MapList[X + Y * AreaWidth] = LayerList[k].MapList[X + 1 + Y * (1 + AreaWidth)];
      }
    }
    LayerList[k].MapList.resize(mapsize - AreaHeight);
  }
  return true;
}

bool CPlanArea::reduceUp() {
  if (AreaHeight <= 1) return false;
  int mapsize = AreaWidth * AreaHeight;

  for (int k = 0; k < LayerList.size(); k++) {
    // Move (copy) our existing maps around, so that their
    // orientation is preserved.
    for (int Y = 0; Y < AreaHeight - 1; Y++) {
      for (int X = 0; X < AreaWidth; X++) {
        LayerList[k].MapList[X + Y * AreaWidth] = LayerList[k].MapList[X + (Y + 1) * AreaWidth];
      }
    }
    LayerList[k].MapList.resize(mapsize - AreaWidth);
  }
  AreaHeight--;  // We "officially" make our Area's height one map smaller
  return true;
}

bool CPlanArea::reduceDown() {
  if (AreaHeight <= 1) return false;

  // Probably the simplest area adjustment.
  // We remove the bottom row of maps,
  // which requires no rearranging of the
  // MapList and no loading of blank maps.
  // The camera position doesn't have to be
  // changed, either!
  int mapsize = AreaWidth * AreaHeight;
  for (int k = 0; k < LayerList.size(); k++) LayerList[k].MapList.resize(mapsize - AreaWidth);
  AreaHeight--;
  return true;
}

bool CPlanArea::isRightEmpty() {
  // scan the right side of each layer's area
  // for content.
  for (int k = 0; k < LayerList.size(); k++) {
    for (int Y = 0; Y < AreaHeight; Y++) {
      int ID = (AreaWidth * (Y + 1)) - 1;
      if (!LayerList[k].MapList[ID].isEmpty()) return false;
    }
  }
  return true;
}

bool CPlanArea::isLeftEmpty() {
  // scan the left side of each layer's area
  // for content.
  for (int k = 0; k < LayerList.size(); k++) {
    for (int Y = 0; Y < AreaHeight; Y++) {
      int ID = AreaWidth * Y;
      if (!LayerList[k].MapList[ID].isEmpty()) return false;
    }
  }
  return true;
}

bool CPlanArea::isUpEmpty() {
  // scan the upper side of each layer's area
  // for content.
  for (int k = 0; k < LayerList.size(); k++) {
    for (int ID = 0; ID < AreaWidth; ID++) {
      if (!LayerList[k].MapList[ID].isEmpty()) return false;
    }
  }
  return true;
}

bool CPlanArea::isDownEmpty() {
  // scan the lower side of each layer's area
  // for content.
  for (int k = 0; k < LayerList.size(); k++) {
    for (int ID = AreaWidth * (AreaHeight - 1); ID < AreaWidth * AreaHeight; ID++) {
      if (!LayerList[k].MapList[ID].isEmpty()) return false;
    }
  }
  return true;
}


bool CPlanArea::OnLoad(char const* File)  {
  // try to load area/maps
  std::string fname = FPATH + std::string(File) + EXT;

  FILE* FileHandle = fopen(fname.c_str(), "rb");
  if (FileHandle == NULL) {
    CInform::InfoControl.pushInform("---CPlanArea.Onload---\nfailed to open area file");
    return false;
  }

  // Grab the ID of the tileset for the area
  short setID;
  fread(&setID, sizeof(short), 1, FileHandle);

  // Get AreaWidth, AreaHeight and number of layers
  int AreaDepth = LayerList.size();
  fread(&AreaWidth, sizeof(int), 1, FileHandle);
  fread(&AreaHeight, sizeof(int), 1, FileHandle);
  fread(&AreaDepth, sizeof(int), 1, FileHandle);

  if (!CTileset::TSControl.changeTileset(setID)) {
    CInform::InfoControl.pushInform("---CPlanArea.Onload---\ncould not load tileset");
    fclose(FileHandle);
    return false;
  }

  // MapList.clear();
  LayerList.clear();

  // read map data
  for (int k = 0; k < AreaDepth; k++) {
    CPlanLayer tempLayer;

    // get layer height
    fread(&tempLayer.Z, sizeof(short), 1, FileHandle);

    for (int i = 0; i < AreaWidth * AreaHeight; i++) {
      CPlanMap tempMap;
      if (tempMap.OnLoad(FileHandle) == false) {
        fclose(FileHandle);
        return false;
      }
      tempLayer.MapList.push_back(tempMap);
    }
    // insert the new layer into the LayerList vector
    LayerList.push_back(tempLayer);
  }
  fclose(FileHandle);
  return true;
}

bool CPlanArea::OnSave(char const* File) {
  // try to save area/maps
  std::string fname = FPATH + std::string(File) + EXT;
  // FILE* FileHandle = fopen(fname.c_str(), "w");
  FILE* FileHandle = fopen(fname.c_str(), "wb");

  if (FileHandle == NULL)  {
    CInform::InfoControl.pushInform("---CPlanArea.OnSave---\nfailed to open new area file");
    return false;
  }

  // Output the ID of the tileset for the area
  short setID = CTileset::TSControl.getFileID();
  fwrite(&setID, sizeof(short), 1, FileHandle);

  // Output AreaWidth, AreaHeight, number of layers
  int AreaDepth = LayerList.size();
  fwrite(&AreaWidth, sizeof(int), 1, FileHandle);
  fwrite(&AreaHeight, sizeof(int), 1, FileHandle);
  fwrite(&AreaDepth, sizeof(int), 1, FileHandle);

  // Output map data to .pvm file
  for (int k = 0; k < AreaDepth; k++) {
    fwrite(&LayerList[k].Z, sizeof(short), 1, FileHandle); // write layer height
    for (int i = 0; i < AreaWidth * AreaHeight; i++) {
      if (!LayerList[k].MapList[i].OnSave(FileHandle)) {
        fclose(FileHandle);
        return false;
      }
    }
  }

  fclose(FileHandle);
  return true;
}
