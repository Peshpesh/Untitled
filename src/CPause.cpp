#include "CPause.h"

enum globopts
{
	RESUME = 0,
};
enum mainopts
{
	VIDEO = 1,
	AUDIO,
	GOTOMAIN,
};
enum quitopts
{
	QUIT = 1,
};

CPause::CPause()
{
	Active = false;
	Submit = false;
	Breakable = true;
	Quitgame = false;

	videomenu = false;
	audiomenu = false;
	quitmenu = false;

	options = NULL;
	Nops = 0;
	hilight = 0;
}

void CPause::OnInit()
{
	Active = false;
	Submit = false;
	Breakable = true;
	Quitgame = false;

	videomenu = false;
	audiomenu = false;
	quitmenu = false;

	options = "\
						%RESUME\
						\n%VIDEO\
						\n%AUDIO\
						\n%QUIT TO MAIN";
	Nops = 4;
	hilight = 0;
}

void CPause::MenuChange(char* opts)
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

void CPause::OnEvent(SDL_Keycode sym)
{
	if (sym == Config::ConfControl.confirm)
	{
		Submit = true;
	}
	if (sym == Config::ConfControl.left)
	{
		// defunct
	}
	if (sym == Config::ConfControl.right)
	{
		// defunct
	}
	if (sym == Config::ConfControl.down)
	{
		if (hilight == Nops - 1) hilight = 0;
		else hilight++;
	}
	if (sym == Config::ConfControl.up)
	{
		if (hilight == 0) hilight = Nops - 1;
		else hilight--;
	}
	if (sym == SDLK_ESCAPE)
	{
		Submit = true;
		hilight = RESUME;
	}
}

bool CPause::OnLoop()
{
	if (Submit)
	{
		if (quitmenu)	QuitMenuLoop();
		else if (videomenu)	VidMenuLoop();
		else if (audiomenu)	AudMenuLoop();
		else
		{
			switch (hilight)
			{
				case RESUME: Active = false; break;
				case VIDEO:
				{
					videomenu = true;
					MenuChange("%OK");
					break;
				}
				case AUDIO:
				{
					audiomenu = true;
					MenuChange("%OK");
					break;
				}
				case GOTOMAIN:
				{
					quitmenu = true;
					MenuChange("\
											%CANCEL\
											\n%QUIT TO MAIN");
					break;
				}
				default: break;
			}
			Submit = false;
			hilight = RESUME;
		}
	}
	return Active;
}

void CPause::VidMenuLoop()
{
	switch (hilight)
	{
		case RESUME:
		{
			videomenu = false;
			MenuChange("\
									%RESUME\
									\n%VIDEO\
									\n%AUDIO\
									\n%QUIT TO MAIN");
			break;
		}
		default: break;
	}
	Submit = false;
	hilight = RESUME;
}
void CPause::AudMenuLoop()
{
	switch (hilight)
	{
		case RESUME:
		{
			audiomenu = false;
			MenuChange("\
									%RESUME\
									\n%VIDEO\
									\n%AUDIO\
									\n%QUIT TO MAIN");
			break;
		}
		default: break;
	}
	Submit = false;
	hilight = RESUME;
}
void CPause::QuitMenuLoop()
{
	switch (hilight)
	{
		case RESUME:
		{
			quitmenu = false;
			MenuChange("\
									%RESUME\
									\n%VIDEO\
									\n%AUDIO\
									\n%QUIT TO MAIN");
			break;
		}
		case QUIT: Quitgame = true; quitmenu = false; Active = false; break;
		default: break;
	}
	Submit = false;
	hilight = RESUME;
}

int CPause::GetResponse()
{
	return hilight;
}

void CPause::OnRender(SDL_Renderer* renderer)
{
	Font::CenterBoxWrite(renderer, Font::FontControl.Tex_Font, options, 0, 0, 400, 200, 16, 256, 0);
	if (videomenu)
		Font::CenterWrite(renderer, Font::FontControl.Tex_Font, "VIDEO MENU IS NOT\nCURRENTLY ACTIVE", 200, 30);
	else if (audiomenu)
		Font::CenterWrite(renderer, Font::FontControl.Tex_Font, "AUDIO MENU IS NOT\nCURRENTLY ACTIVE", 200, 30);
	else if (quitmenu)
		Font::CenterWrite(renderer, Font::FontControl.Tex_Font, "ARE YOU SURE", 200, 30);
	Font::CenterWrite(renderer, Font::FontControl.Tex_Font, "X", 200, 110 + 20 * (hilight - (Nops / 2)));
}

void CPause::OnCleanup()
{

}
