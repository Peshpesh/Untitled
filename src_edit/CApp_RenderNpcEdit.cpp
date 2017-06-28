#include "CApp.h"

using namespace npc_editor;

bool CApp::RenderNPCedit()
{
	if (CEntityEdit::NPCControl.UseCommon)
		tabl_name_W = Font::Write(FONT_DEFAULT, "COMMON", tbl_nm_x, tbl_nm_y);
	else
		tabl_name_W = Font::Write(FONT_DEFAULT, "UNIQUE", tbl_nm_x, tbl_nm_y);

	// CSurface::OnDraw(Map_Interface, tbl_nm_x - ARR_SZ - 5, tbl_nm_y, L_ARR_X, L_ARR_Y, ARR_SZ, ARR_SZ);
	// CSurface::OnDraw(Map_Interface, tbl_nm_x + tabl_name_W + 5, tbl_nm_y, R_ARR_X, R_ARR_Y, ARR_SZ, ARR_SZ);

	// Draw working NPC name
	if (!CEntityEdit::NPCControl.CWrite_Name(FONT_DEFAULT, ent_nm_x, ent_nm_y))
		return false;

	// Print # of NPCs in the area
	Font::Write(FONT_DEFAULT, " NPCS", Font::Write(FONT_DEFAULT,
		CEntityEdit::NPCControl.EntityList.size(), 5, EHEIGHT - 20) + 5, EHEIGHT - 20);

	// Print "NPC Tables" crap-button
	// CSurface::OnDraw(Map_Interface, but_nset::x, but_nset::y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE);
	Font::Write(FONT_DEFAULT, "NPC TABLES", but_nset::x + SWITCH_SIZE + SYM_SPACING, but_nset::y);

	return true;
}
