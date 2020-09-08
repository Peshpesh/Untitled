#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  workTile.ID = 0;
  visflag = pvm_visflags::MAP | pvm_visflags::FILL;
  placeflag = ENABLE_BG | ENABLE_TYPE | ENABLE_COLL;
  k = 0;
  sel_k = 0;
  sel_z = 0;
  active_opacity = MAX_RGBA;
  over_opacity = 120;
  under_opacity = 200;
  req_rm_side = NULL;
  pDomain_A = NULL; // point A of domain to fill with tiles/pattern of tiles
  pDomain_B = NULL; // point B of domain ...
  pattern_w = 0;
  pattern_h = 0;
}

bool CPlanEditor::OnInit() {
  return true;
}

void CPlanEditor::getK(int& k) {
  k = this->k;
}

void CPlanEditor::OnTerminate() {

}
