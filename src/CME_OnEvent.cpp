#include "CMapEdit.h"

void CMapEdit::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CMapEdit::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
		switch (sym)
		{
		case SDLK_d:
			CArea::AreaControl.OnExpandRight(); break;
		case SDLK_a:
			CArea::AreaControl.OnExpandLeft();
			CCamera::CameraControl.OnMove(MAP_WIDTH*TILE_SIZE, 0);  // Keeps the area from jerking around
			for (int i = 0; i < CME_NPC::NPCControl.EntityList.size(); i++)
			{
				if (&CME_NPC::NPCControl.EntityList[i] == NULL) continue;
				CME_NPC::NPCControl.EntityList[i].X += MAP_WIDTH*TILE_SIZE;
			}	// This loop updates the position of our entities
			// to prevent unwanted repositioning over the changed area
			break;
		case SDLK_s:
			CArea::AreaControl.OnExpandDown(); break;
		case SDLK_w:
			CArea::AreaControl.OnExpandUp();
			CCamera::CameraControl.OnMove(0, MAP_HEIGHT*TILE_SIZE);
			for (int i = 0; i < CME_NPC::NPCControl.EntityList.size(); i++)
			{
				if (&CME_NPC::NPCControl.EntityList[i] == NULL) continue;
				CME_NPC::NPCControl.EntityList[i].Y += MAP_HEIGHT*TILE_SIZE;
			}
			break;

		case SDLK_l:
			CArea::AreaControl.OnReduceRight(); break;
		case SDLK_j:
			if (CArea::AreaControl.OnReduceLeft())
			{
				CCamera::CameraControl.OnMove(-MAP_WIDTH*TILE_SIZE, 0);
				for (int i = 0; i < CME_NPC::NPCControl.EntityList.size(); i++)
				{
					if (&CME_NPC::NPCControl.EntityList[i] == NULL) continue;
					CME_NPC::NPCControl.EntityList[i].X -= MAP_WIDTH*TILE_SIZE;
				}
			}
			break;
		case SDLK_k:
			CArea::AreaControl.OnReduceDown(); break;
		case SDLK_i:
			if (CArea::AreaControl.OnReduceUp())
			{
				CCamera::CameraControl.OnMove(0, -MAP_HEIGHT*TILE_SIZE);
				for (int i = 0; i < CME_NPC::NPCControl.EntityList.size(); i++)
				{
					if (&CME_NPC::NPCControl.EntityList[i] == NULL) continue;
					CME_NPC::NPCControl.EntityList[i].Y -= MAP_WIDTH*TILE_SIZE;
				}
			}
			break;

		case SDLK_ESCAPE:
			OnExit(); break;
		default:
			break;
		}
}

