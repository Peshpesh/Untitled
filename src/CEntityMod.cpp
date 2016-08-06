#include "CEntityMod.h"

CEntityMod CEntityMod::EntityControl;

CEntityMod::CEntityMod()
{
	Com_Texture = NULL;
	Unq_Texture = NULL;
	Arm_Texture = NULL;
	Tex_Bullets = NULL;
}

bool CEntityMod::OnInit(SDL_Renderer* renderer)
{
	if ((Com_Texture = CSurface::OnLoad("../res/npc/common.png", renderer)) == NULL) return false;
	if ((Arm_Texture = CSurface::OnLoad("../res/npc/arms.png", renderer)) == NULL) return false;
	if ((Tex_Bullets = CSurface::OnLoad("../res/npc/bullet.png", renderer)) == NULL) return false;
	return true;
}

bool CEntityMod::LoadNPCs(char* NPC_List, SDL_Renderer* renderer)
{
	// We will need to clear all the NPCs that already exist in the
	// EntityList vector. This has to be done before loading a new
	// list of NPCs in an area. Of course, we will also need to take
	// care in preserving the Player (user) entity.
	if (CEntity::EntityList.size() > 1)
	{
		for (int i = (CEntity::EntityList.size() - 1); i > 0; i--)
		{
			delete CEntity::EntityList[i];
			CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
		}
	}
	// Now, we begin to load the NPC information for the new area.
	int ID, X_loc, Y_loc, Table_ID;
	char* EntityFile = new char[255];

	// Try to open the Entity data file.
	FILE* NFileHandle = fopen(NPC_List, "r");
	if (NFileHandle == NULL) return false;

	// The first entry in the data file is always the Table_ID.
	// This tells us which unique (local) NPCs were working with.
	fscanf(NFileHandle, "%d\n", &Table_ID);

	// Get the necessary info describing all NPCs in the new area.
	switch (Table_ID)
	{
		case DEBUG: CEntityInfo::OnLoad("../res/npc/debug.tbl"); std::strcpy(EntityFile, "../res/npc/debug.png"); break;
		default: break;
	}

	// Load the texture of unique NPCs.
	if ((Unq_Texture = CSurface::OnLoad(EntityFile, renderer)) == NULL)	return false;

	// Get the info about the NPCs in the area (which NPC and where they are)
	while (fscanf(NFileHandle, "%d:%d:%d\n", &ID, &X_loc, &Y_loc) == 3)
	{
		int MaxFrames = 0;
		if (CEntityInfo::EntityInfoList[ID].Common)
		{
			switch (ID)
			{
				case YOSHI:	CEntity::EntityList.push_back(new CYoshi); break;
				case MAINCHAR: break;
				case EVILMAIN: CEntity::EntityList.push_back(new CShop); break;
				case BOMB: CEntity::EntityList.push_back(new CBomb); break;
				default:	break;
			} // end of common switch
			CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(Com_Texture, renderer, CEntityInfo::EntityInfoList[ID].Xo,
				CEntityInfo::EntityInfoList[ID].Yo, CEntityInfo::EntityInfoList[ID].W, CEntityInfo::EntityInfoList[ID].H, MaxFrames);
		}
		else
		{ // start of non-common switch
			switch (Table_ID)
			{
				case DEBUG:
				{
					switch (ID)
					{
						case WSTAR: break;
						case BSTAR: break;
						case BARS: CEntity::EntityList.push_back(new CBars); break;
						case BOX: CEntity::EntityList.push_back(new CBox); break;
						case SPIKEFALL: CEntity::EntityList.push_back(new CSpikefall); break;
						case BLDSPK_UP: CEntity::EntityList.push_back(new CBldspkup); break;
						case HEART: CEntity::EntityList.push_back(new CHeart); break;
						case AMYTHYST: CEntity::EntityList.push_back(new CAmythyst); break;
						case ACIDBALL: CEntity::EntityList.push_back(new CAcidball); break;
						case DOOR: CEntity::EntityList.push_back(new CDoor); break;
						case SVPT: CEntity::EntityList.push_back(new CSVPT); break;
						case SIGN: CEntity::EntityList.push_back(new CSign); break;
						default: break;
					}
					break; // end of DEBUG
				}
				default: break;
			} // end of non-common switch
			CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(Unq_Texture, renderer, CEntityInfo::EntityInfoList[ID].Xo,
				CEntityInfo::EntityInfoList[ID].Yo, CEntityInfo::EntityInfoList[ID].W, CEntityInfo::EntityInfoList[ID].H, MaxFrames);
		}
		CEntity::EntityList[CEntity::EntityList.size() - 1]->X = X_loc;
		CEntity::EntityList[CEntity::EntityList.size() - 1]->Y = Y_loc;
	}
	fclose(NFileHandle);
	delete EntityFile;
	return true;
}

void CEntityMod::OnCleanup()
{
	for (int i = (CEntity::EntityList.size() - 1); i > 0; i--)
	{
		delete CEntity::EntityList[i];   // All entities that are not the player/user are dynamic
	}
	CEntity::EntityList.clear(); // Destroy the vector properly
}
