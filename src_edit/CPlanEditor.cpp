#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  //
}

bool CPlanEditor::OnInit() {
  return true;
}

void CPlanEditor::OnEvent(SDL_Event* Event) {

}

bool CPlanEditor::OnRender(const SDL_Point& m) {
  // if (!RenderWkspc(mouse)) return false;
  if (!CAsset::drawAppFrame()) return false;
  // if (!RenderSidebar(mouse)) return false;
  // if (!RenderBottom(mouse)) return false;
  return true;
}

void CPlanEditor::OnTerminate() {

}
