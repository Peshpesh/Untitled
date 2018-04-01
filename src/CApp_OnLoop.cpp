#include "CApp.h"

void CApp::OnLoop() {
	if (CMode::isFlagOn(APP_MODE_GAME)) {
		CGame::control.OnLoop();
	} else if (CMode::isFlagOn(APP_MODE_TITLE)) {
		CTitle::control.OnLoop();
		if (CMode::isFlagOn(APP_MODE_GAME)) {
			// switching from Title to Game
			if (!CGame::control.OnInit()) {
				// ERROR COULD NOT INITIALIZE GAME
			}
		}
	} else if (CMode::isFlagOn(APP_MODE_FATAL)) {
		//
	}

	// CFPS::FPSControl.OnLoop();

	if (esc_init && (SDL_GetTicks() - esc_init) >= ESC_THRESH) {
		// call to terminate game
		Running = false;
	}
}

// void CApp::OnLoop()
// {
// 	// Title Screen Loop
// 	if (CTitle::MainMenu.Active)
// 	{
// 		CTitle::MainMenu.OnLoop();
// 		if (CTitle::MainMenu.Submit)
// 		{
// 			switch (CTitle::MainMenu.hilight)
// 			{
// 				case NEW_GAME:
// 				{
// 					if (!InitGame())
// 					{
// 						// error
// 					}
// 					CGameData::GameControl.CreateData(CTitle::MainMenu.sfile, 1);
// 					break;
// 				}
// 				case LOAD_GAME:
// 				{
// 					if (!InitGame())
// 					{
// 						// error
// 					}
// 					CGameData::GameControl.ImportData(CTitle::MainMenu.sfile, CTransport::Transporter.Destination, Player.MaxHealth, Player.Health,
// 						Player.Weapon, Player.Ammo, Player.Purse, Player.Arsenal, CTransport::Transporter.rX, CTransport::Transporter.rY);
// 					break;
// 				}
// 				case OPTIONS:	break;
// 				case QUIT_GAME: OnExit(); break;
// 				default:	break;
// 			}
// 		}
// 	}
// 	if (!CTitle::MainMenu.Active)
// 	{
// 		if (CTransport::Transporter.Relocate)
// 		{
// 			CTransport::Transporter.OnTransport(Player.X, Player.Y, Win_Renderer);
// 		}
// 		if (CGameData::GameControl.Save)
// 		{
// 			CGameData::GameControl.ExportData(CTransport::Transporter.Destination, Player.MaxHealth,
// 				Player.Health, Player.Weapon, Player.Ammo, Player.Purse, Player.Arsenal, Player.X, Player.Y);
// 		}
// 		CCinema::CinemaControl->OnLoop(Player.X, Player.Y, Win_Renderer);
//
// 		if (PauseMenu.Active)
// 		{
// 			PauseMenu.OnLoop();
// 			if (!PauseMenu.Active)
// 			{
// 				Paused = false;
// 				if (PauseMenu.Quitgame)
// 				{
// 					ExitGame();
// 					PauseMenu.Quitgame = false;
// 				}
// 			}
// 		}
// 		else
// 		{
// 			if (CMenu::MenuList.size() > 0)
// 			{
// 				CMenu::MenuList[CMenu::MenuList.size() - 1]->OnLoop();
// 			}
// 			if (CInventory::InvControl.active)
// 			{
// 				// IDEA: Onloop functions from CInventory & PauseMenu
// 				// can return bool, where return true means the menu is still active,
// 				// and return false means the menu has just been terminated.
// 				Suspend = CInventory::InvControl.OnLoop(); // OR: OnEvent returns bool
// 			}
// 		}
//
// 		if (Suspend || Paused)
// 		{
// 			// suspended gameplay
// 		}
// 		else if (CCinema::CinemaControl->Scene)	// cutscene
// 		{
// 			CCinema::CinemaControl->OnSceneLoop();
// 		}
// 		else	// standard gameplay
// 		{
// 			for (int i = 0; i < CEntity::EntityList.size(); i++)
// 			{
// 				if (!CEntity::EntityList[i]) continue;
//
// 				// This should trigger AFTER a death animation.
// 				if (CEntity::EntityList[i]->Dead == true && i != 0)
// 				{
// 					delete CEntity::EntityList[i];
// 					CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
// 					continue;
// 				}
// 				CEntity::EntityList[i]->OnLoop();
// 			}
// 			for (int i = 0; i < CScenery::SceneList.size(); i++)
// 			{
// 				if (!CScenery::SceneList[i]) continue;
// 				CScenery::SceneList[i]->OnLoop();
// 			}
//
// 			// Collisions
// 			for (int i = 0; i < CEntityCol::EntityColList.size(); i++)
// 			{
// 				CEntity* EntityA = CEntityCol::EntityColList[i].EntityA;
// 				CEntity* EntityB = CEntityCol::EntityColList[i].EntityB;
//
// 				if (EntityA == NULL || EntityB == NULL) continue;
//
// 				if (EntityA->OnCollision(EntityB))
// 				{
// 					EntityB->OnCollision(EntityA);
// 				}
// 			}
// 			Player.TryInteract = false;
// 			CEntityCol::EntityColList.clear();
//
// 			// Interactions
// 			if (Player.Engaged)	// Player has engaged an NPC. With what is the player engaged?
// 			{
// 				bool response = false;	// Has an NPC reciprocated?
// 				for (int i = 1; i < CEntity::EntityList.size(); i++)
// 				{
// 					if (CEntity::EntityList[i]->Engaged)
// 					{
// 						response = true;
// 						if (!CEntity::EntityList[i]->OnInteract(Win_Renderer))	// The NPC may refuse to engage.
// 							Player.TryInteract = Player.Engaged = false;
// 						break;
// 					}
// 				}
// 				if (!response) Player.Engaged = false;	// If no NPC reciprocated, the player is not engaged.
// 			}
// 		}
// 	}
//
// 	CFPS::FPSControl.OnLoop();
// 	CGameData::GameControl.Global.uptime = CGameData::GameControl.InitTime + (SDL_GetTicks() / 10);
//
// 	//char Buffer[255];
// 	//sprintf(Buffer, "%d", CFPS::FPSControl.GetFPS());
// 	//SDL_SetWindowTitle(Win_Display, Buffer);
//
// }

// void CApp::ExitGame()
// {
// 	CEntityCol::EntityColList.clear();
// 	for (int i = (CEntity::EntityList.size() - 1); i > 0; i--)
// 	{
// 		delete CEntity::EntityList[i];
// 		CEntity::EntityList.erase(CEntity::EntityList.begin() + i);
// 	}
// 	CEntity::EntityList.clear();
// 	CTransport::Transporter.OnCleanup();
// 	for (int i = (CMenu::MenuList.size() - 1); i >= 0; i--)
// 	{
// 		CMenu::MenuList[i]->OnCleanup();
// 		delete CMenu::MenuList[i];
// 		CMenu::MenuList.erase(CMenu::MenuList.begin() + i);
// 	}
// 	CMenu::MenuList.clear();
// 	CTitle::MainMenu.Active = true;
// }
