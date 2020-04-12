#include "CTitle.h"

bool CTitle::OnRender() {
  bool retval = false;
  CType::control.SetFont(FONT_MINI);

  switch (menu_kind) {
    case Title::MAIN:       retval = drawMainMenu(); break;
    case Title::NEW_GAME:   retval = drawNewGame();  break;
    case Title::LOAD_GAME:  retval = drawLoadGame(); break;
    case Title::OPTIONS:    retval = drawOptions();  break;
    default: break;
  }

  return retval;
}

bool CTitle::drawMainMenu() {
  using namespace Title;

  SDL_Rect bar = {x, y, opt_w, opt_h};

  for (int i = 0; i < num_options; i++) {
    if (i == decision::DEC_LOAD && !CGameIO::control.getNumSavedGames()) {
      if (!CAsset::drawStrBox(bar, stroke_w, o_lock)) return false;
      CType::CenterWrite(opt_list[i], bar, f_lock);
    } else {
      if (!CAsset::drawStrBox(bar, stroke_w, (i != pos) ? o_def : o_hov)) return false;
      CType::CenterWrite(opt_list[i], bar, (i != pos) ? f_def : f_hov);
    }
    bar.x += dx;
    bar.y += dy + opt_h;
  }
  return true;
}

bool CTitle::drawNewGame() {
  if (!drawGameInfo()) return false;

  if (sel_difficulty && (!drawDifficulty() || !drawOverwriteWarn(pos))) {
    return false;
  }

  return true;
}

bool CTitle::drawLoadGame() {
  if (!drawGameInfo()) return false;

  return true;
}

bool CTitle::drawOptions() {
  if (!drawControls()) return false;
  if (!drawConfig()) return false;

  return true;
}

bool CTitle::drawGameSlot(const CGameinfo& info, const SDL_Rect& slot) {
  using namespace Title::pick_game::slot;
  std::string str;
  SDL_Point pos;
  if (info.diff == EASY || info.diff == NORMAL || info.diff == HARD || info.diff == BRUTAL) {
    str = Title::pick_game::difficulty::list[info.diff];
  }
  pos.x = slot.x + diff_pos.x; pos.y = slot.y + diff_pos.y;
  CType::CenterWrite(str.c_str(), pos);

  str = CUtil::msToHHMMSS(info.time);
  pos.x = slot.x + time_pos.x; pos.y = slot.y + time_pos.y;
  CType::CenterWrite(str.c_str(), pos);
  // CType::CenterWrite(str.c_str(), slot, (i != pos) ? f_def : f_hov);

  return true;
}

bool CTitle::drawGameInfo() {
  using namespace Title::pick_game;

  SDL_Rect slot = {x, y, slot::w, slot::h};
  for (int i = 0; i < slot::num; i++) {
    if (!CAsset::drawStrBox(slot, stroke_w, (i != pos) ? o_def : o_hov)) return false;
    if (CGameinfo::infolist[i]) {
      if (!drawGameSlot(*CGameinfo::infolist[i], slot)) return false;
    } else {
      CType::CenterWrite(empty_text, slot, (i != pos) ? f_def : f_hov);
    }
    slot.x += dx;
    slot.y += dy;
  }

  SDL_Rect bar = {x, slot.y, opt_w, opt_h};
  for (int i = 0; i < num_other; i++) {
    if (!CAsset::drawStrBox(bar, stroke_w, (i != pos - slot::num) ? o_def : o_hov)) return false;
    CType::CenterWrite(other_list[i], bar, (i != pos - slot::num) ? f_def : f_hov);
    bar.x += dx;
    bar.y += dy;
  }
  return true;
}

