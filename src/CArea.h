#ifndef _CAREA_H_
#define _CAREA_H_

#include "CMap.h"

class CArea
{
public:
	static CArea	AreaControl;

public:
	std::vector<CMap>	MapList;

private:
	int	AreaWidth;		// Maps
	int	AreaHeight;		// Maps
	SDL_Texture*	Tex_Tileset;

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
	bool	OnLoad(char const* File, SDL_Renderer* renderer);

	/*	Loads an "empty" 1 x 1 map area.
			param tileset : Tileset for the area.
			^^; This function is incomplete.
	*/
	bool	OnLoad(SDL_Texture* tileset);

	/*	Renders the area, or set of maps, to our renderer.
			It will only render the maps that could possibly be visible
			in the window at any time, using CameraX and CameraY.
			param renderer	:	Current renderer
			param CameraX		:	Camera's X position (increasing LEFT)
			param CameraY		:	Camera's Y position (increasing UP)
			param bg			:	Flag to draw foreground or middleground
	*/
	void	OnRender(SDL_Renderer* renderer, int CameraX, int CameraY, bool bg);
	void	ViewArea(SDL_Renderer* renderer, SDL_Texture* ui);

	void	ChangeSet(SDL_Texture* newset);
	void	ChangeTile(int X, int Y, int tile, int fore, int type, int slope);
	void	OnCleanup();
};
#endif
