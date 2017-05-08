#include "CConfig.h"

CConfig CConfig::ConfControl;

CConfig::CConfig()
{
	modify		=	false;
	querykey	=	false;
	hilight		=	CF_RETURN;

	// MAIN CONTROLS
	confirm	=	SDLK_z;
	pause		=	SDLK_p;
	select	=	SDLK_i;
	left		=	SDLK_LEFT;
	right		=	SDLK_RIGHT;
	up			=	SDLK_UP;
	down		=	SDLK_DOWN;
	jump		=	SDLK_SPACE;

	// DEBUG CONTROLS
}

bool CConfig::OnInit()
{
	char pre[] = "../data/game/config";
	char ext[] = ".key";
	/* filename character string must be long enough to contain:
	* pre[], or the file prefix;
	* + ext[], file suffix;
	* + 1 character for "\0"
	*/
	char* fconfig = new char[std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(fconfig, pre);
	std::strcat(fconfig, ext);
	FILE* FileHandle = fopen(fconfig, "r");
	// No config data found; make some
	if (FileHandle == NULL)
	{
		delete fconfig;
		Save();
	}
	else // Read config data
	{
		fscanf(FileHandle, "%d:%d:%d:%d:%d:%d:%d:%d", &confirm, &pause, &select, &left, &right, &up, &down, &jump);
		// fscanf(FileHandle, "%d:%d:%d:%d:%d:%d:%d", &confirm, &pause, &left, &right, &up, &down, &jump);
		fclose(FileHandle);
		delete fconfig;
	}
	return true;
}

void CConfig::OnEvent(SDL_Keycode sym)
{
	if (!querykey)
	{
		if (sym == CConfig::ConfControl.confirm)
		{
			if (hilight == CF_RETURN) modify = false;
			else if (hilight == CF_RESTORE) Reset();
			else querykey = true;
			return;
		}
		if (sym == CConfig::ConfControl.left)
		{
			return;
		}
		if (sym == CConfig::ConfControl.right)
		{
			return;
		}
		if (sym == CConfig::ConfControl.down)
		{
			if (hilight == CF_RESTORE) hilight = CF_RETURN;
			else hilight++;
			return;
		}
		if (sym == CConfig::ConfControl.up)
		{
			if (hilight == CF_RETURN) hilight = CF_RESTORE;
			else hilight--;
			return;
		}
		if (sym == SDLK_ESCAPE)
		{
			if (hilight != CF_RETURN) hilight = CF_RETURN;
			else modify = false;
			return;
		}
	}
	else // querykey == true
	{
		querykey = false;
		if (!ErrCheck(sym))
		{
			switch (hilight)
			{
				case CF_CONFIRM:	confirm = sym;	break;
				case CF_JUMP:			jump = sym;			break;
				case CF_LEFT:			left = sym;			break;
				case CF_RIGHT:		right = sym;		break;
				case CF_DOWN:			down = sym;			break;
				case CF_UP:				up = sym;				break;
				case CF_SELECT:		select = sym;		break;
				case CF_PAUSE:		pause = sym;		break;
				default:	break;
			}
			Save();
		}
	}
}

bool CConfig::OnRender(SDL_Renderer* renderer)
{
	Font::Write(renderer, FONT_DEFAULT,
		"BACK\n\nATTACK\nJUMP\nLEFT\nRIGHT\nDOWN\nUP\nINVENTORY\nPAUSE\n\nRESTORE TO DEFAULT",
		60, (WHEIGHT / 2) - 16);

	if (hilight != CF_RETURN && hilight != CF_RESTORE)
		Font::Write(renderer, FONT_DEFAULT, "X", 30, (WHEIGHT / 2) + (hilight * 16));
	else if (hilight == CF_RETURN)
		Font::Write(renderer, FONT_DEFAULT, "X", 30, (WHEIGHT / 2) - 16);
	else
		Font::Write(renderer, FONT_DEFAULT, "X", 30, (WHEIGHT / 2) + (hilight * 16) + 16);

	if (querykey && hilight == CF_CONFIRM)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(confirm), F_RED, true, 200, (WHEIGHT / 2) + (CF_CONFIRM * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(confirm), 200, (WHEIGHT / 2) + (CF_CONFIRM * 16));
	if (querykey && hilight == CF_JUMP)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(jump), F_ORANGE, true, 200, (WHEIGHT / 2) + (CF_JUMP * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(jump), 200, (WHEIGHT / 2) + (CF_JUMP * 16));
	if (querykey && hilight == CF_LEFT)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(left), F_YELLOW, false, 200, (WHEIGHT / 2) + (CF_LEFT * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(left), 200, (WHEIGHT / 2) + (CF_LEFT * 16));
	if (querykey && hilight == CF_RIGHT)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(right), F_GREEN, false, 200, (WHEIGHT / 2) + (CF_RIGHT * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(right), 200, (WHEIGHT / 2) + (CF_RIGHT * 16));
	if (querykey && hilight == CF_DOWN)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(down), F_CYAN, true, 200, (WHEIGHT / 2) + (CF_DOWN * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(down), 200, (WHEIGHT / 2) + (CF_DOWN * 16));
	if (querykey && hilight == CF_UP)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(up), F_BLUE, true, 200, (WHEIGHT / 2) + (CF_UP * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(up), 200, (WHEIGHT / 2) + (CF_UP * 16));
	if (querykey && hilight == CF_SELECT)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(select), F_VIOLET, true, 200, (WHEIGHT / 2) + (CF_SELECT * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(select), 200, (WHEIGHT / 2) + (CF_SELECT * 16));
	if (querykey && hilight == CF_PAUSE)
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(pause), F_VIOLET, true, 200, (WHEIGHT / 2) + (CF_PAUSE * 16));
	else
		Font::Write(renderer, FONT_DEFAULT, (char*)SDL_GetKeyName(pause), 200, (WHEIGHT / 2) + (CF_PAUSE * 16));
	return true;
}

bool CConfig::ErrCheck(SDL_Keycode sym)
{
	// Prevent multiple responses for single input
	if (sym == confirm) return true;
	if (sym == select)	return true;
	if (sym == pause)	return true;
	if (sym == left)	return true;
	if (sym == right)	return true;
	if (sym == up)		return true;
	if (sym == down)	return true;
	if (sym == jump)	return true;

	if (sym == SDLK_ESCAPE) return true;

	return false;
}

void CConfig::Reset()
{
	// MAIN CONTROLS
	confirm		= SDLK_z;
	select		= SDLK_i;
	pause		= SDLK_p;
	left		= SDLK_LEFT;
	right		= SDLK_RIGHT;
	up			= SDLK_UP;
	down		= SDLK_DOWN;
	jump		= SDLK_SPACE;
	Save();
}

void CConfig::Save()
{
	char pre[] = "../data/game/config";
	char ext[] = ".key";

	/* filename character string must be long enough to contain:
	* pre[], or the file prefix;
	* + ext[], file suffix;
	* + 1 character for "\0"
	*/
	char* fconfig = new char[std::strlen(pre) + std::strlen(ext) + 1];

	std::strcpy(fconfig, pre);
	std::strcat(fconfig, ext);

	FILE* FileHandle = fopen(fconfig, "w");

	fprintf(FileHandle, "%d:%d:%d:%d:%d:%d:%d:%d", confirm, pause, select, left, right, up, down, jump);
//	fprintf(FileHandle, "%d:%d:%d:%d:%d:%d:%d", confirm, pause, left, right, up, down, jump);
	fclose(FileHandle);
	delete fconfig;
}
