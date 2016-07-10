#include "CGamedata.h"

CGameData CGameData::GameControl;

CGameData::CGameData()
{
	Slot = 'A';
	Difficulty = 1;
	InitTime = 0;
	StartTime = 0;
	PrevTime = 0;
	Save = false;
}

bool CGameData::OnInit()
{
	GlobalInfo* GLOBALDATA = new GlobalInfo;

	char pre[] = "../data/game/Global";
	char ext[] = ".bin";

	/* filename character string must be long enough to contain:
	* pre[], or the file prefix;
	* + ext[], file suffix;
	* + 1 character for "\0"
	*/
	char* fglobal = new char[std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(fglobal, pre);
	std::strcat(fglobal, ext);
	FILE* FileHandle = fopen(fglobal, "rb");
	// No global data found; make some
	if (FileHandle == NULL)
	{
		FILE* NewFile = fopen(fglobal, "wb");
		if (fwrite(GLOBALDATA, sizeof(struct GlobalInfo), 1, NewFile) != 1) return false;
		fclose(NewFile);
	}
	else // Global.bin found
	{
		if (fread(GLOBALDATA, sizeof(struct GlobalInfo), 1, FileHandle) != 1) return false;
		Global.deathcount	= GLOBALDATA->deathcount;
		Global.powercount	= GLOBALDATA->powercount + 1;
		Global.Nfinish		= GLOBALDATA->Nfinish;
		Global.uptime			= GLOBALDATA->uptime;
		Global.playtime		= GLOBALDATA->playtime;
		fclose(FileHandle);
	}
	InitTime = Global.uptime;
	delete GLOBALDATA;
	delete fglobal;
	return true;
}

void CGameData::CreateData(char slot, short difficulty)
{
	Slot = slot;
	Difficulty = difficulty;
	StartTime = SDL_GetTicks();
	PrevTime = 0;
}

bool CGameData::ImportData(char slot, int& area, int& MaxHP, int& HP, int& weap, int& ammo,
	unsigned int& purse, int& arsenal, float& pX, float& pY)
{
	GameInfo* GAME = new GameInfo;
	PlayerInfo* PLAYER = new PlayerInfo;

	char pre[] = "../data/game/Game";
	char ext[] = ".bin";

	/* filename character string must be long enough to contain:
	* pre[], or the gamefile prefix;
	* + ext[], gamefile suffix;
	* + 1 character for the slot variable
	* + 1 character for "\0"
	*/
	// 	SDL_Delay(5000);
	char* filename = new char[std::strlen(pre) + std::strlen(ext) + 1 + 1];
	std::strcpy(filename, pre);
	std::strcat(filename, &slot);
	std::strcat(filename, ext);
	FILE* FileHandle = fopen(filename, "rb");

	if (FileHandle == NULL) return false;

	// Write the new game data to the file
	if (fread(GAME, sizeof(struct GameInfo), 1, FileHandle) != 1) return false;

	// Write the fresh player data
	if (fread(PLAYER, sizeof(struct PlayerInfo), 1, FileHandle) != 1) return false;

	// Write game progress to the file
	if (fread(&ProgressList[0], sizeof(int), 1, FileHandle) != 1) return false;

	// ok yeah cool
	fclose(FileHandle);

	Slot = slot;
	Difficulty = GAME->Difficulty;
	StartTime = SDL_GetTicks();
	PrevTime = GAME->TotalTime;
	area = GAME->Area;

	pX = PLAYER->X;
	pY = PLAYER->Y;
	MaxHP = PLAYER->MaxHealth;
	arsenal = arsenal | PLAYER->Arsenal;
	HP = PLAYER->Health;
	purse = PLAYER->Purse;
	weap = PLAYER->Weapon;
	ammo = PLAYER->Ammo;
	delete GAME;
	delete PLAYER;
	delete filename;
	return true;
}

bool CGameData::ExportData(const int& area, const int& MaxHP, const int& HP, const int& weap, const int& ammo,
	const unsigned int& purse, const int& arsenal, const float& pX, const float& pY)
{
	GameInfo* GAME = new GameInfo;
	PlayerInfo* PLAYER = new PlayerInfo;

	PLAYER->X = pX;
	PLAYER->Y = pY;
	PLAYER->MaxHealth = MaxHP;
	PLAYER->Arsenal = arsenal;
	PLAYER->Health = HP;
	PLAYER->Purse = purse;
	PLAYER->Weapon = weap;
	PLAYER->Ammo = ammo;

	GAME->Slot = Slot;
	GAME->Difficulty = Difficulty;
	GAME->Area = area;
	GAME->TotalTime = (SDL_GetTicks() - StartTime) + PrevTime;

	Global.playtime += (SDL_GetTicks() - StartTime) / 10;

	// Update the StartTime and PrevTime
	StartTime = SDL_GetTicks();
	PrevTime = GAME->TotalTime;

	char pre[] = "../data/game/Game";
	char ext[] = ".bin";

	/* filename character string must be long enough to contain:
	* pre[], or the gamefile prefix;
	* + ext[], gamefile suffix;
	* + 1 character for the slot variable
	* + 1 character for "\0"
	*/
	char* filename = new char[std::strlen(pre) + std::strlen(ext) + 1 + 1];
	std::strcpy(filename, pre);
	std::strcat(filename, &Slot);
	std::strcat(filename, ext);
	FILE* FileHandle = fopen(filename, "wb");

	if (FileHandle == NULL) return false;

	// Write the new game data to the file
	if (fwrite(GAME, sizeof(struct GameInfo), 1, FileHandle) != 1) return false;

	// Write the fresh player data
	if (fwrite(PLAYER, sizeof(struct PlayerInfo), 1, FileHandle) != 1) return false;

	// Write game progress to the file
	if (fwrite(&ProgressList[0], sizeof(int), 1, FileHandle) != 1) return false;

	// ok yeah cool
	fclose(FileHandle);
	delete GAME;
	delete PLAYER;
	delete filename;

	Save = false;
	return true;
}

void CGameData::UpdateProg(const int& area, const int& prog)
{
	ProgressList[area] = prog;
}

void CGameData::OnCleanup()
{
	GlobalInfo* GLOBALDATA = new GlobalInfo;
	GLOBALDATA->deathcount = Global.deathcount;
	GLOBALDATA->powercount = Global.powercount;
	GLOBALDATA->Nfinish = Global.Nfinish;
	GLOBALDATA->uptime = Global.uptime;
	GLOBALDATA->playtime = Global.playtime;

	char pre[] = "../data/game/Global";
	char ext[] = ".bin";

	/* filename character string must be long enough to contain:
	* pre[], or the file prefix;
	* + ext[], file suffix;
	* + 1 character for "\0"
	*/
	char* fglobal = new char[std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(fglobal, pre);
	std::strcat(fglobal, ext);
	FILE* FileHandle = fopen(fglobal, "wb");
	if (FileHandle == NULL) return;
	else // Global.bin found
	{
		if (fwrite(GLOBALDATA, sizeof(struct GlobalInfo), 1, FileHandle) != 1) return;
	}
	fclose(FileHandle);
	delete GLOBALDATA;
	delete fglobal;
}
