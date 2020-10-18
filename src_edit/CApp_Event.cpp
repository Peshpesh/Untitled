#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event) {
  if (CInterrupt::isNone()) {
    CEvent::OnEvent(Event);
  } else {
    if (handleInterr(Event)) return;
  }
  CStage::control.OnEvent(Event);
}

bool CApp::handleInterr(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_MAP_MODEL)) {
    CModel::Control.OnEvent(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE)) {
    CFileIO::IOhandle.OnEvent(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_EXIT)) {
    CTerminate::control.OnEvent(Event);
    if (CTerminate::control.willTerminate()) {
      OnExit();
    }
    return true;
  }
  return false;
}

// Handle key-press events
void CApp::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (!CInterrupt::isNone()) return;

  switch (sym) {
    case SDLK_LEFT:   {
      pan_l = true;
      CSimulate::control.moveLeft();
      break;
    }
    case SDLK_RIGHT:   {
      pan_r = true;
      CSimulate::control.moveRight();
      break;
    }
    case SDLK_UP:     pan_u = true; break;
    case SDLK_DOWN:   pan_d = true; break;
    case SDLK_SPACE:  {
      CSimulate::control.jump();
      break;
    }
    case SDLK_ESCAPE: CInterrupt::appendFlag(INTRPT_EXIT); break;
    default: break;
  }
}

void CApp::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    case SDLK_LEFT:   {
      pan_l = false;
      CSimulate::control.stopMoveLeft();
      break;
    }
    case SDLK_RIGHT:   {
      pan_r = false;
      CSimulate::control.stopMoveRight();
      break;
    }
    case SDLK_UP:     pan_u = false; break;
    case SDLK_DOWN:   pan_d = false; break;
    case SDLK_SPACE:  {
      CSimulate::control.jumpRelease();
      break;
    }
    default: break;
  }
}

// Handle left-click events
void CApp::OnLButtonDown(int mX, int mY) {
  if (mX < 0 || mY < 0 || mX >= EWIDTH || mY >= EHEIGHT) return;

  const SDL_Point m = {mX, mY};
  if (CModule::control.handleSwitch(m)) return;
  // if (handleEngSwitch(&m)) return;
  if (handleModelSwitch(&m)) return;
  if (handleIO(&m)) return;
}

void CApp::OnRButtonDown(int mX, int mY) {
  if (mX < 0 || mY < 0 || mX > EWIDTH || mY > EHEIGHT) return;
}

// bool CApp::handleEngSwitch(const SDL_Point* m) {
//   using namespace engineSwitch;
//
//   // Clicks on a modify option button. Changes the MODIFY "flag" accordingly.
//   for (int i = MODIFY_MAP; i <= MODIFY_OPTIONS; i++) {
//     if (SDL_PointInRect(m, &engineButton[i])) {
//       active_mod = i;
//       if (active_mod != MODIFY_SIM) {
//         CSimulate::control.resetxywh();
//         if (CSimulate::control.getStatus() == PLACE) {
//           CSimulate::control.stopSim();
//         }
//       }
//       return true;
//     }
//   }
//   return false;
// }

bool CApp::handleModelSwitch(const SDL_Point* m) {
  using namespace modelSwitch;

  if (SDL_PointInRect(m, &button)) {
    CInterrupt::appendFlag(INTRPT_MAP_MODEL);
    CModel::Control.OnInit();
    return true;
  }
  return false;
}

bool CApp::handleIO(const SDL_Point* m) {
  using namespace io_ui;

  if (SDL_PointInRect(m, &newButton)) {
    CInterrupt::appendFlag(INTRPT_NEW);
    return true;
  }
  if (SDL_PointInRect(m, &loadButton)) {
    CInterrupt::appendFlag(INTRPT_LOAD);
    return true;
  }
  if (SDL_PointInRect(m, &saveButton)) {
    CInterrupt::appendFlag(INTRPT_SAVE);
    return true;
  }

  return false;
}
