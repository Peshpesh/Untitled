#include "CArea.h"

CArea CArea::AreaControl;

CArea::CArea()
{
	AreaWidth = AreaHeight = 0;
	Tex_Tileset = NULL;
}

CMap* CArea::GetMap(int X, int Y)
{
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	int ID = X / MapWidth;
	ID += ((Y / MapHeight) * AreaWidth);

	if (ID < 0 || ID >= MapList.size()) return NULL;

	return &MapList[ID];
}

CTile* CArea::GetTile(int X, int Y)
{
	int MapWidth = MAP_WIDTH * TILE_SIZE;
	int MapHeight = MAP_HEIGHT * TILE_SIZE;

	CMap* Map = GetMap(X, Y);

	if (Map == NULL) return NULL;

	X = X % MapWidth;
	Y = Y % MapHeight;
	return Map->GetTile(X, Y);
}

bool CArea::OnLoad(char const* File, SDL_Renderer* renderer)
{
	MapList.clear();

	FILE* FileHandle = fopen(File, "r");
	if (FileHandle == NULL) return false;
	char TilesetFile[255];
	fscanf(FileHandle, "%s\n", TilesetFile);

	if ((Tex_Tileset = CSurface::OnLoad(TilesetFile, renderer)) == false)
	{
		fclose(FileHandle);
		return false;
	}

	fscanf(FileHandle, "%d %d\n", &AreaWidth, &AreaHeight);

	for (int X = 0; X < AreaWidth; X++)
	{
		for (int Y = 0; Y < AreaHeight; Y++)
		{
			char MapFile[255];
			fscanf(FileHandle, "%s ", MapFile);

			CMap tempMap;
			if (tempMap.OnLoad(MapFile) == false)
			{
				fclose(FileHandle);
				return false;
			}

			tempMap.Tex_Tileset = Tex_Tileset;

			MapList.push_back(tempMap);
		}
		fscanf(FileHandle, "\n");
	}
	fclose(FileHandle);
	return true;
}

bool CArea::OnLoad(SDL_Texture* tileset)
{
	MapList.clear();
	AreaHeight = AreaWidth = 1;

	CMap tempMap;
	tempMap.OnLoad();
	tempMap.Tex_Tileset = tileset;

	MapList.push_back(tempMap);
	return true;
}

void CArea::OnRender(SDL_Renderer* renderer, int CameraX, int CameraY, bool bg)
{
	int MapWidth = MAP_WIDTH * TILE_SIZE; // pixels
	int MapHeight = MAP_HEIGHT * TILE_SIZE; // pixels

	int FirstID = -CameraX / MapWidth;
	FirstID = FirstID + ((-CameraY / MapHeight) * AreaWidth);

	for (int i = 0; i < 4; i++)
	{
		int ID = FirstID + ((i / 2) * AreaWidth) + (i % 2);
		if (ID < 0 || ID >= MapList.size()) continue;

		int X = ((ID % AreaWidth) * MapWidth) + CameraX;
		int Y = ((ID / AreaWidth) * MapHeight) + CameraY;

		MapList[ID].OnRender(renderer, X, Y, bg);
	}
}

void CArea::ViewArea(SDL_Renderer* renderer, SDL_Texture* ui)
{
	// We will map our whole area by scanning every map,
	// and plotting every tile as a 2 x 2 solid color proxy (blue).
	// Think of it as plotting all the maps at once instead of just
	// some, only the tiles are 2 x 2 in size and are restricted to
	// certain colors. Shades of the map are determined by type
	// and (sometimes) tile. First, we need to know how big of
	// an area we need to render.
	int VTileSize = 2;

	int PixWidth = AreaWidth * MAP_WIDTH * VTileSize;
	int PixHeight = AreaHeight * MAP_HEIGHT * VTileSize;

	// Let's draw our area in the center of the workspace.
	int Xo = (WWIDTH - PixWidth) / 2;
	int Yo = (WHEIGHT - PixHeight) / 2;

	// Cycle through all the maps, draw 'em...
	for (int j = 0; j < AreaHeight; j++)
	{
		for (int i = 0; i < AreaWidth; i++)
		{
			int ID = i + j * AreaWidth;
			// X and Y passes are modified so that the next map of each loop is either on the
			// next row or right beside the current positioned map. The added (offset) term
			// is just the dimension of a map in pixels using VTS px x VTS px tiles.
			MapList[ID].ViewMap(renderer, ui, Xo + i * MAP_WIDTH * VTileSize, Yo + j * MAP_HEIGHT * VTileSize);
		}
	}
	for (int X = Xo - VTileSize; X <= Xo + PixWidth; X += VTileSize)
	{
		CSurface::OnDraw(renderer, ui, X, Yo - VTileSize, 0, 352, VTileSize, VTileSize);
		CSurface::OnDraw(renderer, ui, X, Yo + PixHeight, 0, 352, VTileSize, VTileSize);
	}
	for (int Y = Yo; Y < Yo + PixHeight; Y += VTileSize)
	{
		CSurface::OnDraw(renderer, ui, Xo - VTileSize, Y, 0, 352, VTileSize, VTileSize);
		CSurface::OnDraw(renderer, ui, Xo + PixWidth, Y, 0, 352, VTileSize, VTileSize);
	}
}

void CArea::ChangeSet(SDL_Texture* newset)
{
	for (int X = 0; X < AreaWidth; X++)
	{
		for (int Y = 0; Y < AreaHeight; Y++)
		{
			MapList[X + Y*AreaWidth].Tex_Tileset = newset;
		}
	}
}

void CArea::ChangeTile(int X, int Y, int tile, int fore, int type, int slope)
{
	if (X < 0 || Y < 0 || X > AreaWidth * MAP_WIDTH * TILE_SIZE - 1 || Y > AreaHeight * MAP_HEIGHT * TILE_SIZE - 1)
		return;

	int MapWidth = MAP_WIDTH*TILE_SIZE;
	int MapHeight = MAP_HEIGHT*TILE_SIZE;
	int ID = (X / MapWidth) + (Y / MapHeight) * AreaWidth;
	MapList[ID].ChangeTile(X % MapWidth, Y % MapHeight, tile, fore, type, slope);
}

void CArea::OnCleanup()
{
	if (Tex_Tileset) SDL_DestroyTexture(Tex_Tileset);
	MapList.clear();
}
