#include "CPlanSimulate.h"

void CPlanSimulate::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

bool CPlanSimulate::handleInterr(SDL_Event* Event) {
  return false;
}

void CPlanSimulate::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleStartSim(&m))   return;
  if (handleSuspendSim(&m)) return;
  if (handleStopSim(&m))    return;
  if (handleDraftEntry(&m)) return;
  if (handleDraftOpts(&m))  return;
  if (status == pvmsimulator::ACTIVE || status == pvmsimulator::SUSPENDED) {
    if (edit_xywh) clearxywh();
    if (handleCameraOption(&m)) return;
    if (handleManualCam(&m))    return;
    if (handleFollowCam(&m))    return;
    if (handleApplyCam(&m))     return;
  }
}

void CPlanSimulate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (edit_xywh) {
    switch (sym) {
      case SDLK_0:          addToEdit('0');        break;
      case SDLK_1:          addToEdit('1');        break;
      case SDLK_2:          addToEdit('2');        break;
      case SDLK_3:          addToEdit('3');        break;
      case SDLK_4:          addToEdit('4');        break;
      case SDLK_5:          addToEdit('5');        break;
      case SDLK_6:          addToEdit('6');        break;
      case SDLK_7:          addToEdit('7');        break;
      case SDLK_8:          addToEdit('8');        break;
      case SDLK_9:          addToEdit('9');        break;
      case SDLK_BACKSPACE:  delFromEdit();        break;
      case SDLK_ESCAPE:     clearxywh();          break;
      case SDLK_RETURN:     applyEdit();          break;
      default:              break;
    }
  } else if (edit_draft) {
    switch (sym) {
      case SDLK_0:          addToDraft('0');   break;
      case SDLK_1:          addToDraft('1');   break;
      case SDLK_2:          addToDraft('2');   break;
      case SDLK_3:          addToDraft('3');   break;
      case SDLK_4:          addToDraft('4');   break;
      case SDLK_5:          addToDraft('5');   break;
      case SDLK_6:          addToDraft('6');   break;
      case SDLK_7:          addToDraft('7');   break;
      case SDLK_8:          addToDraft('8');   break;
      case SDLK_9:          addToDraft('9');   break;
      case SDLK_a:          addToDraft('a');   break;
      case SDLK_b:          addToDraft('b');   break;
      case SDLK_c:          addToDraft('c');   break;
      case SDLK_d:          addToDraft('d');   break;
      case SDLK_e:          addToDraft('e');   break;
      case SDLK_f:          addToDraft('f');   break;
      case SDLK_g:          addToDraft('g');   break;
      case SDLK_h:          addToDraft('h');   break;
      case SDLK_i:          addToDraft('i');   break;
      case SDLK_j:          addToDraft('j');   break;
      case SDLK_k:          addToDraft('k');   break;
      case SDLK_l:          addToDraft('l');   break;
      case SDLK_m:          addToDraft('m');   break;
      case SDLK_n:          addToDraft('n');   break;
      case SDLK_o:          addToDraft('o');   break;
      case SDLK_p:          addToDraft('p');   break;
      case SDLK_q:          addToDraft('q');   break;
      case SDLK_r:          addToDraft('r');   break;
      case SDLK_s:          addToDraft('s');   break;
      case SDLK_t:          addToDraft('t');   break;
      case SDLK_u:          addToDraft('u');   break;
      case SDLK_v:          addToDraft('v');   break;
      case SDLK_w:          addToDraft('w');   break;
      case SDLK_x:          addToDraft('x');   break;
      case SDLK_y:          addToDraft('y');   break;
      case SDLK_z:          addToDraft('z');   break;
      case SDLK_BACKSPACE:  delFromDraft();    break;
      case SDLK_ESCAPE:     clearDraftEntry(); break;
      case SDLK_RETURN:     loadDraft();       break;
      default:              break;
    }
  } else {
    switch (sym) {
      case SDLK_UP:    startMove('U'); break;
      case SDLK_DOWN:  startMove('D'); break;
      case SDLK_LEFT:  startMove('L'); break;
      case SDLK_RIGHT: startMove('R'); break;
      case SDLK_p:     {
        if (status == pvmsimulator::ACTIVE)         status = pvmsimulator::SUSPENDED;
        else if (status == pvmsimulator::SUSPENDED) status = pvmsimulator::ACTIVE;
        break;
      }
    }
  }
}

void CPlanSimulate::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

bool CPlanSimulate::handleStartSim(const SDL_Point* m) {
  if (status != pvmsimulator::PLACE) {
    if (SDL_PointInRect(m, &pvmsimulator::r_start)) {
      if (status == pvmsimulator::ACTIVE || status == pvmsimulator::SUSPENDED) stopSim();
      hero.OnLoad();
      status = pvmsimulator::PLACE;
      return true;
    }
  } else if (CAsset::inWorkspace(m)) {
    updateCamera();
    status = pvmsimulator::ACTIVE;
    return true;
  }
  return false;
}

