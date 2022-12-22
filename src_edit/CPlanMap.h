#ifndef _C_PLANMAP_H_
#define _C_PLANMAP_H_

#include <SDL.h>
#include <vector>
#include <stdio.h>
#include <cstring>
#include "CAsset.h"
#include "CTile.h"
#include "CTileset.h"
#include "CSurface.h"
#include "CInform.h"

/* Contains vector of a layer of the cell's appearance */
class CPlanMap {
  std::vector<CPlanTile> TileList;

public:
  CPlanMap();
  CPlanTile* GetTile(int X, int Y);

public:
  void OnLoad();
  bool OnLoad(FILE* fhandle);
  bool OnSave(FILE* fhandle);

  void OnRenderFill(int MapX, int MapY);
  void OnRender(int MapX, int MapY);

  void changeTile(const int& X, const int& Y, const CPlanTile& tile, const int& useTiles);
  bool isEmpty();
};

/* Contains vector of cell attributes */
class CPlanMapAtt {
  std::vector<CPlanTileAtt> AttList;

public:
  CPlanMapAtt();
  CPlanTileAtt* GetTileAtt(int X, int Y);

public:
  void OnLoad();
  bool OnLoad(FILE* fhandle);
  bool OnSave(FILE* fhandle);

  void OnRenderType(int MapX, int MapY);
  void OnRenderSolid(int MapX, int MapY);
  void OnRenderBarrier(int MapX, int MapY);

  void changeTileAtt(const int& X, const int& Y, const CPlanTileAtt& att, const int& useTiles);
};

#endif
