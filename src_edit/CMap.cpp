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
			// fscanf(FileHandle, "%d:%d:%d ", &tempTile.TileID, &tempTile.ForeID, &tempTile.TypeID);
			fscanf(FileHandle, "%d:%d:%d:%d ", &tempTile.TileID, &tempTile.ForeID, &tempTile.TypeID, &tempTile.Slope);
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
	tempTile.TileID = 0;
	tempTile.ForeID = -1;
	tempTile.TypeID = TILE_TYPE_NONE;
	tempTile.Slope = SLOPE_FLAT;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			TileList.push_back(tempTile);
		}
	}
}

void CMap::OnRender(SDL_Renderer* renderer, int MapX, int MapY, bool depth)
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
			if (TileList[ID].TypeID == TILE_TYPE_NONE)
			{
				ID++;
				continue;
			}
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			int TilesetX = 0, TilesetY = 0;
			if (!depth)
			{
				TilesetX = (TileList[ID].TileID % TilesetWidth) * TILE_SIZE;
				TilesetY = (TileList[ID].TileID / TilesetWidth) * TILE_SIZE;
			}
			else if (TileList[ID].ForeID >= 0)
			{
				TilesetX = (TileList[ID].ForeID % TilesetWidth) * TILE_SIZE;
				TilesetY = (TileList[ID].ForeID / TilesetWidth) * TILE_SIZE;
			}
			else
			{
				ID++;
				continue;
			}
			CSurface::OnDraw(renderer, Tex_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::OnRenderType(SDL_Renderer* renderer, SDL_Texture* tileset, int MapX, int MapY)
{
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int TilesetWidth = PixWidth / TILE_SIZE; // tiles
	int TilesetHeight = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			int TilesetX = (TileList[ID].TypeID % TilesetWidth) * TILE_SIZE;
			int TilesetY = (TileList[ID].TypeID / TilesetWidth) * TILE_SIZE;
			CSurface::OnDraw(renderer, tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::OnRenderSlope(SDL_Renderer* renderer, SDL_Texture* tileset, int MapX, int MapY)
{
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int TilesetWidth = PixWidth / TILE_SIZE; // tiles
	int TilesetHeight = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			int TilesetX = ((TileList[ID].Slope) % TilesetWidth) * TILE_SIZE;
			int TilesetY = ((TileList[ID].Slope) / TilesetWidth) * TILE_SIZE;
			CSurface::OnDraw(renderer, tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
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
			if (TileList[ID].TypeID == TILE_TYPE_NONE && TileList[ID].TileID == 0)
			{
				// Do Nothing
			}
			else
			{
				switch (TileList[ID].TypeID)
				{
					case TILE_TYPE_NONE: VTileY += VTileSize; break;
					case TILE_TYPE_HOLLOW: VTileY += VTileSize; break;
					case TILE_TYPE_NORMAL: VTileY += VTileSize * 3; break;
					case TILE_TYPE_BLOCK: break;
					case TILE_TYPE_WATER: VTileY += VTileSize * 2; break;
					case TILE_TYPE_ICE: VTileY += VTileSize * 4; break;
					case TILE_TYPE_FIRE: VTileY += VTileSize * 4; break;
					default: break;
				}
			}
			CSurface::OnDraw(renderer, ui, Xo + X * VTileSize, Yo + Y * VTileSize, 0, VTileY, VTileSize, VTileSize);
			ID++;
		}
	}
}

void CMap::ChangeTile(int X, int Y, int tile, int fore, int type, int slope)
{
	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
	TileList[ID].TileID = tile;
	TileList[ID].ForeID = fore;
	TileList[ID].TypeID = type;
	TileList[ID].Slope = slope;
}

void CMap::SaveMap(int ID, char const* areaname)
{
	int TensDigit = ID / 10;
	int OnesDigit = ID % 10;

	// Add 48, as 48 is the ASCII decimal code for zero ('0')
	char ID_ASCII[] = { (char)(TensDigit + 48), (char)(OnesDigit + 48), '\0'};

	// Add 5 for ext and '\0', 7 for pre, and 2 for ID
//	char* filename = new char[std::strlen(areaname) + 5 + 7 + 2];
	char pre[] = "../data/maps/";
	char ext[] = ".map";
	char* filename = new char[std::strlen(areaname) + std::strlen(pre) + std::strlen(ext) + std::strlen(ID_ASCII) + 1];
	std::strcpy(filename, pre);
	std::strcat(filename, areaname);
	std::strcat(filename, ID_ASCII);
	std::strcat(filename, ext);

	FILE* FileHandle = fopen(filename, "w");
	if (FileHandle == NULL) return;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int ID = X + Y * MAP_WIDTH;
			// fprintf(FileHandle, "%d:%d:%d ", TileList[ID].TileID, TileList[ID].ForeID, TileList[ID].TypeID);
			fprintf(FileHandle, "%d:%d:%d:%d ", TileList[ID].TileID, TileList[ID].ForeID, TileList[ID].TypeID, TileList[ID].Slope);
		}
		fprintf(FileHandle, "\n");
	}
	fclose(FileHandle);
	delete filename;
}
