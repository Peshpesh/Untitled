#include "CTitle.h"

namespace Title {
  const SDL_Color* f_def = &rgb::black;
  const SDL_Color* f_hov = &rgb::black;
  const SDL_Color* f_lock = &rgb::gray;
  const SDL_Point* o_def = &palette::white;
  const SDL_Point* o_hov = &palette::light_green;
  const SDL_Point* o_lock = &palette::light_gray;
  const short num_options = 4;
  const char* const opt_list[] = {
    "New",
    "Load",
    "Options",
    "Quit",
  };
  const short dx = 5;       // horizontal offset for each menu option
  const short dy = 30;      // vertical offset for each menu option
  const short w = 200;                // menu width
  const short h = dy * num_options;   // menu height
  const short x = WWIDTH - (w + dy + (dx * num_options));   // menu x position
  const short y = WHEIGHT - (h + dy); // menu y position
  const short stroke_w = 2;

  namespace new_game {
    //
  };
  namespace load_game {
    //
  };
  namespace options {
    const SDL_Color* f_def = &rgb::black;
    const SDL_Color* f_hov = &rgb::black;
    const SDL_Color* f_act = &rgb::black;
    const SDL_Point* o_def = &palette::white;
    const SDL_Point* o_hov = &palette::light_green;
    const SDL_Point* o_act = &palette::light_red;
    const SDL_Point* fill_col = &palette::cyan;
    const short num_controls = 7;
    const short num_config = 5;
    const short num_options = num_controls + num_config;
    const char* const controls_text[] = {
      "Confirm - Attack",
      "Back - Jump",
      "Left",
      "Right",
      "Up",
      "Down - Examine",
      "Pause",
    };
    const Gamecon controls_list[] = {
      CON_ATTACK,
      CON_JUMP,
      CON_LEFT,
      CON_RIGHT,
      CON_UP,
      CON_DOWN,
      CON_PAUSE,
    };
    const char* const config_text[] = {
      "SFX Volume",
      "BGM Volume",
      "Type Volume",
      "Audio Output",
      "Video Display",
    };
    const Configflag config_list[] = {
      CONFIG_SFX,
      CONFIG_BGM,
      CONFIG_TEX,
      CONFIG_AUDIOOUT,
      CONFIG_DISPLAY,
    };
    const short dx = 0;       // horizontal offset for each menu option
    const short dy = 20;      // vertical offset for each menu option
    const short name_w = 150; // option name width
    const short stroke_w = 2;
    const short val_w = MAX_VOLUME + (stroke_w * 2);     // option value width
    const short w = name_w + val_w;     // menu width
    const short h = dy * num_options;   // menu height
    const short x = (WWIDTH - w) / 2;   // menu x position
    const short y = (WHEIGHT - h) / 2;  // menu y position
  };
};
