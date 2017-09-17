#include "CSceneryEditor.h"

bool CSceneryEditor::OnRender(const SDL_Point* m) {
  bool no_intrpt = CInterrupt::isNone();

  if (no_intrpt) {
    //
  }
  if (!CAsset::drawAppFrame()) return false;

  if (!no_intrpt) {
    if (!drawIntrpt(m)) return false;
  }
  return true;
}

bool CSceneryEditor::drawBackground() {
  // Draw background scenery
	// int s_i = 0;
	// while (s_i < CSceneryEdit::SceneList.size())
	// {
	// 	float Z = CSceneryEdit::SceneList[s_i]->Z;
	// 	if (Z <= 1.0f) break;
	// 	if (active_mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
	// 	{
	// 		CSceneryEdit::SceneList[s_i]->OnRender();
	// 	}
	// 	s_i++;
	// }

  return true;
}

bool CSceneryEditor::drawForeground() {
  // Draw foreground scenery
	// while (s_i < CSceneryEdit::SceneList.size())
	// {
	// 	float Z = CSceneryEdit::SceneList[s_i]->Z;
	// 	if (active_mod != REMOVE_SCENE || ((Z >= CSceneryEdit::ScnControl.Zl) && (Z <= CSceneryEdit::ScnControl.Zu)))
	// 	{
	// 		CSceneryEdit::SceneList[s_i]->OnRender();
	// 	}
	// 	s_i++;
	// }

  return true;
}

///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

bool CSceneryEditor::drawIntrpt(const SDL_Point* m) {
  return true;
}
