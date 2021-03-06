#include "CEntityMod.h"

// CEntityMod CEntityMod::EntityControl;

CEntityMod::CEntityMod()
{
	// Com_Texture = NULL;
	// Unq_Texture = NULL;
	// Arm_Texture = NULL;
	// Tex_Bullets = NULL;
}

// bool CEntityMod::OnInit(SDL_Renderer* renderer)
// {
// 	// if ((Com_Texture = CSurface::OnLoad("../res/npc/common.png", renderer)) == NULL) return false;
// 	// if ((Arm_Texture = CSurface::OnLoad("../res/npc/arms.png", renderer)) == NULL) return false;
// 	// if ((Tex_Bullets = CSurface::OnLoad("../res/npc/bullet.png", renderer)) == NULL) return false;
// 	return true;
// }

// bool CEntityMod::LoadNPCs(char* NPC_List, SDL_Renderer* renderer)
bool CEntityMod::LoadEntities(char const* NPC_List, SDL_Renderer* renderer)
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
	int Table_ID, com, ID, X_loc, Y_loc;
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
		// case DEBUG: CEntityInfo::OnLoad("../res/npc/debug.tbl"); std::strcpy(EntityFile, "../res/npc/debug.png"); break;
		case SET_DEBUG: CEntityInfo::LoadUnique("../res/npc/debug.tbl"); std::strcpy(EntityFile, "../res/npc/debug.png"); break;
		default: break;
	}

	// Load the texture of unique NPCs.
	// if ((Unq_Texture = CSurface::OnLoad(EntityFile, renderer)) == NULL)	return false;
	if (!CEntityRes::OnLoad(renderer, Table_ID)) return false;

	// Get the info about the NPCs in the area (which NPC and where they are)
	//	while (fscanf(NFileHandle, "%d:%d:%d\n", &ID, &X_loc, &Y_loc) == 3)
	while (fscanf(NFileHandle, "%d:%d:%d:%d\n", &com, &ID, &X_loc, &Y_loc) == 4)
	{
		int MaxFrames = 0;
		// if (CEntityInfo::EntityInfoList[ID].Common)
		if (com)
		{
			switch (ID)
			{
				case YOSHI:	CEntity::EntityList.push_back(new CYoshi); break;
				case MAINCHAR: break;
				case EVILMAIN: CEntity::EntityList.push_back(new CShop); break;
				case BOMB: CEntity::EntityList.push_back(new CBomb); MaxFrames = 2; break;
				case EXPLODE: CEntity::EntityList.push_back(new CExplode); MaxFrames = 2; break;
				default:	break;
			} // end of common switch
			// CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(Com_Texture, CEntityInfo::EntityInfoList[ID].Xo,
			// 	CEntityInfo::EntityInfoList[ID].Yo, CEntityInfo::EntityInfoList[ID].W, CEntityInfo::EntityInfoList[ID].H, MaxFrames);
			int Xt = CEntityInfo::Com_EntityInfo[ID].Xo;
			int Yt = CEntityInfo::Com_EntityInfo[ID].Yo;
			int W = CEntityInfo::Com_EntityInfo[ID].W;
			int H = CEntityInfo::Com_EntityInfo[ID].H;
			CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityRes::Com_Texture, Xt, Yt, W, H, MaxFrames);
		}
		else
		{ // start of non-common switch
			switch (Table_ID)
			{
				case SET_DEBUG:
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
			// CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(Unq_Texture, CEntityInfo::EntityInfoList[ID].Xo,
			// 	CEntityInfo::EntityInfoList[ID].Yo, CEntityInfo::EntityInfoList[ID].W, CEntityInfo::EntityInfoList[ID].H, MaxFrames);
			int Xt = CEntityInfo::Unq_EntityInfo[ID].Xo;
			int Yt = CEntityInfo::Unq_EntityInfo[ID].Yo;
			int W = CEntityInfo::Unq_EntityInfo[ID].W;
			int H = CEntityInfo::Unq_EntityInfo[ID].H;
			CEntity::EntityList[CEntity::EntityList.size() - 1]->OnLoad(CEntityRes::Unq_Texture, Xt, Yt, W, H, MaxFrames);
		}
		// place the entity at the assigned position
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
