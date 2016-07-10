#ifndef _CMEUI_H_
#define _CMEUI_H_

#include "CSurface.h"
#include "CEvent.h"
#include "Define.h"
#include "Font.h"
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

class CMEUI : public CEvent {
public:
	static CMEUI		UIControl;

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
	CMEUI();

	SDL_Texture* OnChange(SDL_Renderer* renderer, SDL_Texture* map_ui, SDL_Texture* font, char* &setpath);
	int OnEntity(SDL_Renderer* renderer, SDL_Texture* map_ui, SDL_Texture* font);

	bool OnWindow(SDL_Renderer* renderer, SDL_Texture* map_ui, SDL_Texture* font, int type);

	void OnEvent(SDL_Event* Event);

	void OnExit();

	SDL_Texture* ChangeSet(SDL_Renderer* renderer, int setname, char* &setpath);

	//void OnLoad();

	//void OnSave();

	void OnCleanup();

	void OnLButtonDown(int mX, int mY);
};

#endif