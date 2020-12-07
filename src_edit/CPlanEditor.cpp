#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  workTile.ID = 0;
  visflag     = pvm_visflags::MAP | pvm_visflags::FILL;
  placeflag   = ENABLE_BG | ENABLE_TYPE | ENABLE_COLL;
  k = 0;
  sel_k = 0;
  sel_z = 0;
  active_opacity = MAX_RGBA;
  over_opacity = 120;
  under_opacity = MAX_RGBA;
  prev_opacity = 155;
  req_rm_side = NULL;
  pDomain_A = NULL; // point A of domain to fill with tiles/pattern of tiles
  pDomain_B = NULL; // point B of domain ...
  pattern_w = 0;
  pattern_h = 0;
}

void CPlanEditor::OnInit() {

}

void CPlanEditor::setK(const int& k) {
  this->k = k;
}

void CPlanEditor::getK(int& k) {
  k = this->k;
}

int CPlanEditor::getDefaultOpacityAtZ(const int& z) {
  int opac = 0;
  if (z < 0) return opac;

  int current_z = CPlanArea::control.getZ(k);

  if (z == current_z)     opac = active_opacity;
  else if (z > current_z) opac = over_opacity;
  else                    opac = under_opacity;

  return opac;
}

void CPlanEditor::OnTerminate() {

}
