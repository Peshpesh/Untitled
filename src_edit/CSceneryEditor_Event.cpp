#include "CSceneryEditor.h"

void CSceneryEditor::OnEvent(SDL_Event* Event) {
  CEvent::OnEvent(Event);
}

void CSceneryEditor::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  switch (sym) {
    default: break;
  }
}

void CSceneryEditor::OnLButtonDown(int mX, int mY) {
  const SDL_Point m = {mX, mY};

  if (handleChScenery(&m)) return;
  if (handleLayerMeter(&m)) return;
  if (handleOtherMeter(&m)) return;
  if (handleSwitchView(&m)) return;
  if (handleSwitchPlace(&m)) return;
  if (handleSceneryList(&m)) return;
  if (handlePlaceRelPos(&m)) return;
  if (handleAddScenery(&m)) return;
}

bool CSceneryEditor::handleAddScenery(const SDL_Point* m) {
  if (!CAsset::inWorkspace(m)) return false;
  // click in workspace attempts to add scenery data

  SDL_Rect srcR = CSceneryData::getDecorDims(group_ID, scene_ID);

  int X = m->x;
  int Y = m->y;

  getPosDisplace(X, Y, m, srcR);
  const SDL_Point dstP = {X, Y};
  CScenery newDecor(group_ID, scene_ID, &dstP, layer);
  CScenery::sceneryList.push_back(newDecor);

  return true;
}

bool CSceneryEditor::handleChScenery(const SDL_Point* m) {
  using namespace sceneryEngine::buttons::chScenery;

  if (SDL_PointInRect(m, &button.dstR)) {
    // CChangeScenery::Control.OnInit(group_ID, scene_ID);
    // CInterrupt::appendFlag(INTRPT_CHANGE_SC);
    return true;
  }
  return false;
}

bool CSceneryEditor::handleLayerMeter(const SDL_Point* m) {
  using namespace sceneryEngine::meters::opacLayer;

  if (SDL_PointInRect(m, &meter.dstR)) {
    double fract = 0.0;
    if (meter.clickPos(m, fract)) {
      layer_alpha = fract * MAX_RGBA;
      // for (int i = 0; i < CScenery::textureList.size(); i++) {
      //   SDL_SetTextureAlphaMod(CScenery::textureList[i].img, layer_alpha);
      // }
    }
    return true;
  }
  return false;
}

bool CSceneryEditor::handleOtherMeter(const SDL_Point* m) {
  using namespace sceneryEngine::meters::opacOther;

  if (SDL_PointInRect(m, &meter.dstR)) {
    double fract = 0.0;
    if (meter.clickPos(m, fract)) {
      other_alpha = fract * MAX_RGBA;
      // for (int i = 0; i < CScenery::textureList.size(); i++) {
      //   SDL_SetTextureAlphaMod(CScenery::textureList[i].img, layer_alpha);
      // }
    }
    return true;
  }
  return false;
}

bool CSceneryEditor::handleSwitchView(const SDL_Point* m) {
  using namespace sceneryEngine::switches::view;

  bool* flags[] = {
    &showScenery,
    &showWorkScenery
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handleSwitchPlace(const SDL_Point* m) {
  using namespace sceneryEngine::switches::place;

  bool* flags[] = {
    &snap_scenery
  };

  for (int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      *flags[i] = !(*flags[i]);
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handleSceneryList(const SDL_Point* m) {
  for (int i = 0; i < sceneryButtons.size(); i++) {
    if (SDL_PointInRect(m, &sceneryButtons[i].dstR)) {
      scene_ID = i;
      return true;
    }
  }
  return false;
}

bool CSceneryEditor::handlePlaceRelPos(const SDL_Point* m) {
  using namespace sceneryEngine::buttons::placeRelPos;
  using namespace sceneryEngine::misc::placeRelPos;

  for (int i = TOP_LEFT; i <= BOTTOM_RIGHT; i++) {
    if (SDL_PointInRect(m, &buttons[i].dstR)) {
      placePos = i;
      return true;
    }
  }
  return false;
}
