#ifndef _C_AREA_H_
#define _C_AREA_H_

#include <string>
#include "CAsset.h"
#include "CMap.h"

namespace Tileset {
  const short num = 1;
	const char* const path = "../res/tile/";
	const char* const extension = ".png";
  enum {
    TS_DEFAULT = 0,
  };
  const std::string name[] = {
    "default",
  };
};

class CArea {
public:
	static CArea	control;

public:
	std::vector<CMap>	MapList;

private:
	int	AreaWidth;		// Maps
	int	AreaHeight;		// Maps
	// SDL_Texture*	Tex_Tileset;
	short tileset_ID;

public:
	void OnInit();
	bool Load(char const* File);
	bool ChangeTileset(const short& fID);

	void GetDims(int& mW, int& mH);
	CMap* GetMap(int X, int Y);
	CTile* GetTile(int X, int Y);

	void OnRender(int CameraX, int CameraY, bool bg);
	void ShowAreaMap();

	// void ChangeTile(int X, int Y, CTile* NewTile, int useTiles);

	void OnCleanup();

public:
	CArea();
};
#endif
