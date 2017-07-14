#ifndef _C_ENTITYEDITOR_H_
#define _C_ENTITYEDITOR_H_

#include <vector>

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
    extern const short sz;
    extern const short lab_y_offset;
    extern const short lab_x_offset;
    namespace view {
      extern const SDL_Point* offCol;
      extern const SDL_Point* onCol;
      extern const short x;
      extern const char* const labels[];
      extern CButton buttons[];
    }
  }
  namespace meters {
    namespace opacEntity
    {
      extern const char* const label;
      extern CMeter meter;
    }
    namespace opacHitbox
    {
      extern const char* const label;
      extern CMeter meter;
    }
  }
  namespace misc {
    namespace entityButtons {
      extern const SDL_Point* offCol;
      extern const SDL_Point* onCol;
      extern const SDL_Point* hovCol;
      extern const short list_x;
      extern const short list_y;
      extern const short button_w;
      extern const short button_h;
      extern const short max_buttons;
    }
  }
} // Entity engine namespaces //

class CEntityEditor : public CEvent {
private:
  CEntityEditor();

  bool showEntity;
  bool showHitbox;
  bool showWorkEntity;
  bool showWorkHitbox;
  unsigned short entity_alpha;
  unsigned short hitbox_alpha;

  int group_ID;
  int entity_ID;

public:
  static CEntityEditor Control;

private:
  std::vector<CButton> entityButtons;

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
  bool handleEntityMeter(const SDL_Point* m);
  bool handleHitboxMeter(const SDL_Point* m);
  bool handleSwitchView(const SDL_Point* m);

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
  bool drawSwitchView();
};

#endif
