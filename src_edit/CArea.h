#ifndef _C_AREA_H_
#define _C_AREA_H_

#include "CMap.h"
#include "CInform.h"
#include <string>

class CArea
{
public:
	static CArea	control;

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
	bool	OnLoad(char const* File);
	bool 	NewLoad(char const* File);
	bool	NewSave(char const* File);


	/*	Loads an "empty" 1 x 1 map area.
			param tileset : Tileset for the area.
	*/
	// bool	OnLoad(SDL_Texture* tileset);

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
	void	OnRenderType(SDL_Texture* tileset, int CameraX, int CameraY);
	void	OnRenderColl(SDL_Texture* tileset, int CameraX, int CameraY);
	void	ViewArea(SDL_Texture* ui);

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

	void	ChangeSet(SDL_Texture* newset);
	void 	ChangeTile(int X, int Y, CTile* NewTile, int useTiles);
	bool	SaveArea(char const* areaname);
	void	OnCleanup();
};
#endif
