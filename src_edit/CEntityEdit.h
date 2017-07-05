#ifndef _C_ENTITYEDIT_H_
#define _C_ENTITYEDIT_H_

#include <SDL.h>
#include "CEntity.h"
#include "CEntityRes.h"
#include "CFont.h"

enum Tablename
{
	DEBUG = 0
};

class CEntityEdit
{
public:
	static CEntityEdit NPCControl;

	SDL_Texture* NPC_Tileset;	// Tileset containing entities for the area
	SDL_Texture* NPC_Common;    // Tileset containing global entities

	std::vector<CEntity> EntityList; // Working list of entities
	std::vector<bool> CommonList;		 // List bool, true for common entities, false for local
	std::vector<int> ID_List;        // List of NPC_IDs that identify entities of equal index in EntityList

	int Table_ID;     // Working Table ID in Map Editor (starts at 0, aka DEBUG)
	bool UseCommon;		// When true, NPC_ID is for common set. Otherwise, for unique
	int NPC_ID;       // Working NPC ID in Map Editor (starts at 0)

public:
	CEntityEdit();

	void clearVectors();

	bool CWrite_Name(const int& fontID, int X, int Y);

	void CWrite_Common(const int& fontID, int X, int Y);
	void CWrite_Debug(const int& fontID, int X, int Y);

	// Write out a list of entity information for the working area.
	bool SaveList(char const* filename);

	// Load an existing list of entities for an area.
	bool LoadList(char const* filename);

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
