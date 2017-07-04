#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	if (handleInterr(Event)) return;

	CEvent::OnEvent(Event);

	if (active_mod == MODIFY_MAP) CEditMap::MapEditor.OnEvent(Event);
}

bool CApp::handleInterr(SDL_Event* Event)
{
	if (CInterrupt::isFlagOn(INTRPT_LOAD) || CInterrupt::isFlagOn(INTRPT_SAVE))
	{
		CFileIO::IOhandle.OnEvent(Event);
		return true;
	}

	return false;
}

// Handle key-press events
void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
	if (!CInterrupt::isNone()) return;

  switch (sym)
  {
    case SDLK_ESCAPE: OnExit(); break;
    default: break;
  }
}

// Handle left-click events
void CApp::OnLButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT) return;

	// Clicks on permanently-placed options buttons (independent of active_mod)
	if (mX >= PERM_OPTS_X && mX < PERM_OPTS_X + PERM_OPTS_W)
	{
		if (mY >= PERM_OPTS_Y && mY < PERM_OPTS_Y + PERM_OPTS_H)
		{
			EventOPTS(mX, mY);
			return;
		}
	}

	if (active_mod == MODIFY_NPC || active_mod == REMOVE_NPC)
	{
		// returns false if error...
		EventNPCedit(mX, mY);
	}
	else if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
	{
		// returns false if error...
		EventSCNedit(mX, mY);
	}
}

void CApp::OnRButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX > EWIDTH || mY > EHEIGHT) return;

	// If we're trying to do stuff with NPCs ... This places the NPC at the X, Y
	// coordinates of the map tile clicked upon (good for doors, save points, etc.)
	if (active_mod == MODIFY_NPC && mX < WWIDTH && mY < WHEIGHT)
	{
		int Xo = mX + CCamera::CameraControl.GetX();
		int Yo = mY + CCamera::CameraControl.GetY();

		if (!AddEntity(Xo - (Xo % TILE_SIZE), Yo - (Yo % TILE_SIZE)))
			OnExit();
	}
}

bool CApp::EventOPTS(int mX, int mY)
{
	using namespace io_ui;
	// const SDL_Point mouse = {mX, mY};
	// Clicks on a modify option button. Changes the MODIFY "flag" accordingly.
	for (int i = MODIFY_MAP; i <= REMOVE_SCENE; i++)
	{
		if (SDL_PointInRect(&mouse, &engineButton[i]))
		{
			active_mod = i;
			// break;
			return true;
		}
	}

	// View Area Call (click on "MODEL")
	if (mX >= MODEL_BUT_X && mX < MODEL_BUT_X + MODEL_BUT_W)
	{
		if (mY >= MODEL_BUT_Y && mY < MODEL_BUT_Y + MODEL_BUT_H)
		{
			// CArea::AreaControl.ViewArea(Map_Interface);
			// SDL_RenderPresent(Map_Renderer);
			// SDL_Event Event;
			// SDL_WaitEvent(&Event);
			// SDL_WaitEvent(&Event);
			return true;
		}
	}

	// Save and load functions
	if (mX >= IO_BUT_X && mX < IO_BUT_X + IO_BUT_W)
	{
		// Save maps and entities
		if (mY >= SAVE_BUT_Y && mY < SAVE_BUT_Y + IO_BUT_H)
		{
			CInterrupt::appendFlag(INTRPT_SAVE);
			// char* Filename = CIO::IOControl.OnSave(Map_Interface);
			// CArea::AreaControl.SaveArea(Filename, Tileset_Path);
			// CEntityEdit::NPCControl.SaveList(Filename);
			// CSceneryEdit::ScnControl.SaveScenery(Filename);
			return true;
		}

		// Load maps and entities; update the current tileset if area is loaded successfully.
		// Note that the functions to load entities is contained within the IOC.OnLoad function below.
		if (mY >= LOAD_BUT_Y && mY < LOAD_BUT_Y + IO_BUT_H)
		{
			CInterrupt::appendFlag(INTRPT_LOAD);
			// if (CIO::IOControl.OnLoad(Map_Interface, Tileset_Path))
			// {
			// 	// Main_Tileset = CSurface::OnLoad(Tileset_Path);
			// 	// active_bg = active_type = 0;
			// 	//
			// 	// QueryTileset();
			// 	// return true;
			// }
		}
	}
	return true;
}
