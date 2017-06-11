#include "CApp.h"

using namespace scn_editor;

bool CApp::EventSCNedit(int mX, int mY)
{
	if (mX < WWIDTH && mY < WHEIGHT)
	{
		// add or subtract scenery objects...
		if (active_mod == MODIFY_SCENE)
		{
			// add object
			CSceneryEdit::ScnControl.AddObject(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
		else
		{
			// remove object
			CSceneryEdit::ScnControl.SubObject(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
	}
	else
	{
		if (mY >= scn_nm_y && mY < scn_nm_y + CHAR_HEIGHT)
		{
			// The Y-range overlaps the scenery name display.
			// A click may have been over the arrow keys to change scenery.
			if (CheckSCNchange(mX)) return true;
		}
		if (mY >= dp_adj::y - (ARR_SZ + SYM_SPACING) && mY < dp_adj::y - SYM_SPACING)
		{
			// The Y-range satisfied overlaps the up-arrow buttons.
			// We check to see if any of those buttons were pressed.
			if (CheckZup(mX)) return true;
		}
		if (mY >= dp_adj::y + CHAR_HEIGHT + SYM_SPACING && mY < dp_adj::y + CHAR_HEIGHT + SYM_SPACING + ARR_SZ)
		{
			// The Y-range satisfied overlaps the down-arrow buttons.
			// We check to see if any of those buttons were pressed.
			if (CheckZdown(mX)) return true;
		}
		if (mX >= popt_flip::x && mX < popt_flip::x + SWITCH_SIZE)
		{
			// The X-range satisfied overlaps the scenery switches.
			// We check to see if any switches were flipped.
			if (CheckSCNswitch(mY)) return true;
		}
	}
	return true;
}

bool CApp::CheckZup(const int& mX)
{
	if (mX >= dp_adj::c_x && mX < dp_adj::c_x + (Z_PRECISION * CHAR_WIDTH))
	{
		// ... middle up arrows pressed
		float Z_inc = GetZincrement(mX, dp_adj::c_x);
		CSceneryEdit::ScnControl.Z += Z_inc;
		return true;
	}
	if (active_mod == REMOVE_SCENE)
	{
		if (mX >= dp_adj::l_x && mX < dp_adj::l_x + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... left up arrows pressed
			float Z_inc = GetZincrement(mX, dp_adj::l_x);
			if (CSceneryEdit::ScnControl.Zl + Z_inc < CSceneryEdit::ScnControl.Zu)
				CSceneryEdit::ScnControl.Zl += Z_inc;
			return true;
		}
		if (mX >= dp_adj::u_x && mX < dp_adj::u_x + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... right up arrows pressed
			float Z_inc = GetZincrement(mX, dp_adj::u_x);
			CSceneryEdit::ScnControl.Zu += Z_inc;
			return true;
		}
	}
	return false;
}

bool CApp::CheckZdown(const int& mX)
{
	if (mX >= dp_adj::c_x && mX < dp_adj::c_x + (Z_PRECISION * CHAR_WIDTH))
	{
		// ... middle dw arrows pressed
		float Z_inc = GetZincrement(mX, dp_adj::c_x);
		if (CSceneryEdit::ScnControl.Z > Z_inc) CSceneryEdit::ScnControl.Z -= Z_inc;
		return true;
	}
	if (active_mod == REMOVE_SCENE)
	{
		if (mX >= dp_adj::l_x && mX < dp_adj::l_x + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... left dw arrows pressed
			float Z_inc = GetZincrement(mX, dp_adj::l_x);
			if (CSceneryEdit::ScnControl.Zl > Z_inc) CSceneryEdit::ScnControl.Zl -= Z_inc;
			return true;
		}
		if (mX >= dp_adj::u_x && mX < dp_adj::u_x + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... right dw arrows pressed
			float Z_inc = GetZincrement(mX, dp_adj::u_x);
			if (CSceneryEdit::ScnControl.Zu - Z_inc > CSceneryEdit::ScnControl.Zl)
				CSceneryEdit::ScnControl.Zu -= Z_inc;
			return true;
		}
	}
	return false;
}

float CApp::GetZincrement(const int& mX, const int& Xo)
{
	float val = 1.0f;
	int ArrowID = (mX - Xo) / CHAR_WIDTH;
	for (int i = 0; i < ArrowID; i++)
	{
		val /= 10.0;
	}
	return val;
}

bool CApp::CheckSCNswitch(const int& mY)
{
	int Yi = popt_flip::y;
	int Yf = popt_flip::y + SWITCH_SIZE;
	if (mY >= Yi && mY < Yf)
	{
		if (!CSceneryEdit::ScnControl.hori_repeat) CSceneryEdit::ScnControl.hori_repeat = true;
		else CSceneryEdit::ScnControl.hori_repeat = false;
		return true;
	}
	Yi += SWITCH_SIZE + SYM_SPACING;
	Yf += SWITCH_SIZE + SYM_SPACING;
	if (mY >= Yi && mY < Yf)
	{
		if (!CSceneryEdit::ScnControl.vert_repeat) CSceneryEdit::ScnControl.vert_repeat = true;
		else CSceneryEdit::ScnControl.vert_repeat = false;
		return true;
	}
	Yi += SWITCH_SIZE + SYM_SPACING;
	Yf += SWITCH_SIZE + SYM_SPACING;
	if (mY >= Yi && mY < Yf)
	{
		if (!CSceneryEdit::ScnControl.permanent) CSceneryEdit::ScnControl.permanent = true;
		else CSceneryEdit::ScnControl.permanent = false;
		return true;
	}
	return false;
}

bool CApp::CheckSCNchange(const int& mX)
{
	if (mX >= scn_nm_x - ARR_SZ - SYM_SPACING && mX < scn_nm_x - SYM_SPACING)
	{
		// left arrow clicked...
		CSceneryEdit::ScnControl.SwitchObj(CSceneryEdit::ScnControl.scn_ID - 1);
		return true;
	}
	if (mX >= scn_nm_x + scn_nm_w + SYM_SPACING && mX < scn_nm_x + scn_nm_w + SYM_SPACING + ARR_SZ)
	{
		// right arrow clicked...
		CSceneryEdit::ScnControl.SwitchObj(CSceneryEdit::ScnControl.scn_ID + 1);
		return true;
	}
	return false;
}
