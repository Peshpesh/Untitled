#include "CApp.h"

void CApp::OnExit()
{
  Running = false;
}

void CApp::OnTerminate()
{
  SDL_DestroyWindow(Map_Display);
  CSurface::OnCleanup();
  CAsset::OnCleanup();
  CEditMap::MapEditor.OnTerminate();
  CEntityEditor::Control.OnTerminate();
  CSceneryEditor::control.OnTerminate();
}