bool CTitle::drawDifficulty() {
  using namespace Title::pick_game::difficulty;

  SDL_Rect bar = {x, y, opt_w, opt_h};
  for (int i = 0; i < num; i++) {
    if (i != difficulty) {
      if (!CAsset::drawStrBox(bar, stroke_w, o_diff[i])) return false;
      CType::CenterWrite(list[i], bar, f_def);
    } else {
      SDL_Rect info_bar = {bar.x + opt_w, bar.y, info_w, info_h};
      if (!CAsset::drawStrBox(bar, stroke_w, h_diff[i])) return false;
      if (!CAsset::drawStrBox(info_bar, stroke_w, h_diff[i])) return false;
      CType::CenterWrite(list[i], bar, f_hov);
      CType::CenterWrite(info[i], info_bar, f_hov);
    }
    bar.x += dx;
    bar.y += dy;
  }
  return true;
}

bool CTitle::drawOverwriteWarn(const short& slot) {
  using namespace Title::pick_game::overwrite;

  if (CGameinfo::infolist[slot]) {
    SDL_Rect bar = {x, y, w, h};
    if (!CAsset::drawStrBox(bar, stroke_w, o_col)) return false;
    CType::CenterWrite(info, bar, f_col);
  }

  return true;
}

bool CTitle::drawControls() {
  using namespace Title::options;

  SDL_Rect l_bar = {x, y_control, name_w, dy};
  SDL_Rect r_bar = {x + name_w, y_control, val_w, dy};

  for (int i = 0; i < num_controls; i++) {
    bool modify = CControls::handler.con_change != CON_NONE;
    const SDL_Color* f_col = (i != pos) ? f_def : (modify ? f_act : f_hov);
    const SDL_Point* o_col = (i != pos) ? o_def : (modify ? o_act : o_hov);
    CAsset::drawStrBox(l_bar, stroke_w, o_col);
    CAsset::drawStrBox(r_bar, stroke_w, o_col);
    CType::CenterWrite(controls_text[i], l_bar, f_col);
    CType::CenterWrite(
      (char*)(SDL_GetKeyName(CControls::handler.getAssignKey(controls_list[i]))), r_bar, f_col);
    l_bar.x += dx; r_bar.x += dx;
    l_bar.y += dy; r_bar.y += dy;
  }
  return true;
}

bool CTitle::drawConfig() {
  using namespace Title::options;

  SDL_Rect l_bar = {x, y_config, name_w, dy};
  SDL_Rect r_bar = {x + name_w, y_config, val_w, dy};

  for (int i = 0; i < num_config; i++) {
    bool modify = CConfig::control.con_change != CONFIG_NONE;
    const SDL_Color* f_col = (i != pos - num_controls) ? f_def : (modify ? f_act : f_hov);
    const SDL_Point* o_col = (i != pos - num_controls) ? o_def : (modify ? o_act : o_hov);
    if (!CAsset::drawStrBox(l_bar, stroke_w, o_col)) return false;
    if (!CAsset::drawStrBox(r_bar, stroke_w, o_col)) return false;
    CType::CenterWrite(config_text[i], l_bar, f_col);

    std::string val;
    if (config_list[i] == CONFIG_SFX || config_list[i] == CONFIG_BGM || config_list[i] == CONFIG_TEX) {
      double fill_fract = CConfig::control.getVolume(config_list[i]) / (double)(MAX_VOLUME);
      SDL_Rect bar_fill = {r_bar.x + stroke_w, r_bar.y + stroke_w, fill_fract * (r_bar.w - (stroke_w * 2)), r_bar.h - (stroke_w * 2)};
      if (!CAsset::drawBoxFill(bar_fill, fill_col)) return false;
      val = CUtil::intToStr(CConfig::control.getVolume(config_list[i]));
    } else if (config_list[i] == CONFIG_AUDIOOUT) {
      if (CConfig::control.isStereo()) val = "Stereo";
      else val = "Mono";
    } else if (config_list[i] == CONFIG_DISPLAY) {
      if (CConfig::control.isFullscreen()) val = "Fullscreen";
      else val = "Windowed";
    } CType::CenterWrite(val.c_str(), r_bar, f_col);
    l_bar.x += dx; r_bar.x += dx;
    l_bar.y += dy; r_bar.y += dy;
  }
  return true;
}
