#include "CTitle.h"

CTitle CTitle::MainMenu;

CTitle::CTitle()
{
	Active = true;
	Submit = false;

	selectGame = false;
	sfile = 'A';
	showstats = false;

	options = NULL;
	hilight = NEW_GAME;
}

bool CTitle::OnInit()
{
	return true;
}

void CTitle::OnEvent(SDL_Keycode sym)
{
	if (!Config::ConfControl.modify && !selectGame)
	{
		if (sym == Config::ConfControl.confirm)
		{
			if (!showstats)	Submit = true;
			else showstats = false;
			return;
		}
		if (sym == Config::ConfControl.left) return;
		if (sym == Config::ConfControl.right)	return;
		if (sym == Config::ConfControl.down)
		{
			// if (hilight == MAP_EDITOR) hilight = NEW_GAME;
			if (hilight == QUIT_GAME) hilight = NEW_GAME;
			else hilight++;
			return;
		}
		if (sym == Config::ConfControl.up)
		{
			// if (hilight == NEW_GAME) hilight = MAP_EDITOR;
			if (hilight == NEW_GAME) hilight = QUIT_GAME;
			else hilight--;
			return;
		}
		if (sym == SDLK_ESCAPE)
		{
			if (!showstats)
			{
				if (hilight != QUIT_GAME) hilight = QUIT_GAME;
				else Submit = true;
			}
			else showstats = false;
			return;
		}
	}
	else if (selectGame)
	{
		if (sym == Config::ConfControl.confirm)
		{
			Submit = true;
			return;
		}
		if (sym == Config::ConfControl.left) return;
		if (sym == Config::ConfControl.right) return;
		if (sym == Config::ConfControl.down)
		{
			switch (sfile)
			{
				case 'A':	sfile = 'B'; break;
				case 'B':	sfile = 'C'; break;
				case 'C':	sfile = 'A'; break;
				default:	break;
			}
			return;
		}
		if (sym == Config::ConfControl.up)
		{
			switch (sfile)
			{
				case 'A':	sfile = 'C'; break;
				case 'B':	sfile = 'A'; break;
				case 'C':	sfile = 'B'; break;
				default:	break;
			}
			return;
		}
		if (sym == SDLK_ESCAPE)
		{
			selectGame = false;
			sfile = 'A';
			return;
		}
	}
	else Config::ConfControl.OnEvent(sym);
}

void CTitle::OnLoop()
{
	if (Submit)
	{
		switch (hilight)
		{
			case NEW_GAME:
			{
				if (!selectGame)
				{
					selectGame = true;
					Submit = false;
				}
				else selectGame = false;
				break;
			}
			case LOAD_GAME:
			{
				if (!selectGame)
				{
					selectGame = true;
					Submit = false;
				}
				else selectGame = false;
				break;
			}
			case STATISTICS: Submit = false; showstats = true; break;
			case OPTIONS:	Submit = false; Config::ConfControl.modify = true; break;
			case QUIT_GAME: break;
			// case MAP_EDITOR: break;
			default: break;
		}
	}
}

