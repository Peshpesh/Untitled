#include "CME_NPC.h"

CME_NPC CME_NPC::NPCControl;

CME_NPC::CME_NPC()
{
	NPC_Tileset = NULL;
	NPC_Common = NULL;
	NPC_ID = 0;
	Table_ID = DEBUG;
	Speak_ID = 0;
}

bool CME_NPC::CWrite_Name(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	if (renderer == NULL || font == NULL)
		return false;

	if (CEntityInfo::EntityInfoList[NPC_ID].Common)
		CWrite_Common(renderer, font, X, Y);
	else 
	{
		switch (Table_ID)
		{
		case DEBUG: CWrite_Debug(renderer, font, X, Y); break;
		default: break;
		}
	}
	return true;
}

void CME_NPC::SaveList(char* filename)
{
	char pre[] = "../data/maps/";
	char ext[] = ".ent";
	char* e_listname = new char[std::strlen(filename) + std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(e_listname, pre);
	std::strcat(e_listname, filename);
	std::strcat(e_listname, ext);

	FILE* FileHandle = fopen(e_listname, "w");

	if (FileHandle == NULL)
		return;

	// The very start of the file will be a number that 
	// indicates which table of entities we're using.
	fprintf(FileHandle, "%d\n", Table_ID);

	// We need NPC_IDs, and the location of 
	// all normal entities on the map.
	for (int i = 0; i < EntityList.size(); i++)
	{
		int X = EntityList[i].X;
		int Y = EntityList[i].Y;
		fprintf(FileHandle, "%d:%d:%d\n", ID_List[i], X, Y);
	}

	fclose(FileHandle);

	delete e_listname;
}

bool CME_NPC::LoadList(char* filename, SDL_Renderer* renderer)
{
	char* EntityFile = new char[255];

	int ID, Xo, Yo;

	char pre[] = "../data/maps/";
	char ext[] = ".ent";
	char* listname = new char[std::strlen(filename) + std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(listname, pre);
	std::strcat(listname, filename);
	std::strcat(listname, ext);

	FILE* EFileHandle = fopen(listname, "r");
	if (EFileHandle == NULL)
		return false;

	fscanf(EFileHandle, "%d\n", &Table_ID);

	switch (Table_ID)
	{
	case DEBUG: CEntityInfo::OnLoad("../res/npc/debug.tbl"); std::strcpy(EntityFile, "../res/npc/debug.png"); break;
	default: break;
	}

	if ((NPC_Tileset = CSurface::OnLoad(EntityFile, renderer)) == NULL)
	{
		return false;
	}

	EntityList.clear();
	ID_List.clear();
	NPC_ID = 0;

	while (fscanf(EFileHandle, "%d:%d:%d\n", &ID, &Xo, &Yo) == 3)
	{
		EntityList.resize(EntityList.size() + 1);
		ID_List.resize(ID_List.size() + 1);
		if (!EntityList[EntityList.size() - 1].OnLoad(ForwardSet(ID), renderer,
			CEntityInfo::EntityInfoList[ID].Xo, CEntityInfo::EntityInfoList[ID].Yo,
			CEntityInfo::EntityInfoList[ID].W, CEntityInfo::EntityInfoList[ID].H, ID)) return false;
		EntityList[EntityList.size() - 1].X = Xo; EntityList[EntityList.size() - 1].Y = Yo;
		ID_List[EntityList.size() - 1] = ID;
	}

	fclose(EFileHandle);
	delete listname;
	delete EntityFile;
	return true;
}

bool CME_NPC::LoadTable(int ID, char* &entitypath)
{
	switch (ID)
	{
	case DEBUG: CEntityInfo::OnLoad("../res/npc/debug.tbl"); Table_ID = DEBUG; entitypath = "../res/npc/debug.png"; break;
	default: break;
	}

	EntityList.clear();
	ID_List.clear();
	NPC_ID = 0;
	
	return true;
}

SDL_Texture* CME_NPC::ForwardSet()
{
	if (CEntityInfo::EntityInfoList[NPC_ID].Common)
		return NPC_Common;
	
	return NPC_Tileset;
}

// Returns an SDL Texture pointer: either the common NPC texture,
// or the unique (local) NPC texture.
SDL_Texture* CME_NPC::ForwardSet(int ID)
{
	if (CEntityInfo::EntityInfoList[ID].Common)
		return NPC_Common;

	return NPC_Tileset;
}