#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  workTile.ID = 1;
  visflag = pvm_visflags::MAP | pvm_visflags::FILL;
  placeflag = ENABLE_BG | ENABLE_TYPE | ENABLE_COLL;
  k = 0;
  new_k = 0;
  new_z = 0;
}

bool CPlanEditor::OnInit() {
  return true;
}

void CPlanEditor::OnTerminate() {

}
