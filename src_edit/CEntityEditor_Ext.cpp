#include "CEntityEditor.h"

namespace entityEngine
{
  namespace buttons {
    namespace chGroup
    { // Change entity group button
      const char* const label = "Change Group";
      CButton button(325, 534, 100, 24);
    }
    namespace chEntity
    { // Change entity button
      const char* const label = "Change Entity";
      CButton button(325, 510, 100, 24);
    }
  }
  namespace switches {
    //
  }
  namespace meters {
    namespace opacEntity
    {
      CMeter meter(645, 390, 90, 4);
      const char* const label = "Entity Opacity";
    }
    namespace opacHitbox
    {
      CMeter meter(645, 460, 90, 4);
      const char* const label = "Hitbox Opacity";
    }
  }
  namespace misc {
    //
  }
} // Entity engine namespaces //
