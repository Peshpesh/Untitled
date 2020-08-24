#include "CStage.h"

CStage CStage::control;

CStage::CStage() {
  planview = false;
  name = "new";
  k = 0;
}

void CStage::OnEvent(SDL_Event* Event) {
  if (!planview) OnEventPlatform(Event);
  else OnEventPlanview(Event);
}

void CStage::OnEventPlatform(SDL_Event* Event) {
  switch (CModule::control.active_mod) {
    case MODIFY_MAP: CEditMap::MapEditor.OnEvent(Event); break;
    case MODIFY_NPC: CEntityEditor::Control.OnEvent(Event); break;
    case MODIFY_SCENE: CSceneryEditor::control.OnEvent(Event); break;
    case MODIFY_SIM: CSimulate::control.OnEvent(Event); break;
    case MODIFY_OPTIONS: COptions::control.OnEvent(Event); break;
    default: break;
  }
}

void CStage::OnEventPlanview(SDL_Event* Event) {
  CPlanEditor::control.OnEvent(Event);
}

void CStage::OnLoop() {
  if (planview) {
    switch (CModule::control.active_mod) {
      case MODIFY_MAP:			CPlanEditor::control.getK(k); break;
      default:							break;
    }
  }
}

void CStage::OnRender(const SDL_Point& m) {
  if (!planview) OnRenderPlatform(m);
  else OnRenderPlanview(m);
}

void CStage::OnRenderPlatform(const SDL_Point& m) {
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

  switch (CModule::control.active_mod) {
    case MODIFY_MAP: {
      CEditMap::MapEditor.OnRender(&m);
      CAsset::drawAppFrame();
      CEditMap::MapEditor.OnRenderSettings(&m);
      break;
    }
    case MODIFY_NPC: {
      CEntityEditor::Control.OnRender(&m);
      CAsset::drawAppFrame();
      CEntityEditor::Control.OnRenderSettings(&m);
      break;
    }
    case MODIFY_SCENE: {
      CSceneryEditor::control.OnRender(&m);
      CAsset::drawAppFrame();
      CSceneryEditor::control.OnRenderSettings(&m);
      break;
    }
    case MODIFY_SIM: {
      CAsset::drawAppFrame();
      CSimulate::control.OnRender(&m);
      break;
    }
    case MODIFY_OPTIONS: {
      CAsset::drawAppFrame();
      COptions::control.OnRender(&m);
      break;
    }
    default: break;
  }
}

void CStage::OnRenderPlanview(const SDL_Point& m) {
  CPlanEditor::control.RenderMap();

  switch (CModule::control.active_mod) {
    case MODIFY_MAP:			CPlanEditor::control.OnRender(m);    break;
    // case MODIFY_NPC:			CEntityEditor::Control.OnRender(&m); 	break;
    // case MODIFY_SCENE:		CSceneryEditor::control.OnRender(&m); break;
    // case MODIFY_SIM:			CSimulate::control.OnRender(&m); 			break;
    // case MODIFY_OPTIONS:	COptions::control.OnRender(&m);				break;
    default:							break;
  }
}
