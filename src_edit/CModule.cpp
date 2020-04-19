#include "CModule.h"

CModule CModule::control;

namespace engineSwitch {
  const char* engineName[] = {
    "Map Editor",
    "Npc Editor",
    "Scn Editor",
    "Simulate",
    "Options"
  };
  const SDL_Rect engineButton[] = {
    {525, 490, 70, 16},
    {525, 506, 70, 16},
    {525, 522, 70, 16},
    {525, 538, 70, 16},
    {525, 554, 70, 16}
  };
  const SDL_Point* engineOnCol = &palette::cyan;
  const SDL_Point* engineOffCol = &palette::gray;
  const SDL_Point* engineHvCol = &palette::light_violet;
  const short bsiz = 2;
}

////////////////////////////////////////////////////////////////////////////////

CModule::CModule() {
  active_mod = MODIFY_MAP;
}

void CModule::renderSwitch(const SDL_Point& m) {
  using namespace engineSwitch;

	bool canHilight = CInterrupt::isNone();
	bool noHov;

	const SDL_Point* color = NULL;
	for (int i = MODIFY_MAP; i <= MODIFY_OPTIONS; i++) {
		noHov = (!canHilight || !SDL_PointInRect(&m, &engineButton[i]));
		color = (active_mod == i) ? engineOnCol : (noHov ? engineOffCol : engineHvCol);
		CAsset::drawStrBox(&engineButton[i], bsiz, color);
		Font::NewCenterWrite(FONT_MINI, engineName[i], &engineButton[i]);
	}
}

bool CModule::handleSwitch(const SDL_Point& m) {
  using namespace engineSwitch;

  // Clicks on a module button. Changes the active_mod "flag".
  for (int i = MODIFY_MAP; i <= MODIFY_OPTIONS; i++) {
    if (SDL_PointInRect(m, &engineButton[i])) {
      active_mod = i;
      if (active_mod != MODIFY_SIM) {
        CSimulate::control.resetxywh();
        if (CSimulate::control.getStatus() == PLACE) {
          CSimulate::control.stopSim();
        }
      }
      return true;
    }
  }
  return false;
}
