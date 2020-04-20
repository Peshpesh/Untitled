#ifndef _C_AREA_H_
#define _C_AREA_H_

#include "CMap.h"
#include "CInform.h"
#include <string>

class CArea {
public:
	static CArea control;

public:
	std::vector<CMap>	MapList;

private:
	int	AreaWidth;		// Maps
	int	AreaHeight;		// Maps

public:
	CArea();

	void OnInit();

	void GetDims(int& mW, int& mH);
	CMap* GetMap(int X, int Y);
	CTile* GetTile(int X, int Y);

	/*	Loads an area, or set of maps, from an existing area file.
			param File			:	Area file name
			param renderer	:	Renderer for the area.
			Renderer is used in a call to CSurface to load
			a tileset, which needs the renderer in use.
	*/
	bool 	OnLoad(char const* File);
	bool	OnSave(char const* File);

	/*	Renders the area, or set of maps, to our renderer.
			It will only render the maps that could possibly be visible
			in the window at any time, using CameraX and CameraY.
			param renderer	:	Current renderer
			param CameraX		:	Camera's X position (increasing LEFT)
			param CameraY		:	Camera's Y position (increasing UP)
			param bg			:	Flag to draw foreground or middleground
	*/
	void 	OnRenderFill(int CameraX, int CameraY);
	void	OnRender(int CameraX, int CameraY, bool bg);
	void	OnRenderType(int CameraX, int CameraY);
	void	OnRenderColl(int CameraX, int CameraY);

	/*	Intended only for map editing.
			Expands the current area rightward by one map.
			For example, a 2 map x 2 map area will turn to a
			3 map x 2 map area upon this call. The added maps
			are initialized as "empty."
	*/
	void	OnExpandRight();
	void	OnExpandLeft();
	void	OnExpandUp();
	void	OnExpandDown();

	void	OnReduceRight();
	bool	OnReduceLeft();
	bool	OnReduceUp();
	void	OnReduceDown();

	void 	ChangeTile(int X, int Y, CTile* NewTile, int useTiles);

	void	OnCleanup();
	// bool	OnLoad(char const* File);
	// void	ChangeSet(SDL_Texture* newset);
	// bool	SaveArea(char const* areaname);
	// void	ViewArea(SDL_Texture* ui);
};

#endif
