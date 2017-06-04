#include "CMenu.h"

std::vector<CMenu*> CMenu::MenuList;

CMenu::CMenu()
{
	Active = false;
//	Freeze = false;
	Breakable = false;
	Break = false;
	Submit = false;
	options = NULL;
	Nops = 0;
	hilight = 0;
}

CMenu::~CMenu()
{

}

void CMenu::OnInit(char* opts)
{
	Nops = 0;
	hilight = 0;
	int i = 0;
	options = opts;

	while (options[i] != '\0')
	{
		if (options[i] == '%') Nops++;
		i++;
	}
}

void CMenu::OnEvent(SDL_Keycode sym)
{
	if (sym == Config::ConfControl.confirm)
	{
	//	Freeze = false;
	//  Active = Breakable = false;
		Submit = true;
	//	options = NULL;
		return;
	}
	if (sym == Config::ConfControl.left)
	{
		return;
	}
	if (sym == Config::ConfControl.right)
	{
		return;
	}
	if (sym == Config::ConfControl.down)
	{
		if (hilight == Nops - 1)
			hilight = 0;
		else
			hilight++;
		return;
	}
	if (sym == Config::ConfControl.up)
	{
		if (hilight == 0)
			hilight = Nops - 1;
		else
			hilight--;
		return;
	}
	if (sym == SDLK_ESCAPE)
	{
		if (Breakable){
		//	Freeze = false;
		//	Active = Breakable = false;
			Break = true;
		}
		return;
	}
}

bool CMenu::OnLoop()
{
	return true;
}

int CMenu::GetResponse()
{
	return hilight;
}

void CMenu::OnRender(SDL_Renderer* renderer)
{
	Font::CenterBoxWrite(renderer, FONT_DEFAULT, options, 0, 0, 400, 200, 16, 256, 0);
	Font::CenterWrite(renderer, FONT_DEFAULT, "X", 200, 110 + 20 * (hilight - (Nops / 2)));
}

void CMenu::OnCleanup()
{
	Active = false;
//	Freeze = false;
	Breakable = false;
	options = NULL;
	Nops = 0;
	hilight = 0;
}
