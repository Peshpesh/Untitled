#ifndef _CPAUSE_H_
#define _CPAUSE_H_

#include "CMenu.h"

class CPause : public CMenu
{
public:
	bool Quitgame;

private:
	bool videomenu;
	bool audiomenu;
	bool quitmenu;

public:
	CPause();

	void	OnInit();

	void	MenuChange(char* opts);

	void	OnEvent(SDL_Keycode sym);

	bool	OnLoop();
	void	VidMenuLoop();
	void	AudMenuLoop();
	void	QuitMenuLoop();

	int		GetResponse();

	void	OnRender(SDL_Renderer* renderer);

	void	OnCleanup();
};
#endif
