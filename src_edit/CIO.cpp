#include "CIO.h"

CIO CIO::IOControl;
int CIO::symbolnum = 0;

CIO::CIO()
{
	UI_Width = 300;
	UI_Height = 100;
}

char* CIO::OnSave(SDL_Texture* map_ui)
{
	Running = true;
	SDL_Event Event;
	while (Running)
	{
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		// SDL_RenderClear(renderer);
		CSurface::Clear();
		CSurface::OnDraw(map_ui, (WWIDTH - UI_Width) / 2, (WHEIGHT - UI_Height) / 2,
			0, WHEIGHT - UI_Height, UI_Width, UI_Height);
		Font::CenterWrite(FONT_DEFAULT, "ENTER AN AREANAME", WWIDTH / 2, ((WHEIGHT - UI_Height) / 2) + 16);
		Font::Write(FONT_DEFAULT, Areaname, ((WWIDTH - UI_Width) / 2) + 10, ((WHEIGHT - UI_Height) / 2) + 32);
		// SDL_RenderPresent(renderer);
		CSurface::Present();
	}

	return Areaname;
}

bool CIO::OnLoad(SDL_Texture* map_ui, char* &setpath)
{
	Running = true;
	SDL_Event Event;
	while (Running)
	{
		while (SDL_PollEvent(&Event))
		{
			OnEvent(&Event);
		}

		// SDL_RenderClear(renderer);
		CSurface::Clear();
		CSurface::OnDraw(map_ui, (WWIDTH - UI_Width) / 2, (WHEIGHT - UI_Height) / 2,
			0, WHEIGHT - UI_Height, UI_Width, UI_Height);
		Font::CenterWrite(FONT_DEFAULT, "ENTER AREANAME TO LOAD", WWIDTH / 2, ((WHEIGHT - UI_Height) / 2) + 16);
		Font::Write(FONT_DEFAULT, Areaname, ((WWIDTH - UI_Width) / 2) + 10, ((WHEIGHT - UI_Height) / 2) + 32);
		// SDL_RenderPresent(renderer);
		CSurface::Present();
	}
	char pre[] = "../data/maps/";
	char ext[] = ".area";
	char* filename = new char[std::strlen(Areaname) + std::strlen(pre) + std::strlen(ext) + 1];
	std::strcpy(filename, pre);
	std::strcat(filename, Areaname);
	std::strcat(filename, ext);

	FILE* AFileHandle = fopen(filename, "r");
	if (AFileHandle == NULL)
		return false;

	CArea::AreaControl.OnLoad(filename);

	fscanf(AFileHandle, "%s\n", TilesetPath);

	fclose(AFileHandle);

	setpath = TilesetPath;

	if (!CEntityEdit::NPCControl.LoadList(Areaname))
		return false;

	char scnext[] = ".scn";
	char* scnfile = new char[std::strlen(Areaname) + std::strlen(pre) + std::strlen(scnext) + 1];
	std::strcpy(filename, pre);
	std::strcat(filename, Areaname);
	std::strcat(filename, scnext);
	if (!CSceneryEdit::ScnControl.LoadScenery(filename))
		return false;

	delete filename;
	delete scnfile;

	return true;
}

void CIO::OnEvent(SDL_Event* Event)
{
	CEvent::OnEvent(Event);
}

void CIO::OnKeyDown(SDL_Keycode sym, Uint16 mod)
{
	if (symbolnum < 15)
	{
		switch (sym)
		{
		case SDLK_0:		Areaname[symbolnum++] = '0'; break;
		case SDLK_1:		Areaname[symbolnum++] = '1'; break;
		case SDLK_2:		Areaname[symbolnum++] = '2'; break;
		case SDLK_3:		Areaname[symbolnum++] = '3'; break;
		case SDLK_4:		Areaname[symbolnum++] = '4'; break;
		case SDLK_5:		Areaname[symbolnum++] = '5'; break;
		case SDLK_6:		Areaname[symbolnum++] = '6'; break;
		case SDLK_7:		Areaname[symbolnum++] = '7'; break;
		case SDLK_8:		Areaname[symbolnum++] = '8'; break;
		case SDLK_9:		Areaname[symbolnum++] = '9'; break;
		case SDLK_a:		Areaname[symbolnum++] = 'A'; break;
		case SDLK_b:		Areaname[symbolnum++] = 'B'; break;
		case SDLK_c:		Areaname[symbolnum++] = 'C'; break;
		case SDLK_d:		Areaname[symbolnum++] = 'D'; break;
		case SDLK_e:		Areaname[symbolnum++] = 'E'; break;
		case SDLK_f:		Areaname[symbolnum++] = 'F'; break;
		case SDLK_g:		Areaname[symbolnum++] = 'G'; break;
		case SDLK_h:		Areaname[symbolnum++] = 'H'; break;
		case SDLK_i:		Areaname[symbolnum++] = 'I'; break;
		case SDLK_j:		Areaname[symbolnum++] = 'J'; break;
		case SDLK_k:		Areaname[symbolnum++] = 'K'; break;
		case SDLK_l:		Areaname[symbolnum++] = 'L'; break;
		case SDLK_m:		Areaname[symbolnum++] = 'M'; break;
		case SDLK_n:		Areaname[symbolnum++] = 'N'; break;
		case SDLK_o:		Areaname[symbolnum++] = 'O'; break;
		case SDLK_p:		Areaname[symbolnum++] = 'P'; break;
		case SDLK_q:		Areaname[symbolnum++] = 'Q'; break;
		case SDLK_r:		Areaname[symbolnum++] = 'R'; break;
		case SDLK_s:		Areaname[symbolnum++] = 'S'; break;
		case SDLK_t:		Areaname[symbolnum++] = 'T'; break;
		case SDLK_u:		Areaname[symbolnum++] = 'U'; break;
		case SDLK_v:		Areaname[symbolnum++] = 'V'; break;
		case SDLK_w:		Areaname[symbolnum++] = 'W'; break;
		case SDLK_x:		Areaname[symbolnum++] = 'X'; break;
		case SDLK_y:		Areaname[symbolnum++] = 'Y'; break;
		case SDLK_z:		Areaname[symbolnum++] = 'Z'; break;

		case SDLK_BACKSPACE:
		{
							   if (symbolnum > 0)
								   Areaname[--symbolnum] = '\0';
							   break;
		}
		case SDLK_RETURN:
		{
							Running = false;
							break;
		}
		default: break;
		}
	}
	else
	{
		switch (sym)
		{
			case SDLK_BACKSPACE:
			{
							   if (symbolnum > 0)
								   Areaname[--symbolnum] = '\0';
							   break;
			}
			case SDLK_RETURN:
			{
							Running = false;
							break;
			}
			default: break;
		}
	}
}
