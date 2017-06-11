#include "CApp.h"

bool CApp::OnInit()
{
	CCamera::CameraControl.SetTarget(NULL, NULL);
	CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
	CCamera::CameraControl.SetPos(0, 0);

	if ((Map_Display = SDL_CreateWindow("Map Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		EWIDTH, EHEIGHT, SDL_WINDOW_SHOWN)) == NULL)
	{
		return false;
	}

	if (!CSurface::SurfControl.OnInit(Map_Display))
	{
		return false;
	}

	if ((Map_Interface = CSurface::OnLoad("../res_edit/interface_plain.png")) == NULL)
	{
		return false;
	}

	if ((Main_Tileset = CSurface::OnLoad(Tileset_Path)) == NULL)
	{
		return false;
	}

	int PixWidth, PixHeight;
	SDL_QueryTexture(Main_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	tset_w = PixWidth / TILE_SIZE;
	tset_h = PixHeight / TILE_SIZE;

	if ((Type_Tileset = CSurface::OnLoad("../res_edit/types.png")) == NULL)
	{
		return false;
	}
	SDL_SetTextureAlphaMod(Type_Tileset, type_alpha);

	SDL_QueryTexture(Type_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	type_w = PixWidth / TILE_SIZE;
	type_h = PixHeight / TILE_SIZE;

	if ((Coll_Tileset = CSurface::OnLoad("../res_edit/slopes.png")) == NULL)
	{
		return false;
	}
	SDL_SetTextureAlphaMod(Coll_Tileset, coll_alpha);

	SDL_QueryTexture(Coll_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	coll_w = PixWidth / TILE_SIZE;
	coll_h = PixHeight / TILE_SIZE;

	if (!Font::FontControl.OnInit())
	{
		return false;
	}

	if ((CEntityEdit::NPCControl.NPC_Tileset = CSurface::OnLoad(Entity_Path)) == NULL)
	{
		return false;
	}

	if ((CEntityEdit::NPCControl.NPC_Common = CSurface::OnLoad("../res/npc/common.png")) == NULL)
	{
		return false;
	}

	if (!CEntityInfo::LoadCommon())
		return false;

	if ((CEntityEdit::NPCControl.Table_ID = CEntityInfo::LoadUnique("../res/npc/debug.tbl")) < 0)
		return false;

	if (CArea::AreaControl.OnLoad(Main_Tileset) == false)
		return false;

	if (CEditMap::MapEditor.OnInit() == false)
		return false;

	return true;
}

void CApp::QueryTileset()
{
	int PixWidth, PixHeight;
	SDL_QueryTexture(Main_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	tset_w = PixWidth / TILE_SIZE;
	tset_h = PixHeight / TILE_SIZE;
}
