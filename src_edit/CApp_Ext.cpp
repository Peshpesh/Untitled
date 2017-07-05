#include "CApp.h"

namespace io_ui
{
  // IO button info
  const char* const new_label = "NEW STAGE";
  const char* const load_label = "LOAD STAGE";
  const char* const save_label = "SAVE STAGE";
  const SDL_Rect newButton  = {WWIDTH + 5, WHEIGHT + 5, 90, 30};
  const SDL_Rect loadButton = {WWIDTH + 5, newButton.y + newButton.h, 90, 30};
  const SDL_Rect saveButton = {WWIDTH + 5, loadButton.y + loadButton.h, 90, 30};
  const SDL_Point* newButCol = &palette::green;
  const SDL_Point* loadButCol = &palette::cyan;
  const SDL_Point* saveButCol = &palette::yellow;
  const SDL_Point* newHovCol = &palette::light_green;
  const SDL_Point* loadHovCol = &palette::light_cyan;
  const SDL_Point* saveHovCol = &palette::light_yellow;
  const short bsiz = 2;
}

namespace engineSwitch
{
  const char* engineName[] = {
    "Map Editor",
    "Npc Placer",
    "Npc Culler",
    "Scn Placer",
    "Scn Culler"
  };
  const SDL_Rect engineButton[] = {
    {520, 490, 70, 16},
    {520, 506, 70, 16},
    {520, 522, 70, 16},
    {520, 538, 70, 16},
    {520, 554, 70, 16}
  };
  const SDL_Point* engineOnCol = &palette::cyan;
  const SDL_Point* engineOffCol = &palette::gray;
  const SDL_Point* engineHvCol = &palette::light_violet;
  const short bsiz = 2;
}
