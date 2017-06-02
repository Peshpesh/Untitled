#include "CMap.h"

CMap::CMap()
{
	Tex_Tileset = NULL;
}

CTile* CMap::GetTile(int X, int Y)
{
	int ID = 0;
	ID = X / TILE_SIZE;
	ID += (MAP_WIDTH * (Y / TILE_SIZE));

	if (ID < 0 || ID >= TileList.size())
	{
		return NULL;
	}
	return &TileList[ID];
}

bool CMap::OnLoad(char const* File)
{
	TileList.clear();
	FILE* FileHandle = fopen(File, "r");

	if (FileHandle == NULL) return false;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			CTile tempTile;
			fscanf(FileHandle, "%d:%d:%d:%d ", &tempTile.TileID, &tempTile.ForeID, &tempTile.TypeID, &tempTile.CollID);
			TileList.push_back(tempTile);
		}
		fscanf(FileHandle, "\n");
	}
	fclose(FileHandle);
	return true;
}

void CMap::OnLoad()
{
	TileList.clear();

	CTile tempTile;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			TileList.push_back(tempTile);
		}
	}
}

void CMap::OnRender(SDL_Renderer* renderer, int MapX, int MapY, bool bg)
{
	if (Tex_Tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(Tex_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	int TilesetWidth  = PixWidth / TILE_SIZE; // tiles
	int TilesetHeight = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int TilesetX = 0, TilesetY = 0;
			if (bg && TileList[ID].TileID >= 0)
			{
				TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
				TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;
			}
			else if (!bg && TileList[ID].ForeID >= 0)
			{
				TilesetX = (TileList[ID].ForeID % TilesetWidth) * TILE_SIZE;
				TilesetY = (TileList[ID].ForeID / TilesetWidth) * TILE_SIZE;
			}
			else
			{
				ID++;
				continue;
			}
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			CSurface::OnDraw(renderer, Tex_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::ViewMap(SDL_Renderer* renderer, SDL_Texture* ui, int Xo, int Yo)
{
	if (ui == NULL)	return;

	int VTileSize = 2; // Pixels
	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int VTileY = 350; // 350 px is where the 2 x 2 tiles start for the editor.
			if (TileList[ID].TileID < 0)
			{
				// Do Nothing
			}
			else
			{
				switch (TileList[ID].TypeID)
				{
					case TILE_TYPE_NORMAL: VTileY += VTileSize; break;
					case TILE_TYPE_WATER: VTileY += VTileSize * 2; break;
					case TILE_TYPE_ICE: VTileY += VTileSize * 3; break;
					case TILE_TYPE_FIRE: VTileY += VTileSize * 4; break;
					default: break;
				}
			}
			CSurface::OnDraw(renderer, ui, Xo + X * VTileSize, Yo + Y * VTileSize, 0, VTileY, VTileSize, VTileSize);
			ID++;
		}
	}
}

void CMap::ChangeTile(int X, int Y, int tile, int fore, int type, int coll)
{
	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
	TileList[ID].TileID = tile;
	TileList[ID].ForeID = fore;
	TileList[ID].TypeID = type;
	TileList[ID].CollID = coll;
}
