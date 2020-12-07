#ifndef _C_PLANAREA_H_
#define _C_PLANAREA_H_

#include "CCamera.h"
#include "CPlanMap.h"
#include "CError.h"
#include "Define.h"

// NOTE: wall tiles should probably have Z equal to their top
// (ex: a wall that appears to have a base at Z=0 and a top at Z=2
//      should have Z=2).

namespace pvm_visflags {
  enum {
    MAP     = 0x01, // show "visible" map tiles
    SOLID   = 0x02, // show whether tiles are solid or not
    TYPE    = 0x04, // show tile types
    BARRIER = 0x08, // show barriers
    FILL    = 0x10, // fill void tiles
  };
}

struct CPlanLayer {
  std::vector<CPlanMap> MapList;
  short Z;
  short opacity;      // opacity unique to this layer regardless of K or Z
  bool force_opacity; // if true, use layer's unique opacity
  CPlanLayer(): Z(0),opacity(MAX_RGBA),force_opacity(false){};
};

class CPlanArea {
  CPlanArea();

public:
  static CPlanArea control;

public:
  // std::vector<CPlanMap> MapList;
  // std::vector<std::vector<CPlanMap>> MapList;
  std::vector<CPlanLayer> LayerList;

private:
  // std::vector<short>  DepthList;  // list of layer depths
  int  AreaWidth;    // width in Maps
  int  AreaHeight;    // height in Maps

public:
  void OnInit();

  void addLayer(const short& K, const short& Z);
  void delLayer(const short& K);
  void GetDims(int& mW, int& mH);
  int getZ(const int& k);
  bool doesZexist(const int& z);
  int getMaxZ();

  /* convert mouse coords on window to map coords (X,Y,Z) */
  void getCoords(const int& mX, const int& mY, const int& k, int& X, int& Y, short& Z);
  void getTileCoords(const int& mX, const int& mY, const int& k, int& X, int& Y, short& Z);

  // CPlanMap* GetMap(int X, int Y);
  CPlanTile* GetTile(const int& X, const int& Y, const int& k); // get address to tile in map
  // CPlanTile GetTileCopy(int X, int Y); // get copy of a tile in map

  // void   OnRenderFill(const int& CameraX, const int& CameraY, const int& k);
  void OnRender(const int& CamX, const int& CamY, const int& k, const short& visflag, const short& opacity);
  // void  OnRenderType(SDL_Texture* tileset, int CameraX, int CameraY);
  // void  OnRenderColl(SDL_Texture* tileset, int CameraX, int CameraY);

  bool changeTile(const int& X, const int& Y, const int& k, const CPlanTile& tile, const int& useTiles);

  void expandRight();
  void expandLeft();
  void expandUp();
  void expandDown();

  bool reduceRight();
  bool reduceLeft();
  bool reduceUp();
  bool reduceDown();

  bool isRightEmpty();
  bool isLeftEmpty();
  bool isUpEmpty();
  bool isDownEmpty();

  bool OnLoad(char const* File);
  bool OnSave(char const* File);

  // void  OnCleanup();
};
#endif
