#include "CPlanMap.h"

CPlanMapAtt::CPlanMapAtt() {
  //
}

CPlanTileAtt* CPlanMapAtt::GetTileAtt(int X, int Y) {
  int ID = 0;
  ID = X / TILE_SIZE;
  ID += (MAP_WIDTH * (Y / TILE_SIZE));

  if (ID < 0 || ID >= AttList.size()) {
    return NULL;
  }
  return &AttList[ID];
}

void CPlanMapAtt::OnLoad() {
  AttList.clear();

  CPlanTileAtt tempTile;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      AttList.push_back(tempTile);
    }
  }
}

bool CPlanMapAtt::OnLoad(FILE* fhandle)  {
  if (fhandle == NULL) {
    CInform::InfoControl.pushInform("---CPlanMapAtt.OnLoad---\ninvalid file handle");
    return false;
  }

  AttList.clear();

  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      CPlanTileAtt tempTile;
      if (fread(&tempTile, sizeof(struct CPlanTileAtt), 1, fhandle) != 1) {
        CInform::InfoControl.pushInform("---CPlanMapAtt.OnLoad---\nfailed to load tile data");
        return false;
      }
      AttList.push_back(tempTile);
    }
  }
  return true;
}

bool CPlanMapAtt::OnSave(FILE* fhandle) {
  if (fhandle == NULL) {
    CInform::InfoControl.pushInform("---CPlanMapAtt.OnSave---\ninvalid file handle");
    return false;
  }

  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      int ID = X + Y * MAP_WIDTH;
      if (fwrite(&AttList[ID], sizeof(struct CPlanTileAtt), 1, fhandle) != 1) {
        CInform::InfoControl.pushInform("---CPlanMapAtt.OnSave---\nfailed to write tile data");
        return false;
      }
    }
  }
  return true;
}

void CPlanMapAtt::OnRenderType(int MapX, int MapY) {
  if (CTileset::TSControl.type_tileset == NULL) return;

  // Render tile types
  int ID = 0;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      if (AttList[ID].type != TILE_TYPE_NORMAL) {
        int tX = MapX + (X * TILE_SIZE);
        int tY = MapY + (Y * TILE_SIZE);
        if (!CTileset::TSControl.drawType(AttList[ID].type, tX, tY)) return;
      }
      ID++;
    }
  }
}

void CPlanMapAtt::OnRenderSolid(int MapX, int MapY) {
  if (CTileset::TSControl.grid_tileset == NULL) return;

  // Render mask for solid tiles
  int ID = 0;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      if (AttList[ID].solid) {
        int tX = MapX + (X * TILE_SIZE);
        int tY = MapY + (Y * TILE_SIZE);
        if (!CTileset::TSControl.drawSolid(tX, tY)) return;
      }
      ID++;
    }
  }
}

void CPlanMapAtt::OnRenderBarrier(int MapX, int MapY) {
  if (CTileset::TSControl.barr_tileset == NULL) return;

  // Render tile barriers
  int ID = 0;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      if (AttList[ID].barrier) {
        int tX = MapX + (X * TILE_SIZE);
        int tY = MapY + (Y * TILE_SIZE);
        if (!CTileset::TSControl.drawBarrier(AttList[ID].barrier, tX, tY)) return;
      }
      ID++;
    }
  }
}

void CPlanMapAtt::changeTileAtt(const int& X, const int& Y, const CPlanTileAtt& att, const int& useTiles) {
  int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
  if (useTiles & ENABLE_TYPE)    AttList[ID].type    = att.type;
  if (useTiles & ENABLE_COLL)    AttList[ID].solid   = att.solid;
  if (useTiles & ENABLE_BARRIER) AttList[ID].barrier = att.barrier;
}
