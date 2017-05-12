#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

// Handle key-press events
void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
		switch (sym)
		{
		case SDLK_d:
			CArea::AreaControl.OnExpandRight(); break;
		case SDLK_a:
			CArea::AreaControl.OnExpandLeft();
			CCamera::CameraControl.OnMove(MAP_WIDTH*TILE_SIZE, 0);  // Keeps the area from jerking around
			for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
			{
				if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
				CEntityEdit::NPCControl.EntityList[i].X += MAP_WIDTH*TILE_SIZE;
			}	// This loop updates the position of our entities
			// to prevent unwanted repositioning over the changed area
			break;
		case SDLK_s:
			CArea::AreaControl.OnExpandDown(); break;
		case SDLK_w:
			CArea::AreaControl.OnExpandUp();
			CCamera::CameraControl.OnMove(0, MAP_HEIGHT*TILE_SIZE);
			for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
			{
				if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
				CEntityEdit::NPCControl.EntityList[i].Y += MAP_HEIGHT*TILE_SIZE;
			}
			break;

		case SDLK_l:
			CArea::AreaControl.OnReduceRight(); break;
		case SDLK_j:
			if (CArea::AreaControl.OnReduceLeft())
			{
				CCamera::CameraControl.OnMove(-MAP_WIDTH*TILE_SIZE, 0);
				for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
				{
					if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
					CEntityEdit::NPCControl.EntityList[i].X -= MAP_WIDTH*TILE_SIZE;
				}
			}
			break;
		case SDLK_k:
			CArea::AreaControl.OnReduceDown(); break;
		case SDLK_i:
			if (CArea::AreaControl.OnReduceUp())
			{
				CCamera::CameraControl.OnMove(0, -MAP_HEIGHT*TILE_SIZE);
				for (int i = 0; i < CEntityEdit::NPCControl.EntityList.size(); i++)
				{
					if (&CEntityEdit::NPCControl.EntityList[i] == NULL) continue;
					CEntityEdit::NPCControl.EntityList[i].Y -= MAP_WIDTH*TILE_SIZE;
				}
			}
			break;

		case SDLK_ESCAPE:
			OnExit(); break;
		default:
			break;
		}
}

// Handle left-click events
void CApp::OnLButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT)
		return;

	if (Active_Mod == MODIFY_NPC || Active_Mod == REMOVE_NPC)
	{
		// returns false if error...
		EventNPCedit(mX, mY);
	}
	else if (Active_Mod == MODIFY_SCENE || Active_Mod == REMOVE_SCENE)
	{
		// returns false if error...
		EventSCNedit(mX, mY);
	}
	else
	{
		// returns false if error...
		EventMAPedit(mX, mY);
	}

	// Clicks on a modify option button. Changes the MODIFY "flag" accordingly.
	if (mX >= WWIDTH - 100 - 32 && mX < WWIDTH - 32)
	{
		if (mY >= WHEIGHT && mY < WHEIGHT + 33)
		{
			Active_Mod = MODIFY_MAP;
			return;
		}
		if (mY >= WHEIGHT + 33 && mY < WHEIGHT + 66)
		{
			// Clicking "NPC" twice allows NPCs to be deleted.
			if (Active_Mod == MODIFY_NPC) Active_Mod = REMOVE_NPC;
			else Active_Mod = MODIFY_NPC;
			return;
		}
		if (mY >= WHEIGHT + 66 && mY < EHEIGHT)
		{
			if (Active_Mod == MODIFY_SCENE) Active_Mod = REMOVE_SCENE;
			else Active_Mod = MODIFY_SCENE;
			return;
		}
	}

	// View Area Call (click on "MODEL")
	if (mX >= 608 && mX <= 639)
	{
		if (mY >= WHEIGHT)
		{
			CArea::AreaControl.ViewArea(Map_Renderer, Map_Interface);
			SDL_RenderPresent(Map_Renderer);
			SDL_Event Event;
			SDL_WaitEvent(&Event);
			SDL_WaitEvent(&Event);
			return;
		}
	}

	// Save and load functions
	if (mX > WWIDTH)
	{
		// Save maps and entities
		if (mY >= WHEIGHT && mY < WHEIGHT + 50)
		{
			char* Filename = CIO::IOControl.OnSave(Map_Renderer, Map_Interface);
			CArea::AreaControl.SaveArea(Filename, Tileset_Path);
			CEntityEdit::NPCControl.SaveList(Filename);
			CSceneryEdit::ScnControl.SaveScenery(Filename);
			return;
		}

		// Load maps and entities; update the current tileset if area is loaded successfully.
		// Note that the functions to load entities is contained within the IOC.OnLoad function below.
		if (mY >= WHEIGHT + 50)
		{
			if (CIO::IOControl.OnLoad(Map_Renderer, Map_Interface, Tileset_Path))
			{
				Main_Tileset = CSurface::OnLoad(Tileset_Path, Map_Renderer);
				Current_Tile = Current_Type = 0;

				QueryTileset();
				return;
			}
		}
	}
}