void CTitle::OnRender(SDL_Renderer* renderer)
{
	if (!Config::ConfControl.modify)
	{
		if (!showstats && !selectGame)
		{
			// Font::Write(renderer, FONT_DEFAULT,
			// 	"NEW GAME\nLOAD GAME\nSTATISTICS\nOPTIONS\nQUIT\n\nMAP EDITOR", WWIDTH / 2, WHEIGHT / 2);
			// if (hilight != MAP_EDITOR)
			// 	Font::Write(renderer, FONT_DEFAULT, "X", (WWIDTH / 2) - 30, (WHEIGHT / 2) + (hilight * 16));
			// else
			// 	Font::Write(renderer, FONT_DEFAULT, "X", (WWIDTH / 2) - 30, (WHEIGHT / 2) + ((hilight + 1) * 16));
			Font::Write(renderer, FONT_DEFAULT, "NEW GAME\nLOAD GAME\nSTATISTICS\nOPTIONS\nQUIT", WWIDTH / 2, WHEIGHT / 2);
			Font::Write(renderer, FONT_DEFAULT, "X", (WWIDTH / 2) - 30, (WHEIGHT / 2) + (hilight * 16));
		}
		else if (selectGame)
		{
			int displace = 0;
			Font::Write(renderer, FONT_DEFAULT, "FILE A\nFILE B\nFILE C", WWIDTH / 2, WHEIGHT / 2);
			switch (sfile)
			{
				case 'A': break;
				case 'B': displace = 1; break;
				case 'C': displace = 2; break;
				default: break;
			}
			Font::Write(renderer, FONT_DEFAULT, "X", (WWIDTH / 2) - 30, (WHEIGHT / 2) + (displace * 16));
		}
		else RenderStats(renderer);
	}
	else Config::ConfControl.OnRender(renderer);
}

void CTitle::RenderStats(SDL_Renderer* renderer)
{
	Font::Write(renderer, FONT_DEFAULT,
		"DEATH COUNT\nPOWER COUNT\nFINISHED GAMES\nRUNNING TIME\nPLAY TIME",
		60, WHEIGHT / 2);
	Font::Write(renderer, FONT_DEFAULT, CGameData::GameControl.Global.deathcount, 300, (WHEIGHT / 2) + (16 * 0));
	Font::Write(renderer, FONT_DEFAULT, CGameData::GameControl.Global.powercount, 300, (WHEIGHT / 2) + (16 * 1));
	Font::Write(renderer, FONT_DEFAULT, CGameData::GameControl.Global.Nfinish, 300, (WHEIGHT / 2) + (16 * 2));

	int allhr = CGameData::GameControl.Global.uptime / 360000;
	int allmn = (CGameData::GameControl.Global.uptime % 360000) / 6000;
	int allsc = ((CGameData::GameControl.Global.uptime % 360000) % 6000) / 100;

	int offset = 0;
	offset += Font::Write(renderer, FONT_DEFAULT, allhr, 300 + offset, (WHEIGHT / 2) + (16 * 3));
	if (allmn < 10)
		offset += Font::Write(renderer, FONT_DEFAULT, 0, 300 + offset, (WHEIGHT / 2) + (16 * 3));
	offset += Font::Write(renderer, FONT_DEFAULT, allmn, 300 + offset, (WHEIGHT / 2) + (16 * 3));
	if (allsc < 10)
		offset += Font::Write(renderer, FONT_DEFAULT, 0, 300 + offset, (WHEIGHT / 2) + (16 * 3));
	Font::Write(renderer, FONT_DEFAULT, allsc, 300 + offset, (WHEIGHT / 2) + (16 * 3));

	int gamehr = CGameData::GameControl.Global.playtime / 360000;
	int gamemn = (CGameData::GameControl.Global.playtime % 360000) / 6000;
	int gamesc = ((CGameData::GameControl.Global.playtime % 360000) % 6000) / 100;

	offset = 0;
	offset += Font::Write(renderer, FONT_DEFAULT, gamehr, 300 + offset, (WHEIGHT / 2) + (16 * 4));
	if (gamemn < 10)
		offset += Font::Write(renderer, FONT_DEFAULT, 0, 300 + offset, (WHEIGHT / 2) + (16 * 4));
	offset += Font::Write(renderer, FONT_DEFAULT, gamemn, 300 + offset, (WHEIGHT / 2) + (16 * 4));
	if (gamesc < 10)
		offset += Font::Write(renderer, FONT_DEFAULT, 0, 300 + offset, (WHEIGHT / 2) + (16 * 4));
	Font::Write(renderer, FONT_DEFAULT, gamesc, 300 + offset, (WHEIGHT / 2) + (16 * 4));
}