void CMapEdit::OnLButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT)
		return;

	// If we're allowing NPC additions, this function does that
	if (Active_Mod == MODIFY_NPC && mX < WWIDTH && mY < WHEIGHT)
	{
		if (!AddEntity(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY()))
			OnExit();
	}

	// When the active mod is set to remove entities, we have to check if a click is over an entity.
	// If there are multiple entities stacked in one spot, the first entity to be checked in the
	// loop will be erased. Others in the stack will remain unless clicked again. The entity list
	// is searched from the last (most recently created) index to the first (oldest), which allows
	// the entity "on top" of a stack to be deleted.
	if (Active_Mod == REMOVE_NPC && mX < WWIDTH && mY < WHEIGHT)
	{
		for (int i = CME_NPC::NPCControl.EntityList.size() - 1; i >= 0; i--)
		{
			if (&CME_NPC::NPCControl.EntityList[i] == NULL) continue;
			int Xf = CME_NPC::NPCControl.EntityList[i].X + CME_NPC::NPCControl.EntityList[i].Width - 1;
			int Yf = CME_NPC::NPCControl.EntityList[i].Y + CME_NPC::NPCControl.EntityList[i].Height - 1;
			if (mX + CCamera::CameraControl.GetX() >= CME_NPC::NPCControl.EntityList[i].X
				&& mX + CCamera::CameraControl.GetX() <= Xf)
			{
				if (mY + CCamera::CameraControl.GetY() >= CME_NPC::NPCControl.EntityList[i].Y
					&& mY + CCamera::CameraControl.GetY() <= Yf)
				{
					CME_NPC::NPCControl.EntityList.erase(CME_NPC::NPCControl.EntityList.begin() + i);
					CME_NPC::NPCControl.ID_List.erase(CME_NPC::NPCControl.ID_List.begin() + i);

					return;
				}
			}
		}
	}

	// This region is over the leftward arrow next to "ENTITY."
	// This changes the NPC_ID, which changes the active entity being placed.
	if (mX >= 259 && mX <= 273)
	{
		if (mY >= 487 && mY <= 504)
		{
			if (CME_NPC::NPCControl.NPC_ID != 0)
				--CME_NPC::NPCControl.NPC_ID;
			return;
		}
	}

	// This region is over the rightward arrow next to "ENTITY."
	if (mX >= 366 && mX <= 380)
	{
		if (mY >= 487 && mY <= 504)
		{
			if (CME_NPC::NPCControl.NPC_ID != CEntityInfo::EntityInfoList.size() - 1)
				++CME_NPC::NPCControl.NPC_ID;
			return;
		}
	}

	// Click is on "NPC Tables". This displays a prompt to change entity tables,
	// and the function within the loop performs a change if requested.
	if (mX >= 5 && mX <= 165)
	{
		if (mY >= EHEIGHT - 40 && mY <= EHEIGHT - 26)
		{
			int New_Table = CMEUI::UIControl.OnEntity(Map_Renderer, Map_Interface, Font);
			if (New_Table >= 0)
			{
				CME_NPC::NPCControl.LoadTable(New_Table, Entity_Path);
				return;
			}
		}
	}

	// Click is on "Set". This displays a prompt to change tilesets,
	// and the function within the loop performs a change if requested.
	if (mX >= EWIDTH - 75 && mX <= EWIDTH - 25)
	{
		if (mY >= 10 && mY <= 40)
		{
			if ((Main_Tileset = CMEUI::UIControl.OnChange(Map_Renderer, Map_Interface, Font, Tileset_Path)) != NULL)
			{
				CArea::AreaControl.ChangeSet(Main_Tileset);
				Current_Tile = 0;
				QueryTileset();
				return;
			}
		}
	}

	// Click over "CHANGE TILE". A display of all tiles is rendered,
	// and clicking a tile will update the active tile to use the clicked tile.
	if (mX >= EWIDTH - 100 && mX < EWIDTH)
	{
		if (mY >= 42 && mY <= 74)
		{
			Current_Tile = CME_ChTile::UIControl.OnExecute(Map_Renderer, Main_Tileset);
			return;
		}
	}

	// Click is on left side of active tile type. Changes the tile type to that left type.
	if (Current_Type != 0)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2))
		{
			if (mY >= 405 && mY < 405 + TILE_SIZE)
			{
				Current_Type -= 1;
				return;
			}
		}
	}
	// Click is on right side of active tile type. Changes the tile type to that right type.
	if (Current_Type != TILE_TYPE_FIRE)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE * 2)
		{
			if (mY >= 405 && mY < 405 + TILE_SIZE)
			{
				Current_Type += 1;
				return;
			}
		}
	}
	// Click is on left side of active tile slope. Changes the tile slope to that left slope.
	if (Current_Slope != 0)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2))
		{
			if (mY >= 320 && mY < 320 + TILE_SIZE)
			{
				Current_Slope -= 1;
				return;
			}
		}
	}
	// Click is on right side of active tile slope. Changes the tile slope to that right slope.
	if (Current_Slope != STEEP_DSCE)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE * 2)
		{
			if (mY >= 320 && mY < 320 + TILE_SIZE)
			{
				Current_Slope += 1;
				return;
			}
		}
	}
	// Click is on left side of active tile. Changes the active tile to that left tile.
	if (Current_Tile != 0)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2))
		{
			if (mY >= 275 && mY < 275 + TILE_SIZE)
			{
				Current_Tile -= 1;
				return;
			}
		}
	}
	// Click is on right side of active tile. Changes the active tile to that right tile.
	if (Current_Tile != TilesetWidth * TilesetHeight - 1)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE * 2)
		{
			if (mY >= 275 && mY < 275 + TILE_SIZE)
			{
				Current_Tile += 1;
				return;
			}
		}
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
			Active_Mod = MODIFY_BG;
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
			char* Filename = CME_IO::IOControl.OnSave(Map_Renderer, Map_Interface, Font);
			CArea::AreaControl.SaveArea(Filename, Tileset_Path);
			CME_NPC::NPCControl.SaveList(Filename);
			return;
		}

		// Load maps and entities; update the current tileset if area is loaded successfully.
		// Note that the functions to load entities is contained within the IOC.OnLoad function below.
		if (mY >= WHEIGHT + 50)
		{
			if (CME_IO::IOControl.OnLoad(Map_Renderer, Map_Interface, Font, Tileset_Path))
			{
				Main_Tileset = CSurface::OnLoad(Tileset_Path, Map_Renderer);
				Current_Tile = Current_Type = 0;

				QueryTileset();
				return;
			}
		}
	}
}

