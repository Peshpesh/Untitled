#include "CMapEdit.h"
#include "CHUD.h"

void CMapEdit::OnRender()
{
	SDL_RenderClear(Map_Renderer);

	// Draw the working area
	CArea::AreaControl.OnRender(Map_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), false);
	CArea::AreaControl.OnRender(Map_Renderer, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY(), true);
	CArea::AreaControl.OnRenderType(Map_Renderer, Type_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());
	CArea::AreaControl.OnRenderSlope(Map_Renderer, Slope_Tileset, -CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

	// Draw the entities in the area
	for (int i = 0; i < CME_NPC::NPCControl.EntityList.size(); i++)
	{
		if (&CME_NPC::NPCControl.EntityList[i] == NULL) continue;
		CME_NPC::NPCControl.EntityList[i].OnRender(Map_Renderer);
	}

	// Draws the surrounding interface containing current info and accessible buttons
	CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH, 0, WWIDTH, 0, EWIDTH - WWIDTH, EHEIGHT);
	CSurface::OnDraw(Map_Renderer, Map_Interface, 0, WHEIGHT, 0, WHEIGHT, EWIDTH, EHEIGHT - WHEIGHT);

	switch (Active_Mod)
	{
	case MODIFY_MAP:
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT, WWIDTH - 100 - 32, WHEIGHT - 100, 100, 33);
		break;
	}
	case MODIFY_NPC:
	{
	  CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 33, WWIDTH - 100 - 32, WHEIGHT - 67, 100, 33);
	  break;
	}
	case REMOVE_NPC:
	{
	  CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 33, WWIDTH - 100 - 32, WHEIGHT - 134, 100, 33);
		break;
	}
	case MODIFY_BG:
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 66, WWIDTH - 100 - 32, WHEIGHT - 34, 100, 34);
		break;
	}
	default: break;
	}

	if (Active_Mod == MODIFY_NPC || Active_Mod == REMOVE_NPC)
	{
		if (CME_NPC::NPCControl.UseCommon)
			tabl_name_W = Font::Write(Map_Renderer, Font, "COMMON", TABL_NAME_X, TABL_NAME_Y);
		else
			tabl_name_W = Font::Write(Map_Renderer, Font, "UNIQUE", TABL_NAME_X, TABL_NAME_Y);

		CSurface::OnDraw(Map_Renderer, Map_Interface, TABL_NAME_X - ARROW_SIZE - 5, TABL_NAME_Y, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
		CSurface::OnDraw(Map_Renderer, Map_Interface, TABL_NAME_X + tabl_name_W + 5, TABL_NAME_Y, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

		// Draw working NPC name
		if (!CME_NPC::NPCControl.CWrite_Name(Map_Renderer, Font, ENT_NAME_X, ENT_NAME_Y))
			OnExit();

		// Print # of NPCs in the area
		Font::Write(Map_Renderer, Font, " NPCS", Font::Write(Map_Renderer, Font,
			CME_NPC::NPCControl.EntityList.size(), 5, EHEIGHT - 20) + 5, EHEIGHT - 20);

		// Print "NPC Tables" crap-button
		Font::Write(Map_Renderer, Font, "NPC TABLES", 5, EHEIGHT - 40);
	}

	// Write a button name for changing tiles within a tileset
	Font::CenterWrite(Map_Renderer, Font, "CHANGE", EWIDTH - 50, 50);
	Font::CenterWrite(Map_Renderer, Font, "TILE", EWIDTH - 50, 66);

	// Draw the active tileset, tiles, and type.
	// Draws active tile
	CSurface::OnDraw(Map_Renderer, Main_Tileset, EWIDTH - (50 + TILE_SIZE / 2), 275,
		(Current_Tile % TilesetWidth) * TILE_SIZE,
		(Current_Tile / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile before active tile
	if (Current_Tile != 0)
		CSurface::OnDraw(Map_Renderer, Main_Tileset, EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE, 275,
		((Current_Tile - 1) % TilesetWidth) * TILE_SIZE,
		((Current_Tile - 1) / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws tile after active tile
	if (Current_Tile != TilesetWidth * TilesetHeight - 1)
		CSurface::OnDraw(Map_Renderer, Main_Tileset, EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE, 275,
		((Current_Tile + 1) % TilesetWidth) * TILE_SIZE,
		((Current_Tile + 1) / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draw active foreground tile on top of active tile
	if (Current_Fore != 0)
	{
		CSurface::OnDraw(Map_Renderer, Main_Tileset, EWIDTH - (50 + TILE_SIZE / 2), 275,
			(Current_Fore % TilesetWidth) * TILE_SIZE,
			(Current_Fore / TilesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);
	}

	// Draws active type
	CSurface::OnDraw(Map_Renderer, Type_Tileset, EWIDTH - (50 + TILE_SIZE / 2), 405,
		(Current_Type % TypesetWidth) * TILE_SIZE,
		(Current_Type / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws type before active type
	if (Current_Type != TILE_TYPE_NONE)
		CSurface::OnDraw(Map_Renderer, Type_Tileset, EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE, 405,
		((Current_Type - 1) % TypesetWidth) * TILE_SIZE,
		((Current_Type - 1) / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws type after active type
	if (Current_Type != TILE_TYPE_FIRE)
		CSurface::OnDraw(Map_Renderer, Type_Tileset, EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE, 405,
		((Current_Type + 1) % TypesetWidth) * TILE_SIZE,
		((Current_Type + 1) / TypesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Writes out the active type
	switch (Current_Type)
	{
		case TILE_TYPE_NONE: Font::CenterWrite(Map_Renderer, Font, "NONE", EWIDTH - 50, 447); break;
		case TILE_TYPE_HOLLOW: Font::CenterWrite(Map_Renderer, Font, "HOLLO", EWIDTH - 50, 447); break;
		case TILE_TYPE_NORMAL: Font::CenterWrite(Map_Renderer, Font, "NORM", EWIDTH - 50, 447); break;
		case TILE_TYPE_BLOCK: Font::CenterWrite(Map_Renderer, Font, "BLOCK", EWIDTH - 50, 447); break;
		case TILE_TYPE_WATER: Font::CenterWrite(Map_Renderer, Font, "WATER", EWIDTH - 50, 447); break;
		case TILE_TYPE_ICE: Font::CenterWrite(Map_Renderer, Font, "ICE", EWIDTH - 50, 447); break;
		case TILE_TYPE_FIRE: Font::CenterWrite(Map_Renderer, Font, "FIRE", EWIDTH - 50, 447); break;
		default: break;
	}

	// Draws active slope
	if (Current_Slope != SLOPE_FLAT)
		CSurface::OnDraw(Map_Renderer, Slope_Tileset, EWIDTH - (50 + TILE_SIZE / 2), 320,
			((Current_Slope - 1) % SlopesetWidth) * TILE_SIZE,
			((Current_Slope - 1) / SlopesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws slope before active slope
	if (Current_Slope > SLOPE_FLAT + 1)
		CSurface::OnDraw(Map_Renderer, Slope_Tileset, EWIDTH - (50 + TILE_SIZE / 2) - TILE_SIZE, 320,
		((Current_Slope - 2) % SlopesetWidth) * TILE_SIZE,
		((Current_Slope - 2) / SlopesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Draws slope after active slope
	if (Current_Slope != STEEP_DSCE)
		CSurface::OnDraw(Map_Renderer, Slope_Tileset, EWIDTH - (50 + TILE_SIZE / 2) + TILE_SIZE, 320,
		((Current_Slope) % SlopesetWidth) * TILE_SIZE,
		((Current_Slope) / SlopesetWidth) * TILE_SIZE, TILE_SIZE, TILE_SIZE);

	// Writes out the active slope
	switch (Current_Slope)
	{
	case SLOPE_FLAT: Font::CenterWrite(Map_Renderer, Font, "FLAT", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_ASC: Font::CenterWrite(Map_Renderer, Font, "ASC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_ASCE: Font::CenterWrite(Map_Renderer, Font, "ASCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_DSC: Font::CenterWrite(Map_Renderer, Font, "DSC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case SLOPE_DSCE: Font::CenterWrite(Map_Renderer, Font, "DSCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_ASC: Font::CenterWrite(Map_Renderer, Font, "SASC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_DSC: Font::CenterWrite(Map_Renderer, Font, "SDSC", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_ASCE: Font::CenterWrite(Map_Renderer, Font, "SASCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	case STEEP_DSCE: Font::CenterWrite(Map_Renderer, Font, "SDSCE", EWIDTH - 50, 320 + TILE_SIZE + 8); break;
	default: break;
	}

	// if (CME_NPC::NPCControl.UseCommon)
	// 	Font::CenterWrite(Map_Renderer, Font, "COMMON", WWIDTH / 2, EHEIGHT - 85);
	// else
	// 	Font::CenterWrite(Map_Renderer, Font, "UNIQUE", WWIDTH / 2, EHEIGHT - 85);
	//
	// // Draw working NPC name
	// if (!CME_NPC::NPCControl.CWrite_Name(Map_Renderer, Font, WWIDTH / 2, EHEIGHT - 65))
	// 	OnExit();
	//
	// // Print # of NPCs in the area
	// Font::Write(Map_Renderer, Font, " NPCS", Font::Write(Map_Renderer, Font,
	// 	CME_NPC::NPCControl.EntityList.size(), 5, EHEIGHT - 20) + 5, EHEIGHT - 20);
	//
	// // Print "NPC Tables" crap-button
	// Font::Write(Map_Renderer, Font, "NPC TABLES", 5, EHEIGHT - 40);

	int tX = -CCamera::CameraControl.GetX() + (32 * (mouseX / 32));
	int tY = -CCamera::CameraControl.GetY() + (32 * (mouseY / 32));
	if (mouseX < 0)
	{
		tX -= 32;
	}
	if (mouseY < 0)
	{
		tY -= 32;
	}

	if (mouseX != -404404 && mouseY != -404404)
	{
		CSurface::OnDraw(Map_Renderer, Map_Interface, tX, tY, 300, 448, 32, 32);
	}

	SDL_RenderPresent(Map_Renderer);
}
