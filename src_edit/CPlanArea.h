#ifndef _C_PLANAREA_H_
#define _C_PLANAREA_H_

#include "CPlanMap.h"
#include "CError.h"

// NOTE: wall tiles should probably have Z equal to their top
// (ex: a wall that appears to have a base at Z=0 and a top at Z=2
//      should have Z=2).

namespace pvm_visflags {
  enum {
    MAP   = 0x01, // show "visible" map tiles
    SOLID = 0x02, // show whether tiles are solid or not
    TYPE  = 0x04, // show tile types
    FILL  = 0x08, // fill void tiles
  };
}

struct CPlanLayer {
  std::vector<CPlanMap> MapList;
  short Z;
  CPlanLayer(): Z(0) {};
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
	int	AreaWidth;		// width in Maps
	int	AreaHeight;		// height in Maps

public:
	void OnInit();

  void addLayer(const short& K, const short& Z);

	void GetDims(int& mW, int& mH);
	// CPlanMap* GetMap(int X, int Y);
	// CPlanTile* GetTile(int X, int Y);

	/*	Renders the area, or set of maps, to our renderer.
			It will only render the maps that could possibly be visible
			in the window at any time, using CameraX and CameraY.
			param renderer	:	Current renderer
			param CameraX		:	Camera's X position (increasing LEFT)
			param CameraY		:	Camera's Y position (increasing UP)
			param bg			:	Flag to draw foreground or middleground
	*/
	// void 	OnRenderFill(const int& CameraX, const int& CameraY, const int& k);
	void	OnRender(const int& CamX, const int& CamY, const int& k, const short& visflag);
	// void	OnRenderType(SDL_Texture* tileset, int CameraX, int CameraY);
	// void	OnRenderColl(SDL_Texture* tileset, int CameraX, int CameraY);

	/*	Intended only for map editing.
			Expands the current area rightward by one map.
			For example, a 2 map x 2 map area will turn to a
			3 map x 2 map area upon this call. The added maps
			are initialized as "empty."
	*/
	// void	OnExpandRight();
	// void	OnExpandLeft();
	// void	OnExpandUp();
	// void	OnExpandDown();
  //
	// void	OnReduceRight();
	// bool	OnReduceLeft();
	// bool	OnReduceUp();
	// void	OnReduceDown();

	void 	changeTile(const int& X, const int& Y, const int& k, const CPlanTile& tile, const int& useTiles);
  bool 	OnLoad(char const* File);
  bool	OnSave(char const* File);

	// void	OnCleanup();
};
#endif
