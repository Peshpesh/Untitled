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

bool CArea::OnLoad(char* File, SDL_Renderer* renderer)
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

void CArea::OnRender(SDL_Renderer* renderer, int CameraX, int CameraY, bool depth)
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

		MapList[ID].OnRender(renderer, X, Y, depth);
	}
}

void CArea::OnRenderType(SDL_Renderer* renderer, SDL_Texture* tileset, int CameraX, int CameraY)
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

		MapList[ID].OnRenderType(renderer, tileset, X, Y);
	}
}

void CArea::OnRenderSlope(SDL_Renderer* renderer, SDL_Texture* tileset, int CameraX, int CameraY)
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

		MapList[ID].OnRenderSlope(renderer, tileset, X, Y);
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

void CArea::OnExpandRight()
{
	// This resize will make the necessary amount of empty maps.
	// When we expand one map in width, we need the number of ROWS (or height)
	// of maps we are currently using. We make that amount of empty maps.
	// Or, mathematically, 1 (# of new columns) x AreaHeight = # of new maps.
	MapList.resize(MapList.size() + AreaHeight);

	// Move (copy) our existing maps around, so that their
	// orientation is preserved.
	for (int Y = AreaHeight - 1; Y > 0; Y--)
	{
		for (int X = AreaWidth - 1; X >= 0; X--)
		{
			MapList[X + Y + Y * AreaWidth] = MapList[X + Y * AreaWidth];
		}
	}
	AreaWidth++;	// We "officially" make our Area's width one map larger

	// Empty out/refresh our new maps (rightmost column)
	for (int i = 1; i <= AreaHeight; i++)
	{
		CMap tempMap;
		tempMap.OnLoad();
		tempMap.Tex_Tileset = MapList[0].Tex_Tileset;
		MapList[i*AreaWidth - 1] = tempMap;
	}
}

void CArea::OnExpandLeft()
{
	// This resize will make the necessary amount of empty maps.
	// When we expand one map in width, we need the number of ROWS (or height)
	// of maps we are currently using. We make that amount of empty maps.
	// Or, mathematically, 1 (# of new columns) x AreaHeight = # of new maps.
	MapList.resize(MapList.size() + AreaHeight);

	AreaWidth++;

	// Move (copy) our existing maps around, so that their
	// orientation is preserved.
	for (int Y = AreaHeight - 1; Y >= 0; Y--)
	{
		for (int X = AreaWidth - 1; X > 0; X--)
		{
			int ID = X + Y * AreaWidth;
			MapList[ID] = MapList[ID - (Y + 1)];
		}
	}
	// Empty out/refresh our new maps (leftmost column)
	for (int i = 0; i < AreaHeight; i++)
	{
		CMap tempMap;
		tempMap.OnLoad();
		tempMap.Tex_Tileset = MapList[0].Tex_Tileset;
		MapList[i*AreaWidth] = tempMap;
	}
}

void CArea::OnExpandUp()
{
	// This resize will make the necessary amount of empty maps.
	// When we expand one map in height, we need the number of COLUMNS (or width)
	// of maps we are currently using. We make that amount of empty maps.
	// Or, mathematically, 1 (# of new rows) x AreaWidth = # of new maps.
	MapList.resize(MapList.size() + AreaWidth);
	AreaHeight++;	// We "officially" make our Area's height one map larger

	// Move (copy) our existing maps around, so that their
	// orientation is preserved.
	for (int Y = AreaHeight - 1; Y > 0; Y--)
	{
		for (int X = AreaWidth - 1; X >= 0; X--)
		{
			int ID = X + Y * AreaWidth;
			MapList[ID] = MapList[ID - AreaWidth];
		}
	}
	// Make our new maps (top row)
	for (int i = 0; i < AreaWidth; i++)
	{
		CMap tempMap;
		tempMap.OnLoad();
		tempMap.Tex_Tileset = MapList[0].Tex_Tileset;
		MapList[i] = tempMap;
	}
}

