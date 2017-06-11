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
	if (sym == CConfig::ConfControl.confirm)
	{
	//	Freeze = false;
	//  Active = Breakable = false;
		Submit = true;
	//	options = NULL;
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
		if (hilight == Nops - 1)
			hilight = 0;
		else
			hilight++;
		return;
	}
	if (sym == CConfig::ConfControl.up)
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

void CMenu::OnRender()
{
	Font::CenterBoxWrite(FONT_DEFAULT, options, 0, 0, 400, 200, 16, 256, 0);
	Font::CenterWrite(FONT_DEFAULT, "X", 200, 110 + 20 * (hilight - (Nops / 2)));
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
