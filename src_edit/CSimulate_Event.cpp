#include "CSimulate.h"

void CSimulate::OnEvent(SDL_Event* Event) {
  if (handleInterr(Event)) return;

  CEvent::OnEvent(Event);
}

void CSimulate::moveLeft() {
  hero.move_left = true;
}

void CSimulate::moveRight() {
  hero.move_right = true;
}

void CSimulate::stopMoveLeft() {
  hero.move_left = false;
}

void CSimulate::stopMoveRight() {
  hero.move_right = false;
}

void CSimulate::jump() {
  hero.Jump();
}

void CSimulate::jumpRelease() {
  hero.JumpRelease();
}

bool CSimulate::handleInterr(SDL_Event* Event) {
  return false;
}

void CSimulate::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleStartSim(&m))   return;
  if (handleSuspendSim(&m)) return;
  if (handleStopSim(&m))    return;
  if (status == ACTIVE || status == SUSPENDED) {
    if (edit_xywh) clearxywh();
    if (handleCameraOption(&m)) return;
    if (handleManualCam(&m))    return;
    if (handleFollowCam(&m))    return;
    if (handleApplyCam(&m))     return;
  }
}

bool CSimulate::handleStartSim(const SDL_Point* m) {
  if (status != PLACE) {
    if (SDL_PointInRect(m, &simulator::r_start)) {
      if (status == ACTIVE || status == SUSPENDED) stopSim();
      hero.OnLoad();
      status = PLACE;
      return true;
    }
  } else if (CAsset::inWorkspace(m)) {
    updateCamera();
    status = ACTIVE;
    return true;
  }
  return false;
}

bool CSimulate::handleSuspendSim(const SDL_Point* m) {
  if (SDL_PointInRect(m, &simulator::r_suspend)) {
    if      (status == ACTIVE)    status = SUSPENDED;
    else if (status == SUSPENDED) status = ACTIVE;
    return true;
  }
  return false;
}

bool CSimulate::handleStopSim(const SDL_Point* m) {
  if (status != INACTIVE && SDL_PointInRect(m, &simulator::r_stop)) {
    stopSim();
    return true;
  }
  return false;
}

bool CSimulate::handleCameraOption(const SDL_Point* m) {
  using namespace simulator::camera;
  for (int i = 0; i <= TARGET_MODE_FOLLOW; i++) {
    if (i != cam_option && SDL_PointInRect(m, &r_modes[i])) {
      cam_option = i;
      updateCamera();
      return true;
    }
  }
  return false;
}

bool CSimulate::handleManualCam(const SDL_Point* m) {
  using namespace simulator::camera;
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

bool CSimulate::handleFollowCam(const SDL_Point* m) {
  using namespace simulator::camera;
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

bool CSimulate::handleApplyCam(const SDL_Point* m) {
  using namespace simulator::camera;
  if (did_edit_xywh && SDL_PointInRect(m, &r_app_mf)) {
    updateCamera();
    did_edit_xywh = false;
    return true;
  } return false;
}

void CSimulate::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (edit_xywh) {
    switch (sym) {
      case SDLK_0:	        addToEdit('0');	      break;
      case SDLK_1:	        addToEdit('1');	      break;
      case SDLK_2:	        addToEdit('2');	      break;
      case SDLK_3:	        addToEdit('3');	      break;
      case SDLK_4:	        addToEdit('4');	      break;
      case SDLK_5:	        addToEdit('5');	      break;
      case SDLK_6:	        addToEdit('6');	      break;
      case SDLK_7:	        addToEdit('7');	      break;
      case SDLK_8:	        addToEdit('8');	      break;
      case SDLK_9:	        addToEdit('9');	      break;
      case SDLK_BACKSPACE:  delFromEdit();        break;
      case SDLK_ESCAPE:     clearxywh();          break;
      case SDLK_RETURN:     applyEdit();          break;
      default:              break;
    }
  } else if (sym == SDLK_p) {
    if (status == ACTIVE)         status = SUSPENDED;
    else if (status == SUSPENDED) status = ACTIVE;
  }
}

void CSimulate::addToEdit(const char& c) {
  if (edit_sval.size() >= simulator::camera::max_edit_dig) return;
  if (edit_sval == "0") {
    if (c != '0') edit_sval[0] = c;
  } else {
    edit_sval.push_back(c);
  }
}

void CSimulate::delFromEdit() {
  if (edit_sval.size() > 0) edit_sval.erase(edit_sval.end() - 1);
}

void CSimulate::applyEdit() {
  if (!edit_sval.empty()) {
    int appl_val = CUtil::strToInt(edit_sval);
    switch (edit_xywh) {
      case simulator::camera::EDIT_CAM_X: {
        if (cam_x != appl_val) {
          cam_x = appl_val;
          did_edit_xywh = true;
        } break;
      }
      case simulator::camera::EDIT_CAM_Y: {
        if (cam_y != appl_val) {
          cam_y = appl_val;
          did_edit_xywh = true;
        } break;
      }
      case simulator::camera::EDIT_FOLLOW_W: {
        if (follow_w != appl_val) {
          follow_w = appl_val;
          did_edit_xywh = true;
        } break;
      }
      case simulator::camera::EDIT_FOLLOW_H: {
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
