#include "ESavepoint.h"

enum
{
	SAVEGAME = 0,
	CANCEL,
};

CSVPT::CSVPT()
{
	SaveMenu = NULL;
	ConfirmMenu = NULL;
	MaxSpeedX = 0;
	MaxSpeedY = 0;
	Flags = ENTITY_FLAG_HOLLOW;
	Type = ENTITY_TYPE_NPC;

	Prompt = false;
}

bool CSVPT::OnLoad(SDL_Texture* entityset, int Xo, int Yo, int Width, int Height, int MaxFrames)
{
	if (CEntity::OnLoad(entityset, Xo, Yo, Width, Height, MaxFrames) == false)
		return false;

	return true;
}

void CSVPT::OnLoop()
{
	if (Prompt)
	{
		if (!ConfirmMenu)
		{
			if (SaveMenu->Break)
			{
				ExitMenu(SaveMenu);
				SaveMenu = NULL;
				Prompt = Engaged = false;
			}
			else if (SaveMenu->Submit)
			{
				switch (SaveMenu->GetResponse())
				{
				case SAVEGAME: // ASK TO SAVE GAME
				{
										ConfirmMenu = new CMenu;
										ConfirmMenu->Active = ConfirmMenu->Breakable = true;
										ConfirmMenu->OnInit("\
														 %YES\
														\n%NO");

										CMenu::MenuList.push_back(ConfirmMenu);
										SaveMenu->Submit = false;
										break;
				}
				case CANCEL:
				{
										ExitMenu(SaveMenu);
										SaveMenu = NULL;
										Prompt = Engaged = false;
										break;
				}
				default: 	break;
				}
			}
		}
		else
		{
			if (ConfirmMenu->Break)
			{
				ExitMenu(ConfirmMenu);
				ConfirmMenu = NULL;
			}
			else if (ConfirmMenu->Submit)
			{
				switch (ConfirmMenu->GetResponse())
				{
				case SAVEGAME: // SAVE THE GAME
				{
										CGameData::GameControl.Save = true;
										break;
				}
				case CANCEL:
				{
										break;
				}
				default: 	break;
				}
				ExitMenu(ConfirmMenu);
				ConfirmMenu = NULL;
			}
		}
	}
	CEntity::OnLoop();
}

void CSVPT::OnRender(SDL_Renderer* renderer)
{
	CEntity::OnRender(renderer);
}

void CSVPT::ExitMenu(CMenu* menu)
{
	menu->OnCleanup();
	delete CMenu::MenuList[CMenu::MenuList.size() - 1];
	CMenu::MenuList.erase(CMenu::MenuList.begin() + CMenu::MenuList.size() - 1);
}

void CSVPT::OnCleanup()
{
	CEntity::OnCleanup();
}

void CSVPT::OnAnimate()
{
	CEntity::OnAnimate();
}

bool CSVPT::OnCollision(CEntity* Entity)
{
	return true;
}

bool CSVPT::OnInteract(SDL_Renderer* renderer)
{
	// If thus far unprompted, then the savepoint is just now
	// being interacted with. We must then add a menu (the save
	// menu) to the menu list. While the SVPT is being interacted with,
	// nothing else should happen.
	if (!Prompt)
	{
		Prompt = true;
		SaveMenu = new CMenu;
		SaveMenu->Active = SaveMenu->Breakable = true;
		SaveMenu->OnInit("\
						 %SAVE\
	 					\n%CANCEL");

		CMenu::MenuList.push_back(SaveMenu);
	}
	return Engaged;
}