void CApp::OnRButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX > EWIDTH || mY > EHEIGHT)
		return;

	// If we're trying to do stuff with NPCs ... This places the NPC at the X, Y
	// coordinates of the map tile clicked upon (good for doors, save points, etc.)
	if (Active_Mod == MODIFY_NPC && mX < WWIDTH && mY < WHEIGHT)
	{
		int Xo = mX + CCamera::CameraControl.GetX();
		int Yo = mY + CCamera::CameraControl.GetY();

		if (!AddEntity(Xo - (Xo % TILE_SIZE), Yo - (Yo % TILE_SIZE)))
			OnExit();
	}
}

bool CApp::EventMAPedit(int mX, int mY)
{
	/*
	Interactive buttons to add/update:
	1. Change Tileset button
	2. Change Tile(s) button
	3a. Separate background and foreground tiles for precision/simplicity
	3b. Render combined tile result for clarity
	3c. Scroll-through (left/right) Tile buttons
	4. Enable/disable 2x2 Tile "block" placer
	5. Change Tile "block" button(s)
	*/

	// Click on "Change Tileset" button. This displays a prompt to change tilesets,
	// and the function within the loop performs a change if requested.
	if (mX >= TS_CHG_BUT_X && mX < TS_CHG_BUT_X + TS_CHG_BUT_W)
	{
		if (mY >= TS_CHG_BUT_Y && mY < TS_CHG_BUT_Y + TS_CHG_BUT_H)
		{
			if ((Main_Tileset = CUI::UIControl.OnChange(Map_Renderer, Map_Interface, Tileset_Path)) != NULL)
			{
				CArea::AreaControl.ChangeSet(Main_Tileset);
				Current_Tile = 0;
				QueryTileset();
				return true;
			}
		}
	}

	// Click on "Change Tile" button. A display of all tiles is rendered,
	// and clicking a tile will update the active tile to use the clicked tile.
	if (mX >= TILE_CHG_BUT_X && mX < TILE_CHG_BUT_X + TILE_CHG_BUT_W)
	{
		if (mY >= TILE_CHG_BUT_Y && mY < TILE_CHG_BUT_Y + TILE_CHG_BUT_H)
		{
			Current_Tile = CChangeTile::UIControl.OnExecute(Map_Renderer, Main_Tileset);
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active background tile.
	// Changes the active tile to previous or next index.
	if (mY >= DISP_BTILE_Y && mY < DISP_BTILE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_BTILE_X - TILE_SIZE && mX < DISP_BTILE_X)
		{
				if (Current_Tile != 0) Current_Tile -= 1;
				else Current_Tile = (TilesetWidth * TilesetHeight) - 1;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_BTILE_X + TILE_SIZE && mX < DISP_BTILE_X + (TILE_SIZE * 2))
		{
				if (Current_Tile != (TilesetWidth * TilesetHeight) - 1) Current_Tile += 1;
				else Current_Tile = 0;
				return true;
		}
	}

	// Click on foreground activity switch.
	// Turn the foreground tile on/off.
	if (mY >= FORE_SWIT_Y && mY < FORE_SWIT_Y + SWITCH_SIZE)
	{
		if (mX >= FORE_SWIT_X && mX < FORE_SWIT_X + SWITCH_SIZE)
		{
			if (!Use_Fore) Use_Fore = true;
			else Use_Fore = false;
			return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active foreground tile.
	// Changes the active tile to previous or next index.
	if (mY >= DISP_FTILE_Y && mY < DISP_FTILE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_FTILE_X - TILE_SIZE && mX < DISP_FTILE_X)
		{
				if (Current_Fore != 0) Current_Fore -= 1;
				else Current_Fore = (TilesetWidth * TilesetHeight) - 1;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_FTILE_X + TILE_SIZE && mX < DISP_FTILE_X + (TILE_SIZE * 2))
		{
				if (Current_Fore != (TilesetWidth * TilesetHeight) - 1) Current_Fore += 1;
				else Current_Fore = 0;
				return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active tile type.
	// Changes the active tile type to previous or next type index.
	if (mY >= DISP_TYPE_Y && mY < DISP_TYPE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_TYPE_X - TILE_SIZE && mX < DISP_TYPE_X)
		{
				if (Current_Type != 0) Current_Type -= 1;
				else Current_Type = TILE_TYPE_FIRE;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_TYPE_X + TILE_SIZE && mX < DISP_TYPE_X + (TILE_SIZE * 2))
		{
				if (Current_Type != TILE_TYPE_FIRE) Current_Type += 1;
				else Current_Type = 0;
				return true;
		}
	}

	// Click on arrow LEFT or RIGHT of active tile slope.
	// Changes the active tile slope to previous or next slope index.
	if (mY >= DISP_SLOPE_Y && mY < DISP_SLOPE_Y + TILE_SIZE)
	{
		// Left Arrow
		if (mX >= DISP_SLOPE_X - TILE_SIZE && mX < DISP_SLOPE_X)
		{
				if (Current_Slope != 0) Current_Slope -= 1;
				else Current_Slope = STEEP_DSCE;
				return true;
		}
		// Right Arrow
		if (mX >= DISP_SLOPE_X + TILE_SIZE && mX < DISP_SLOPE_X + (TILE_SIZE * 2))
		{
				if (Current_Slope != STEEP_DSCE) Current_Slope += 1;
				else Current_Slope = 0;
				return true;
		}
	}
	return true;
}

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

bool CApp::EventSCNedit(int mX, int mY)
{
	if (mX < WWIDTH && mY < WHEIGHT)
	{
		// add or subtract scenery objects...
		if (Active_Mod == MODIFY_SCENE)
		{
			// add object
			CSceneryEdit::ScnControl.AddObject(Map_Renderer, mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
		else
		{
			// remove object
			CSceneryEdit::ScnControl.SubObject(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
	}
	else
	{
		if (mY >= SCN_NAME_Y && mY < SCN_NAME_Y + CHAR_HEIGHT)
		{
			// The Y-range overlaps the scenery name display.
			// A click may have been over the arrow keys to change scenery.
			if (CheckSCNchange(mX)) return true;
		}
		if (mY >= DEPTH_COMBO_Y - (ARROW_SIZE + SYM_SPACING) && mY < DEPTH_COMBO_Y - SYM_SPACING)
		{
			// The Y-range satisfied overlaps the up-arrow buttons.
			// We check to see if any of those buttons were pressed.
			if (CheckZup(mX)) return true;
		}
		if (mY >= DEPTH_COMBO_Y + CHAR_HEIGHT + SYM_SPACING && mY < DEPTH_COMBO_Y + CHAR_HEIGHT + SYM_SPACING + ARROW_SIZE)
		{
			// The Y-range satisfied overlaps the down-arrow buttons.
			// We check to see if any of those buttons were pressed.
			if (CheckZdown(mX)) return true;
		}
		if (mX >= SWITCHLIST_X && mX < SWITCHLIST_X + SWITCH_SIZE)
		{
			// The X-range satisfied overlaps the scenery switches.
			// We check to see if any switches were flipped.
			if (CheckSCNswitch(mY)) return true;
		}
	}
	return true;
}

bool CApp::CheckZup(const int& mX)
{
	if (mX >= DEPTH_COMBO_X && mX < DEPTH_COMBO_X + (Z_PRECISION * CHAR_WIDTH))
	{
		// ... middle up arrows pressed
		float Z_inc = GetZincrement(mX, DEPTH_COMBO_X);
		CSceneryEdit::ScnControl.Z += Z_inc;
		return true;
	}
	if (Active_Mod == REMOVE_SCENE)
	{
		if (mX >= DEPTH_LOWER_X && mX < DEPTH_LOWER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... left up arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_LOWER_X);
			if (CSceneryEdit::ScnControl.Zl + Z_inc < CSceneryEdit::ScnControl.Zu)
				CSceneryEdit::ScnControl.Zl += Z_inc;
			return true;
		}
		if (mX >= DEPTH_UPPER_X && mX < DEPTH_UPPER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... right up arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_UPPER_X);
			CSceneryEdit::ScnControl.Zu += Z_inc;
			return true;
		}
	}
	return false;
}

bool CApp::CheckZdown(const int& mX)
{
	if (mX >= DEPTH_COMBO_X && mX < DEPTH_COMBO_X + (Z_PRECISION * CHAR_WIDTH))
	{
		// ... middle dw arrows pressed
		float Z_inc = GetZincrement(mX, DEPTH_COMBO_X);
		if (CSceneryEdit::ScnControl.Z > Z_inc) CSceneryEdit::ScnControl.Z -= Z_inc;
		return true;
	}
	if (Active_Mod == REMOVE_SCENE)
	{
		if (mX >= DEPTH_LOWER_X && mX < DEPTH_LOWER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... left dw arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_LOWER_X);
			if (CSceneryEdit::ScnControl.Zl > Z_inc) CSceneryEdit::ScnControl.Zl -= Z_inc;
			return true;
		}
		if (mX >= DEPTH_UPPER_X && mX < DEPTH_UPPER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... right dw arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_UPPER_X);
			if (CSceneryEdit::ScnControl.Zu - Z_inc > CSceneryEdit::ScnControl.Zl)
				CSceneryEdit::ScnControl.Zu -= Z_inc;
			return true;
		}
	}
	return false;
}

float CApp::GetZincrement(const int& mX, const int& Xo)
{
	float val = 1.0f;
	int ArrowID = (mX - Xo) / CHAR_WIDTH;
	for (int i = 0; i < ArrowID; i++)
	{
		val /= 10.0;
	}
	return val;
}

bool CApp::CheckSCNswitch(const int& mY)
{
	int Yi = SWITCHLIST_Y;
	int Yf = SWITCHLIST_Y + SWITCH_SIZE;
	if (mY >= Yi && mY < Yf)
	{
		if (!CSceneryEdit::ScnControl.hori_repeat) CSceneryEdit::ScnControl.hori_repeat = true;
		else CSceneryEdit::ScnControl.hori_repeat = false;
		return true;
	}
	Yi += SWITCH_SIZE + SYM_SPACING;
	Yf += SWITCH_SIZE + SYM_SPACING;
	if (mY >= Yi && mY < Yf)
	{
		if (!CSceneryEdit::ScnControl.vert_repeat) CSceneryEdit::ScnControl.vert_repeat = true;
		else CSceneryEdit::ScnControl.vert_repeat = false;
		return true;
	}
	Yi += SWITCH_SIZE + SYM_SPACING;
	Yf += SWITCH_SIZE + SYM_SPACING;
	if (mY >= Yi && mY < Yf)
	{
		if (!CSceneryEdit::ScnControl.permanent) CSceneryEdit::ScnControl.permanent = true;
		else CSceneryEdit::ScnControl.permanent = false;
		return true;
	}
	return false;
}

bool CApp::CheckSCNchange(const int& mX)
{
	if (mX >= SCN_NAME_X - ARROW_SIZE - SYM_SPACING && mX < SCN_NAME_X - SYM_SPACING)
	{
		// left arrow clicked...
		CSceneryEdit::ScnControl.SwitchObj(CSceneryEdit::ScnControl.scn_ID - 1);
		return true;
	}
	if (mX >= SCN_NAME_X + SCN_NAME_W + SYM_SPACING && mX < SCN_NAME_X + SCN_NAME_W + SYM_SPACING + ARROW_SIZE)
	{
		// right arrow clicked...
		CSceneryEdit::ScnControl.SwitchObj(CSceneryEdit::ScnControl.scn_ID + 1);
		return true;
	}
	return false;
}

void CApp::QueryTileset()
{
	int PixWidth, PixHeight;
	SDL_QueryTexture(Main_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	TilesetWidth = PixWidth / TILE_SIZE;
	TilesetHeight = PixHeight / TILE_SIZE;
}
