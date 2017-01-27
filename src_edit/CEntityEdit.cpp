#include "CEntityEdit.h"

CEntityEdit CEntityEdit::NPCControl;

CEntityEdit::CEntityEdit()
{
	NPC_Tileset = NULL;
	NPC_Common = NULL;
	NPC_ID = 0;
	UseCommon = true;
	Table_ID = DEBUG;
	Speak_ID = 0;
}

bool CEntityEdit::CWrite_Name(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	if (renderer == NULL || font == NULL)
		return false;

//	if (CEntityInfo::EntityInfoList[NPC_ID].Common)
	if (UseCommon) CWrite_Common(renderer, font, X, Y);
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

void CEntityEdit::SaveList(char const* filename)
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
		int C = CommonList[i];
		int ID = ID_List[i];
		int X = EntityList[i].X;
		int Y = EntityList[i].Y;
		fprintf(FileHandle, "%d:%d:%d:%d\n", C, ID, X, Y);
	}

	fclose(FileHandle);
	delete e_listname;
}

bool CEntityEdit::LoadList(char const* filename, SDL_Renderer* renderer)
{
	char* EntityFile = new char[255];

	int com, ID, Xo, Yo;

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
		// case DEBUG: CEntityInfo::OnLoad("../res/npc/debug.tbl"); std::strcpy(EntityFile, "../res/npc/debug.png"); break;
		case DEBUG: CEntityInfo::LoadUnique("../res/npc/debug.tbl"); std::strcpy(EntityFile, "../res/npc/debug.png"); break;
		default: break;
	}

	if ((NPC_Tileset = CSurface::OnLoad(EntityFile, renderer)) == NULL)
	{
		return false;
	}

	EntityList.clear();
	CommonList.clear();
	ID_List.clear();
	NPC_ID = 0;

	while (fscanf(EFileHandle, "%d:%d:%d:%d\n", &com, &ID, &Xo, &Yo) == 4)
	{
		EntityList.resize(EntityList.size() + 1);
		CommonList.resize(CommonList.size() + 1);
		ID_List.resize(ID_List.size() + 1);

		// if (!EntityList[EntityList.size() - 1].OnLoad(ForwardSet(ID),
		// 	CEntityInfo::EntityInfoList[ID].Xo, CEntityInfo::EntityInfoList[ID].Yo,
		// 	CEntityInfo::EntityInfoList[ID].W, CEntityInfo::EntityInfoList[ID].H, ID)) return false;

		if (com)
		{
			int Xt = CEntityInfo::Com_EntityInfo[ID].Xo;
			int Yt = CEntityInfo::Com_EntityInfo[ID].Yo;
			int W = CEntityInfo::Com_EntityInfo[ID].W;
			int H = CEntityInfo::Com_EntityInfo[ID].H;
			if (!EntityList[EntityList.size() - 1].OnLoad(NPC_Common, Xt, Yt, W, H, ID))
				return false;
		}
		else
		{
			int Xt = CEntityInfo::Unq_EntityInfo[ID].Xo;
			int Yt = CEntityInfo::Unq_EntityInfo[ID].Yo;
			int W = CEntityInfo::Unq_EntityInfo[ID].W;
			int H = CEntityInfo::Unq_EntityInfo[ID].H;
			if (!EntityList[EntityList.size() - 1].OnLoad(NPC_Tileset, Xt, Yt, W, H, ID))
				return false;
		}
		EntityList[EntityList.size() - 1].X = Xo; EntityList[EntityList.size() - 1].Y = Yo;
		CommonList[CommonList.size() - 1] = com;
		ID_List[EntityList.size() - 1] = ID;
	}

	fclose(EFileHandle);
	delete listname;
	delete EntityFile;
	return true;
}

bool CEntityEdit::LoadTable(int ID, char* &entitypath)
{
	switch (ID)
	{
	// case DEBUG: CEntityInfo::OnLoad("../res/npc/debug.tbl"); Table_ID = DEBUG; entitypath = "../res/npc/debug.png"; break;
	case DEBUG: CEntityInfo::LoadUnique("../res/npc/debug.tbl"); Table_ID = DEBUG; entitypath = "../res/npc/debug.png"; break;
	default: break;
	}

	EntityList.clear();
	CommonList.clear();
	ID_List.clear();
	NPC_ID = 0;

	return true;
}

SDL_Texture* CEntityEdit::ForwardSet()
{
//	if (CEntityInfo::EntityInfoList[NPC_ID].Common)
	if (UseCommon)
		return NPC_Common;

	return NPC_Tileset;
}

// Returns an SDL Texture pointer: either the common NPC texture,
// or the unique (local) NPC texture.
SDL_Texture* CEntityEdit::ForwardSet(int ID)
{
//	if (CEntityInfo::EntityInfoList[ID].Common)
	if (CommonList[ID])
		return NPC_Common;

	return NPC_Tileset;
}


void CEntityEdit::CWrite_Common(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	switch (NPC_ID)
	{
	/*ID*/
	/*00*/ case YOSHI: Font::Write(renderer, font, "YOSHI", X, Y); break;
	/*01*/ case MAINCHAR: Font::Write(renderer, font, "MAINCHAR", X, Y); break;
	/*02*/ case EVILMAIN: Font::Write(renderer, font, "EVILMAIN", X, Y); break;
	case BOMB: Font::Write(renderer, font, "BOMB", X, Y); break;
	case EXPLODE: Font::Write(renderer, font, "EXPLODE", X, Y); break;
	default: break;
	}
}

void CEntityEdit::CWrite_Debug(SDL_Renderer* renderer, SDL_Texture* font, int X, int Y)
{
	switch (NPC_ID)
	{
	/*ID*/
	/*03*/ case WSTAR: Font::Write(renderer, font, "WHITE STAR", X, Y); break;
	/*04*/ case BSTAR: Font::Write(renderer, font, "BLACK STAR", X, Y); break;
	/*05*/ case BARS: Font::Write(renderer, font, "BARS", X, Y); break;
	/*06*/ case BOX: Font::Write(renderer, font, "BOX", X, Y); break;
	/*07*/ case SPIKEFALL: Font::Write(renderer, font, "SPIKEFALL", X, Y); break;
	/*08*/ case BLDSPK_UP: Font::Write(renderer, font, "BLDSPK UP", X, Y); break;
	/*09*/ case HEART: Font::Write(renderer, font, "HEART", X, Y); break;
	/*10*/ case AMYTHYST: Font::Write(renderer, font, "AMYTHYST", X, Y); break;
	/*11*/ case ACIDBALL: Font::Write(renderer, font, "ACIDBALL", X, Y); break;
	/*12*/ case DOOR: Font::Write(renderer, font, "DOOR", X, Y); break;
	/*13*/ case SVPT: Font::Write(renderer, font, "SAVEPT", X, Y); break;
	/*14*/ case SIGN: Font::Write(renderer, font, "SIGN", X, Y); break;
	default: break;
	}
}