void CMapEdit::OnRButtonDown(int mX, int mY)
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

	if (Current_Fore != 0)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2))
		{
			if (mY >= 275 && mY < 275 + TILE_SIZE)
			{
				Current_Fore -= 1;
			}
		}
	}

	if (Current_Fore != TilesetWidth * TilesetHeight - 1)
	{
		if (mX >= EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE && mX < EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE * 2)
		{
			if (mY >= 275 && mY < 275 + TILE_SIZE)
			{
				Current_Fore += 1;
			}
		}
	}
}

void CMapEdit::OnExit()
{
	Running = false;
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
// Xo, Xo, X, Y, and the dimensions of the NPC placeholding image (W and H).
// After all these are gathered, we feed them to an entity-like object that
// contains all these integer values. That object is then pushed back into
// a vector that contains all active entities in the workspace, which is used
// to render all NPCs to the window.
bool CMapEdit::AddEntity(int Xo, int Yo)
{
	CME_NPC::NPCControl.EntityList.resize(CME_NPC::NPCControl.EntityList.size() + 1);
	CME_NPC::NPCControl.ID_List.resize(CME_NPC::NPCControl.ID_List.size() + 1);

	// this will also fill the temp. entity's width and height values
	if (CME_NPC::NPCControl.EntityList[CME_NPC::NPCControl.EntityList.size() - 1].OnLoad(CME_NPC::NPCControl.ForwardSet(),
		CEntityInfo::EntityInfoList[CME_NPC::NPCControl.NPC_ID].Xo,
		CEntityInfo::EntityInfoList[CME_NPC::NPCControl.NPC_ID].Yo,
		CEntityInfo::EntityInfoList[CME_NPC::NPCControl.NPC_ID].W,
		CEntityInfo::EntityInfoList[CME_NPC::NPCControl.NPC_ID].H,
		CME_NPC::NPCControl.NPC_ID) == false)
		return false;

	CME_NPC::NPCControl.EntityList[CME_NPC::NPCControl.EntityList.size() - 1].X = Xo;
	CME_NPC::NPCControl.EntityList[CME_NPC::NPCControl.EntityList.size() - 1].Y = Yo;

	/*if (CEntityInfo::EntityInfoList[CME_NPC::NPCControl.NPC_ID].Speak)
	{
		EnterText = true;
	}*/

	CME_NPC::NPCControl.ID_List[CME_NPC::NPCControl.EntityList.size() - 1] = CME_NPC::NPCControl.NPC_ID;

	return true;
}

void CMapEdit::QueryTileset()
{
	int PixWidth, PixHeight;
	SDL_QueryTexture(Main_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	TilesetWidth = PixWidth / TILE_SIZE;
	TilesetHeight = PixHeight / TILE_SIZE;
}
