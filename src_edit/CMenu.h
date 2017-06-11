#ifndef _CMENU_H_
#define _CMENU_H_

#include <vector>
#include "CFont.h"
#include "CConfig.h"

class CMenu
{
public:
	static std::vector<CMenu*>	MenuList;

public:
	bool Active;
	bool Submit;
//	bool Freeze;
	bool Breakable;
	bool Break;

protected:
	char*			options;
	unsigned short	Nops;
	unsigned short	hilight;

public:
	CMenu();

	virtual ~CMenu();

public:
	virtual void	OnInit(char* opts);

	virtual void	OnEvent(SDL_Keycode sym);

	virtual bool	OnLoop();

	virtual int		GetResponse();

	virtual void	OnRender();

	virtual void	OnCleanup();
};

#endif
