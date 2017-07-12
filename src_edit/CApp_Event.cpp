#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	if (handleInterr(Event)) return;

	CEvent::OnEvent(Event);

	if (active_mod == MODIFY_MAP) CEditMap::MapEditor.OnEvent(Event);
	if (active_mod == MODIFY_NPC) CEntityEditor::Control.OnEvent(Event);
}

bool CApp::handleInterr(SDL_Event* Event)
{
	if (CInterrupt::isFlagOn(INTRPT_MAP_MODEL)) {
		CModel::Control.OnEvent(Event);
		return true;
	}
	if (CInterrupt::isFlagOn(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE)) {
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
	if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT) {
		return;
	}

	{
		const SDL_Point m = {mX, mY};
		if (handleEngSwitch(&m)) return;
		if (handleModelSwitch(&m)) return;
		if (handleIO(&m)) return;
	}

	if (active_mod == MODIFY_SCENE || active_mod == REMOVE_SCENE)
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

		// if (!AddEntity(Xo - (Xo % TILE_SIZE), Yo - (Yo % TILE_SIZE)))
		// 	OnExit();
	}
}

bool CApp::handleEngSwitch(const SDL_Point* m)
{
	using namespace engineSwitch;

	// Clicks on a modify option button. Changes the MODIFY "flag" accordingly.
	for (int i = MODIFY_MAP; i <= REMOVE_SCENE; i++)
	{
		if (SDL_PointInRect(m, &engineButton[i])) {
			active_mod = i;
			return true;
		}
	}
	return false;
}

bool CApp::handleModelSwitch(const SDL_Point* m)
{
	using namespace modelSwitch;

	if (SDL_PointInRect(m, &button)) {
		CInterrupt::appendFlag(INTRPT_MAP_MODEL);
		CModel::Control.OnInit();
		return true;
	}
	return false;
}

bool CApp::handleIO(const SDL_Point* m)
{
	using namespace io_ui;

	if (SDL_PointInRect(m, &newButton)) {
		CInterrupt::appendFlag(INTRPT_NEW);
		return true;
	}
	if (SDL_PointInRect(m, &loadButton)) {
		CInterrupt::appendFlag(INTRPT_LOAD);
		return true;
	}
	if (SDL_PointInRect(m, &saveButton)) {
		CInterrupt::appendFlag(INTRPT_SAVE);
		return true;
	}

	return false;
}
