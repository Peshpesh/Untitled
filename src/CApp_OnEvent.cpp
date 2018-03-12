#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
	// if (CInterrupt::isNone()) {
	// 	CEvent::OnEvent(Event);
	// }
	// else {
	// 	if (handleInterr(Event)) return;
	// }
	// if (active_mod == MODIFY_MAP) CEditMap::MapEditor.OnEvent(Event);
	// if (active_mod == MODIFY_NPC) CEntityEditor::Control.OnEvent(Event);
	// if (active_mod == MODIFY_SCENE) CSceneryEditor::control.OnEvent(Event);

	if (CMode::isFlagOn(APP_MODE_GAME)) {
		// Process events during gameplay
		CGame::control.OnEvent(Event);
	} else if (CMode::isFlagOn(APP_MODE_TITLE)) {
		// Process events at title screen
		CTitle::control.OnEvent(Event);
		if (CTitle::control.call_terminate) Running = false;
	} else if (CMode::isFlagOn(APP_MODE_FATAL)) {
		// Process events during a fatal error
	}
	CEvent::OnEvent(Event);
}


void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
	switch (sym) {
		case SDLK_ESCAPE: {
			if (!esc_init) esc_init = SDL_GetTicks();
			break;
		}
		default: break;
	}
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
	switch (sym) {
		case SDLK_ESCAPE: esc_init = false; break;
		default: break;
	}
}

void CApp::OnExit() {
	Running = false;
}

// void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod)
// {
// 	// No Menus, not at Main Menu
// 	if (CMenu::MenuList.size() == 0 && !CInventory::InvControl.active && !PauseMenu.Active && !CTitle::MainMenu.Active)
// 	{
// 		if (sym == Config::ConfControl.confirm)
// 		{
// 			if (Player.Engaged || CCinema::CinemaControl->Scene)
// 			{
// 				CDialogue::DiaControl.FastType = true;
// 			}
// 			else
// 			{
// 				if (!Player.Shooting)
// 				{
// 					Player.Shooting = true;
// 					Player.OnShoot();
// 				}
// 			}
// 			return;
// 		}
// 		if (sym == Config::ConfControl.left)
// 		{
// 			Player.MoveLeft = true;
// 			return;
// 		}
// 		if (sym == Config::ConfControl.right)
// 		{
// 			Player.MoveRight = true;
// 			return;
// 		}
// 		if (sym == Config::ConfControl.down)
// 		{
// 			if (!Player.Interact())
// 			{
// 				// Aim down in midair?
// 			}
// 			return;
// 		}
// 		if (sym == Config::ConfControl.jump)
// 		{
// 			if (!CCinema::CinemaControl->Scene) Player.Jump();
// 			return;
// 		}
// 		if (!Player.Engaged)
// 		{
// 			if (sym == Config::ConfControl.select)
// 			{
// 				CInventory::InvControl.active = true;
// 				Suspend = true;
// 				return;
// 			}
// 			// Open Pause Menu
// 			if (sym == Config::ConfControl.pause)
// 			{
// 				PauseMenu.Active = true;
// 				Paused = true;
// 				return;
// 			}
// 		}
// 	}
// 	// Not at Main Menu, but there is at least one menu...
// 	else if (!CTitle::MainMenu.Active)
// 	{
// 		if (sym == Config::ConfControl.left) Player.MoveLeft = true;
// 		if (sym == Config::ConfControl.right) Player.MoveRight = true;
// 		// Events are processed for the LATEST menu to appear.
// 		// For multiple menus, events will only affect the latest menu.
// 		// The active pause menu is always the latest menu.
// 		// The active inventory menu is always the last menu.
// 		// (why: the inventory is unopenable unless there are NO
// 		// menus active. The inventory can spawn generic menus, which
// 		// will always take event precedence over the main inventory
// 		// interface. Thus, if the pause menu is inactive, we first
// 		// check for any generic menus in the menu list. If there are none,
// 		// then we check to see if the inventory is open.)
// 		if (PauseMenu.Active)	PauseMenu.OnEvent(sym);
// 		else if (CMenu::MenuList.size() > 0) CMenu::MenuList[CMenu::MenuList.size() - 1]->OnEvent(sym);
// 		else if (CInventory::InvControl.active) Suspend = CInventory::InvControl.OnEvent(sym);
// 	}
// 	else // Title Screen
// 	{
// 		CTitle::MainMenu.OnEvent(sym);
// 	}
// }

// void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod)
// {
// 	if (CMenu::MenuList.size() == 0 && !CTitle::MainMenu.Active)
// 	{
// 		if (sym == Config::ConfControl.confirm)
// 		{
// 			if (Player.Shooting) Player.Shooting = false;
// 			return;
// 		}
// 		if (sym == Config::ConfControl.left)
// 		{
// 			Player.MoveLeft = false;
// 			return;
// 		}
// 		if (sym == Config::ConfControl.right)
// 		{
// 			Player.MoveRight = false;
// 			return;
// 		}
// 	}
// 	else if (!CTitle::MainMenu.Active)
// 	{
// 		if (sym == Config::ConfControl.left)
// 		{
// 			Player.MoveLeft = false;
// 			return;
// 		}
// 		if (sym == Config::ConfControl.right)
// 		{
// 			Player.MoveRight = false;
// 			return;
// 		}
// 	}
// }
