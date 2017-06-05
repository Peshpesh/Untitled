#include "CApp.h"

using namespace npc_editor;

bool CApp::RenderNPCedit()
{
	if (Active_Mod == MODIFY_NPC)
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 33, WWIDTH - 100 - 32, WHEIGHT - 67, 100, 33);
	else
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 33, WWIDTH - 100 - 32, WHEIGHT - 134, 100, 33);

	if (CEntityEdit::NPCControl.UseCommon)
		tabl_name_W = Font::Write(Map_Renderer, FONT_DEFAULT, "COMMON", tbl_nm_x, tbl_nm_y);
	else
		tabl_name_W = Font::Write(Map_Renderer, FONT_DEFAULT, "UNIQUE", tbl_nm_x, tbl_nm_y);

	CSurface::OnDraw(Map_Renderer, Map_Interface, tbl_nm_x - ARROW_SIZE - 5, tbl_nm_y, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
	CSurface::OnDraw(Map_Renderer, Map_Interface, tbl_nm_x + tabl_name_W + 5, tbl_nm_y, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE);

	// Draw working NPC name
	if (!CEntityEdit::NPCControl.CWrite_Name(Map_Renderer, FONT_DEFAULT, ent_nm_x, ent_nm_y))
		return false;

	// Print # of NPCs in the area
	Font::Write(Map_Renderer, FONT_DEFAULT, " NPCS", Font::Write(Map_Renderer, FONT_DEFAULT,
		CEntityEdit::NPCControl.EntityList.size(), 5, EHEIGHT - 20) + 5, EHEIGHT - 20);

	// Print "NPC Tables" crap-button
	CSurface::OnDraw(Map_Renderer, Map_Interface, but_nset::x, but_nset::y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	Font::Write(Map_Renderer, FONT_DEFAULT, "NPC TABLES", but_nset::x + SWITCH_SIZE + SYM_SPACING, but_nset::y);

	return true;
}
