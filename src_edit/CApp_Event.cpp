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
	if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT) return;

	// Event is passed to interrupting prompts, if there are any
	if (Interrupt & ~INTRPT_NONE)
	{
		if (Interrupt & INTRPT_CH_BTILE)
		{
			if (PickTile.OnLClick(mX, mY, Current_Tile)) Interrupt = INTRPT_NONE;
		}
		if (Interrupt & INTRPT_CH_FTILE)
		{
			if (PickTile.OnLClick(mX, mY, Current_Fore)) Interrupt = INTRPT_NONE;
		}
		return;
	}

	// Clicks on permanently-placed options buttons (independent of Active_Mod)
	if (mX >= PERM_OPTS_X && mX < PERM_OPTS_X + PERM_OPTS_W)
	{
		if (mY >= PERM_OPTS_Y && mY < PERM_OPTS_Y + PERM_OPTS_H)
		{
			EventOPTS(mX, mY);
			return;
		}
	}

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
}

void CApp::OnRButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX > EWIDTH || mY > EHEIGHT) return;

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

bool CApp::EventOPTS(int mX, int mY)
{
	// Clicks on a modify option button. Changes the MODIFY "flag" accordingly.
	if (mX >= EDIT_BUT_X && mX < EDIT_BUT_X + EDIT_BUT_W)
	{
		if (mY >= MAP_BUT_Y && mY < MAP_BUT_Y + EDIT_BUT_H)
		{
			Active_Mod = MODIFY_MAP;
			return true;
		}
		if (mY >= NPC_BUT_Y && mY < NPC_BUT_Y + EDIT_BUT_H)
		{
			// Clicking "NPC" twice allows NPCs to be deleted.
			if (Active_Mod == MODIFY_NPC) Active_Mod = REMOVE_NPC;
			else Active_Mod = MODIFY_NPC;
			return true;
		}
		if (mY >= SCN_BUT_Y && mY < SCN_BUT_Y + EDIT_BUT_H)
		{
			if (Active_Mod == MODIFY_SCENE) Active_Mod = REMOVE_SCENE;
			else Active_Mod = MODIFY_SCENE;
			return true;
		}
	}

	// View Area Call (click on "MODEL")
	if (mX >= MODEL_BUT_X && mX < MODEL_BUT_X + MODEL_BUT_W)
	{
		if (mY >= MODEL_BUT_Y && mY < MODEL_BUT_Y + MODEL_BUT_H)
		{
			CArea::AreaControl.ViewArea(Map_Renderer, Map_Interface);
			SDL_RenderPresent(Map_Renderer);
			SDL_Event Event;
			SDL_WaitEvent(&Event);
			SDL_WaitEvent(&Event);
			return true;
		}
	}

	// Save and load functions
	if (mX >= IO_BUT_X && mX < IO_BUT_X + IO_BUT_W)
	{
		// Save maps and entities
		if (mY >= SAVE_BUT_Y && mY < SAVE_BUT_Y + IO_BUT_H)
		{
			char* Filename = CIO::IOControl.OnSave(Map_Renderer, Map_Interface);
			CArea::AreaControl.SaveArea(Filename, Tileset_Path);
			CEntityEdit::NPCControl.SaveList(Filename);
			CSceneryEdit::ScnControl.SaveScenery(Filename);
			return true;
		}

		// Load maps and entities; update the current tileset if area is loaded successfully.
		// Note that the functions to load entities is contained within the IOC.OnLoad function below.
		if (mY >= LOAD_BUT_Y && mY < LOAD_BUT_Y + IO_BUT_H)
		{
			if (CIO::IOControl.OnLoad(Map_Renderer, Map_Interface, Tileset_Path))
			{
				Main_Tileset = CSurface::OnLoad(Tileset_Path, Map_Renderer);
				Current_Tile = Current_Type = 0;

				QueryTileset();
				return true;
			}
		}
	}
	return true;
}
