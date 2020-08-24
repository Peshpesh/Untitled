#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  workTile.ID = 1;
  visflag = pvm_visflags::MAP | pvm_visflags::FILL;
  placeflag = ENABLE_BG | ENABLE_TYPE | ENABLE_COLL;
  k = 0;
  sel_k = 0;
  sel_z = 0;
  active_opacity = MAX_RGBA;
  over_opacity = 80;
  under_opacity = 160;
}

bool CPlanEditor::OnInit() {
  return true;
}

void CPlanEditor::getK(int& k) {
  k = this->k;
}

void CPlanEditor::OnTerminate() {

}
