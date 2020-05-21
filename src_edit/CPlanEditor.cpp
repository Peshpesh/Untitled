#include "CPlanEditor.h"

CPlanEditor CPlanEditor::control;

CPlanEditor::CPlanEditor() {
  workTile.ID = 1;
  onTiles = ENABLE_BG | ENABLE_TYPE | ENABLE_COLL;
  Z = 0;
}

bool CPlanEditor::OnInit() {
  return true;
}

void CPlanEditor::OnTerminate() {

}
