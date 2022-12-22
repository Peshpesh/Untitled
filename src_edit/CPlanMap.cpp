#include "CPlanMap.h"

CPlanMap::CPlanMap() {
  //
}

CPlanTile* CPlanMap::GetTile(int X, int Y) {
  int ID = 0;
  ID = X / TILE_SIZE;
  ID += (MAP_WIDTH * (Y / TILE_SIZE));

  if (ID < 0 || ID >= TileList.size()) {
    return NULL;
  }
  return &TileList[ID];
}

void CPlanMap::OnLoad() {
  TileList.clear();

  CPlanTile tempTile;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      TileList.push_back(tempTile);
    }
  }
}

bool CPlanMap::OnLoad(FILE* fhandle)  {
  if (fhandle == NULL) {
    CInform::InfoControl.pushInform("---CPlanMap.OnLoad---\ninvalid file handle");
    return false;
  }

  TileList.clear();

  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      CPlanTile tempTile;
      if (fread(&tempTile, sizeof(struct CPlanTile), 1, fhandle) != 1) {
        CInform::InfoControl.pushInform("---CPlanMap.OnLoad---\nfailed to load tile data");
        return false;
      }
      TileList.push_back(tempTile);
    }
  }
  return true;
}

bool CPlanMap::OnSave(FILE* fhandle) {
  if (fhandle == NULL) {
    CInform::InfoControl.pushInform("---CPlanMap.OnSave---\ninvalid file handle");
    return false;
  }

  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      int ID = X + Y * MAP_WIDTH;
      if (fwrite(&TileList[ID], sizeof(struct CPlanTile), 1, fhandle) != 1) {
        CInform::InfoControl.pushInform("---CPlanMap.OnSave---\nfailed to write tile data");
        return false;
      }
    }
  }
  return true;
}

void CPlanMap::OnRender(int MapX, int MapY) {
  if (CTileset::TSControl.tileset == NULL) return;

  int tset_w = CTileset::TSControl.ts_w; // tiles
  int tset_h = CTileset::TSControl.ts_h; // tiles

  // Render surface tiles, row by row
  int ID = 0;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      int TilesetX = 0, TilesetY = 0;
      if (TileList[ID].ID >= 0) {
        TilesetX = (TileList[ID].ID % tset_w) * TILE_SIZE;  // X on src texture
        TilesetY = (TileList[ID].ID / tset_w) * TILE_SIZE;  // Y on src texture
      } else {
        ID++;
        continue;
      }
      int tX = MapX + (X * TILE_SIZE);
      int tY = MapY + (Y * TILE_SIZE);
      CSurface::OnDraw(CTileset::TSControl.tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
      ID++;
    }
  }
}

void CPlanMap::OnRenderFill(int MapX, int MapY) {
  if (CTileset::TSControl.grid_tileset == NULL) return;

  // Render grid fill
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      int tX = MapX + (X * TILE_SIZE);
      int tY = MapY + (Y * TILE_SIZE);
      if (!CTileset::TSControl.drawFill(tX, tY)) return;
    }
  }
}

void CPlanMap::changeTile(const int& X, const int& Y, const CPlanTile& tile, const int& useTiles) {
  if (useTiles & ENABLE_BG) {
    int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
    TileList[ID].ID = tile.ID;
  }
}

bool CPlanMap::isEmpty() {
  int ID = 0;
  for (int Y = 0; Y < MAP_HEIGHT; Y++) {
    for (int X = 0; X < MAP_WIDTH; X++) {
      if (TileList[ID].ID != -1) return false;
      ID++;
    }
  }
  return true;
}
