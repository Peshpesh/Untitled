#include "CEntityEditor.h"

CEntityEditor CEntityEditor::Control;

CEntityEditor::CEntityEditor()
{
  showEntity = true;
  showHitbox = true;

  entity_alpha = MAX_RGBA;
  hitbox_alpha = MAX_RGBA / 4;
}

bool CEntityEditor::OnInit() {
  return true;
}

void CEntityEditor::OnTerminate() {
  //
}