bool CPlanSimulate::handleSuspendSim(const SDL_Point* m) {
  if (SDL_PointInRect(m, &pvmsimulator::r_suspend)) {
    if      (status == pvmsimulator::ACTIVE)    status = pvmsimulator::SUSPENDED;
    else if (status == pvmsimulator::SUSPENDED) status = pvmsimulator::ACTIVE;
    return true;
  }
  return false;
}

bool CPlanSimulate::handleStopSim(const SDL_Point* m) {
  if (status != pvmsimulator::INACTIVE && SDL_PointInRect(m, &pvmsimulator::r_stop)) {
    stopSim();
    return true;
  }
  return false;
}

bool CPlanSimulate::handleDraftEntry(const SDL_Point* m) {
  using namespace pvmsimulator::draft;

  if (SDL_PointInRect(m, &r_newdraft)) {
    if (!edit_draft) {
      edit_draft = true;
      if (edit_xywh) clearxywh(); // can't be using entry field for camera & draft name at same time
    }
    return true;
  } else if (edit_draft) clearDraftEntry();

  return false;
}

bool CPlanSimulate::handleDraftOpts(const SDL_Point* m) {
  using namespace pvmsimulator::draft;

  if (SDL_PointInRect(m, &r_clear)) {
    CDraft::control.OnCleanup();
    return true;
  }

  if (SDL_PointInRect(m, &r_show)) {
    CDraft::control.hidden = !(CDraft::control.hidden);
    return true;
  }

  if (SDL_PointInRect(m, &r_zpos)) {
    CDraft::control.draw_on_top = !(CDraft::control.draw_on_top);
    return true;
  }

  return false;
}

bool CPlanSimulate::handleCameraOption(const SDL_Point* m) {
  using namespace pvmsimulator::camera;
  for (int i = 0; i <= TARGET_MODE_FOLLOW; i++) {
    if (i != cam_option && SDL_PointInRect(m, &r_modes[i])) {
      cam_option = i;
      updateCamera();
      return true;
    }
  }
  return false;
}

bool CPlanSimulate::handleManualCam(const SDL_Point* m) {
  using namespace pvmsimulator::camera;
  bool retval = false;
  if (SDL_PointInRect(m, &r_cam_x)) {
    edit_xywh = EDIT_CAM_X;
    retval = true;
  } else if (SDL_PointInRect(m, &r_cam_y)) {
    edit_xywh = EDIT_CAM_Y;
    retval = true;
  }
  return retval;
}

bool CPlanSimulate::handleFollowCam(const SDL_Point* m) {
  using namespace pvmsimulator::camera;
  bool retval = false;
  if (SDL_PointInRect(m, &r_follow_w)) {
    edit_xywh = EDIT_FOLLOW_W;
    retval = true;
  } else if (SDL_PointInRect(m, &r_follow_h)) {
    edit_xywh = EDIT_FOLLOW_H;
    retval = true;
  }
  return retval;
}

bool CPlanSimulate::handleApplyCam(const SDL_Point* m) {
  using namespace pvmsimulator::camera;
  if (did_edit_xywh && SDL_PointInRect(m, &r_app_mf)) {
    updateCamera();
    did_edit_xywh = false;
    return true;
  } return false;
}

void CPlanSimulate::addToEdit(const char& c) {
  if (xywh_sval.size() >= pvmsimulator::camera::max_edit_dig) return;
  if (xywh_sval == "0") {
    if (c != '0') xywh_sval[0] = c;
  } else {
    xywh_sval.push_back(c);
  }
}

void CPlanSimulate::delFromEdit() {
  if (xywh_sval.size() > 0) xywh_sval.erase(xywh_sval.end() - 1);
}

void CPlanSimulate::applyEdit() {
  if (!xywh_sval.empty()) {
    int appl_val = CUtil::strToInt(xywh_sval);
    switch (edit_xywh) {
      case pvmsimulator::camera::EDIT_CAM_X: {
        if (cam_x != appl_val) {
          cam_x = appl_val;
          did_edit_xywh = true;
        } break;
      }
      case pvmsimulator::camera::EDIT_CAM_Y: {
        if (cam_y != appl_val) {
          cam_y = appl_val;
          did_edit_xywh = true;
        } break;
      }
      case pvmsimulator::camera::EDIT_FOLLOW_W: {
        if (follow_w != appl_val) {
          follow_w = appl_val;
          did_edit_xywh = true;
        } break;
      }
      case pvmsimulator::camera::EDIT_FOLLOW_H: {
        if (follow_h != appl_val) {
          follow_h = appl_val;
          did_edit_xywh = true;
        } break;
      }
      default: break;
    }
  }
  clearxywh();
}

void CPlanSimulate::addToDraft(const char& c) {
  static short draft_charmax = 16;
  if (draft_s.size() >= draft_charmax) return;
  draft_s.push_back(c);
}

void CPlanSimulate::delFromDraft() {
  if (draft_s.size() > 0) draft_s.erase(draft_s.end() - 1);
}

void CPlanSimulate::loadDraft() {
  CDraft::control.OnLoad(draft_s);
  clearDraftEntry();
}

void CPlanSimulate::startMove(const char& c) {
  hero.intentdir = c;
  hero.intentmove = true;
}
