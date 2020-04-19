#include "CStage.h"

CStage CStage::control;

CStage::CStage() {
  planview = false;
}

void CStage::OnEvent(SDL_Event* Event) {
  switch (active_mod) {
    case MODIFY_MAP: CEditMap::MapEditor.OnEvent(Event); break;
    case MODIFY_NPC: CEntityEditor::Control.OnEvent(Event); break;
    case MODIFY_SCENE: CSceneryEditor::control.OnEvent(Event); break;
    case MODIFY_SIM: CSimulate::control.OnEvent(Event); break;
    case MODIFY_OPTIONS: COptions::control.OnEvent(Event); break;
    default: break;
  }
}

void CStage::OnRender(const SDL_Point& m) {
  if (!planview) {
    // Draw working background
    CArea::control.OnRenderFill(-CCamera::CameraControl.GetX(), -CCamera::CameraControl.GetY());

    int scn_N = CScenery::sceneryList.size();

    // Draw background scenery
    CSceneryEditor::control.drawBackground(scn_N);

    // Draw the working area
    CEditMap::MapEditor.RenderMap();

    // Draw the entities in the area
    CEntityEditor::Control.drawEntities();

    // Draw simulation Entity
    CSimulate::control.drawHero();

    // Draw foreground scenery
    CSceneryEditor::control.drawForeground(scn_N);

    // Draw camera limits
    COptions::control.drawCameraLims();

    switch (active_mod) {
      case MODIFY_MAP:			CEditMap::MapEditor.OnRender(m); 		break;
      case MODIFY_NPC:			CEntityEditor::Control.OnRender(m); 	break;
      case MODIFY_SCENE:		CSceneryEditor::control.OnRender(m); break;
      case MODIFY_SIM:			CSimulate::control.OnRender(m); 			break;
      case MODIFY_OPTIONS:	COptions::control.OnRender(m);				break;
      default:							break;
    }
  } else {

  }
}
