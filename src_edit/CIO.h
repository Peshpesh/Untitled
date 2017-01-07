#ifndef _C_IO_H_
#define _C_IO_H_

#include "CEntityEdit.h"
#include "CSurface.h"
#include "CEvent.h"
#include "CArea.h"
#include "Define.h"
#include "Font.h"
#include <cstring>
#include "CSceneryEdit.h"

class CIO : public CEvent
{
public:
	static CIO		IOControl;

	static int symbolnum;
	int UI_Width;
	int UI_Height;

	char Areaname[16];
	char TilesetPath[255];

private:
	bool Running;

public:
	CIO();

	char* OnSave(SDL_Renderer* renderer, SDL_Texture* map_ui, SDL_Texture* font);
	bool OnLoad(SDL_Renderer* renderer, SDL_Texture* map_ui, SDL_Texture* font, char* &setpath);

	void OnEvent(SDL_Event* Event);

	void OnKeyDown(SDL_Keycode sym, Uint16 mod);
};

#endif
