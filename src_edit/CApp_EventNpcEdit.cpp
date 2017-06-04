#include "CApp.h"

bool CApp::EventNPCedit(int mX, int mY)
{
	if (mX < WWIDTH && mY < WHEIGHT)
	{
		// If we're allowing NPC additions, this function does that
		if (Active_Mod == MODIFY_NPC)
		{
			if (!AddEntity(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY()))
				OnExit();
		}
		// Attempt to remove an entity
		if (Active_Mod == REMOVE_NPC)
		{
			// returns true if an entity was removed successfully
			SubEntity(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
	}

	// Changing Entity (or Type)
	if (mX >= TABL_NAME_X - ARROW_SIZE - SYM_SPACING && mX <= TABL_NAME_X + tabl_name_W + ARROW_SIZE + SYM_SPACING)
	{
		if (mY >= TABL_NAME_Y && mY <= ENT_NAME_Y + CHAR_HEIGHT)
		{
			ModEntity(mX, mY);
		}
	}

	// Click is on "NPC Tables" button. This displays a prompt to change entity tables,
	// and the function within the loop performs a change if requested.
	if (mX >= TBL_CHG_BUTTON_X && mX <= TBL_CHG_BUTTON_X + SWITCH_SIZE)
	{
		if (mY >= TBL_CHG_BUTTON_Y && mY <= TBL_CHG_BUTTON_Y + SWITCH_SIZE)
		{
			int New_Table = CUI::UIControl.OnEntity(Map_Renderer, Map_Interface);
			if (New_Table >= 0)
			{
				CEntityEdit::NPCControl.LoadTable(New_Table, Entity_Path);
				return true;
			}
		}
	}
	return true;
}

void CApp::ModEntity(int mX, int mY)
{
	// This region is over the leftward arrow next to "COMMON" or "UNIQUE"
	// This changes the NPC_ID, which changes the active entity being placed.
	if (mX >= TABL_NAME_X - ARROW_SIZE - SYM_SPACING && mX <= TABL_NAME_X - SYM_SPACING)
	{
		if (mY >= TABL_NAME_Y && mY <= TABL_NAME_Y + ARROW_SIZE)
		{
			if (CEntityEdit::NPCControl.NPC_ID != 0)
				--CEntityEdit::NPCControl.NPC_ID;
			return;
		}
	}
	// This region is between the arrows enclosing "COMMON" or "UNIQUE"
	if (mX >= TABL_NAME_X && mX <= TABL_NAME_X + tabl_name_W)
	{
		if (mY >= TABL_NAME_Y && mY <= TABL_NAME_Y + CHAR_HEIGHT)
		{
			if (CEntityEdit::NPCControl.UseCommon) CEntityEdit::NPCControl.UseCommon = false;
			else CEntityEdit::NPCControl.UseCommon = true;
			CEntityEdit::NPCControl.NPC_ID = 0;
			return;
		}
	}
	// This region is over the rightward arrow next to "COMMON" or "UNIQUE"
	if (mX >= TABL_NAME_X + tabl_name_W + SYM_SPACING && mX <= TABL_NAME_X + tabl_name_W + SYM_SPACING + ARROW_SIZE)
	{
		if (mY >= TABL_NAME_Y && mY <= TABL_NAME_Y + CHAR_HEIGHT)
		{
			if (CEntityEdit::NPCControl.UseCommon)
			{
				if (CEntityEdit::NPCControl.NPC_ID != CEntityInfo::Com_EntityInfo.size() - 1)
					++CEntityEdit::NPCControl.NPC_ID;
			}
			else
			{
				if (CEntityEdit::NPCControl.NPC_ID != CEntityInfo::Unq_EntityInfo.size() - 1)
					++CEntityEdit::NPCControl.NPC_ID;
			}
			return;
		}
	}
}

// Info: We take Xo and Yo as coords (Q2) to plot our current NPC.
// Our current NPC has assigned to it a texture position (X and Y),
// which can be used to reveal what entity we are using.
// However, for NPC image sets with variable NPC size and frame number,
// the determination of X and Y for each NPC is not formulaic. It is best to
// instead store in memory an appropriate ID (perhaps as an enumerated value)
// that represents the NPC we are working with in the NPC image set. That ID
// can be used to look-up the appropriate X, Y, W, and H associated with the NPC.
// That info along with the mX and mY are necessary info to report to an external
// file for gameplay (i.e., the NPC and where it is). We need, however, the
// Xo, Yo, X, Y, and the dimensions of the NPC placeholding image (W and H).
// After all these are gathered, we feed them to an entity-like object that
// contains all these integral values. That object is then pushed back into
// a vector that contains all active entities in the workspace, which is used
// to render all NPCs to the window.
bool CApp::AddEntity(int Xo, int Yo)
{
	CEntityEdit::NPCControl.EntityList.resize(CEntityEdit::NPCControl.EntityList.size() + 1);
	CEntityEdit::NPCControl.ID_List.resize(CEntityEdit::NPCControl.ID_List.size() + 1);
	CEntityEdit::NPCControl.CommonList.resize(CEntityEdit::NPCControl.CommonList.size() + 1);

	// this will also fill the temp. entity's width and height values
	int ID, Xt, Yt, W, H;
	ID = CEntityEdit::NPCControl.NPC_ID;
	if (CEntityEdit::NPCControl.UseCommon)
	{
		Xt = CEntityInfo::Com_EntityInfo[ID].Xo;
		Yt = CEntityInfo::Com_EntityInfo[ID].Yo;
		W = CEntityInfo::Com_EntityInfo[ID].W;
		H = CEntityInfo::Com_EntityInfo[ID].H;
	}
	else
	{
		Xt = CEntityInfo::Unq_EntityInfo[ID].Xo;
		Yt = CEntityInfo::Unq_EntityInfo[ID].Yo;
		W = CEntityInfo::Unq_EntityInfo[ID].W;
		H = CEntityInfo::Unq_EntityInfo[ID].H;
	}

	if (CEntityEdit::NPCControl.EntityList[CEntityEdit::NPCControl.EntityList.size() - 1].OnLoad(
		CEntityEdit::NPCControl.ForwardSet(), Xt,	Yt,	W, H, CEntityEdit::NPCControl.NPC_ID) == false)
		return false;

	CEntityEdit::NPCControl.EntityList[CEntityEdit::NPCControl.EntityList.size() - 1].X = Xo;
	CEntityEdit::NPCControl.EntityList[CEntityEdit::NPCControl.EntityList.size() - 1].Y = Yo;

	CEntityEdit::NPCControl.ID_List[CEntityEdit::NPCControl.EntityList.size() - 1] = CEntityEdit::NPCControl.NPC_ID;
	CEntityEdit::NPCControl.CommonList[CEntityEdit::NPCControl.EntityList.size() - 1] = CEntityEdit::NPCControl.UseCommon;

	return true;
}

bool CApp::SubEntity(int Xo, int Yo)
{
	// When the active mod is set to remove entities, we have to check if a click is over an entity.
	// If there are multiple entities stacked in one spot, the first entity to be checked in the
	// loop will be erased. Others in the stack will remain unless clicked again. The entity list
	// is searched from the last (most recently created) index to the first (oldest), which allows
	// the entity "on top" of a stack to be deleted.
	for (int i = CEntityEdit::NPCControl.EntityList.size() - 1; i >= 0; i--)
	{
		if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
		int Xi = CEntityEdit::NPCControl.EntityList[i].X;
		int Yi = CEntityEdit::NPCControl.EntityList[i].Y;
		int Xf = CEntityEdit::NPCControl.EntityList[i].X + CEntityEdit::NPCControl.EntityList[i].Width - 1;
		int Yf = CEntityEdit::NPCControl.EntityList[i].Y + CEntityEdit::NPCControl.EntityList[i].Height - 1;
		if (Xo >= Xi && Xo <= Xf)
		{
			if (Yo >= Yi && Yo <= Yf)
			{
				CEntityEdit::NPCControl.EntityList.erase(CEntityEdit::NPCControl.EntityList.begin() + i);
				CEntityEdit::NPCControl.CommonList.erase(CEntityEdit::NPCControl.CommonList.begin() + i);
				CEntityEdit::NPCControl.ID_List.erase(CEntityEdit::NPCControl.ID_List.begin() + i);
				return true;
			}
		}
	}
	return false;
}
