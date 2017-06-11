#ifndef _C_UI_H_
#define _C_UI_H_

#include "CSurface.h"
#include "CEvent.h"
#include "Define.h"
#include "CFont.h"
#include <vector>

enum
{
	TILESET_DEF = 0,
	TILESET_FOREST,
	TILESET_CAVE
};

enum
{
	ENTITY_DEBUG = 0
};

enum
{
	TILESET = 0,
	ENTITY
};

class CUI : public CEvent {
public:
	static CUI		UIControl;

	std::vector<int>	Title_Length;

	Uint8				New_Tileset;

	int					UI_Width;
	int					UI_Height;
	int					Px;
	int					Py;
	Uint8				Current_Set;
	int					Current_Table;


private:
	bool Running;

	int Window_Type;

public:
	CUI();

	SDL_Texture* OnChange(SDL_Texture* map_ui, char* &setpath);
	int OnEntity(SDL_Texture* map_ui);

	bool OnWindow(SDL_Texture* map_ui, int type);

	void OnEvent(SDL_Event* Event);

	void OnExit();

	SDL_Texture* ChangeSet(int setname, char* &setpath);

	//void OnLoad();

	//void OnSave();

	void OnCleanup();

	void OnLButtonDown(int mX, int mY);
};

#endif
