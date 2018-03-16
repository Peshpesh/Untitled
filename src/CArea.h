#ifndef _C_AREA_H_
#define _C_AREA_H_

#include <string>
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
	SDL_Texture*	Tex_Tileset;
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

	void ChangeTile(int X, int Y, CTile* NewTile, int useTiles);

	void OnCleanup();

public:
	CArea();

	CMap* GetMap(int X, int Y);
	CTile* GetTile(int X, int Y);

	/*	Loads an area, or set of maps, from an existing area file.
			param File			:	Area file name
			param renderer	:	Renderer for the area.
			Renderer is used in a call to CSurface to load
			a tileset, which needs the renderer in use.
	*/
	bool	OnLoad(char const* File);

	/*	Loads an "empty" 1 x 1 map area.
			param tileset : Tileset for the area.
			^^; This function is incomplete.
	*/
	bool	OnLoad(SDL_Texture* tileset);

	/*	Renders the area, or set of maps, to our renderer.
			It will only render the maps that could possibly be visible
			in the window at any time, using CameraX and CameraY.
			param CameraX		:	Camera's X position (increasing LEFT)
			param CameraY		:	Camera's Y position (increasing UP)
			param bg			:	Flag to draw foreground or middleground
	*/
	void	OnRender(int CameraX, int CameraY, bool bg);
	void	ShowAreaMap();

	void	OnCleanup();
};
#endif
