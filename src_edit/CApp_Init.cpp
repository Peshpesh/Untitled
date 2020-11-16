#include "CApp.h"

bool CApp::OnInit()
{
  CCamera::CameraControl.SetTarget(NULL, NULL);
  CCamera::CameraControl.TargetMode = TARGET_MODE_NORMAL;
  CCamera::CameraControl.SetPos(0, 0);

  if ((Map_Display = SDL_CreateWindow("Map Editor",
                                      SDL_WINDOWPOS_CENTERED,
                                      SDL_WINDOWPOS_CENTERED,
                                      EWIDTH,
                                      EHEIGHT,
                                      SDL_WINDOW_SHOWN)) == NULL)
  {
    CError::handler.ReportErr("FATAL => SDL_CreateWindow failed.");
    return false;
  }

  if (!CSurface::OnInit(Map_Display)) {
    CError::handler.ReportErr("FATAL => CSurface failed to initialize.");
    return false;
  }

  if (!CAsset::OnInit()) {
    CError::handler.ReportErr("FATAL => CAsset failed to initialize.");
    return false;
  }

  if (!Font::FontControl.OnInit()) {
    CError::handler.ReportErr("FATAL => CFont failed to initialize.");
    return false;
  }

  if (!CTileset::TSControl.OnInit()) {
    CError::handler.ReportErr("FATAL => CTileset failed to initialize.");
    return false;
  }

  CStage::control.OnInit();

  if (CEditMap::MapEditor.OnInit() == false) {
    CError::handler.ReportErr("FATAL => CEditMap failed to initialize.");
    return false;
  }

  CPlanArea::control.OnInit();

  if (CEntityEditor::Control.OnInit() == false) {
    CError::handler.ReportErr("FATAL => CEntityEditor failed to initialize.");
    return false;
  }

  if (CSceneryEditor::control.OnInit() == false) {
    CError::handler.ReportErr("FATAL => CSceneryEditor failed to initialize.");
    return false;
  }

  if (CPlanScnEdit::control.OnInit() == false) {
    CError::handler.ReportErr("FATAL => CPlanScnEdit failed to initialize.");
    return false;
  }



  COptions::control.OnInit();

  ///////////////////////
  // Debugging section //
  ///////////////////////

  return true;
}
