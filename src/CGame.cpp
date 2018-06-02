#include "CGame.h"

CGame CGame::control;

CGame::CGame() {
  //
}

// For terminating the application
void CGame::OnCleanup() {
  OnExit();
}

// For quitting the game
void CGame::OnExit() {
  // CArea::control.OnInit();
  CEntityIO::Cleanup();
  CSceneryIO::Cleanup();
}
