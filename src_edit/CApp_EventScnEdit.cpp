#include "CApp.h"

bool CApp::EventSCNedit(int mX, int mY)
{
	if (mX < WWIDTH && mY < WHEIGHT)
	{
		// add or subtract scenery objects...
		if (Active_Mod == MODIFY_SCENE)
		{
			// add object
			CSceneryEdit::ScnControl.AddObject(Map_Renderer, mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
		else
		{
			// remove object
			CSceneryEdit::ScnControl.SubObject(mX + CCamera::CameraControl.GetX(), mY + CCamera::CameraControl.GetY());
		}
	}
	else
	{
		if (mY >= SCN_NAME_Y && mY < SCN_NAME_Y + CHAR_HEIGHT)
		{
			// The Y-range overlaps the scenery name display.
			// A click may have been over the arrow keys to change scenery.
			if (CheckSCNchange(mX)) return true;
		}
		if (mY >= DEPTH_COMBO_Y - (ARROW_SIZE + SYM_SPACING) && mY < DEPTH_COMBO_Y - SYM_SPACING)
		{
			// The Y-range satisfied overlaps the up-arrow buttons.
			// We check to see if any of those buttons were pressed.
			if (CheckZup(mX)) return true;
		}
		if (mY >= DEPTH_COMBO_Y + CHAR_HEIGHT + SYM_SPACING && mY < DEPTH_COMBO_Y + CHAR_HEIGHT + SYM_SPACING + ARROW_SIZE)
		{
			// The Y-range satisfied overlaps the down-arrow buttons.
			// We check to see if any of those buttons were pressed.
			if (CheckZdown(mX)) return true;
		}
		if (mX >= SWITCHLIST_X && mX < SWITCHLIST_X + SWITCH_SIZE)
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
	if (mX >= DEPTH_COMBO_X && mX < DEPTH_COMBO_X + (Z_PRECISION * CHAR_WIDTH))
	{
		// ... middle up arrows pressed
		float Z_inc = GetZincrement(mX, DEPTH_COMBO_X);
		CSceneryEdit::ScnControl.Z += Z_inc;
		return true;
	}
	if (Active_Mod == REMOVE_SCENE)
	{
		if (mX >= DEPTH_LOWER_X && mX < DEPTH_LOWER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... left up arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_LOWER_X);
			if (CSceneryEdit::ScnControl.Zl + Z_inc < CSceneryEdit::ScnControl.Zu)
				CSceneryEdit::ScnControl.Zl += Z_inc;
			return true;
		}
		if (mX >= DEPTH_UPPER_X && mX < DEPTH_UPPER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... right up arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_UPPER_X);
			CSceneryEdit::ScnControl.Zu += Z_inc;
			return true;
		}
	}
	return false;
}

bool CApp::CheckZdown(const int& mX)
{
	if (mX >= DEPTH_COMBO_X && mX < DEPTH_COMBO_X + (Z_PRECISION * CHAR_WIDTH))
	{
		// ... middle dw arrows pressed
		float Z_inc = GetZincrement(mX, DEPTH_COMBO_X);
		if (CSceneryEdit::ScnControl.Z > Z_inc) CSceneryEdit::ScnControl.Z -= Z_inc;
		return true;
	}
	if (Active_Mod == REMOVE_SCENE)
	{
		if (mX >= DEPTH_LOWER_X && mX < DEPTH_LOWER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... left dw arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_LOWER_X);
			if (CSceneryEdit::ScnControl.Zl > Z_inc) CSceneryEdit::ScnControl.Zl -= Z_inc;
			return true;
		}
		if (mX >= DEPTH_UPPER_X && mX < DEPTH_UPPER_X + (Z_PRECISION * CHAR_WIDTH))
		{
			// ... right dw arrows pressed
			float Z_inc = GetZincrement(mX, DEPTH_UPPER_X);
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
	int Yi = SWITCHLIST_Y;
	int Yf = SWITCHLIST_Y + SWITCH_SIZE;
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
	if (mX >= SCN_NAME_X - ARROW_SIZE - SYM_SPACING && mX < SCN_NAME_X - SYM_SPACING)
	{
		// left arrow clicked...
		CSceneryEdit::ScnControl.SwitchObj(CSceneryEdit::ScnControl.scn_ID - 1);
		return true;
	}
	if (mX >= SCN_NAME_X + SCN_NAME_W + SYM_SPACING && mX < SCN_NAME_X + SCN_NAME_W + SYM_SPACING + ARROW_SIZE)
	{
		// right arrow clicked...
		CSceneryEdit::ScnControl.SwitchObj(CSceneryEdit::ScnControl.scn_ID + 1);
		return true;
	}
	return false;
}
