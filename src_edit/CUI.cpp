#include "CUI.h"

CUI CUI::UIControl;

CUI::CUI()
{
	UI_Width = 458;
	UI_Height = 350;
	Px = (WWIDTH - UI_Width) / 2;
	Py = (WHEIGHT - UI_Height) / 2;
	Title_Length.resize(3);
	Current_Set = TILESET_DEF;
	Current_Table = -1;
}

bool CUI::OnWindow(SDL_Renderer* renderer, SDL_Texture* map_ui, int type)
{
	if (CSurface::OnDraw(renderer, map_ui, Px, Py, 0, 0, UI_Width, UI_Height) == false)
		return false;

	if (type == TILESET)
	{
		Font::Write(renderer, FONT_DEFAULT, "CHOOSE A TILESET", Px + 10, Py + 5);
		Title_Length[TILESET_DEF] = Font::Write(renderer, FONT_DEFAULT, "DEFAULT", Px + 25, Py + 10 + 17 * 1);
		Title_Length[TILESET_FOREST] = Font::Write(renderer, FONT_DEFAULT, "FOREST", Px + 25, Py + 10 + 17 * 2);
		Title_Length[TILESET_CAVE] = Font::Write(renderer, FONT_DEFAULT, "CAVE", Px + 25, Py + 10 + 17 * 3);
	}
	else if (type == ENTITY)
	{
		Font::Write(renderer, FONT_DEFAULT, "CHOOSE A NPC TABLE", Px + 10, Py + 5);
		Title_Length[ENTITY_DEBUG] = Font::Write(renderer, FONT_DEFAULT, "DEBUG", Px + 25, Py + 10 + 17 * 1);

		Font::Write(renderer, FONT_DEFAULT, "WARNING\nTHIS WILL REMOVE ALL NPCS", Px + 10, Py + 80);
	}

	Font::Write(renderer, FONT_DEFAULT, "NVM", Px + UI_Width - 10 - 14 * 3, Py + UI_Height - 5 - 14);
	SDL_RenderPresent(renderer);
	return true;
}

/* This is the executable member that contains the editor's
* critical functions. Initialization, event handling, data manipulation,
* rendering, and house keeping are done within this member.
*/

int CUI::OnEntity(SDL_Renderer* renderer, SDL_Texture* map_ui)
{
	Window_Type = ENTITY;
	Running = OnWindow(renderer, map_ui, Window_Type);

	SDL_Event Event;
	// This loop will run endlessly until something makes the Running
	// flag false. That will happen, hopefully, by the user's decision.
	while (Running)
	{
		// Check for pending events; handle them
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
	}

	OnCleanup();       // Clean up the program before exiting

	return Current_Table;
}

SDL_Texture* CUI::OnChange(SDL_Renderer* renderer, SDL_Texture* map_ui, char* &setpath)
{
	Window_Type = TILESET;
	Running = OnWindow(renderer, map_ui, Window_Type);

	SDL_Event Event;
	// This loop will run endlessly until something makes the Running
	// flag false. That will happen, hopefully, by the user's decision.
	while (Running)
	{
		// Check for pending events; handle them
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}
	}

	OnCleanup();       // Clean up the program before exiting

	return ChangeSet(renderer, New_Tileset, setpath);
}

void CUI::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CUI::OnLButtonDown(int mX, int mY)
{
	if (Window_Type == TILESET)
	{
		// "NVM"
		if (mY >= Py + UI_Height - 5 - 14 && mY <= Py + UI_Height)
		{
			if (mX >= Px + UI_Width - 10 - 14 * 3 && mX <= Px + UI_Width)
			{
				New_Tileset = Current_Set;
				OnExit();
				return;
			}
		}

		// "DEFAULT"
		if (mY >= Py + 10 + 17 * 1 && mY < Py + 10 + 17 * 1 + 14)
		{
			if (mX >= Px + 25 && mX < Px + 25 + Title_Length[TILESET_DEF])
			{
				New_Tileset = TILESET_DEF;
				OnExit();
				return;
			}
		}

		// "FOREST"
		if (mY >= Py + 10 + 17 * 2 && mY < Py + 10 + 17 * 2 + 14)
		{
			if (mX >= Px + 25 && mX < Px + 25 + Title_Length[TILESET_FOREST])
			{
				New_Tileset = TILESET_FOREST;
				OnExit();
				return;
			}
		}

		// "CAVE"
		if (mY >= Py + 10 + 17 * 3 && mY < Py + 10 + 17 * 3 + 14)
		{
			if (mX >= Px + 25 && mX < Px + 25 + Title_Length[TILESET_CAVE])
			{
				New_Tileset = TILESET_CAVE;
				OnExit();
				return;
			}
		}
	}
////////////////////////////////////////////////////////////////////////////////
	else if (Window_Type == ENTITY)
	{
		// "NVM"
		if (mY >= Py + UI_Height - 5 - 14 && mY <= Py + UI_Height)
		{
			if (mX >= Px + UI_Width - 10 - 14 * 3 && mX <= Px + UI_Width)
			{
				Current_Table = -1;
				OnExit();
				return;
			}
		}

		// "DEBUG"
		if (mY >= Py + 10 + 17 * 1 && mY < Py + 10 + 17 * 1 + 14)
		{
			if (mX >= Px + 25 && mX < Px + 25 + Title_Length[ENTITY_DEBUG])
			{
				Current_Table = ENTITY_DEBUG;
				OnExit();
				return;
			}
		}
	}
}

SDL_Texture* CUI::ChangeSet(SDL_Renderer* renderer, int setname, char* &setpath)
{
	SDL_Texture* Newset = NULL;

	switch (setname)
	{
			case TILESET_DEF:
									setpath = "../res/tile/default.png";
									Newset = CSurface::OnLoad(setpath, renderer);
									break;

			case TILESET_FOREST:
									setpath = "../res/tile/forest.png";
									Newset = CSurface::OnLoad(setpath, renderer);
									break;

			case TILESET_CAVE:
									setpath = "../res/tile/cave.png";
									Newset = CSurface::OnLoad(setpath, renderer);
									break;

			default: break;
	}
	Current_Set = setname;

	return Newset;
}

void CUI::OnExit()
{
	Running = false;
}

void CUI::OnCleanup()
{
	//
}