void CArea::OnExpandDown()
{
	// This resize will make the necessary amount of empty maps.
	// When we expand one map in height, we need the number of COLUMNS (or width)
	// of maps we are currently using. We make that amount of empty maps.
	// Or, mathematically, 1 (# of new rows) x AreaWidth = # of new maps.
	MapList.resize(MapList.size() + AreaWidth);

	// No movement of maps is necessary! :D-\-<
	// Make our new maps (bottom row)
	for (int i = 0; i < AreaWidth; i++)
	{
		CMap tempMap;
		tempMap.OnLoad();
		tempMap.Tex_Tileset = MapList[0].Tex_Tileset;
		MapList[i + AreaHeight * AreaWidth] = tempMap;
	}
	AreaHeight++;	// We "officially" make our Area's height one map larger
								// We waited until after making new maps. Otherwise,
								// we can just sub in (AreaHeight - 1) into the last
								// statement in the "for" loop above.
								// It makes little difference, I think.
}

void CArea::OnReduceRight()
{
	if (AreaWidth <= 1) return;
	AreaWidth--;	// We "officially" make our Area's width one map smaller

	// Move (copy) our existing maps around, so that their
	// orientation is preserved.
	for (int Y = 1; Y < AreaHeight; Y++)
	{
		for (int X = 0; X < AreaWidth; X++)
		{
			MapList[X + Y * AreaWidth] = MapList[X + Y + Y * AreaWidth];
		}
	}
	MapList.resize(MapList.size() - AreaHeight);
}

bool CArea::OnReduceLeft()
{
	if (AreaWidth <= 1) return false;
	AreaWidth--;	// We "officially" make our Area's width one map smaller

	// Move (copy) our existing maps around, so that their
	// orientation is preserved.
	for (int Y = 0; Y < AreaHeight; Y++)
	{
		for (int X = 0; X < AreaWidth; X++)
		{
			MapList[X + Y * AreaWidth] = MapList[X + 1 + Y * (1 + AreaWidth)];
		}
	}
	MapList.resize(MapList.size() - AreaHeight);
	return true;
}

bool CArea::OnReduceUp()
{
	if (AreaHeight <= 1)	return false;

	// Move (copy) our existing maps around, so that their
	// orientation is preserved.
	for (int Y = 0; Y < AreaHeight - 1; Y++)
	{
		for (int X = 0; X < AreaWidth; X++)
		{
			MapList[X + Y * AreaWidth] = MapList[X + (Y + 1) * AreaWidth];
		}
	}
	AreaHeight--;	// We "officially" make our Area's height one map smaller
	MapList.resize(MapList.size() - AreaWidth);
	return true;
}

void CArea::OnReduceDown()
{
	if (AreaHeight <= 1)	return;

	// Probably the simplest area adjustment.
	// We remove the bottom row of maps,
	// which requires no rearranging of the
	// MapList and no loading of blank maps.
	// The camera position doesn't have to be
	// changed, either!

	AreaHeight--;
	MapList.resize(MapList.size() - AreaWidth);
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

void CArea::SaveArea(char* areaname, char* setpath)
{
	char pre[] = "../data/maps/";
	char ext[] = ".area";
	char* filename = new char[std::strlen(areaname) + std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(filename, pre);
	std::strcat(filename, areaname);
	std::strcat(filename, ext);
	FILE* FileHandle = fopen(filename, "w");

	if (FileHandle == NULL)	return;

	// Output the path to the tileset for the area
	fprintf(FileHandle, setpath);
	fprintf(FileHandle, "\n");

	// Output AreaWidth & AreaHeight
	fprintf(FileHandle, "%d %d\n", AreaWidth, AreaHeight);

	for (int Y = 0; Y < AreaHeight; Y++)
	{
		for (int X = 0; X < AreaWidth; X++)
		{
			int ID = X + Y * AreaWidth;
			MapList[ID].SaveMap(ID, areaname);
			fprintf(FileHandle, "%s%s%02d%s ", pre, areaname, ID, ".map");
		}
		fprintf(FileHandle, "\n");
	}
	fclose(FileHandle);
	delete filename;
}

void CArea::OnCleanup()
{
	if (Tex_Tileset) SDL_DestroyTexture(Tex_Tileset);
	MapList.clear();
}
