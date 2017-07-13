#ifndef _C_ENTITYEDITOR_H_
#define _C_ENTITYEDITOR_H_

#include "CEvent.h"
#include "CButton.h"
#include "CMeter.h"
#include "CAsset.h"
#include "CFont.h"
#include "CEntity.h"
#include "CInterrupt.h"
#include "CInform.h"
#include "CCamera.h"
#include "Define.h"

namespace entityEngine
{
  namespace buttons {
    namespace chGroup
    { // Change entity group button
      extern const char* const label;
      extern CButton button;
    }
    namespace chEntity
    { // Change entity button
      extern const char* const label;
      extern CButton button;
    }
  }
  namespace switches {
    //
  }
  namespace meters {
    namespace opacEntity
    {
      extern CMeter meter;
      extern const char* const label;
    }
    namespace opacHitbox
    {
      extern CMeter meter;
      extern const char* const label;
    }
  }
  namespace misc {
    //
  }
} // Entity engine namespaces //

class CEntityEditor : public CEvent {
private:
  CEntityEditor();

  bool showEntity;
  bool showHitbox;
  unsigned short entity_alpha;
  unsigned short hitbox_alpha;

  int group_ID;
  int entity_ID;

public:
  static CEntityEditor Control;

public:
  bool OnInit();
  void OnTerminate();

public:
  void OnEvent(SDL_Event* Event);
private:
  bool handleInterr(SDL_Event* Event);
  void OnKeyDown(SDL_Keycode sym, Uint16 mod);
  void OnLButtonDown(int mX, int mY);
  bool handleAddEntity(const SDL_Point* m);
  bool handleChEntity(const SDL_Point* m);
  bool handleChGroup(const SDL_Point* m);

  void OnRButtonDown(int mX, int mY);

public:
  bool OnRender(const SDL_Point* m);
  bool drawEntities();
  bool drawWorkingEntity(const SDL_Point* m);
  bool drawHitboxes();

private:
  bool drawChGroup(const SDL_Point* m);
  bool drawChEntity(const SDL_Point* m);
  bool drawOpacEntity();
  bool drawOpacHitbox();
};

#endif
