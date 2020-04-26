#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  visflag = pvm_visflags::MAP | pvm_visflags::FILL;
}

bool CPlanEditor::OnInit() {
  return true;
}

void CPlanEditor::OnEvent(SDL_Event* Event) {

}

bool CPlanEditor::OnRender(const SDL_Point& m) {
  return true;
}

void CPlanEditor::OnTerminate() {

}
