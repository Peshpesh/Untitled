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
  const short opt_w = 200;
  const short opt_h = 30;
  const short dx = 5;       // horizontal offset for each menu option
  const short dy = 10;      // vertical offset for each menu option
  const short w = opt_w + (dx * (num_options - 1));                   // menu width
  const short h = (opt_h * num_options) + (dy * (num_options - 1));   // menu height
  const short x = WWIDTH - (w + dy + (dx * num_options));   // menu x position
  const short y = WHEIGHT - (h + dy + opt_h);   // menu y position
  const short stroke_w = 2;

  namespace pick_game {
    namespace slot {
      const short num = 3;
      const short w = 260;    // slot width
      const short h = 60;     // slot height
      const SDL_Point diff_pos = {w / 5, h / 3};
      const SDL_Point time_pos = {w / 5, 2 * h / 3};
    };
    const SDL_Color* f_def = &rgb::black;
    const SDL_Color* f_hov = &rgb::black;
    const SDL_Color* f_lock = &rgb::gray;
    const SDL_Point* o_def = &palette::white;
    const SDL_Point* o_hov = &palette::light_green;
    const SDL_Point* o_lock = &palette::light_gray;
    const short num_other = 1;
    const short num_options = slot::num + num_other;
    const char* const other_list[] = {
      "Back",
    };
    const short opt_w = slot::w / 2;
    const short opt_h = slot::h / 2;
    const short dx = 0;                 // horizontal offset for each menu option
    const short dy = slot::h + 10;       // vertical offset for each menu option
    const short w = slot::w;             // menu width
    const short h = (dy * slot::num) + opt_h;   // menu height
    const short x = (WWIDTH - w) / 2;   // menu x position
    const short y = (WHEIGHT - h) / 2;  // menu y position
    const short stroke_w = 2;
    const char* const empty_text = "$R$R No Data $L$L";
    namespace difficulty {
      const SDL_Color* f_def = &rgb::black;
      const SDL_Color* f_hov = &rgb::black;
      const short num = 4;
      const short opt_w = 130;
      const short opt_h = 60;
      const short info_w = 260;
      const short info_h = 60;
      const short dx = 0;                 // horizontal offset for each menu option
      const short dy = opt_h;             // vertical offset for each menu option
      const short w = opt_w + info_w;             // menu width
      const short h = opt_h * num;                // menu height
      const short x = (WWIDTH - w) / 2;           // menu x position
      const short y = ((2 * WHEIGHT / 3) - h) / 2;          // menu y position
      const char* const list[] = {
        "Easy",
        "Normal",
        "Hard",
        "Brutal",
      };
      const char* const info[] = {
        "An easy-going experience, ideal for less familiar players and gamers.",
        "A casual, balanced level of gameplay suitable for most players looking for a fair challenge.",
        "An unforgiving mode that demands persistence and determination.\nLittle will pass easily.",
        "You are not meant to succeed here."
      };
      const SDL_Point* o_diff[] = {
        &palette::dark_cyan,
        &palette::dark_yellow,
        &palette::dark_magenta,
        &palette::dark_violet,
      };
      const SDL_Point* h_diff[] = {
        &palette::light_cyan,
        &palette::light_yellow,
        &palette::light_magenta,
        &palette::light_violet,
      };
      const short stroke_w = 2;
    };
    namespace overwrite {
      const SDL_Color* f_col = &rgb::black;
      const SDL_Point* o_col = &palette::red;
      const short w = 260;
      const short h = 100;
      const short x = (WWIDTH - w) / 2;
      const short y = (2 * WHEIGHT / 3);
      const short stroke_w = 2;
      const char* const info = "\
        WARNING\n\
        --------------\n\n\
        The slot you have chosen\n\
        already has data saved to it.\n\n\
        That data will be OVERWRITTEN AND LOST\n\
        if you save your game at any point.";
    };
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
    const short y_control = (WHEIGHT - h) / 2;  // control menu y position
    const short y_config = y_control + (num_controls * dy);  // control menu y position
  };
};
