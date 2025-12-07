#include "CApp.h"

void CApp::OnRender() {
  static const bool debug = true;

  CSurface::Clear();

  CStage::control.OnRender(mouse);

  CModule::control.renderSwitch(mouse);
  // renderEngSwitch();
  renderModelButton();
  renderIOButtons();

  CInform::InfoControl.OnRender();

  if (CInterrupt::isFlagOn(INTRPT_MAP_MODEL)) {
    CModel::Control.OnRender(&mouse);
  }

  if (CInterrupt::isFlagOn(INTRPT_NEW | INTRPT_LOAD | INTRPT_SAVE)) {
    CFileIO::IOhandle.OnRender(&mouse);
  }

  if (CInterrupt::isFlagOn(INTRPT_EXIT)) {
    CTerminate::control.OnRender(mouse);
  }

  //  DEBUGGING
  if (debug) {
    std::string fps_str = Font::intToStr(CFPS::FPSControl.GetFPS()) + " fps";
    Font::Write(FONT_MINI, fps_str.c_str(), WWIDTH + 5, 1);
  }
  CSurface::Present();
}

bool CApp::renderModelButton() {
  using namespace modelSwitch;

  bool active = CInterrupt::isFlagOn(INTRPT_MAP_MODEL);
  bool canHov = active ? false : CInterrupt::isNone();
  bool hov = (!canHov) ? false : SDL_PointInRect(&mouse, &button);

  CAsset::drawStrBox(&button, bsiz, active ? onCol : (hov ? hovCol : offCol));
  Font::NewCenterWrite(FONT_MINI, label, &button);

  return true;
}

bool CApp::renderIOButtons() {
  using namespace io_ui;

  bool hov = CInterrupt::isNone();

  CAsset::drawStrBox(&newButton, bsiz, (hov && SDL_PointInRect(&mouse, &newButton)) ? newHovCol : newButCol);
  CAsset::drawStrBox(&loadButton, bsiz, (hov && SDL_PointInRect(&mouse, &loadButton)) ? loadHovCol : loadButCol);
  CAsset::drawStrBox(&saveButton, bsiz, (hov && SDL_PointInRect(&mouse, &saveButton)) ? saveHovCol : saveButCol);

  Font::FontControl.SetFont(FONT_MINI);
  Font::NewCenterWrite(new_label, &newButton);
  Font::NewCenterWrite(load_label, &loadButton);
  Font::NewCenterWrite(save_label, &saveButton);

  return true;
}
