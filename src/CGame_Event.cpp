#include "CGame.h"

void CGame::OnEvent(SDL_Event* Event) {
  /* Events in gameplay can be directed in multiple ways:
  * - Normal gameplay
  * - Pause menu
  * - Inventory
  * - Map
  * - Cinematic interruptions
  * - Dialogue
  * - In-game menus (shops, save points, etc.)
  * - Minigames
  * - Surely, there could be more...
  * In the circumstance where inputs should be processed for "normal gameplay,"
  * the OnEvent() function should be executed.
  */
  if (handleInterrupts(Event)) return;

	CEvent::OnEvent(Event);
}

bool CGame::handleInterrupts(SDL_Event* Event) {
  if (CInterrupt::isFlagOn(INTRPT_PAUSE)) {
    // CAnchorScenery::Control.OnEvent(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_VIEW_MAP)) {
    // CAnchorScenery::Control.OnEvent(Event);
    return true;
  }
  if (CInterrupt::isFlagOn(INTRPT_INVENTORY)) {
    // CAnchorScenery::Control.OnEvent(Event);
    return true;
  }
  return false;
}


void CGame::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  // switch (CControls::handler.getAction(sym, mod)) {
  //   case CON_ATTACK:  {
  //     Hero.Attack();
  //     break;
  //   }
  //   case CON_JUMP:    {
  //     Hero.Jump();
  //     break;
  //   }
  //   case CON_LEFT:    {
  //     Hero.move_left = true;
  //     break;
  //   }
  //   case CON_RIGHT:   {
  //     Hero.move_right = true;
  //     break;
  //   }
  //   case CON_DOWN:    {
  //     break;
  //   }
  //   case CON_UP:      {
  //     Hero.look_up = true;
  //     break;
  //   }
  //   case CON_PAUSE:   {
  //     CInterrupt::appendFlag(INTRPT_PAUSE);
  //     break;
  //   }
  //   default: break;
  // }
}

void CGame::OnKeyUp(SDL_Keycode sym, Uint16 mod) {
  // switch (CControls::handler.getAction(sym, mod)) {
  //   case CON_ATTACK:  {
  //     Hero.Release();
  //     break;
  //   }
  //   case CON_JUMP:    {
  //     Hero.JumpRelease();
  //     break;
  //   }
  //   case CON_LEFT:    {
  //     Hero.move_left = false;
  //     break;
  //   }
  //   case CON_RIGHT:   {
  //     Hero.move_right = false;
  //     break;
  //   }
  //   case CON_DOWN:    {
  //     break;
  //   }
  //   case CON_UP:      {
  //     Hero.look_up = false;
  //     break;
  //   }
  //   case CON_PAUSE:   {
  //     break;
  //   }
  //   default: break;
  // }
}
