#include "CStage.h"

CStage CStage::control;

CStage::CStage() {
  planview = false;
  name = "new";
  k = 0;
}

void CStage::OnInit() {
  CEntityEditor::Control.planview = &planview;
  CEntityEditor::Control.k = &k;
  CEntity::planview = &planview;
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
  switch (CModule::control.active_mod) {
    case MODIFY_MAP: CPlanEditor::control.OnEvent(Event); break;
    case MODIFY_NPC: CEntityEditor::Control.OnEvent(Event); break;
    case MODIFY_SCENE: CPlanScnEdit::control.OnEvent(Event); break;
    // case MODIFY_SIM: CPlanSimulate::control.OnEvent(Event); break;
    // case MODIFY_OPTIONS: CPlanOptions::control.OnEvent(Event); break;
    default: break;
  }
}

void CStage::OnLoop() {
  if (planview) {
    switch (CModule::control.active_mod) {
      case MODIFY_MAP: {
        CPlanEditor::control.getK(k);
        break;
      }
      // case MODIFY_NPC: CPlanEntity::control.getK(k); break;
      case MODIFY_SCENE: CPlanScnEdit::control.getK(k); break;
      default: break;
    }
    if (CModule::control.active_mod != MODIFY_MAP) CPlanEditor::control.setK(k);
    // if (CModule::control.active_mod != MODIFY_NPC) CPlanEntity::control.setK(k);
    if (CModule::control.active_mod != MODIFY_SCENE) CPlanScnEdit::control.setK(k);
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
  // #1: Render each map layer, starting with the lowest k (z)
  //      and ending with the highest k (z).
  // #2: After a map layer is rendered, render all shadows cast
  //      by objects on the same z.
  // #3: After all shadows are rendered on some depth z,
  //      render all objects designated to render WITH the map.
  //      These objects should be rendered by Y, from lowest to highest.
  // #4: Once all map layers are rendered, including shadows and specified
  //      objects, render all remaining objects that are NOT rendered with
  //      the map. As in #3, these should be rendered by Y, from lowest to highest.

  int z = 0;
  int opac = 0;
  int scn_i = 0;
  int ent_i = 0;
  int max_z = CPlanArea::control.getMaxZ();
  int max_scn = CPlanScnEdit::scnList_back.size();
  int max_ent = CEntity::entList_back.size();
  bool drawScn = CPlanScnEdit::control.showScenery * (bool)(max_scn);
  bool drawEnt = CEntityEditor::Control.showEntity * (bool)(max_ent);

  while (z <= max_z) {
    opac = CPlanEditor::control.getDefaultOpacityAtZ(z);
    CPlanScnEdit::control.setOpacity(opac);

    // Handle step #1.
    int next_z = CPlanEditor::control.RenderLayerZ(z);

    // Handle step #2.
    // Note: this could probably be made more efficient...
    //       but it's probably not an issue and shouldn't be one for gameplay
    if (drawScn) {
      for (int i = 0; i < CPlanScnEdit::scnList_back.size(); i++) {
        if (CPlanScnEdit::scnList_back[i].Z == z) {
          CPlanScnEdit::scnList_back[i].OnRenderShadow();
        } else if (CPlanScnEdit::scnList_back[i].Z > z) break;
        // the above break is only possible with scenery rendered with the map layer
        // due to the way these scenery are ordered (differs from scnList_front)
      }
      for (int i = 0; i < CPlanScnEdit::scnList_front.size(); i++) {
        if (CPlanScnEdit::scnList_front[i].Z == z) {
          CPlanScnEdit::scnList_front[i].OnRenderShadow();
        }
      }
    }

    // Handle step #3.
    bool scn_valid = drawScn && (scn_i < max_scn) && (CPlanScnEdit::scnList_back[scn_i].Z == z);
    bool ent_valid = drawEnt && (ent_i < max_ent) && (CEntity::entList_back[ent_i].Z == z);
    while (scn_valid || ent_valid) {
      if (scn_valid && ent_valid) {
        // compare the Y of the current scn and ent objects.
        // render the object with the lowest Y.
        // increment-up the index of the object type (scn or ent) rendered.
        int scn_Y = CPlanScnEdit::scnList_back[scn_i].Y_base;
        int ent_Y = CEntity::entList_back[ent_i].Y_base;
        if (scn_Y < ent_Y) {
          CPlanScnEdit::scnList_back[scn_i++].OnRender();
        } else {
          CEntity::entList_back[ent_i++].OnRender();
        }
      } else if (scn_valid) {
        CPlanScnEdit::scnList_back[scn_i++].OnRender();
      } else {
        // render/increment index for entity vector
        CEntity::entList_back[ent_i++].OnRender();
      }

      if (scn_valid) {
        if (scn_i >= max_scn || CPlanScnEdit::scnList_back[scn_i].Z >= next_z) scn_valid = false;
      }
      if (ent_valid) {
        if (ent_i >= max_ent || CEntity::entList_back[ent_i].Z >= next_z) ent_valid = false;
      }
    }
    z = next_z;
  }

  // Handle step #4.
  scn_i = 0;
  ent_i = 0;
  max_scn = CPlanScnEdit::scnList_front.size();
  max_ent = CEntity::entList_front.size();
  drawScn = CPlanScnEdit::control.showScenery * (bool)(max_scn);
  drawEnt = CEntityEditor::Control.showEntity * (bool)(max_ent);

  int total_obj = (drawScn * max_scn) + (drawEnt * max_ent);
  while (scn_i + ent_i < total_obj) {
    if (!drawEnt) { // only draw scenery
      z = CPlanScnEdit::scnList_front[scn_i].Z;
      opac = CPlanEditor::control.getDefaultOpacityAtZ(z);
      CPlanScnEdit::control.setOpacity(opac);
      CPlanScnEdit::scnList_front[scn_i++].OnRender();
    } else if (!drawScn) { // only draw entities
      CEntity::entList_front[ent_i++].OnRender();
    } else {
      if (scn_i >= max_scn) {
        CEntity::entList_front[ent_i++].OnRender();
      } else if (ent_i >= max_ent) {
        z = CPlanScnEdit::scnList_front[scn_i].Z;
        opac = CPlanEditor::control.getDefaultOpacityAtZ(z);
        CPlanScnEdit::control.setOpacity(opac);
        CPlanScnEdit::scnList_front[scn_i++].OnRender();
      } else {
        int scn_Y = CPlanScnEdit::scnList_front[scn_i].Y_base;
        int ent_Y = CEntity::entList_front[ent_i].Y_base;
        if (scn_Y < ent_Y) {
          CPlanScnEdit::scnList_front[scn_i++].OnRender();
        } else {
          CEntity::entList_front[ent_i++].OnRender();
        }
      }
    }
  }

  CPlanScnEdit::control.resetOpacity();

  switch (CModule::control.active_mod) {
    case MODIFY_MAP:      CPlanEditor::control.OnRender(m);    break;
    case MODIFY_NPC:      {
      CEntityEditor::Control.OnRender(&m);
      CAsset::drawAppFrame();
      CEntityEditor::Control.OnRenderSettings(&m);
      break;
    }
    case MODIFY_SCENE:    CPlanScnEdit::control.OnRender(m);   break;
    // case MODIFY_SIM: CPlanSimulate::control.OnRender(m); break;
    // case MODIFY_OPTIONS: CPlanOptions::control.OnRender(m); break;
    default:              break;
  }
}

void CStage::resetK() {
  k = 0;
  CPlanEditor::control.setK(k);
}
