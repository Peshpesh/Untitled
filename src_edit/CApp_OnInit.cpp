#include "CApp.h"

bool CApp::OnInit()
{
	// CEntity::EntityList.clear();
	CCamera::CameraControl.SetTarget(NULL, NULL);
	CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
	CCamera::CameraControl.SetPos(0, 0);

	if ((Map_Display = SDL_CreateWindow("TD Map Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		EWIDTH, EHEIGHT, SDL_WINDOW_SHOWN)) == NULL)
	{
		return false;
	}

	if ((Map_Renderer = SDL_CreateRenderer(Map_Display, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL)
	{
		return false;
	}

	if ((Map_Interface = CSurface::OnLoad("../res_edit/interface_plain.png", Map_Renderer)) == NULL)
	{
		return false;
	}

	// if ((Main_Tileset = CSurface::OnLoad(Tileset_Path, Map_Renderer, 155, 0, 255)) == NULL)
	if ((Main_Tileset = CSurface::OnLoad(Tileset_Path, Map_Renderer)) == NULL)
	{
		return false;
	}

	int PixWidth, PixHeight;
	SDL_QueryTexture(Main_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	TilesetWidth = PixWidth / TILE_SIZE;
	TilesetHeight = PixHeight / TILE_SIZE;

	if ((Type_Tileset = CSurface::OnLoad("../res_edit/types.png", Map_Renderer)) == NULL)
	{
		return false;
	}

	SDL_QueryTexture(Type_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	TypesetWidth = PixWidth / TILE_SIZE;
	TypesetHeight = PixHeight / TILE_SIZE;

	if ((Slope_Tileset = CSurface::OnLoad("../res_edit/slopes.png", Map_Renderer)) == NULL)
	{
		return false;
	}

	SDL_QueryTexture(Slope_Tileset, NULL, NULL, &PixWidth, &PixHeight);

	SlopesetWidth = PixWidth / TILE_SIZE;
	SlopesetHeight = PixHeight / TILE_SIZE;

	// if ((Font = CSurface::OnLoad("../res/font.png", Map_Renderer)) == NULL)
	// {
	// 	return false;
	// }
	if (!Font::FontControl.OnInit(Map_Renderer))
	{
		return false;
	}

	if ((CEntityEdit::NPCControl.NPC_Tileset = CSurface::OnLoad(Entity_Path, Map_Renderer)) == NULL)
	{
		return false;
	}

	if ((CEntityEdit::NPCControl.NPC_Common = CSurface::OnLoad("../res/npc/common.png", Map_Renderer)) == NULL)
	{
		return false;
	}

	// CHUD::HUDControl.OnInit(Map_Renderer);

	// if ((CEntityEdit::NPCControl.Table_ID = CEntityInfo::OnLoad("../res/npc/debug.tbl")) < 0)
	// 	return false;

	if (!CEntityInfo::LoadCommon())
		return false;

	if ((CEntityEdit::NPCControl.Table_ID = CEntityInfo::LoadUnique("../res/npc/debug.tbl")) < 0)
		return false;

	if (CArea::AreaControl.OnLoad(Main_Tileset) == false)
		return false;

	return true;
}
