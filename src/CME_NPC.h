#ifndef _CME_NPC_H_
#define _CME_NPC_H_

#include <SDL.h>
#include "CEntity.h"
#include "Font.h"

enum Tablename
{
	DEBUG = 0
};

class CME_NPC
{
public:
	static CME_NPC NPCControl;

	SDL_Texture* NPC_Tileset;	// Tileset containing entities for the area
	SDL_Texture* NPC_Common;    // Tileset containing global entities

	std::vector<CEntity> EntityList; // Working list of entities
	std::vector<int> ID_List;        // List of NPC_IDs that identify entities of equal index in EntityList
	char Speak_List[255][50];		 // List of dialogue for each NPC that speaks
	int Speak_ID;

	int Table_ID;     // Working Table ID in Map Editor (starts at 0, aka DEBUG)
	int NPC_ID;       // Working NPC ID in Map Editor (starts at 0)

public:
	CME_NPC();

	bool CWrite_Name(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y);

	void CWrite_Common(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y);
	void CWrite_Debug(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y);

	// Write out a list of entity information for the working area.
	void SaveList(char* filename);

	// Load an existing list of entities for an area.
	bool LoadList(char* filename, SDL_Renderer* renderer);

	// Load a new table of entities to work with.
	bool LoadTable(int ID, char* &entitypath);

	// This function returns either the common or local NPC textures. 
	// Uses static NPC_ID, so this should be used when editing directly.
	SDL_Texture* ForwardSet();

	// This function returns either the common or local NPC textures.
	// Uses a specified NPC_ID as argument, so this should be used if loading
	// NPC information from a data file with ID's listed.
	SDL_Texture* ForwardSet(int ID);
};

#endif