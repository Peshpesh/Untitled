#include "CHUD.h"

CHUD CHUD::HUDControl;

CHUD::CHUD()
{
	Tex_HUD = NULL;
}

bool CHUD::OnInit(SDL_Renderer* renderer)
{
	if ((Tex_HUD = CSurface::OnLoad("../res/HUD.png", renderer)) == NULL) return false;
	return true;
}

void CHUD::OnLoop(int HP, int MaxHP, int Purse)
{

}

void CHUD::OnRender(SDL_Renderer* renderer, const int &HP, const int &Max_HP, const int &Purse, const int &Weapon, const int &Arsenal)
{
	// Error check
	if (Tex_HUD == NULL || renderer == NULL) return;

	// Draw health bar
	CSurface::OnDraw(renderer, Tex_HUD, 25, 50, 0, 0, 100, 10);
	for (int i = 0; i < HealthBar(HP, Max_HP); i++)
	{
		CSurface::OnDraw(renderer, Tex_HUD, 25 + i, 50, 100, 0, 1, 10);
	}

	// Write how much is in purse
	Font::Write(renderer, Font::FontControl.Tex_Font, Purse, WWIDTH-25, WHEIGHT-25);

	// Write how much HP
	// Font::Write(renderer, Font::FontControl.Tex_Font, HP, 260, 25);
	// Font::Write(renderer, Font::FontControl.Tex_Font, Arsenal, 260, 25);

	// Draw weapon selector
	if (Weapon != UNARMED)
	{
		// This draws the SELECTED weapon.
		CSurface::OnDraw(renderer, Tex_HUD, 45, 25, (CPlayer::ConvertBinary(Weapon) - 1) * 18, 10, 18, 18);
		if (Arsenal != Weapon) // Do we have any other weapons?
		{
			// This draws the NEXT weapon.
			int i = Weapon * 2;
			bool found = false;
			while (!found)
			{
				if (Arsenal & i)
				{
					found = true;
					CSurface::OnDraw(renderer, Tex_HUD, 65, 25, (CPlayer::ConvertBinary(i) - 1) * 18, 10, 18, 18);
				}
				else if (i >= ARM_TEST_E)
				{
					i = 1;
				}
				else i *= 2;
			}
			// This draws the PREVIOUS weapon.
			i = Weapon / 2;
			found = false;
			while (!found)
			{
				if (Arsenal & i)
				{
					found = true;
					CSurface::OnDraw(renderer, Tex_HUD, 25, 25, (CPlayer::ConvertBinary(i) - 1) * 18, 10, 18, 18);
				}
				else if (i == 0)
				{
					i = ARM_TEST_E;
				}
				else i /= 2;
			}
		}
	}
}

Uint8 CHUD::HealthBar(const int &HP, const int &MaxHP)
{
	Uint8 Health_W = (100 * HP) / MaxHP;
	return Health_W;
}
