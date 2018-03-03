#ifndef _CGAMEDATA_H_
#define _CGAMEDATA_H_

#include <vector>
#include <stdio.h>
#include <cstring>
#include <SDL.h>

enum AreaID {
	AREA_1 = 0,
	AREA_3,
	ARENA,
};

class CGameData
{
public:
	static CGameData		GameControl;

	char Slot;
	short Difficulty;
	unsigned long InitTime;		// total centiseconds passed over all-time as of most recent SDL initialization
	unsigned long StartTime;	// ms passed since SDL initialization when game data is imported
	unsigned long PrevTime;     // ms elapsed as recorded in imported data
	bool Save;

public:
	int	ProgressList[ARENA + 1];

private:
	struct GlobalInfo
	{
		GlobalInfo()
		{
			deathcount = 0;
			powercount = 1;
			Nfinish = 0;
			uptime = 0;
			playtime = 0;
		}
		int deathcount;
		int powercount;
		int Nfinish;
		unsigned long uptime;
		unsigned long playtime;
	};
	struct GameInfo
	{
		GameInfo()
		{
			Slot = 'A';
			Difficulty = 1;
			Area = ARENA;
			TotalTime = 0;
			Ndeath = 0;
			Nload = 0;
			Nsave = 0;
		}
		char Slot;
		short Difficulty;
		unsigned short Area;
		unsigned long TotalTime;
		unsigned short Ndeath, Nload, Nsave;
	};
	struct PlayerInfo
	{
		PlayerInfo()
		{
			MaxHealth = 3;
			Health = 3;
			Weapon = 1;
			Ammo = 0;
			Purse = 0;
			Arsenal = 0x00000001;
			X = 300.0;
			Y = 300.0;
		}
		int MaxHealth, Health;
		int Weapon, Ammo;
		int Purse;
		int Arsenal;
		float X, Y;
	};

public:
	CGameData();
	GlobalInfo Global;

	bool	OnInit();

	/* The user designates a game-slot and difficulty for their
	* game, and the function uses those to make a gamedata file
	* that contains information describing the conditions at the
	* beginning of the game.
	*/
	void	CreateData(char slot, short difficulty);

	bool	ImportData(char slot, int& area, int& MaxHP, int& HP, int& weap, int& ammo,
		unsigned int& purse, int& arsenal, float& pX, float& pY);

	bool	ExportData(const int& area, const int& MaxHP, const int& HP, const int& weap, const int& ammo,
		const unsigned int& purse, const int& arsenal, const float& pX, const float& pY);

	void	UpdateProg(const int& area, const int& prog);

	void	OnCleanup();
};
#endif
