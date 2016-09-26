#ifndef _C_ENTITYMOD_H_
#define _C_ENTITYMOD_H_

#include <vector>
#include "CEntity.h"
#include "All_Entities.h"
#include "CEntityRes.h"

class CEntityMod
{
private:
	// enum NPC_Tablename
	// {
	// 	DEBUG = 0
	// };
	// enum Common_NPC // NPC_ID order starts at 0 with commons
	// {
	// 	YOSHI = 0,
	// 	MAINCHAR,
	// 	EVILMAIN,
	// 	BOMB,
	// 	EXPLODE
	// };
	// // Note: NPCS after common must start in ID# after where common ends
	// enum Debug_NPC // NPC_ID's from the Debug NPC table
	// {
	// 	WSTAR = 5,
	// 	BSTAR,
	// 	BARS, BOX, SPIKEFALL, BLDSPK_UP,
	// 	HEART, AMYTHYST, ACIDBALL, DOOR, SVPT, SIGN
	// };

public:
	CEntityMod();

	// static CEntityMod EntityControl;
	// SDL_Texture*	Com_Texture;	// Common (global) NPC Image pointer
	// SDL_Texture*	Unq_Texture;	// Unique (local) NPC Image pointer
	// SDL_Texture*	Arm_Texture;	// Arms Image pointer
	// SDL_Texture*	Tex_Bullets;	// Bullets Image pointer

	// bool OnInit(SDL_Renderer* renderer);
	// static bool OnInit(SDL_Renderer* renderer);

	// bool LoadNPCs(char* NPC_List, SDL_Renderer* renderer);
	static bool LoadEntities(char const* EntityFile, SDL_Renderer* renderer);

	// void OnCleanup();
	static void OnCleanup();
};
#endif
