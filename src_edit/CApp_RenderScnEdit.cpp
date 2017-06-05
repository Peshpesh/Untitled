#include "CApp.h"

using namespace scn_editor;

bool CApp::RenderSCNedit()
{
	if (Active_Mod == MODIFY_SCENE)
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 66, WWIDTH - 100 - 32, WHEIGHT - 34, 100, 34);
	else
		CSurface::OnDraw(Map_Renderer, Map_Interface, WWIDTH - 100 - 32, WHEIGHT + 66, WWIDTH - 100 - 32, 312, 100, 34);

	if (!CSurface::OnDraw(Map_Renderer, Map_Interface, scn_nm_x - ARROW_SIZE - SYM_SPACING, scn_nm_y, L_ARROW_XO, L_ARROW_YO, ARROW_SIZE, ARROW_SIZE)) return false;
	if (!CSurface::OnDraw(Map_Renderer, Map_Interface, scn_nm_x + scn_nm_w + SYM_SPACING, scn_nm_y, R_ARROW_XO, R_ARROW_YO, ARROW_SIZE, ARROW_SIZE)) return false;
	if (!CSceneryEdit::ScnControl.RenderName(Map_Renderer, FONT_DEFAULT, scn_nm_x, scn_nm_y)) return false;
	if (!RenderSCNswitch()) return false;
	if (!RenderSCNdepth()) return false;

	return true;
}

bool CApp::RenderSCNdepth()
{
	int Z_magnified = CSceneryEdit::ScnControl.Z * Z_MAGNIFIER;
	int truncator = Z_MAGNIFIER;
	int Xp = dp_adj::c_x;
	int Y_up = dp_adj::y - (CHAR_HEIGHT + SYM_SPACING);
	int Y_dw = dp_adj::y + CHAR_HEIGHT + SYM_SPACING;

	// print each digit of the magnified Z value
	while (truncator != 0)
	{
		int Z_display = (Z_magnified % (truncator * 10)) / truncator;
		Font::Write(Map_Renderer, FONT_DEFAULT, Z_display, Xp, dp_adj::y);
		CSurface::OnDraw(Map_Renderer, Map_Interface, Xp, Y_up, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
		CSurface::OnDraw(Map_Renderer, Map_Interface, Xp, Y_dw, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
		Xp += CHAR_WIDTH;
		truncator /= 10;
	}
	if (Active_Mod == REMOVE_SCENE)
	{
		truncator = Z_MAGNIFIER;
		int Zl_magnified = CSceneryEdit::ScnControl.Zl * Z_MAGNIFIER;
		int Zu_magnified = CSceneryEdit::ScnControl.Zu * Z_MAGNIFIER;
		int Xl = dp_adj::l_x;
		int Xu = dp_adj::u_x;
		while (truncator != 0)
		{
			int Zl_display = (Zl_magnified % (truncator * 10)) / truncator;
			int Zu_display = (Zu_magnified % (truncator * 10)) / truncator;
			Font::Write(Map_Renderer, FONT_DEFAULT, Zl_display, Xl, dp_adj::y);
			Font::Write(Map_Renderer, FONT_DEFAULT, Zu_display, Xu, dp_adj::y);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xl, Y_up, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xl, Y_dw, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xu, Y_up, U_ARROW_XO, U_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			CSurface::OnDraw(Map_Renderer, Map_Interface, Xu, Y_dw, D_ARROW_XO, D_ARROW_YO, ARROW_SIZE, ARROW_SIZE);
			Xl += CHAR_WIDTH; Xu += CHAR_WIDTH;
			truncator /= 10;
		}
	}
	return true;
}

bool CApp::RenderSCNswitch()
{
	if (!CSceneryEdit::ScnControl.hori_repeat)
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface, popt_flip::x, popt_flip::y, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
			return false;
	}
	else
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface, popt_flip::x, popt_flip::y, SWITCH_XO, ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
			return false;
	}
	Font::Write(Map_Renderer, FONT_DEFAULT, "HREP", popt_flip::x + SWITCH_SIZE + SYM_SPACING, popt_flip::y);
	if (!CSceneryEdit::ScnControl.vert_repeat)
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			popt_flip::x, popt_flip::y + SWITCH_SIZE + SYM_SPACING, SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	else
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			popt_flip::x, popt_flip::y + SWITCH_SIZE + SYM_SPACING, SWITCH_XO, ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	Font::Write(Map_Renderer, FONT_DEFAULT, "VREP", popt_flip::x + SWITCH_SIZE + SYM_SPACING, popt_flip::y + SWITCH_SIZE + SYM_SPACING);
	if (!CSceneryEdit::ScnControl.permanent)
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			popt_flip::x, popt_flip::y + (2*(SWITCH_SIZE + SYM_SPACING)), SWITCH_XO, OFF_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	else
	{
		if (!CSurface::OnDraw(Map_Renderer, Map_Interface,
			popt_flip::x, popt_flip::y + (2*(SWITCH_SIZE + SYM_SPACING)), SWITCH_XO, ON_SWITCH_YO, SWITCH_SIZE, SWITCH_SIZE))
		{
			return false;
		}
	}
	Font::Write(Map_Renderer, FONT_DEFAULT, "PERM", popt_flip::x + SWITCH_SIZE + SYM_SPACING, popt_flip::y + (2*(SWITCH_SIZE + SYM_SPACING)));
	return true;
}
