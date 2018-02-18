#include "CControls.h"

CControls CControls::handler;

namespace {
  const char* const key_path = "../data/game/controls.key";
};

CControls::CControls() {
	con_change = CON_NONE;

  if (!OnInit()) {
    Reset();
    Save();
  }
}

bool CControls::OnInit() {
  // load control key file if it exists
  FILE* FileHandle = fopen(key_path, "rb");

  if (FileHandle == NULL)	{
    // CInform::InfoControl.pushInform("---CScenery.OnLoad---\nfailed to open file");
    return false;
  }

  fread(&key, sizeof(ControlKey), 1, FileHandle);
  fclose(FileHandle);
  return true;
}

void CControls::OnEvent(SDL_Event* Event) {
  // The event handler is for modifying controls.
  //
  // A separate function is used to convert an event to
  // a Gamecon flag defined on the control key.
  CEvent::OnEvent(Event);
}

void CControls::OnKeyDown(SDL_Keycode sym, Uint16 mod) {
  if (!ValidKey(sym, mod)) return;
  switch (con_change) {
    case CON_ATTACK:    key.c_attack = sym;   break;
    case CON_JUMP:      key.c_jump = sym;     break;
    case CON_LEFT:      key.c_left = sym;     break;
    case CON_RIGHT:     key.c_right = sym;    break;
    case CON_UP:        key.c_up = sym;       break;
    case CON_DOWN:      key.c_down = sym;     break;
    case CON_PAUSE:     key.c_pause = sym;    break;
    default:            break;
  }
  con_change = CON_NONE;
  Save();
}

bool CControls::ValidKey(SDL_Keycode sym, Uint16 mod) {
  // checks if the entered key is eligible for controls
  // For example, the ESC key cannot be a game control
  // because it's reserved for quitting the game, so
  // setting the ESC to "attack/confirm" should
  // not be allowed.
  if (sym == SDLK_ESCAPE) return false;
  if (getAction(sym, mod) != CON_NONE) return false;
  return true;
}

Gamecon CControls::getAction(SDL_Keycode sym, Uint16 mod) {
  // Convert an SDL_KEYUP/SDL_KEYDOWN Event into an action in the program
  // (e.g., convert Z-key to an "attack" or "confirm" action)
  if (sym == key.c_attack)  return CON_ATTACK;
  if (sym == key.c_jump)    return CON_JUMP;
  if (sym == key.c_left)    return CON_LEFT;
  if (sym == key.c_right)   return CON_RIGHT;
  if (sym == key.c_up)      return CON_UP;
  if (sym == key.c_down)    return CON_DOWN;
  if (sym == key.c_pause)   return CON_PAUSE;
  return CON_NONE;
}

SDL_Keycode CControls::getAssignKey(const Gamecon& action) {
  // return the SDL_Keycode associated with the passed (request)
  // game action.
  switch (action) {
    case CON_ATTACK:  return key.c_attack;  break;
    case CON_JUMP:    return key.c_jump;    break;
    case CON_LEFT:    return key.c_left;    break;
    case CON_RIGHT:   return key.c_right;   break;
    case CON_UP:      return key.c_up;      break;
    case CON_DOWN:    return key.c_down;    break;
    case CON_PAUSE:   return key.c_pause;   break;
  }
  return SDLK_ESCAPE;
}

void CControls::Reset() {
  // reset control key to default settings
  key.c_attack  = SDLK_z;
  key.c_jump    = SDLK_SPACE;
  key.c_left    = SDLK_LEFT;
  key.c_right   = SDLK_RIGHT;
  key.c_down    = SDLK_DOWN;
  key.c_up      = SDLK_UP;
  key.c_pause   = SDLK_p;
}

void CControls::Save() {
  // save control key file
  // const char* const key_path = "../data/game/controls.key";
  FILE* FileHandle = fopen(key_path, "wb");

  if (FileHandle == NULL) {
    // CInform::InfoControl.pushInform("---CSCENERY.OnSave---\nfailed to open new file");
    return;
  }

  fwrite(&key, sizeof(ControlKey), 1, FileHandle);
  fclose(FileHandle);
}
