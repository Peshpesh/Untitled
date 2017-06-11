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
	tempTile.TileID = -1;
	tempTile.ForeID = -1;
	tempTile.TypeID = TILE_TYPE_NORMAL;
	tempTile.CollID = SOLID_NONE;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			TileList.push_back(tempTile);
		}
	}
}

void CMap::OnRender(int MapX, int MapY, bool bg)
{
	if (Tex_Tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(Tex_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w  = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int TilesetX = 0, TilesetY = 0;
			if (bg && TileList[ID].TileID >= 0)
			{
				TilesetX = (TileList[ID].TileID % tset_w) * TILE_SIZE;
				TilesetY = (TileList[ID].TileID / tset_w) * TILE_SIZE;
			}
			else if (!bg && TileList[ID].ForeID >= 0)
			{
				TilesetX = (TileList[ID].ForeID % tset_w) * TILE_SIZE;
				TilesetY = (TileList[ID].ForeID / tset_w) * TILE_SIZE;
			}
			else
			{
				ID++;
				continue;
			}
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			CSurface::OnDraw(Tex_Tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::OnRenderType(SDL_Texture* tileset, int MapX, int MapY)
{
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			int TilesetX = (TileList[ID].TypeID % tset_w) * TILE_SIZE;
			int TilesetY = (TileList[ID].TypeID / tset_w) * TILE_SIZE;
			CSurface::OnDraw(tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::OnRenderColl(SDL_Texture* tileset, int MapX, int MapY)
{
	if (tileset == NULL) return;

	int PixWidth;
	int PixHeight;

	SDL_QueryTexture(tileset, NULL, NULL, &PixWidth, &PixHeight);

	int tset_w = PixWidth / TILE_SIZE; // tiles
	int tset_h = PixHeight / TILE_SIZE; // tiles

	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int tX = MapX + (X * TILE_SIZE);
			int tY = MapY + (Y * TILE_SIZE);
			int TilesetX = ((TileList[ID].CollID) % tset_w) * TILE_SIZE;
			int TilesetY = ((TileList[ID].CollID) / tset_w) * TILE_SIZE;
			CSurface::OnDraw(tileset, tX, tY, TilesetX, TilesetY, TILE_SIZE, TILE_SIZE);
			ID++;
		}
	}
}

void CMap::ViewMap(SDL_Texture* ui, int Xo, int Yo)
{
	if (ui == NULL)	return;

	int VTileSize = 2; // Pixels
	int ID = 0;

	for (int Y = 0; Y < MAP_HEIGHT; Y++)
	{
		for (int X = 0; X < MAP_WIDTH; X++)
		{
			int VTileY = 350; // 350 px is where the 2 x 2 tiles start for the editor.
			switch (TileList[ID].TypeID)
			{
					case TILE_TYPE_NORMAL: VTileY += VTileSize * 3; break;
					case TILE_TYPE_WATER: VTileY += VTileSize * 2; break;
					case TILE_TYPE_ICE: VTileY += VTileSize * 4; break;
					case TILE_TYPE_FIRE: VTileY += VTileSize * 4; break;
					default: break;
			}
			CSurface::OnDraw(ui, Xo + X * VTileSize, Yo + Y * VTileSize, 0, VTileY, VTileSize, VTileSize);
			ID++;
		}
	}
}

void CMap::ChangeTile(int X, int Y, int tile, int fore, int type, int coll, int usetiles)
{
	int ID = (X / TILE_SIZE) + (Y / TILE_SIZE) * MAP_WIDTH;
	if (usetiles & ENABLE_BTILE) 	TileList[ID].TileID = tile;
	if (usetiles & ENABLE_FTILE) 	TileList[ID].ForeID = fore;
	if (usetiles & ENABLE_TYPE)		TileList[ID].TypeID = type;
	if (usetiles & ENABLE_COLL)	TileList[ID].CollID = coll;
}

void CMap::SaveMap(int ID, char const* areaname)
{
	int TensDigit = ID / 10;
	int OnesDigit = ID % 10;
	int zeroASCII = 48;

	// Add 48, as 48 is the ASCII decimal code for zero ('0')
	char ID_ASCII[] = { (char)(TensDigit + zeroASCII), (char)(OnesDigit + zeroASCII), '\0'};

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
			fprintf(FileHandle, "%d:%d:%d:%d ", TileList[ID].TileID, TileList[ID].ForeID, TileList[ID].TypeID, TileList[ID].CollID);
		}
		fprintf(FileHandle, "\n");
	}
	fclose(FileHandle);
	delete filename;
}
