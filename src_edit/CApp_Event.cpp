#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
	if (CInterrupt::isNone()) {
		CEvent::OnEvent(Event);
	}
	else {
		if (handleInterr(Event)) return;
	}
	if (active_mod == MODIFY_MAP) CEditMap::MapEditor.OnEvent(Event);
	if (active_mod == MODIFY_NPC) CEntityEditor::Control.OnEvent(Event);
	if (active_mod == MODIFY_SCENE) CSceneryEditor::control.OnEvent(Event);
	if (active_mod == MODIFY_SANDBOX) ;
	if (active_mod == MODIFY_OPTIONS) ;
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
	if (CInterrupt::isFlagOn(INTRPT_EXIT)) {
		CTerminate::control.OnEvent(Event);
		if (CTerminate::control.willTerminate()) {
			OnExit();
		}
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
    case SDLK_ESCAPE: CInterrupt::appendFlag(INTRPT_EXIT); break;
    default: break;
  }
}

// Handle left-click events
void CApp::OnLButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT) {
		return;
	}

	const SDL_Point m = {mX, mY};
	if (handleEngSwitch(&m)) return;
	if (handleModelSwitch(&m)) return;
	if (handleIO(&m)) return;
}

void CApp::OnRButtonDown(int mX, int mY)
{
	if (mX < 0 || mY < 0 || mX > EWIDTH || mY > EHEIGHT) return;
}

bool CApp::handleEngSwitch(const SDL_Point* m) {
	using namespace engineSwitch;

	// Clicks on a modify option button. Changes the MODIFY "flag" accordingly.
	for (int i = MODIFY_MAP; i <= MODIFY_OPTIONS; i++)
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
